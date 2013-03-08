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
#include "tempsense.h"

/*
 * This is a periodic thread that does absolutely nothing except flashing LEDs.
 */
static WORKING_AREA(waThread1, 128);
static WORKING_AREA(waThread2, 1024);

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

static msg_t TakeTempThread(void *arg) {

  chRegSetThreadName("taketemp");

  takeTemp();

  return 0;
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

  rccEnableGPIOEEN(); /* for ECG PE12, TempSense PE7 */
  rccEnableUSART2(DUMMY_NOT_USED);

  sdStart(&SD2, NULL);

  /*
   * Creates the example thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, TakeTempThread, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state, when the button is
   * pressed the test procedure is launched.
   */

  /* set console output destination */
  setStreamDest(&SD2);
  //  test_print("board up!!!\r\n");

  while (TRUE) {
    chThdSleepMilliseconds(1000);
  }
}
