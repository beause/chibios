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

static void pwmpcb(PWMDriver *pwmp) {

  (void)pwmp;
  palSetPad(GPIOC, GPIOC_LED1);
}

static void pwmc1cb(PWMDriver *pwmp) {

  (void)pwmp;
  palClearPad(GPIOC, GPIOC_LED1);
}

static PWMConfig pwmcfg = {
  10000,                                    /* 10kHz PWM clock frequency.   */
  10000,                                    /* Initial PWM period 1S.       */
  pwmpcb,
  {
   {PWM_OUTPUT_ACTIVE_HIGH, pwmc1cb},
   {PWM_OUTPUT_DISABLED, NULL},
   {PWM_OUTPUT_DISABLED, NULL},
   {PWM_OUTPUT_DISABLED, NULL}
  },
  0,
#if STM32_PWM_USE_ADVANCED
  0
#endif
};

icucnt_t last_width, last_period;

static void icuwidthcb(ICUDriver *icup) {

  last_width = icuGetWidth(icup);
}

static void icuperiodcb(ICUDriver *icup) {

  last_period = icuGetPeriod(icup);
}

static ICUConfig icucfg = {
  ICU_INPUT_ACTIVE_HIGH,
  10000,                                    /* 10kHz ICU clock frequency.   */
  icuwidthcb,
  icuperiodcb,
  NULL,
  ICU_CHANNEL_2
};

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

  PWMDriver* pwmd = NULL;

  // re-program GPIOC_SPI3_SCK to be used for TIM19_CH1 PWM output
  //
  GPIOC->AFRH &= ~(0xf << 8); // clear alternate function for PC10
  GPIOC->AFRH |= (2 << 8);   // set alternate function to AF2 ( TIM19_CH1 )

  // re-program GPIOC_PIN7 to be used for TIM3_CH2 PWM input
  //
  GPIOC->MODER &= ~(0x3 << 14); // clear mode for PC7
  GPIOC->MODER |=  (  2 << 14); // set mode to alternate for PC7

  GPIOC->AFRL &= ~(0xf << 28); // clear alternate function for PC7
  GPIOC->AFRL |=  (  2 << 28); // set alternate function to PC7 ( TIM3_CH2 )

  pwmd = &PWMD19;

  palSetPad(GPIOC, GPIOC_LED3);
  /*
   * Normal main() thread activity, in this demo it does nothing.
   */
  /*
   * LED initially off.
   */
  palSetPad(GPIOC, GPIOC_LED2);

  /*
   * Initializes the PWM driver 19 and ICU driver 3.
   */
  pwmStart(pwmd, &pwmcfg);
  icuStart(&ICUD3, &icucfg);
  icuEnable(&ICUD3);
  chThdSleepMilliseconds(2000);

  /*
   * Starts the PWM channel 0 using 75% duty cycle.
   */
  pwmEnableChannel(pwmd, 0, PWM_PERCENTAGE_TO_WIDTH(pwmd, 7500));
  chThdSleepMilliseconds(5000);


  /*
   * Changes the PWM channel 0 to 50% duty cycle.
   */
  pwmEnableChannel(pwmd, 0, PWM_PERCENTAGE_TO_WIDTH(pwmd, 5000));
  chThdSleepMilliseconds(5000);

  /*
   * Changes the PWM channel 0 to 25% duty cycle.
   */
  pwmEnableChannel(pwmd, 0, PWM_PERCENTAGE_TO_WIDTH(pwmd, 2500));
  chThdSleepMilliseconds(5000);

  /*
   * Changes PWM period to half second the duty cycle becomes 50%
   * implicitly.
   */
  pwmChangePeriod(pwmd, 5000);
  chThdSleepMilliseconds(5000);

  /*
   * Disables channel 0 and stops the drivers.
   */
  pwmDisableChannel(pwmd, 0);
  pwmStop(pwmd);
  icuDisable(&ICUD3);
  icuStop(&ICUD3);
  palClearPad(GPIOC, GPIOC_LED2);

  /*
    last_width should be 2500
    last_period  should be 5000
  */

  while (TRUE) {

    chThdSleepMilliseconds(500);
  }

  return 0;
}
