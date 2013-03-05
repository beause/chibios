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

/**
 * @file    STM32F4xx/adc_lld.c
 * @brief   STM32F4xx/STM32F2xx ADC subsystem low level driver source.
 *
 * @addtogroup ADC
 * @{
 */

#include "ch.h"
#include "hal.h"

#if HAL_USE_ADC || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#define ADC1_DMA_CHANNEL                                                    \
  STM32_DMA_GETCHANNEL(STM32_ADC_ADC1_DMA_STREAM, STM32_ADC1_DMA_CHN)

#define ADC2_DMA_CHANNEL                                                    \
  STM32_DMA_GETCHANNEL(STM32_ADC_ADC2_DMA_STREAM, STM32_ADC2_DMA_CHN)

#define ADC3_DMA_CHANNEL                                                    \
  STM32_DMA_GETCHANNEL(STM32_ADC_ADC3_DMA_STREAM, STM32_ADC3_DMA_CHN)

#define SDADC1_DMA_CHANNEL                                                    \
  STM32_DMA_GETCHANNEL(STM32_ADC_SDADC1_DMA_STREAM, STM32_SDADC1_DMA_CHN)

#define SDADC2_DMA_CHANNEL                                                    \
  STM32_DMA_GETCHANNEL(STM32_ADC_SDADC2_DMA_STREAM, STM32_SDADC2_DMA_CHN)

#define SDADC3_DMA_CHANNEL                                                    \
  STM32_DMA_GETCHANNEL(STM32_ADC_SDADC3_DMA_STREAM, STM32_SDADC3_DMA_CHN)

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/** @brief ADC1 driver identifier.*/
#if STM32_ADC_USE_ADC1 || defined(__DOXYGEN__)
ADCDriver ADCD1;
#endif

/** @brief ADC2 driver identifier.*/
#if STM32_ADC_USE_ADC2 || defined(__DOXYGEN__)
ADCDriver ADCD2;
#endif

/** @brief ADC3 driver identifier.*/
#if STM32_ADC_USE_ADC3 || defined(__DOXYGEN__)
ADCDriver ADCD3;
#endif

/** @brief SDADC1 driver identifier.*/
#if STM32_ADC_USE_SDADC1 || defined(__DOXYGEN__)
ADCDriver SDADCD1;
#endif

/** @brief SDADC2 driver identifier.*/
#if STM32_ADC_USE_SDADC2 || defined(__DOXYGEN__)
ADCDriver SDADCD2;
#endif

/** @brief SDADC3 driver identifier.*/
#if STM32_ADC_USE_SDADC3 || defined(__DOXYGEN__)
ADCDriver SDADCD3;
#endif

/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/**
 * @brief   ADC DMA ISR service routine.
 *
 * @param[in] adcp      pointer to the @p ADCDriver object
 * @param[in] flags     pre-shifted content of the ISR register
 */
