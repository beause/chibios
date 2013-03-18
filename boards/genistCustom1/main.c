/*
    Copyright (C) 2013 Genist
*/

#include "ch.h"
#include "hal.h"
#include "test.h"
#include "ms5803.h"
#include "rtd.h"

#define RTD /* activate RTD thread */

/*
 * This is a periodic thread that does absolutely nothing except flashing LEDs.
 */
static WORKING_AREA(waThread1, 128);
static WORKING_AREA(waThread2, 128);
static WORKING_AREA(waThread3, 128);
static WORKING_AREA(waThread4, 128);

static msg_t Thread1(void *arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (TRUE) {
    switchLED(GPIOC,GPIOC_LED_B, TRUE);
    chThdSleepMilliseconds(125);
    switchLED(GPIOC,GPIOC_LED_B, FALSE);

    switchLED(GPIOC,GPIOC_LED_G, TRUE);
    chThdSleepMilliseconds(125);
    switchLED(GPIOC,GPIOC_LED_G, FALSE);

    switchLED(GPIOC,GPIOC_LED_R, TRUE);
    chThdSleepMilliseconds(125);
    switchLED(GPIOC,GPIOC_LED_R, FALSE);

  }
  return 0;
}

static msg_t ThreadPressureSense(void *arg) {

  chRegSetThreadName("ms5803");
  testMS5803();

  while (TRUE) {  
    chThdSleepMilliseconds(1000);
  }
  return 0;
}

static msg_t ThreadRTD(void *arg) {

  chRegSetThreadName("rtd");
  testRTD();

  while (TRUE) {  
    chThdSleepMilliseconds(1000);
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

#ifdef BLINKER
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
#endif
#ifdef MS5803
  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, ThreadPressureSense, NULL);
#endif
#ifdef RTD
  chThdCreateStatic(waThread3, sizeof(waThread3), NORMALPRIO, ThreadRTD, NULL);
  //  chThdCreateStatic(waThread4, sizeof(waThread3), NORMALPRIO, printADCOutputThread, NULL);
#endif

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state, when the button is
   * pressed the test procedure is launched.
   */

  while (TRUE) {
    chThdSleepMilliseconds(1000);
  }
}

