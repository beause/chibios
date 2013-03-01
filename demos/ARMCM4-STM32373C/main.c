/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012,2013 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ch.h"
#include "hal.h"
#include "test.h"

/*
 * This is a periodic thread that does absolutely nothing except flashing LEDs.
 */
static WORKING_AREA(waThread1, 128);
static WORKING_AREA(waThread2, 128);
static WORKING_AREA(waThread3, 128);

/***
 *** SPI demo - write the values in buf out to pin PC12 available on connector Ch13
 *** 
 ***/
unsigned char buf[2] = {
  0x00,
  0xff
};

static msg_t SPIThread(void *arg) {
  (void)arg;
  chRegSetThreadName("spi");
  while (TRUE) {
    spiSelect(&SPID3);
    spiSend(&SPID3, sizeof(buf), buf);
    spiUnselect(&SPID3);
    chThdSleepMilliseconds(125);
  }
  return 0;
}


static msg_t Thread1(void *arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (TRUE) {
    palSetPad(GPIOC, GPIOC_LED1);
    chThdSleepMilliseconds(125);
    palClearPad(GPIOC, GPIOC_LED1);
    palSetPad(GPIOC, GPIOC_LED2);
    chThdSleepMilliseconds(125);
    palClearPad(GPIOC, GPIOC_LED2);
    palSetPad(GPIOC, GPIOC_LED3);
    chThdSleepMilliseconds(125);
    palClearPad(GPIOC, GPIOC_LED3);
    palSetPad(GPIOC, GPIOC_LED4);
    chThdSleepMilliseconds(125);
    palClearPad(GPIOC, GPIOC_LED4);
  }
  return 0;
}

adcsample_t avg_sense, avg_vrefint, avg_pot;
BinarySemaphore adcOutputBinSem;

static msg_t printADCOutputThread(void *arg) {

  chRegSetThreadName("ADCOutputThread");

  while (TRUE) {
    /* wait for semaphore */
    if (chBSemWait(&adcOutputBinSem) == RDY_OK) {
      test_print("vref:");
      test_printn(avg_vrefint);
      test_print(" sense:");
      test_printn(avg_sense);
      test_print(" pot:");
      test_printn(avg_pot);
      test_print("\r\n");

    }
    else {
      test_print("sem reset");
    }
  }
  return 0;
}

/*
 * SPI end transfer callback.
 */
static void spicb(SPIDriver *spip) {
 
  /* On transfer end just releases the slave select line.*/
  chSysLockFromIsr();
  spiUnselectI(spip);
  chSysUnlockFromIsr();
}


/*
 * SPI configuration structure.
 * Maximum speed (12MHz), CPHA=0, CPOL=0, 16bits frames, MSb transmitted first.
 * The slave select line is the pin GPIOA_SPI1NSS on the port GPIOA.
 */
static const SPIConfig spicfg = {
  spicb,
  /* HW dependent part.*/
  GPIOD,           /* chip select line port */
  GPIOD_LCD_CS,    /* chip select line pad number */
/* CR1 init data - BIDIMODE= 0: 2 line unidirectional mode
                   BIDIOE  = X: N/A (set to 0 )
                   CRCEN   = 1: CRC enabled
                   CRCNEXT = 0: next transmit from tx buffer
                   CRCLEN  = 0: CRC LEN (8/16) set to 0
                   RXONLY  = 0: Full Duplex
                   SSM     = 1: S/W slave mgmt. enabled
                   SSI     = 0: internal slave select
                   LSBFIRST= 0: MSB first
                   SPE     = 0: SPE Enable - enabled by ChibiOS/RT HAL
                   BR[2:0] = 1: div 4 - follows eval s/w lcd
                   MSTR    = 1: Master
                   CPOL    = 1: Clock Polarity when idle send 1s
                   CPHA    = 1: Clock Phase use 2nd clock transition

 */

  SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_CPOL | SPI_CR1_CPHA, // | SPI_CR1_CRCEN,
  /* CR2 init data - bit val desc
                      15 0   reserved
                      14 0   Last DMA transfer for transmission - data transfer even
                      13 0   Last DMA transfer for reception - data transfer even
                      12 1   FIFO reception threshold - RXNE event gen if FIFO level >= 1/4
                    11:8 0x7 data size - 8-bit
                       7 0   tx buf empty interrupt enable - disabled
                       6 0   rx buf empty interrupt enable - disabled
                       5 0   error interrupt enable - disabled
                       4 0   frame format - motorola mode
                       3 0   NSS pulse - no NSS pulse
                       2 1   SS output enabled
                       1 0   TX buffer DMA enable - disabled
                       0 0   RX buffer DMA enable - disabled */
  SPI_CR2_SSOE | SPI_CR2_FRXTH | SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2
};

void adccb(ADCDriver *adcp, adcsample_t *buffer, size_t n);
void adc_err_cb(ADCDriver *adcp, adcerror_t err);
static void spicb(SPIDriver *spip);

