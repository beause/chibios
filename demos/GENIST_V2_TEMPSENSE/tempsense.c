#include <float.h>
#include "ch.h"
#include "hal.h"
#include "test.h"
#include "tempsense.h"

#define PT100_SDADC_VREF       SDADC_VREF_Ext /* External reference is selected */
#define PT100_SDADC_GAIN       SDADC_Gain_8   /* Internal gain 8 is seleted */
#define SDADC_GAIN             (int16_t)8    /* SDADC internal gain is set to 8: update this define
                                                 according to PT100_SDADC_GAIN */
#define PT100_SDADC_CHANNEL    SDADC_Channel_3
#define PT100_BUFFER_SIZE      (uint32_t)1000
#define PT100_VREF_VOLTAGE     (float) 3.3f  /* SDADC external reference is set to 3.3V */
#define SDADC_INIT_TIMEOUT     (uint32_t)30  /* about two SDADC clock cycles after INIT is set */
#define REFERENCE_RESISTOR     (uint32_t)1800 /* Reference resistor: labeled R33 on STM32373C-EVAL */
#define RESISTANCE_ZERODEGRE   (uint32_t)100  /* PT100 resistance at 0 deg C */
#define RESISTANCE_COEFFICIENT (float)0.385f
#define SDADCRESOL                (uint32_t)65535 /* 2e16 - 1 */

static void sdadcEndCallback(ADCDriver *adcdp, adcsample_t *buffer, size_t n);

static void adc_err_cb(ADCDriver *adcdp, adcerror_t err) {
    (void) adcdp;
    (void) err;
  chDbgPanic("ADC Error:Overflow, DMA Failure");
}

ADCConversionGroup adcCalibOffsetGroup = {
  .circular     = FALSE,   /* circular buffer */
  .num_channels = 1,       /* num channels */
  .end_cb       = NULL,    /* callback */
  .error_cb     = NULL,    /* error callback */

  .ll.sdadc = {
          .cr1   = 0,  /* CR1 */
          /* CR2  - do not set SDADC_CR2_RWSTART
             since this is for calibration of the offsets, we let the
             driver function set the SDADC_CR2_STARTCALIB bit */
          .cr2   = sdadcSTM32ChannelSelect( SDADC_Channel_2 ) |
                    SDADC_CR2_ADON, 
          .jchgr = 0,  /* jchgr */
          .conf0r = SDADC_CONFxR_COMMON_VSSA |
                    SDADC_CONFxR_GAIN_X8 |
                    SDADC_CONF0R_SE0_0,  /* conf0r */
          .conf1r = SDADC_CONFxR_COMMON_VSSA |
                    SDADC_CONFxR_GAIN_X8 |
                    SDADC_CONFxR_SE0_DIFFERENTIAL,
          .conf2r = 0,
          /* ch8 uses conf1 */
          .confchr1 = sdadcSTM32Channel1TO7Config( SDADC_Channel_2, 0),
          .confchr2 = sdadcSTM32Channel8Config( SDADC_Channel_8, 1),
  }
};

/**
  * @brief  Configure PT100_SDADC channel in Single Ended Offset mode using DMA
  * @note   The SDADC divider is set 12 supposing the system clock is set 72 MHz.
  *         If system clock is not 72MHz, change SDADC divider in the manner to get
  *         the SDADC clocked by 6 MHz using RCC_SDADCCLKConfig()
  * @param  None
  * @retval 0: SDADC Configured successfully
  *         1: INITRDY flag is not set, check the SDADC reference voltage
  *         2: EOCAL flag is not set
  */
uint32_t PT100_Config(void)
{
  /* PT100_SDADC APB2 interface clock enable */
  /* DeInit PT100_SDADC */
  /* PWR APB1 interface clock enable */
  /* Enable PT100_SDADC analog interface */
  /* Set the SDADC divider: The SDADC should run @6MHz */
  /* If Sysclk is 72MHz, SDADC divider should be 12 */
  /* GPIO Peripheral clock enable */
  /* PT100_SDADC channel 3P pin configuration: PE7 */

  /* Select External reference: The reference voltage selection is available
     only in SDADC1 and therefore to select the VREF for SDADC2/SDADC3, SDADC1
     clock must be already enabled */

  sdadcSTM32VREFSelect(SDADC_VREF_EXT);

  adcStart(&SDADCD1, NULL);

  sdadcSTM32Calibrate(&SDADCD1, SDADC_NUM_CALIB_SEQ_1, &adcCalibOffsetGroup);

  /* SDADC successfully configured */
  return 0;
}


