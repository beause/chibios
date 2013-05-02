/*
 Copyright (C) 2013 Genist
 */

#include "ch.h"
#include "hal.h"
#include "test.h"
#include "ms5803.h"
#include "rtd.h"
#include "led.h"
#include "itmstream.h"
#include "fake.h"
#include "threadlist.h"
#include "inputs.h"
#include "statemachine.h"
#define RTD
#define BLINKER
//#define MS5803
/*
 * This is a periodic thread that does absolutely nothing except flashing LEDs.
 */
//static WORKING_AREA(waThread1, 128);
//static WORKING_AREA(waThreadPressureSensor, 512);
//static WORKING_AREA(waThread3, 128);
//static WORKING_AREA(waThread4, 128);

/*static msg_t Thread1(void *arg)
{
    (void) arg;
    chRegSetThreadName("blinker");
    while (TRUE)
    {
        setLEDColor(LED_RED);
        chThdSleepMilliseconds(125);
        setLEDColor(LED_GREEN);
        chThdSleepMilliseconds(125);
        setLEDColor(LED_BLUE);
        chThdSleepMilliseconds(125);
    }
    return 0;
}*/

/*static msg_t ThreadPressureSense(void *arg)
{
    int64_t pressure, temp;

    chRegSetThreadName("ms5803");

    while (TRUE)
    {
        ms5803_readPressureAndTemp(&pressure, &temp);
        itmprintf("Temp: %d Pressure: %d\n", (int )temp, (int )pressure);
        chThdSleepMilliseconds(1000);
    }
    return 0;
}*/

/*
static msg_t ThreadRTD(void *arg)
{

    chRegSetThreadName("rtd");
    testRTD();

    while (TRUE)
    {
        chThdSleepMilliseconds(1000);
    }
    return 0;
}
*/

/*
 * Application entry point.
 */
int main(void)
{
    int speed;
    /*
     * System initializations.
     * - HAL initialization, this also initializes the configured device drivers
     *   and performs the board-specific initializations.
     * - Kernel initialization, the main() function becomes a thread and the
     *   RTOS is active.
     */
    halInit();
    chSysInit();
    StateMachineMailboxInit();
    startThreadStateMachine();
    startThreadSpeed();
    startThreadBlinker();
    startThreadPressureSensor();
    //startThreadMonitor();
    //startThreadRTD();
    startFakeSpeed();
    /*
     * Normal main() thread activity, in this demo it does nothing except
     * sleeping in a loop and check the button state, when the button is
     * pressed the test procedure is launched.
     */
    itmprintf("Hello there!\n");
    while (TRUE)
    {
/*
        for (speed = 10000; speed < 200000; speed += 10000)
        {
            setFakeSpeed(speed);
            chThdSleepMilliseconds(5000);
        }
*/
        for (speed = 20000; speed > -20000; speed -= 1000)
        {
            setFakeSpeed(speed);
            itmprintf("Fake speed: %d\n", speed);
#if 0
            for (i = 0; i < 20; i++)
            {
                itmprintf("Temp: %d\n", ReadAirTemp());
                itmprintf("Pressure: %d\n", ReadPressure());
                itmprintf("Speed: %d\n", ReadSpeed());
                chThdSleepMilliseconds(2000);
            }
#else
            chThdSleepMilliseconds(10000);
#endif
        }
    }
}