/* Total number of channels to be sampled by a single ADC operation.*/
#define ADC_GRP1_NUM_CHANNELS   3

/* Depth of the conversion buffer, channels are sampled four times each.*/
#define ADC_GRP1_BUF_DEPTH      4

/*
 * ADC samples buffer.
 */
static adcsample_t samples[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];

/*
 * ADC conversion group.
 * Mode:        Linear buffer, 4 samples of 2 channels, SW triggered.
 * Channels:    temp (ADC_IN16) recommended sampling time 17.1 uS (41.5 cycles sample time)
 *              Vrefint (ADC_IN17)  
 *
 *
 *              RCC configured PLL -> 72MHz -> AHB (/1) -> APB2 (/1) -> ADCPRE ( / 8 ) 9MHz
 *              
 * 
 */
static const ADCConversionGroup adcgrpcfg = {
  FALSE,                        /* circular buffer */
  ADC_GRP1_NUM_CHANNELS,        /* num channels */
  adccb,                        /* callback */
  adc_err_cb,                   /* error callback */
  /* HW dependent part.*/

  /*******************  Bit definition for ADC_CR1 register  ***************
  ADC_CR1_AWDCH       AWDCH[4:0] bits (Analog watchdog channel select bits)
  ADC_CR1_EOCIE       Interrupt enable for EOC
  ADC_CR1_AWDIE       Analog Watchdog interrupt enable
  ADC_CR1_JEOCIE      Interrupt enable for injected channels
  ADC_CR1_SCAN        Scan mode
  ADC_CR1_AWDSGL      Enable the watchdog on a single channel in scan mode
  ADC_CR1_JAUTO       Automatic injected group conversion
  ADC_CR1_DISCEN      Discontinuous mode on regular channels
  ADC_CR1_JDISCEN     Discontinuous mode on injected channels
  ADC_CR1_DISCNUM     DISCNUM[2:0] bits (Discontinuous mode channel count)
  ADC_CR1_DISCNUM_0   Bit 0
  ADC_CR1_DISCNUM_1   Bit 1
  ADC_CR1_DISCNUM_2   Bit 2
  ADC_CR1_JAWDEN      Analog watchdog enable on injected channels
  ADC_CR1_AWDEN       Analog watchdog enable on regular channels */
  0,                            /* ADC CR1 reg */

  /*******************  Bit definition for ADC_CR2 register  ***************
  ADC_CR2_ADON        A/D Converter ON / OFF
  ADC_CR2_CONT        Continuous Conversion
  ADC_CR2_CAL         A/D Calibration
  ADC_CR2_RSTCAL      Reset Calibration
  ADC_CR2_DMA         Direct Memory access mode
  ADC_CR2_ALIGN       Data Alignment
  ADC_CR2_JEXTSEL     JEXTSEL[2:0] bits (External event select for injected group)
  ADC_CR2_JEXTTRIG    External Trigger Conversion mode for injected channels
  ADC_CR2_EXTSEL      EXTSEL[2:0] bits (External Event Select for regular group)
  ADC_CR2_EXTTRIG     External Trigger Conversion mode for regular channels
  ADC_CR2_JSWSTART    Start Conversion of injected channels
  ADC_CR2_SWSTART     Start Conversion of regular channels
  ADC_CR2_TSVREFE     Temperature Sensor and VREFINT Enable */
  ADC_CR2_TSVREFE,              /* ADC CR2 reg */

/******************  Bit definition for ADC_SMPR1 register  ************
  ADC_SMPR1_SMP10     SMP10[2:0] bits (Channel 10 Sample time selection)
  ADC_SMPR1_SMP11     SMP11[2:0] bits (Channel 11 Sample time selection)
  ADC_SMPR1_SMP12     SMP12[2:0] bits (Channel 12 Sample time selection)
  ADC_SMPR1_SMP13     SMP13[2:0] bits (Channel 13 Sample time selection)
  ADC_SMPR1_SMP14     SMP14[2:0] bits (Channel 14 Sample time selection)
  ADC_SMPR1_SMP15     SMP15[2:0] bits (Channel 15 Sample time selection)
  ADC_SMPR1_SMP16     SMP16[2:0] bits (Channel 16 Sample time selection)
  ADC_SMPR1_SMP17     SMP17[2:0] bits (Channel 17 Sample time selection) */
  ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_239P5) | ADC_SMPR1_SMP_VREF(ADC_SAMPLE_239P5),

