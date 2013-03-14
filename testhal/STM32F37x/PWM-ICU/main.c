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

#if 0
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
  ICU_CHANNEL_1
};
#endif

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

  //  rccEnableGPIOAEN(); /* for ECG PE12, TempSense PE7 */
  rccEnableGPIOCEN(); /* for ECG PE12, TempSense PE7 */

  // re-program GPIOC_SPI3_SCK to be used for TIM19_CH1 PWM output
  //
  GPIOC->AFRH &= ~(0xf << 8); // clear alternate function for PC10
  GPIOC->AFRH |= (2 << 8);   // set alternate function to AF2 ( TIM19_CH1 )

  palSetPad(GPIOC, GPIOC_LED3);
  /*
   * Normal main() thread activity, in this demo it does nothing.
   */
    /*
     * LED initially off.
     */
    palSetPad(GPIOC, GPIOC_LED2);

    /*
     * Initializes the PWM driver 1 and ICU driver 4.
     */
    pwmStart(&PWMD19, &pwmcfg);
    //  palSetPadMode(IOPORT1, 8, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    //  icuStart(&ICUD4, &icucfg);
    //  icuEnable(&ICUD4);
    chThdSleepMilliseconds(2000);

    /*
     * Starts the PWM channel 0 using 75% duty cycle.
     */
    pwmEnableChannel(&PWMD19, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD19, 7500));
#if 0
    chThdSleepMilliseconds(5000);


    /*
     * Changes the PWM channel 0 to 50% duty cycle.
     */
    pwmEnableChannel(&PWMD19, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD19, 5000));
    chThdSleepMilliseconds(5000);

    /*
     * Changes the PWM channel 0 to 25% duty cycle.
     */
    pwmEnableChannel(&PWMD19, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD19, 2500));
    chThdSleepMilliseconds(5000);

    /*
     * Changes PWM period to half second the duty cycle becomes 50%
     * implicitly.
     */
    pwmChangePeriod(&PWMD19, 5000);
    chThdSleepMilliseconds(5000);

    /*
     * Disables channel 0 and stops the drivers.
     */
    pwmDisableChannel(&PWMD19, 0);
    pwmStop(&PWMD19);
    //  icuDisable(&ICUD4);
    //  icuStop(&ICUD4);
    palClearPad(GPIOC, GPIOC_LED2);
#endif
  while (TRUE) {

    chThdSleepMilliseconds(500);
  }

  return 0;
}
