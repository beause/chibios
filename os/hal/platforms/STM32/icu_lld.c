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
/*
   Concepts and parts of this file have been contributed by Fabio Utzig and
   Xo Wang.
 */

/**
 * @file    STM32/icu_lld.c
 * @brief   STM32 ICU subsystem low level driver header.
 *
 * @addtogroup ICU
 * @{
 */

#include "ch.h"
#include "hal.h"

#if HAL_USE_ICU || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/**
 * @brief   ICUD1 driver identifier.
 * @note    The driver ICUD1 allocates the complex timer TIM1 when enabled.
 */
#if STM32_ICU_USE_TIM1 || defined(__DOXYGEN__)
ICUDriver ICUD1;
#endif

/**
 * @brief   ICUD2 driver identifier.
 * @note    The driver ICUD1 allocates the timer TIM2 when enabled.
 */
#if STM32_ICU_USE_TIM2 || defined(__DOXYGEN__)
ICUDriver ICUD2;
#endif

/**
 * @brief   ICUD3 driver identifier.
 * @note    The driver ICUD1 allocates the timer TIM3 when enabled.
 */
#if STM32_ICU_USE_TIM3 || defined(__DOXYGEN__)
ICUDriver ICUD3;
#endif

/**
 * @brief   ICUD4 driver identifier.
 * @note    The driver ICUD4 allocates the timer TIM4 when enabled.
 */
#if STM32_ICU_USE_TIM4 || defined(__DOXYGEN__)
ICUDriver ICUD4;
#endif

/**
 * @brief   ICUD5 driver identifier.
 * @note    The driver ICUD5 allocates the timer TIM5 when enabled.
 */
#if STM32_ICU_USE_TIM5 || defined(__DOXYGEN__)
ICUDriver ICUD5;
#endif

/**
 * @brief   ICUD8 driver identifier.
 * @note    The driver ICUD8 allocates the timer TIM8 when enabled.
 */
#if STM32_ICU_USE_TIM8 || defined(__DOXYGEN__)
ICUDriver ICUD8;
#endif

/**
 * @brief   ICUD15 driver identifier.
 * @note    The driver ICUD15 allocates the timer TIM15 when enabled.
 */
#if STM32_ICU_USE_TIM15 || defined(__DOXYGEN__)
ICUDriver ICUD15;
#endif

/**
 * @brief   ICUD16 driver identifier.
 * @note    The driver ICUD16 allocates the timer TIM16 when enabled.
 */
#if STM32_ICU_USE_TIM16 || defined(__DOXYGEN__)
ICUDriver ICUD16;
#endif
/**
 * @brief   ICUD17 driver identifier.
 * @note    The driver ICUD17 allocates the timer TIM17 when enabled.
 */
#if STM32_ICU_USE_TIM17 || defined(__DOXYGEN__)
ICUDriver ICUD17;
#endif


/**
 * @brief   ICUD19 driver identifier.
 * @note    The driver ICUD19 allocates the timer TIM19 when enabled.
 */
#if STM32_ICU_USE_TIM19 || defined(__DOXYGEN__)
ICUDriver ICUD19;
#endif

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/**
 * @brief   Shared IRQ handler.
 *
 * @param[in] icup      pointer to the @p ICUDriver object
 */