/******************  Bit definition for ADC_SMPR2 register  **********
  ADC_SMPR2_SMP0      SMP0[2:0] bits (Channel 0 Sample time selection)
  ADC_SMPR2_SMP1      SMP1[2:0] bits (Channel 1 Sample time selection)
  ADC_SMPR2_SMP2      SMP2[2:0] bits (Channel 2 Sample time selection)
  ADC_SMPR2_SMP3      SMP3[2:0] bits (Channel 3 Sample time selection)
  ADC_SMPR2_SMP4      SMP4[2:0] bits (Channel 4 Sample time selection)
  ADC_SMPR2_SMP5      SMP5[2:0] bits (Channel 5 Sample time selection)
  ADC_SMPR2_SMP6      SMP6[2:0] bits (Channel 6 Sample time selection)
  ADC_SMPR2_SMP7      SMP7[2:0] bits (Channel 7 Sample time selection)
  ADC_SMPR2_SMP8      SMP8[2:0] bits (Channel 8 Sample time selection)
  ADC_SMPR2_SMP9      SMP9[2:0] bits (Channel 9 Sample time selection) */
  ADC_SMPR2_SMP_AN9(ADC_SAMPLE_239P5),  /* ADC SMPR2 reg */

/*******************  Bit definition for ADC_SQR1 register  **************
  ADC_SQR1_SQ13       SQ13[4:0] bits (13th conversion in regular sequence)
  ADC_SQR1_SQ14       SQ14[4:0] bits (14th conversion in regular sequence)
  ADC_SQR1_SQ15       SQ15[4:0] bits (15th conversion in regular sequence)
  ADC_SQR1_SQ16       SQ16[4:0] bits (16th conversion in regular sequence)
  ADC_SQR1_L          L[3:0] bits (Regular channel sequence length) */
  ADC_SQR1_NUM_CH(ADC_GRP1_NUM_CHANNELS),   /* ADC SQR1 reg */

  /*******************  Bit definition for ADC_SQR2 register  **********
  ADC_SQR2_SQ7        SQ7[4:0] bits (7th conversion in regular sequence)
  ADC_SQR2_SQ8        SQ8[4:0] bits (8th conversion in regular sequence)
  ADC_SQR2_SQ9        SQ9[4:0] bits (9th conversion in regular sequence)
  ADC_SQR2_SQ10       SQ10[4:0] bits (10th conversion in regular sequence)
  ADC_SQR2_SQ11       SQ11[4:0] bits (11th conversion in regular sequence)
  ADC_SQR2_SQ12       SQ12[4:0] bits (12th conversion in regular sequence) */
  0, /* ADC SQR2 reg */

  /*************  Bit definition for ADC_SQR3 register  ****************
  ADC_SQR3_SQ1        SQ1[4:0] bits (1st conversion in regular sequence)
  ADC_SQR3_SQ2        SQ2[4:0] bits (2nd conversion in regular sequence)
  ADC_SQR3_SQ3        SQ3[4:0] bits (3rd conversion in regular sequence)
  ADC_SQR3_SQ4        SQ4[4:0] bits (4th conversion in regular sequence)
  ADC_SQR3_SQ5        SQ5[4:0] bits (5th conversion in regular sequence)
  ADC_SQR3_SQ6        SQ6[4:0] bits (6th conversion in regular sequence) */

  ADC_SQR3_SQ3_N(ADC_CHANNEL_IN9) | ADC_SQR3_SQ2_N(ADC_CHANNEL_VREFINT) | ADC_SQR3_SQ1_N(ADC_CHANNEL_SENSOR)   /* ADC SQR3 reg */
};

void adc_err_cb(ADCDriver *adcp, adcerror_t err) {
  
  test_print("ADC Error:");
  test_println(err ? "Overflow\n" : "DMA Failure\n");
}

/*
 * ADC end conversion callback.
 * Write temperature out to USART2
 */

#define AVG_SLOPE 4.3    /* obtained from 32f373xx datasheet */

void adccb(ADCDriver *adcp, adcsample_t *buffer, size_t n) {
  /* Note, only in the ADC_COMPLETE state because the ADC driver fires an
     intermediate callback when the buffer is half full.*/
  if (adcp->state == ADC_COMPLETE) {

    /* Calculates the average values from the ADC samples.*/
    avg_sense   = (samples[0] + samples[3] + samples[6] + samples[9]) / 4;
    avg_vrefint = (samples[1] + samples[4] + samples[7] + samples[10]) / 4;
    avg_pot     = (samples[2] + samples[5] + samples[8] + samples[11]) / 4;
    chBSemSignal(&adcOutputBinSem);

  }
}


/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  chBSemInit(&adcOutputBinSem, 0); /* init to not taken */
  

  sdStart(&SD2, NULL);
  spiStart(&SPID3, &spicfg );

  /***
   ***   Sample the temperature from the on-board temp sensor
   ***
   ***
   ***/
  adcStart(&ADCD1, NULL);

  /*
   * Creates the example thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, SPIThread, NULL);
  chThdCreateStatic(waThread3, sizeof(waThread2), NORMALPRIO, printADCOutputThread, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state, when the button is
   * pressed the test procedure is launched.
   */

  /* set console output destination */
  setStreamDest(&SD2);

  while (TRUE) {
    chSysLockFromIsr();
    adcStartConversionI(&ADCD1, &adcgrpcfg, samples, ADC_GRP1_BUF_DEPTH);
    chSysUnlockFromIsr();
    chThdSleepMilliseconds(1000);
  }
}
