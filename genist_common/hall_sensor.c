/**
 * Copyright 2013 Genist Systems Inc.
 * hall_sensor.c
 *
 * This module interprets the quadrature encoded signals from the Hall sensor
 * inputs. These functions are only called if the Hall sensor is actually
 * selected as the speed sensor.
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
#define MAX_DIRECTION   5
static void HallSpeedPeriodCB(ICUDriver *icup);
static void HallSpeedOverflowCB(ICUDriver *icup);

/* Average out samples */
static uint32_t sampleArray[NUM_SAMPLES];
static uint32_t sampleIndex;
static uint32_t sampleSum;
static uint8_t sampleOver;
static int8_t direction;

const ICUConfig HallSpeedSensorConfig = {
        .mode = ICU_INPUT_ACTIVE_HIGH,
        .frequency = HALL_FREQUENCY,
        .width_cb = NULL,
        .period_cb = HallSpeedPeriodCB,
        .overflow_cb = HallSpeedOverflowCB,
        .channel = ICU_CHANNEL_2
};

/**
 * Callback from ICU driver when the next edge is detected. A running average
 * over the last NUM_SAMPLES samples is calculated.
 * @param icup
 */
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
    if (palReadPad(GPIOC, GPIOC_TEST_SPEED1_IN))
    {
        direction++;
        if (!direction)
        {
            /* don't allow zero */
            direction = 1;
        }
        if (direction > MAX_DIRECTION)
        {
            direction = MAX_DIRECTION;
        }
    }
    else
    {
        direction--;
        if (!direction)
        {
            /* don't allow zero */
            direction = -1;
        }
        if (direction < -MAX_DIRECTION)
        {
            direction = -MAX_DIRECTION;
        }
    }


}

/**
 * Callback from ICU driver when the next edge has not occurred before the
 * timer overflows. A count of overflows is used to add the accumulated count
 * when the edge eventually comes. If the edge is way off or never arrives,
 * the it is assumed that the rotation has stopped as indicated by a very long
 * period
 * @param icup
 */
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
int32_t getHallSpeedValue(void)
{
    float val;
    int8_t dir;
    chSysLock();
    val = dbGetWheelScaleFactor() * HALL_FREQUENCY * SEC_PER_HOUR
            * NUM_SAMPLES / (float) sampleSum;
    dir = direction;
    chSysUnlock();
    if (!dir)
    {
        val = -val;
    }
    return (int32_t) val;
}

/**
 * Initialize Hall Speed sensor
 */
void initHallSpeed(void)
{
    sampleOver = 0;
    chRegSetThreadName("HallSpeed");
    memset (sampleArray, 0, sizeof(sampleArray));
    sampleIndex = 0;
    sampleSum = 0;
    direction = MAX_DIRECTION;
    icuStart(&HALL_SENSOR, &HallSpeedSensorConfig);
    icuEnable(&HALL_SENSOR);
}