ADCConversionGroup adcCalibConvGroup = {
  .circular     = FALSE,              /* circular buffer */
  .num_channels = 1,                  /* num channels */
  .end_cb       = sdadcEndCallback, /* callback */
  .error_cb     = adc_err_cb,         /* error callback */

  .ll.sdadc = {
          .cr1   = 0,  /* CR1 */
          .cr2   = sdadcSTM32ChannelSelect( SDADC_Channel_2 ) |
                    SDADC_CR2_RSWSTART | SDADC_CR2_ADON,  /* CR2 */
          .jchgr = 0,  /* jchgr */
          .conf0r = SDADC_CONFxR_COMMON_VSSA |
                    SDADC_CONFxR_GAIN_X8 |
                    SDADC_CONF0R_SE0_0,  /* conf0r */
          .conf1r = SDADC_CONFxR_COMMON_VSSA |
                    SDADC_CONFxR_GAIN_X8 |
                    SDADC_CONFxR_SE0_DIFFERENTIAL,
          .conf2r = 0,
          /* ch8 uses conf1 */
          .confchr1 = sdadcSTM32Channel1TO7Config( SDADC_Channel_2, 0),
          .confchr2 = sdadcSTM32Channel8Config( SDADC_Channel_8, 1),
  }

};

#define CONFIG_SAMPLE_ITER 1000

BinarySemaphore tempSenseBinSem;

static void sdadcEndCallback(ADCDriver *adcp, adcsample_t *buffer, size_t n) {
  /* Note, only in the ADC_COMPLETE state because the ADC driver fires an
     intermediate callback when the buffer is half full.*/
    (void) buffer;
    (void) n;
  if (adcp->state == ADC_COMPLETE) {
    chSysLockFromIsr();
    chBSemSignalI(&tempSenseBinSem);
    chSysUnlockFromIsr();
  }
}

/**
  * @brief  Convert 256 times the external reference voltage (using external
  *         reference resistor 100 Ohm) and compute the correction factor
  * @param  None
  * @retval the correction factor
  */
float SDADC_Calibration(void)
{
  float averagevalue = 0.0f;
  uint16_t samplescounter = 0;
  adcsample_t sample = 0xdead;

  /* In prior to the Calibration execution, the SDADC should be configured
     in differential mode, a common SDADC configuration phase(RCC, GPIO, SDADC configuration
     steps, Channel configuration...) are managed by the above PT100_Config() function */
  for (samplescounter = 0; samplescounter < CONFIG_SAMPLE_ITER; samplescounter++)
  {
    adcStartConversion(&SDADCD1, &adcCalibConvGroup, &sample, 1);

    /* Wait Regular end of conversion flag to be set */
    if (chBSemWait(&tempSenseBinSem) == RDY_OK) {
      averagevalue += (((int16_t) sample) / (int16_t) SDADC_GAIN);
    }
    else {
      chDbgPanic("ERROR - calibration sem reset");
    }
  }

  /* Compute the average value */
  averagevalue = averagevalue / ((float) CONFIG_SAMPLE_ITER);
  /* compute the correction factor */
  return((float)(1820.0f / averagevalue));// 1820 = 100 * 65535 / 3600
  /* T = ((sdadcsample * 3600 / 65535) - 100) / 0.385 = 0 °C
     sdadcsample * 3600 / 65535 = 100 ==> sdadcsample = 100 * 65535 / 3600 = 1820 */
}