static void adc_lld_serve_rx_interrupt(ADCDriver *adcp, uint32_t flags) {

  /* DMA errors handling.*/
  if ((flags & (STM32_DMA_ISR_TEIF | STM32_DMA_ISR_DMEIF)) != 0) {
    /* DMA, this could help only if the DMA tries to access an unmapped
       address space or violates alignment rules.*/
    _adc_isr_error_code(adcp, ADC_ERR_DMAFAILURE);
  }
  else {
    /* It is possible that the conversion group has already be reset by the
       ADC error handler, in this case this interrupt is spurious.*/
    if (adcp->grpp != NULL) {
      if ((flags & STM32_DMA_ISR_HTIF) != 0) {
        /* Half transfer processing.*/
        _adc_isr_half_code(adcp);
      }
      if ((flags & STM32_DMA_ISR_TCIF) != 0) {
        /* Transfer complete processing.*/
        _adc_isr_full_code(adcp);
      }
    }
  }
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#if STM32_ADC_USE_ADC1 || STM32_ADC_USE_ADC2 || STM32_ADC_USE_ADC3 ||       \
    defined(__DOXYGEN__)
/**
 * @brief   ADC interrupt handler.
 *
 * @isr
 */
CH_IRQ_HANDLER(ADC1_2_3_IRQHandler) {
  CH_IRQ_PROLOGUE();

#if STM32_ADC_USE_ADC1
  /* TODO: Add here analog watchdog handling.*/
#endif /* STM32_ADC_USE_ADC1 */

  CH_IRQ_EPILOGUE();
}
#endif

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level ADC driver initialization.
 *
 * @notapi
 */
void adc_lld_init(void) {

#if STM32_ADC_USE_ADC1
  /* Driver initialization.*/
  adcObjectInit(&ADCD1);
  ADCD1.adc = ADC1;
  ADCD1.dmastp  = STM32_DMA_STREAM(STM32_ADC_ADC1_DMA_STREAM);
  ADCD1.dmamode = STM32_DMA_CR_CHSEL(ADC1_DMA_CHANNEL) |
                  STM32_DMA_CR_PL(STM32_ADC_ADC1_DMA_PRIORITY) |
                  STM32_DMA_CR_DIR_P2M |
                  STM32_DMA_CR_MSIZE_HWORD | STM32_DMA_CR_PSIZE_HWORD |
                  STM32_DMA_CR_MINC        | STM32_DMA_CR_TCIE        |
                  STM32_DMA_CR_DMEIE       | STM32_DMA_CR_TEIE;
#endif

#if STM32_ADC_USE_ADC2
  /* Driver initialization.*/
  adcObjectInit(&ADCD2);
  ADCD2.adc = ADC2;
  ADCD2.dmastp  = STM32_DMA_STREAM(STM32_ADC_ADC2_DMA_STREAM);
  ADCD2.dmamode = STM32_DMA_CR_CHSEL(ADC2_DMA_CHANNEL) |
                  STM32_DMA_CR_PL(STM32_ADC_ADC2_DMA_PRIORITY) |
                  STM32_DMA_CR_DIR_P2M |
                  STM32_DMA_CR_MSIZE_HWORD | STM32_DMA_CR_PSIZE_HWORD |
                  STM32_DMA_CR_MINC        | STM32_DMA_CR_TCIE        |
                  STM32_DMA_CR_DMEIE       | STM32_DMA_CR_TEIE;
#endif

#if STM32_ADC_USE_ADC3
  /* Driver initialization.*/
  adcObjectInit(&ADCD3);
  ADCD3.adc = ADC3;
  ADCD3.dmastp  = STM32_DMA_STREAM(STM32_ADC_ADC3_DMA_STREAM);
  ADCD3.dmamode = STM32_DMA_CR_CHSEL(ADC3_DMA_CHANNEL) |
                  STM32_DMA_CR_PL(STM32_ADC_ADC3_DMA_PRIORITY) |
                  STM32_DMA_CR_DIR_P2M |
                  STM32_DMA_CR_MSIZE_HWORD | STM32_DMA_CR_PSIZE_HWORD |
                  STM32_DMA_CR_MINC        | STM32_DMA_CR_TCIE        |
                  STM32_DMA_CR_DMEIE       | STM32_DMA_CR_TEIE;
#endif

  /* The shared vector is initialized on driver initialization and never
     disabled.*/
  nvicEnableVector(ADC1_IRQn, CORTEX_PRIORITY_MASK(STM32_ADC_IRQ_PRIORITY));

#if STM32_ADC_USE_SDADC1
  /* Driver initialization.*/
  adcObjectInit(&SDADCD1);
  SDADCD1.sdadc   = SDADC1;
  SDADCD1.dmastp  = STM32_DMA_STREAM(STM32_ADC_SDADC1_DMA_STREAM);
  SDADCD1.dmamode = STM32_DMA_CR_CHSEL(SDADC1_DMA_CHANNEL) |
                  STM32_DMA_CR_PL(STM32_ADC_SDADC1_DMA_PRIORITY) |
                  STM32_DMA_CR_DIR_P2M |
                  STM32_DMA_CR_MSIZE_HWORD | STM32_DMA_CR_PSIZE_HWORD |
                  STM32_DMA_CR_MINC        | STM32_DMA_CR_TCIE        |
                  STM32_DMA_CR_DMEIE       | STM32_DMA_CR_TEIE;
#endif

#if STM32_ADC_USE_SDADC2
  /* Driver initialization.*/
  adcObjectInit(&SDADCD2);
  SDADCD1.sdadc   = SDADC2;
  SDADCD1.dmastp  = STM32_DMA_STREAM(STM32_ADC_SDADC2_DMA_STREAM);
  SDADCD1.dmamode = STM32_DMA_CR_CHSEL(SDADC2_DMA_CHANNEL) |
                  STM32_DMA_CR_PL(STM32_ADC_SDADC2_DMA_PRIORITY) |
                  STM32_DMA_CR_DIR_P2M |
                  STM32_DMA_CR_MSIZE_HWORD | STM32_DMA_CR_PSIZE_HWORD |
                  STM32_DMA_CR_MINC        | STM32_DMA_CR_TCIE        |
                  STM32_DMA_CR_DMEIE       | STM32_DMA_CR_TEIE;
#endif

#if STM32_ADC_USE_SDADC3
  /* Driver initialization.*/
  adcObjectInit(&SDADCD3);
  SDADCD1.sdadc   = SDADC3;
  SDADCD1.dmastp  = STM32_DMA_STREAM(STM32_ADC_SDADC3_DMA_STREAM);
  SDADCD1.dmamode = STM32_DMA_CR_CHSEL(SDADC3_DMA_CHANNEL) |
                  STM32_DMA_CR_PL(STM32_ADC_SDADC3_DMA_PRIORITY) |
                  STM32_DMA_CR_DIR_P2M |
                  STM32_DMA_CR_MSIZE_HWORD | STM32_DMA_CR_PSIZE_HWORD |
                  STM32_DMA_CR_MINC        | STM32_DMA_CR_TCIE        |
                  STM32_DMA_CR_DMEIE       | STM32_DMA_CR_TEIE;
#endif


  nvicEnableVector(SDADC1_IRQn, CORTEX_PRIORITY_MASK(STM32_ADC_SDADC1_IRQ_PRIORITY));
  nvicEnableVector(SDADC2_IRQn, CORTEX_PRIORITY_MASK(STM32_ADC_SDADC2_IRQ_PRIORITY));
  nvicEnableVector(SDADC3_IRQn, CORTEX_PRIORITY_MASK(STM32_ADC_SDADC3_IRQ_PRIORITY));
}

/**
 * @brief   Initial config for SDADC peripheral.
 *
 * @param[in] adcp            pointer to the @p ADCDriver object
 * @param[in] dmaPriority     priority for the dma channel 0..3
 * @param[in] rxIsrFunc       isr handler for dma,
 * @param[in] dmaSrcLoc       pointer to the @p SDADC data
 * @param[in] periphEnableBit SDADC bit in rcc APB2 Enable register
 *
 * @notapi
 */
void sdadc_lld_start_cr_init_helper(ADCDriver*     adcp, 
				    uint32_t       dmaPriority, 
				    stm32_dmaisr_t rxIsrFunc, 
				    volatile void*          dmaSrcLoc, 
				    uint32_t       periphEnableBit) {
      bool_t b;
      b = dmaStreamAllocate(adcp->dmastp,
                            dmaPriority,
                            rxIsrFunc,
                            adcp);
      chDbgAssert(!b, "adc_lld_start(), #1", "stream already allocated");
      dmaStreamSetPeripheral(adcp->dmastp, dmaSrcLoc);
      rccEnableAPB2(periphEnableBit, FALSE);

      /* SDADC initial setup, starting the analog part here in order to reduce
	 the latency when starting a conversion.*/

      /*
	====== SDADC CR1 settings breakdown =====
	Initialization mode request               : disabled
	DMA Enabled to read data for reg ch. grp  : disabled
	DMA Enabled to read data for inj ch. grp  : disabled
	Launch reg conv sync w SDADC1             : Do not
	Launch injected conv sync w SDADC1        : Do not
	Enter power down mode when idle           : False
	Enter standby mode when idle              : False
	Slow clock mode                           : fast mode
	Reference voltage selection               : external Vref
	reg data overrun interrupt                : disabled
	reg data end of conversion interrupt      : disabled
	injected data overrun interrupt           : disabled
	injected data end of conversion interrupt : disabled
	end of calibration interrupt              : disabled
       */
      adcp->sdadc->CR1 = 0;

      /*
	====== SDADC CR1 settings breakdown =====
	SDADC enable                                    : X
	Number of calibration sequences to be performed : 0 
	Start calibration                               : NO
	Continuous mode selection for injected conv     : once
	Delay start of injected conversions             : asap
	Trig sig sel for launching inj conv             : TIM13_CH1,TIM17_CH1, TIM16_CH1
	Trig en and trig edge sel for injected conv     : disabled
	Start a conv of the inj group of ch             : 0
	Regular channel sel (0-8)                       : 0 
	Continuous mode sel for regular conv            : once
	Software start of a conversion on the regular ch: 0
	Fast conv mode sel                              : disabled
      */
      adcp->sdadc->CR2 = 0;
      adcp->sdadc->CR2 = SDADC_CR2_ADON;
}



/**
 * @brief   Configures and activates the ADC peripheral.
 *
 * @param[in] adcp      pointer to the @p ADCDriver object
 *
 * @notapi
 */
void adc_lld_start(ADCDriver *adcp) {

  /* If in stopped state then enables the ADC and DMA clocks.*/
  if (adcp->state == ADC_STOP) {
#if STM32_ADC_USE_ADC1
    if (&ADCD1 == adcp) {
      bool_t b;
      b = dmaStreamAllocate(adcp->dmastp,
                            STM32_ADC_ADC1_DMA_IRQ_PRIORITY,
                            (stm32_dmaisr_t)adc_lld_serve_rx_interrupt,
                            (void *)adcp);
      chDbgAssert(!b, "adc_lld_start(), #1", "stream already allocated");
      dmaStreamSetPeripheral(adcp->dmastp, &ADC1->DR);
      rccEnableADC1(FALSE);

      /* ADC initial setup, starting the analog part here in order to reduce
	 the latency when starting a conversion.*/
      adcp->adc->CR1 = 0;
      adcp->adc->CR2 = 0;
      adcp->adc->CR2 = ADC_CR2_ADON;
    }
#endif /* STM32_ADC_USE_ADC1 */

#if STM32_ADC_USE_SDADC1
    if (&SDADCD1 == adcp) {
      sdadc_lld_start_cr_init_helper(adcp,
				     STM32_ADC_SDADC1_DMA_IRQ_PRIORITY,
				     (stm32_dmaisr_t) adc_lld_serve_rx_interrupt,
				     &SDADC1->RDATAR,
				     RCC_APB2ENR_SDADC1EN);

    }
#endif /* STM32_ADC_USE_SDADC1 */

#if STM32_ADC_USE_SDADC2
    if (&SDADCD1 == adcp) {
      sdadc_lld_start_cr_init_helper(adcp,
				     STM32_ADC_SDADC2_DMA_IRQ_PRIORITY,
				     (stm32_dmaisr_t) adc_lld_serve_rx_interrupt,
				     &SDADC2->RDATAR,
				     RCC_APB2ENR_SDADC2EN);

    }
#endif /* STM32_ADC_USE_SDADC2 */

#if STM32_ADC_USE_SDADC3
    if (&SDADCD1 == adcp) {
      sdadc_lld_start_cr_init_helper(adcp,
				     STM32_ADC_SDADC3_DMA_IRQ_PRIORITY,
				     (stm32_dmaisr_t) adc_lld_serve_rx_interrupt,
				     &SDADC3->RDATAR,
				     RCC_APB2ENR_SDADC3EN);

    }
#endif /* STM32_ADC_USE_SDADC3 */

  }
}

/**
 * @brief   Deactivates the ADC peripheral.
 *
 * @param[in] adcp      pointer to the @p ADCDriver object
 *
 * @notapi
 */
void adc_lld_stop(ADCDriver *adcp) {

  /* If in ready state then disables the ADC clock.*/
  if (adcp->state == ADC_READY) {
    dmaStreamRelease(adcp->dmastp);
    adcp->adc->CR1 = 0;
    adcp->adc->CR2 = 0;

#if STM32_ADC_USE_ADC1
    if (&ADCD1 == adcp)
      rccDisableADC1(FALSE);
#endif

#if STM32_ADC_USE_ADC2
    if (&ADCD2 == adcp)
      rccDisableADC2(FALSE);
#endif

#if STM32_ADC_USE_ADC3
    if (&ADCD3 == adcp)
      rccDisableADC3(FALSE);
#endif
  }

#if STM32_ADC_USE_SDADC1
    if (&SDADCD1 == adcp)
      rccDisableSDADC1(FALSE);
#endif

#if STM32_ADC_USE_SDADC2
    if (&SDADCD2 == adcp)
      rccDisableSDADC2(FALSE);
#endif

#if STM32_ADC_USE_SDADC3
    if (&SDADCD3 == adcp)
      rccDisableSDADC3(FALSE);
#endif


}

/**
 * @brief   Starts an ADC conversion.
 *
 * @param[in] adcp      pointer to the @p ADCDriver object
 *
 * @notapi
 */
void adc_lld_start_conversion(ADCDriver *adcp) {
  uint32_t mode;
  const ADCConversionGroup *grpp = adcp->grpp;

  /* DMA setup.*/
  mode = adcp->dmamode;
  if (grpp->circular) {
    mode |= STM32_DMA_CR_CIRC;
  }
  if (adcp->depth > 1) {
    /* If the buffer depth is greater than one then the half transfer interrupt
       interrupt is enabled in order to allows streaming processing.*/
    mode |= STM32_DMA_CR_HTIE;
  }
  dmaStreamSetMemory0(adcp->dmastp, adcp->samples);
  dmaStreamSetTransactionSize(adcp->dmastp, (uint32_t)grpp->num_channels *
                                            (uint32_t)adcp->depth);
  dmaStreamSetMode(adcp->dmastp, mode);
  dmaStreamEnable(adcp->dmastp);

  /* ADC setup.*/
  adcp->adc->SR    = 0;
  adcp->adc->SMPR1 = grpp->smpr1;
  adcp->adc->SMPR2 = grpp->smpr2;
  adcp->adc->SQR1  = grpp->sqr1;
  adcp->adc->SQR2  = grpp->sqr2;
  adcp->adc->SQR3  = grpp->sqr3;

  /* ADC configuration and start, the start is performed using the method
     specified in the CR2 configuration, usually ADC_CR2_SWSTART.*/
  adcp->adc->CR1   = grpp->cr1 | ADC_CR1_SCAN;
  if ((grpp->cr2 & ADC_CR2_SWSTART) != 0)
    adcp->adc->CR2 = grpp->cr2 | ADC_CR2_CONT  | ADC_CR2_DMA | ADC_CR2_ADON;
  else
    adcp->adc->CR2 = grpp->cr2 |                 ADC_CR2_DMA | ADC_CR2_ADON;
}

/**
 * @brief   Stops an ongoing conversion.
 *
 * @param[in] adcp      pointer to the @p ADCDriver object
 *
 * @notapi
 */
void adc_lld_stop_conversion(ADCDriver *adcp) {

  dmaStreamDisable(adcp->dmastp);
  adcp->adc->CR1 = 0;
  adcp->adc->CR2 = 0;
  adcp->adc->CR2 = ADC_CR2_ADON;
}

#if 0
/**
 * @brief   Enables the TSVREFE bit.
 * @details The TSVREFE bit is required in order to sample the internal
 *          temperature sensor and internal reference voltage.
 * @note    This is an STM32-only functionality.
 */
void adcSTM32EnableTSVREFE(void) {

  ADC->CCR |= ADC_CCR_TSVREFE;
}

/**
 * @brief   Disables the TSVREFE bit.
 * @details The TSVREFE bit is required in order to sample the internal
 *          temperature sensor and internal reference voltage.
 * @note    This is an STM32-only functionality.
 */
void adcSTM32DisableTSVREFE(void) {

  ADC->CCR &= ~ADC_CCR_TSVREFE;
}

/**
 * @brief   Enables the VBATE bit.
 * @details The VBATE bit is required in order to sample the VBAT channel.
 * @note    This is an STM32-only functionality.
 * @note    This function is meant to be called after @p adcStart().
 */
void adcSTM32EnableVBATE(void) {

  ADC->CCR |= ADC_CCR_VBATE;
}

/**
 * @brief   Disables the VBATE bit.
 * @details The VBATE bit is required in order to sample the VBAT channel.
 * @note    This is an STM32-only functionality.
 * @note    This function is meant to be called after @p adcStart().
 */
void adcSTM32DisableVBATE(void) {

  ADC->CCR &= ~ADC_CCR_VBATE;
}
#endif
#endif /* HAL_USE_ADC */

/** @} */