static void icu_lld_serve_interrupt(ICUDriver *icup) {
  uint16_t sr;

  sr  = icup->tim->SR;
  sr &= icup->tim->DIER;
  icup->tim->SR = ~sr;
  if (icup->config->channel == ICU_CHANNEL_1) {
    if ((sr & TIM_SR_CC1IF) != 0)
      _icu_isr_invoke_period_cb(icup);
    if ((sr & TIM_SR_CC2IF) != 0)
      _icu_isr_invoke_width_cb(icup);
  } else {
    if ((sr & TIM_SR_CC1IF) != 0)
      _icu_isr_invoke_width_cb(icup);
    if ((sr & TIM_SR_CC2IF) != 0)
      _icu_isr_invoke_period_cb(icup);
  }
  if ((sr & TIM_SR_UIF) != 0)
    _icu_isr_invoke_overflow_cb(icup);
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#if STM32_ICU_USE_TIM1
#if !defined(STM32_TIM1_UP_HANDLER)
#error "STM32_TIM1_UP_HANDLER not defined"
#endif
/**
 * @brief   TIM1 compare interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
CH_IRQ_HANDLER(STM32_TIM1_UP_HANDLER) {

  CH_IRQ_PROLOGUE();

  icu_lld_serve_interrupt(&ICUD1);

  CH_IRQ_EPILOGUE();
}

#if !defined(STM32_TIM1_CC_HANDLER)
#error "STM32_TIM1_CC_HANDLER not defined"
#endif
/**
 * @brief   TIM1 compare interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
CH_IRQ_HANDLER(STM32_TIM1_CC_HANDLER) {

  CH_IRQ_PROLOGUE();

  icu_lld_serve_interrupt(&ICUD1);

  CH_IRQ_EPILOGUE();
}
#endif /* STM32_ICU_USE_TIM1 */

#if STM32_ICU_USE_TIM2
#if !defined(STM32_TIM2_HANDLER)
#error "STM32_TIM2_HANDLER not defined"
#endif
/**
 * @brief   TIM2 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
CH_IRQ_HANDLER(STM32_TIM2_HANDLER) {

  CH_IRQ_PROLOGUE();

  icu_lld_serve_interrupt(&ICUD2);

  CH_IRQ_EPILOGUE();
}
#endif /* STM32_ICU_USE_TIM2 */

#if STM32_ICU_USE_TIM3
#if !defined(STM32_TIM3_HANDLER)
#error "STM32_TIM3_HANDLER not defined"
#endif
/**
 * @brief   TIM3 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
CH_IRQ_HANDLER(STM32_TIM3_HANDLER) {

  CH_IRQ_PROLOGUE();

  icu_lld_serve_interrupt(&ICUD3);

  CH_IRQ_EPILOGUE();
}
#endif /* STM32_ICU_USE_TIM3 */

#if STM32_ICU_USE_TIM4
#if !defined(STM32_TIM4_HANDLER)
#error "STM32_TIM4_HANDLER not defined"
#endif
/**
 * @brief   TIM4 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
CH_IRQ_HANDLER(STM32_TIM4_HANDLER) {

  CH_IRQ_PROLOGUE();

  icu_lld_serve_interrupt(&ICUD4);

  CH_IRQ_EPILOGUE();
}
#endif /* STM32_ICU_USE_TIM4 */

#if STM32_ICU_USE_TIM5
#if !defined(STM32_TIM5_HANDLER)
#error "STM32_TIM5_HANDLER not defined"
#endif
/**
 * @brief   TIM5 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
CH_IRQ_HANDLER(STM32_TIM5_HANDLER) {

  CH_IRQ_PROLOGUE();

  icu_lld_serve_interrupt(&ICUD5);

  CH_IRQ_EPILOGUE();
}
#endif /* STM32_ICU_USE_TIM5 */

#if STM32_ICU_USE_TIM8
#if !defined(STM32_TIM8_UP_HANDLER)
#error "STM32_TIM8_UP_HANDLER not defined"
#endif
/**
 * @brief   TIM8 compare interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
CH_IRQ_HANDLER(STM32_TIM8_UP_HANDLER) {

  CH_IRQ_PROLOGUE();

  icu_lld_serve_interrupt(&ICUD8);

  CH_IRQ_EPILOGUE();
}

#if !defined(STM32_TIM8_CC_HANDLER)
#error "STM32_TIM8_CC_HANDLER not defined"
#endif
/**
 * @brief   TIM8 compare interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
CH_IRQ_HANDLER(STM32_TIM8_CC_HANDLER) {

  CH_IRQ_PROLOGUE();

  icu_lld_serve_interrupt(&ICUD8);

  CH_IRQ_EPILOGUE();
}
#endif /* STM32_ICU_USE_TIM8 */

#if STM32_ICU_USE_TIM15
#if !defined(STM32_TIM15_HANDLER)
#error "STM32_TIM15_HANDLER not defined"
#endif
/**
 * @brief   TIM15 compare interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
CH_IRQ_HANDLER(STM32_TIM15_HANDLER) {

  CH_IRQ_PROLOGUE();

  icu_lld_serve_interrupt(&ICUD15);

  CH_IRQ_EPILOGUE();
}
#endif /* STM32_ICU_USE_TIM15 */

#if STM32_ICU_USE_TIM16
#if !defined(STM32_TIM16_HANDLER)
#error "STM32_TIM16_HANDLER not defined"
#endif
/**
 * @brief   TIM16 compare interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
CH_IRQ_HANDLER(STM32_TIM16_HANDLER) {

  CH_IRQ_PROLOGUE();

  icu_lld_serve_interrupt(&ICUD16);

  CH_IRQ_EPILOGUE();
}
#endif /* STM32_ICU_USE_TIM16 */

#if STM32_ICU_USE_TIM17
#if !defined(STM32_TIM17_HANDLER)
#error "STM32_TIM17_HANDLER not defined"
#endif
/**
 * @brief   TIM17 compare interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
CH_IRQ_HANDLER(STM32_TIM17_HANDLER) {

  CH_IRQ_PROLOGUE();

  icu_lld_serve_interrupt(&ICUD17);

  CH_IRQ_EPILOGUE();
}
#endif /* STM32_ICU_USE_TIM17 */

#if STM32_ICU_USE_TIM19
#if !defined(STM32_TIM19_HANDLER)
#error "STM32_TIM19_HANDLER not defined"
#endif
/**
 * @brief   TIM19 compare interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
CH_IRQ_HANDLER(STM32_TIM19_HANDLER) {

  CH_IRQ_PROLOGUE();

  icu_lld_serve_interrupt(&ICUD19);

  CH_IRQ_EPILOGUE();
}
#endif /* STM32_ICU_USE_TIM19 */

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level ICU driver initialization.
 *
 * @notapi
 */
void icu_lld_init(void) {

#if STM32_ICU_USE_TIM1
  /* Driver initialization.*/
  icuObjectInit(&ICUD1);
  ICUD1.tim = STM32_TIM1;
#endif

#if STM32_ICU_USE_TIM2
  /* Driver initialization.*/
  icuObjectInit(&ICUD2);
  ICUD2.tim = STM32_TIM2;
#endif

#if STM32_ICU_USE_TIM3
  /* Driver initialization.*/
  icuObjectInit(&ICUD3);
  ICUD3.tim = STM32_TIM3;
#endif

#if STM32_ICU_USE_TIM4
  /* Driver initialization.*/
  icuObjectInit(&ICUD4);
  ICUD4.tim = STM32_TIM4;
#endif

#if STM32_ICU_USE_TIM5
  /* Driver initialization.*/
  icuObjectInit(&ICUD5);
  ICUD5.tim = STM32_TIM5;
#endif

#if STM32_ICU_USE_TIM8
  /* Driver initialization.*/
  icuObjectInit(&ICUD8);
  ICUD8.tim = STM32_TIM8;
#endif

#if STM32_ICU_USE_TIM15
  /* Driver initialization.*/
  icuObjectInit(&ICUD15);
  ICUD15.tim = STM32_TIM15;
#endif

#if STM32_ICU_USE_TIM16
  /* Driver initialization.*/
  icuObjectInit(&ICUD16);
  ICUD16.tim = STM32_TIM16;
#endif

#if STM32_ICU_USE_TIM17
  /* Driver initialization.*/
  icuObjectInit(&ICUD17);
  ICUD17.tim = STM32_TIM17;
#endif

#if STM32_ICU_USE_TIM19
  /* Driver initialization.*/
  icuObjectInit(&ICUD19);
  ICUD19.tim = STM32_TIM19;
#endif
}

/**
 * @brief   Configures and activates the ICU peripheral.
 *
 * @param[in] icup      pointer to the @p ICUDriver object
 *
 * @notapi
 */
void icu_lld_start(ICUDriver *icup) {
  uint32_t psc;
  uint8_t single_channel = FALSE;
  chDbgAssert((icup->config->channel == ICU_CHANNEL_1) ||
              (icup->config->channel == ICU_CHANNEL_2),
              "icu_lld_start(), #1", "invalid input");

  if (icup->state == ICU_STOP) {
    /* Clock activation and timer reset.*/
#if STM32_ICU_USE_TIM1
    if (&ICUD1 == icup) {
      rccEnableTIM1(FALSE);
      rccResetTIM1();
      nvicEnableVector(STM32_TIM1_UP_NUMBER,
                       CORTEX_PRIORITY_MASK(STM32_ICU_TIM1_IRQ_PRIORITY));
      nvicEnableVector(STM32_TIM1_CC_NUMBER,
                       CORTEX_PRIORITY_MASK(STM32_ICU_TIM1_IRQ_PRIORITY));
      icup->clock = STM32_TIMCLK2;
    }
#endif
#if STM32_ICU_USE_TIM2
    if (&ICUD2 == icup) {
      rccEnableTIM2(FALSE);
      rccResetTIM2();
      nvicEnableVector(STM32_TIM2_NUMBER,
                       CORTEX_PRIORITY_MASK(STM32_ICU_TIM2_IRQ_PRIORITY));
      icup->clock = STM32_TIMCLK1;
    }
#endif
#if STM32_ICU_USE_TIM3
    if (&ICUD3 == icup) {
      rccEnableTIM3(FALSE);
      rccResetTIM3();
      nvicEnableVector(STM32_TIM3_NUMBER,
                       CORTEX_PRIORITY_MASK(STM32_ICU_TIM3_IRQ_PRIORITY));
      icup->clock = STM32_TIMCLK1;
    }
#endif
#if STM32_ICU_USE_TIM4
    if (&ICUD4 == icup) {
      rccEnableTIM4(FALSE);
      rccResetTIM4();
      nvicEnableVector(STM32_TIM4_NUMBER,
                       CORTEX_PRIORITY_MASK(STM32_ICU_TIM4_IRQ_PRIORITY));
      icup->clock = STM32_TIMCLK1;
    }
#endif

#if STM32_ICU_USE_TIM5
    if (&ICUD5 == icup) {
      rccEnableTIM5(FALSE);
      rccResetTIM5();
      nvicEnableVector(STM32_TIM5_NUMBER,
                       CORTEX_PRIORITY_MASK(STM32_ICU_TIM5_IRQ_PRIORITY));
      icup->clock = STM32_TIMCLK1;
    }
#endif

#if STM32_ICU_USE_TIM8
    if (&ICUD8 == icup) {
      rccEnableTIM8(FALSE);
      rccResetTIM8();
      nvicEnableVector(STM32_TIM8_UP_NUMBER,
                       CORTEX_PRIORITY_MASK(STM32_ICU_TIM8_IRQ_PRIORITY));
      nvicEnableVector(STM32_TIM8_CC_NUMBER,
                       CORTEX_PRIORITY_MASK(STM32_ICU_TIM8_IRQ_PRIORITY));
      icup->clock = STM32_TIMCLK2;
    }
#endif

#if STM32_ICU_USE_TIM15
    if (&ICUD15 == icup) {
      rccEnableTIM15(FALSE);
      rccResetTIM15();
      nvicEnableVector(STM32_TIM15_NUMBER,
                       CORTEX_PRIORITY_MASK(STM32_ICU_TIM15_IRQ_PRIORITY));
      icup->clock = STM32_TIMCLK1;
    }
#endif

#if STM32_ICU_USE_TIM16
    if (&ICUD16 == icup) {
      rccEnableTIM16(FALSE);
      rccResetTIM16();
      nvicEnableVector(STM32_TIM16_NUMBER,
                       CORTEX_PRIORITY_MASK(STM32_ICU_TIM16_IRQ_PRIORITY));
      icup->clock = STM32_TIMCLK1;
      single_channel = TRUE;
      chDbgAssert (icup->config->channel == ICU_CHANNEL_1, "icu_lld_start(), #1", "invalid channel for TIM16");
      chDbgAssert (icup->config->width_cb == NULL, "icu_lld_start(), #1", "Width callback not supported in TIM16");
    }
#endif

#if STM32_ICU_USE_TIM17
    if (&ICUD17 == icup) {
      rccEnableTIM17(FALSE);
      rccResetTIM17();
      nvicEnableVector(STM32_TIM17_NUMBER,
                       CORTEX_PRIORITY_MASK(STM32_ICU_TIM17_IRQ_PRIORITY));
      icup->clock = STM32_TIMCLK1;
      single_channel = TRUE;
      chDbgAssert (icup->config->channel == ICU_CHANNEL_1, "icu_lld_start(), #1", "invalid channel for TIM17");
      chDbgAssert (icup->config->width_cb == NULL, "icu_lld_start(), #1", "Width callback not supported in TIM17");
    }
#endif

#if STM32_ICU_USE_TIM19
    if (&ICUD19 == icup) {
      rccEnableTIM19(FALSE);
      rccResetTIM19();
      nvicEnableVector(STM32_TIM19_NUMBER,
                       CORTEX_PRIORITY_MASK(STM32_ICU_TIM19_IRQ_PRIORITY));
      icup->clock = STM32_TIMCLK1;
    }
#endif

  }
  else {
    /* Driver re-configuration scenario, it must be stopped first.*/
    icup->tim->CR1    = 0;                  /* Timer disabled.              */
    icup->tim->DIER   = 0;                  /* All IRQs disabled.           */
    icup->tim->SR     = 0;                  /* Clear eventual pending IRQs. */
    icup->tim->CCR[0] = 0;                  /* Comparator 1 disabled.       */
    icup->tim->CCR[1] = 0;                  /* Comparator 2 disabled.       */
    icup->tim->CNT    = 0;                  /* Counter reset to zero.       */
  }

  /* Timer configuration.*/
  psc = (icup->clock / icup->config->frequency) - 1;
  chDbgAssert((psc <= 0xFFFF) &&
              ((psc + 1) * icup->config->frequency) == icup->clock,
              "icu_lld_start(), #1", "invalid frequency");
  icup->tim->PSC  = (uint16_t)psc;
  icup->tim->ARR   = 0xFFFF;
  if (single_channel) {
      /* Selected input 1.
         CCMR1_CC1S = 01 = CH1 Input on TI1.*/
      icup->tim->CCMR1 = TIM_CCMR1_CC1S_0;
      /* The CCER settings depend on the selected trigger mode.
         ICU_INPUT_ACTIVE_HIGH: Active on rising edge, idle on falling edge.
         ICU_INPUT_ACTIVE_LOW:  Active on falling edge, idle on rising edge.*/
      if (icup->config->mode == ICU_INPUT_ACTIVE_HIGH)
        icup->tim->CCER = TIM_CCER_CC1E;
      else
        icup->tim->CCER = TIM_CCER_CC1E | TIM_CCER_CC1P;
      /* Direct pointers to the capture registers in order to make reading
         data faster from within callbacks.*/
      icup->wccrp = NULL;
      icup->pccrp = &icup->tim->CCR[0];
  } else  if (icup->config->channel == ICU_CHANNEL_1) {
    /* Selected input 1.
       CCMR1_CC1S = 01 = CH1 Input on TI1.
       CCMR1_CC2S = 10 = CH2 Input on TI1.*/
    icup->tim->CCMR1 = TIM_CCMR1_CC1S_0 |
                       TIM_CCMR1_CC2S_1;
    /* SMCR_TS  = 101, input is TI1FP1.
       SMCR_SMS = 100, reset on rising edge.*/
    icup->tim->SMCR  = TIM_SMCR_TS_2 | TIM_SMCR_TS_0 |
                       TIM_SMCR_SMS_2;
    /* The CCER settings depend on the selected trigger mode.
       ICU_INPUT_ACTIVE_HIGH: Active on rising edge, idle on falling edge.
       ICU_INPUT_ACTIVE_LOW:  Active on falling edge, idle on rising edge.*/
    if (icup->config->mode == ICU_INPUT_ACTIVE_HIGH)
      icup->tim->CCER = TIM_CCER_CC1E |
                        TIM_CCER_CC2E | TIM_CCER_CC2P;
    else
      icup->tim->CCER = TIM_CCER_CC1E | TIM_CCER_CC1P |
                        TIM_CCER_CC2E;
    /* Direct pointers to the capture registers in order to make reading
       data faster from within callbacks.*/
    icup->wccrp = &icup->tim->CCR[1];
    icup->pccrp = &icup->tim->CCR[0];
  } else {
    /* Selected input 2.
       CCMR1_CC1S = 10 = CH1 Input on TI2.
       CCMR1_CC2S = 01 = CH2 Input on TI2.*/
    icup->tim->CCMR1 = TIM_CCMR1_CC1S_1 |
                       TIM_CCMR1_CC2S_0;
    /* SMCR_TS  = 110, input is TI2FP2.
       SMCR_SMS = 100, reset on rising edge.*/
    icup->tim->SMCR  = TIM_SMCR_TS_2 | TIM_SMCR_TS_1 |
                       TIM_SMCR_SMS_2;
    /* The CCER settings depend on the selected trigger mode.
       ICU_INPUT_ACTIVE_HIGH: Active on rising edge, idle on falling edge.
       ICU_INPUT_ACTIVE_LOW:  Active on falling edge, idle on rising edge.*/
    if (icup->config->mode == ICU_INPUT_ACTIVE_HIGH)
      icup->tim->CCER = TIM_CCER_CC1E | TIM_CCER_CC1P |
                        TIM_CCER_CC2E;
    else
      icup->tim->CCER = TIM_CCER_CC1E |
                        TIM_CCER_CC2E | TIM_CCER_CC2P;
    /* Direct pointers to the capture registers in order to make reading
       data faster from within callbacks.*/
    icup->wccrp = &icup->tim->CCR[0];
    icup->pccrp = &icup->tim->CCR[1];
  }
}

/**
 * @brief   Deactivates the ICU peripheral.
 *
 * @param[in] icup      pointer to the @p ICUDriver object
 *
 * @notapi
 */
void icu_lld_stop(ICUDriver *icup) {

  if (icup->state == ICU_READY) {
    /* Clock deactivation.*/
    icup->tim->CR1  = 0;                    /* Timer disabled.              */
    icup->tim->DIER = 0;                    /* All IRQs disabled.           */
    icup->tim->SR   = 0;                    /* Clear eventual pending IRQs. */

#if STM32_ICU_USE_TIM1
    if (&ICUD1 == icup) {
      nvicDisableVector(STM32_TIM1_UP_NUMBER);
      nvicDisableVector(STM32_TIM1_CC_NUMBER);
      rccDisableTIM1(FALSE);
    }
#endif
#if STM32_ICU_USE_TIM2
    if (&ICUD2 == icup) {
      nvicDisableVector(STM32_TIM2_NUMBER);
      rccDisableTIM2(FALSE);
    }
#endif
#if STM32_ICU_USE_TIM3
    if (&ICUD3 == icup) {
      nvicDisableVector(STM32_TIM3_NUMBER);
      rccDisableTIM3(FALSE);
    }
#endif
#if STM32_ICU_USE_TIM4
    if (&ICUD4 == icup) {
      nvicDisableVector(STM32_TIM4_NUMBER);
      rccDisableTIM4(FALSE);
    }
#endif
#if STM32_ICU_USE_TIM5
    if (&ICUD5 == icup) {
      nvicDisableVector(STM32_TIM5_NUMBER);
      rccDisableTIM5(FALSE);
    }
#endif
#if STM32_ICU_USE_TIM8
    if (&ICUD8 == icup) {
      nvicDisableVector(STM32_TIM8_UP_NUMBER);
      nvicDisableVector(STM32_TIM8_CC_NUMBER);
      rccDisableTIM8(FALSE);
    }
#endif
#if STM32_ICU_USE_TIM15
    if (&ICUD15 == icup) {
      nvicDisableVector(STM32_TIM15_NUMBER);
      rccDisableTIM15(FALSE);
    }
#endif
    #if STM32_ICU_USE_TIM16
    if (&ICUD16 == icup) {
      nvicDisableVector(STM32_TIM16_NUMBER);
      rccDisableTIM16(FALSE);
    }
#endif
#if STM32_ICU_USE_TIM17
    if (&ICUD17 == icup) {
      nvicDisableVector(STM32_TIM17_NUMBER);
      rccDisableTIM17(FALSE);
    }
#endif
#if STM32_ICU_USE_TIM19
    if (&ICUD19 == icup) {
      nvicDisableVector(STM32_TIM19_NUMBER);
      rccDisableTIM19(FALSE);
    }
#endif
  }
}

/**
 * @brief   Enables the input capture.
 *
 * @param[in] icup      pointer to the @p ICUDriver object
 *
 * @notapi
 */
void icu_lld_enable(ICUDriver *icup) {

  icup->tim->SR = 0;                        /* Clear pending IRQs (if any). */
  if (icup->config->channel == ICU_CHANNEL_1) {
    if (icup->config->period_cb != NULL)
      icup->tim->DIER |= TIM_DIER_CC1IE;
    if (icup->config->width_cb != NULL)
      icup->tim->DIER |= TIM_DIER_CC2IE;
  } else {
    if (icup->config->width_cb != NULL)
      icup->tim->DIER |= TIM_DIER_CC1IE;
    if (icup->config->period_cb != NULL)
      icup->tim->DIER |= TIM_DIER_CC2IE;
  }
  if (icup->config->overflow_cb != NULL)
    icup->tim->DIER |= TIM_DIER_UIE;
  icup->tim->CR1  = TIM_CR1_URS | TIM_CR1_CEN;
}

/**
 * @brief   Disables the input capture.
 *
 * @param[in] icup      pointer to the @p ICUDriver object
 *
 * @notapi
 */
void icu_lld_disable(ICUDriver *icup) {

  icup->tim->CR1  = 0;                      /* Initially stopped.           */
  icup->tim->SR   = 0;                      /* Clear pending IRQs (if any). */
  icup->tim->DIER = 0;                      /* Interrupts disabled.         */
}

#endif /* HAL_USE_ICU */

/** @} */