ADCConversionGroup adcRegConvGroup = {
  .circular     = FALSE,              /* circular buffer */
  .num_channels = 1,                  /* num channels */
  .end_cb       = sdadcEndCallback, /* callback */
  .error_cb     = adc_err_cb,         /* error callback */

  .ll.sdadc = {
          .cr1   = 0,  /* CR1 */
          .cr2   = sdadcSTM32ChannelSelect( SDADC_Channel_2 ) |
                    SDADC_CR2_RSWSTART | SDADC_CR2_ADON,  /* CR2 */
          .jchgr = 0,  /* jchgr */
          .conf0r = SDADC_CONFxR_COMMON_VSSA |
                     SDADC_CONFxR_GAIN_X8 | 
                     SDADC_CONFxR_SE0_SINGLE_ENDED_OFFSET,  /* conf0r */
          .conf1r = SDADC_CONFxR_COMMON_VSSA |
                     SDADC_CONFxR_GAIN_X8 |
                     SDADC_CONFxR_SE0_DIFFERENTIAL,  /* conf1r */
          .conf2r = 0,
          /* ch8 uses conf1 */
          .confchr1 = sdadcSTM32Channel1TO7Config( SDADC_Channel_2, 0),
          .confchr2 = sdadcSTM32Channel8Config( SDADC_Channel_8, 1 ),
  }

};

float SDADCConvDataBuffer[PT100_BUFFER_SIZE];

#if 0
void waitForKeypress()
{
  while (palReadPad(GPIOA, GPIOA_KEY_BUTTON)) { /* active low */
    chThdSleepMilliseconds(500);
  };
}
#endif
void takeTemp()
{
  float coeffcorrection = 0.9536f;
  uint16_t sdadcidx = 0, i;
  adcsample_t sample;
  uint32_t maxidx = 0, minidx = 0;
  float MinTemperaturePT100 = FLT_MAX;
  float MaxTemperaturePT100 = -(FLT_MAX);
  float AvgTemperaturePT100 = 0.0;

  chBSemInit(&tempSenseBinSem, TRUE); /* init to taken */

  test_println("\r\nConfiguring SDADC1");
  if (PT100_Config() != 0) 
    return; /* failed, return */
#if 0
  test_println("Calibrating...");
  test_println("Set jumper J18 to pins 2-3, not 1-2");
  test_println("Then press the key button.");

  waitForKeypress();
#endif
  coeffcorrection = SDADC_Calibration();
#if 0
  test_println("Calibrated...now set jumper J18 back to pins 1-2, not 2-3");
  test_println("Then press the key button.");

  waitForKeypress();
#endif
  test_println("Measuring temperature");
  while (sdadcidx < PT100_BUFFER_SIZE)
  {
    adcStartConversion(&SDADCD1, &adcRegConvGroup, &sample, 1);

    if (chBSemWait(&tempSenseBinSem) == RDY_OK) {
    
      /* Get the converted value */
      SDADCConvDataBuffer[sdadcidx] = 
	(float) ((((coeffcorrection * ((sample & 0xFFF8 ) / SDADC_GAIN) * REFERENCE_RESISTOR * 2) / SDADCRESOL) - RESISTANCE_ZERODEGRE) / RESISTANCE_COEFFICIENT);
      /* Increment index */
      sdadcidx++;

    }
    else {
      chDbgPanic("ERROR - reg conversion sem reset");
    }
  }

  test_println("Processing measurements");
  /* Get the max, min temperature value */
  float accum = 0.0;


  test_println("");
  test_println("");
  test_println("==============================");

  for (i=0;i < sdadcidx;i++) {

    if (SDADCConvDataBuffer[i] > MaxTemperaturePT100) {
      MaxTemperaturePT100 = SDADCConvDataBuffer[i];
      maxidx = i;
    }
    
    if (SDADCConvDataBuffer[i] < MinTemperaturePT100) {
      MinTemperaturePT100 = SDADCConvDataBuffer[i];
      minidx = i;
    }

    accum += SDADCConvDataBuffer[i];
  }

  test_println("==============================");

  AvgTemperaturePT100 = accum / (float) sdadcidx;

  test_print("\r\nAvg Temperature : ");
  test_printn((int) AvgTemperaturePT100);
  test_print("\r\nMax Temperature : ");
  test_printn((int) MaxTemperaturePT100);
  test_print("\r\nMin Temperature : ");
  test_printn((int) MinTemperaturePT100);
}

