/*
    Copyright (C) 2013 Genist
*/

#include "ch.h"
#include "hal.h"
#include "test.h"
#include "tempsense.h"

/*
 * This is a periodic thread that does absolutely nothing except flashing LEDs.
 */
static WORKING_AREA(waThread1, 128);
static WORKING_AREA(waThread2, 128);

static msg_t Thread1(void *arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (TRUE) {
    palSetPad(GPIOC, GPIOC_LED_G);
    chThdSleepMilliseconds(125);
    palClearPad(GPIOC, GPIOC_LED_G);

    palSetPad(GPIOC, GPIOC_LED_B);
    chThdSleepMilliseconds(125);
    palClearPad(GPIOC, GPIOC_LED_B);

    palSetPad(GPIOC, GPIOC_LED_R);
    chThdSleepMilliseconds(125);
    palClearPad(GPIOC, GPIOC_LED_R);
  }
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

  rccEnableGPIOAEN(); /* for SPI2 (pressure sense) */
  rccEnableGPIOCEN(); /* for LEDs / SPI3 (zigbee) */

#if 0
  rccEnableUSART2(DUMMY_NOT_USED);

  sdStart(&SD2, NULL);
  /* set console output destination */
  setStreamDest(&SD2);
#endif
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

  test_print("board up!!!\r\n");

  while (TRUE) {
    chThdSleepMilliseconds(1000);
  }
}
