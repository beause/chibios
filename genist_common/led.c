#include "ch.h"
#include "hal.h"
#include "led.h"
#include "threads.h"

DECLARE_THREAD(ThreadBlinker, NORMALPRIO, 128)

/**
 * Set LED color
 * @param color
 */
void setLEDColor(uint8_t color)
{
    if (color & LED_RED)
    {
        palClearPad(GPIOC, GPIOC_LED_R);
    }
    else
    {
        palSetPad(GPIOC, GPIOC_LED_R);
    }

    if (color & LED_GREEN)
    {
        palClearPad(GPIOC, GPIOC_LED_G);
    }
    else
    {
        palSetPad(GPIOC, GPIOC_LED_G);
    }

    if (color & LED_BLUE)
    {
        palClearPad(GPIOC, GPIOC_LED_B);
    }
    else
    {
        palSetPad(GPIOC, GPIOC_LED_B);
    }
}

static msg_t ThreadBlinker(void *arg)
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
}

