/**
 * db.c
 * Database access.
 * The items here will be stored in Flash as part of the configuration. For now
 * the values are hardcoded.
 *
 *  Created on: 2013-04-30
 *      Author: jeromeg
 */
#include "db.h"
#define WHEEL_DIAMETER_M   0.4  /* Wheel diameter in meters */
#define PULSES_PER_ROTATION 16  /* Pulses per rotation of the wheel */

/**
 * Calculates the number of meters traveled per pulse.
 * @return
 */
float dbGetWheelScaleFactor(void)
{
    return 2 * PI * WHEEL_DIAMETER_M / PULSES_PER_ROTATION;
}

/**
 * Get the threshold between high and low pressure
 * @return
 */
int dbGetPressureUpperThreshold(void)
{
    return 10100;
}

/**
 * Get the threshold between high and low pressure
 * @return
 */
int dbGetPressureLowerThreshold(void)
{
    return 10100;
}

/**
 * Get the high speed upper threshold. High Speed condition is declared when
 * the speed is above this threshold.
 * @return
 */
int dbGetHighSpeedUpperThreshold(void)
{
    return 40000;
}

/**
 * Get the high speed lower threshold. High Speed condition is exited when the
 * speed is below this threshold.
 * @return
 */
int dbGetHighSpeedLowerThreshold(void)
{
    return 35000;
}

int dbGetLowSpeedUpperThreshold(void)
{
    return 0;
}

int dbGetLowSpeedLowerThreshold(void)
{
    return 0;
}

int dbGetStoppedUpperThreshold(void)
{
    return 0;
}

int dbGetStoppedLowerThreshold(void)
{
    return 0;
}
