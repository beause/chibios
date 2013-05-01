/**
 * hall_sensor.c
 *
 * This module interprets the quadrature encoded signals from the Hall sensor
 * inputs.
 *  Created on: 2013-04-29
 *      Author: jeromeg
 */

#include <string.h>
#include "ch.h"
#include "hal.h"
#include "db.h"
#include "itmstream.h"
#include "threads.h"

#define HALL_SENSOR     ICUD19
#define NUM_SAMPLES     8
#define FULL_SCALE      65536
#define HALL_FREQUENCY  100000

static void HallSpeedPeriodCB(ICUDriver *icup);
static void HallSpeedOverflowCB(ICUDriver *icup);
static int32_t HallSpeed;
/* Average out samples */
static uint32_t sampleArray[NUM_SAMPLES];
static uint32_t sampleIndex;
static uint32_t sampleSum;
static uint8_t sampleOver;
static uint8_t direction;

DECLARE_THREAD(ThreadHallSpeed, NORMALPRIO, 1024)

const ICUConfig HallSpeedSensorConfig = {
        .mode = ICU_INPUT_ACTIVE_HIGH,
        .frequency = HALL_FREQUENCY,
        .width_cb = NULL,
        .period_cb = HallSpeedPeriodCB,
        .overflow_cb = HallSpeedOverflowCB,
        .channel = ICU_CHANNEL_2
};

static void HallSpeedPeriodCB(ICUDriver *icup)
{
    uint32_t oldSample;
    (void) icup;
    /* Remove oldest sample and replace it with new reading. */
    oldSample = sampleArray[sampleIndex];
    sampleArray[sampleIndex] = sampleOver * FULL_SCALE + icuGetPeriod(icup);
    sampleSum += sampleArray[sampleIndex] - oldSample;
    sampleIndex = (sampleIndex + 1) % NUM_SAMPLES;
    sampleOver = 0;
    direction = palReadPad(GPIOC, GPIOC_TEST_SPEED1_IN);


}

static void HallSpeedOverflowCB(ICUDriver *icup)
{
    uint32_t oldSample;
    (void) icup;
    /* Accumulate number of overflow events. */
    sampleOver++;
    if (sampleOver >= NUM_SAMPLES)
    {
        /* If no edge has been seen for a while, put in a large reading. */
        oldSample = sampleArray[sampleIndex];
        sampleArray[sampleIndex] = sampleOver * FULL_SCALE;
        sampleSum += sampleArray[sampleIndex] - oldSample;
        sampleIndex = (sampleIndex + 1) % NUM_SAMPLES;
        sampleOver = 0;
    }
}

/**
 * Get Hall speed value. This is an average of the last NUM_SAMPLES samples.
 * @return speed in meters per hour.
 */
float getHallSpeedValue(void)
{
    float val;
    uint8_t dir;
    port_disable();
    val = dbGetWheelScaleFactor() * HALL_FREQUENCY * SEC_PER_HOUR
            * NUM_SAMPLES / (float) sampleSum;
    dir = direction;
    port_enable();
    if (!dir)
    {
        val = -val;
    }
    //itmprintf("Sample avg: %d\n", sampleSum / NUM_SAMPLES);
    return val;
}

static msg_t ThreadHallSpeed(void *arg)
{
    uint32_t i;
    (void) arg;
    sampleOver = 0;
    chRegSetThreadName("HallSpeed");
    memset (sampleArray, 0, sizeof(sampleArray));
/*
    for (i = 0; i < NUM_SAMPLES; i++)
    {
        sampleArray[i] = 0;
    }
*/
    sampleIndex = 0;
    sampleSum = 0;
    icuStart(&HALL_SENSOR, &HallSpeedSensorConfig);
    icuEnable(&HALL_SENSOR);
    while (1)
    {
        HallSpeed = (int32_t) getHallSpeedValue();
        chThdSleepMilliseconds(1000);
    }
    return 0;
}

int32_t ReadSpeed(void)
{
    return HallSpeed;
}
