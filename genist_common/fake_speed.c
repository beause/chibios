/**
 * fake_speed.c
 * Fake a speed sensor using a timer resource.
 *
 * A fake quadrature encoded signal is created using TIM3. Channels 2 and 4
 * are looped back or connected to another board externally to the speed sensor
 * input pins.
 *  Created on: 2013-04-29
 *      Author: jeromeg
 */

#include "ch.h"
#include "hal.h"
#include "itmstream.h"
#include "db.h"

#define PWM_FREQ_HIGH   25000
#define PWM_FREQ_LOW    1200

static PWMConfig FakeSpeedConfig = {
        .frequency = PWM_FREQ_HIGH,
        .period = 100,
        .callback = NULL,
        .channels = {
                {
                        .mode = PWM_OUTPUT_ACTIVE_HIGH,
                        .callback = NULL,
                },
                {
                        .mode = PWM_OUTPUT_ACTIVE_HIGH,
                        .callback = NULL,
                },
                {
                        .mode = PWM_OUTPUT_ACTIVE_HIGH,
                        .callback = NULL,
                },
                {
                        .mode = PWM_OUTPUT_ACTIVE_LOW,
                        .callback = NULL,
                },
        },
        .cr2 = 0
};

/**
 * Create waveform
 * @param arg
 */
void startFakeSpeed(void)
{
    pwmStart(&PWMD3, &FakeSpeedConfig);
    pwmEnableChannel(&PWMD3, 1, 50);
    pwmEnableChannel(&PWMD3, 3, 55);
    itmprintf("Fake Speed Sensor started!\n");
}

void setFakeSpeed(int speed)
{
    uint32_t ticks;
    float f = (float) abs(speed) / dbGetWheelScaleFactor() / SEC_PER_HOUR;
    ticks = (FakeSpeedConfig.frequency / f);

    if (ticks > 65535)
    {
        /* Switch to low gear */
        itmprintf("Fake Speed Low Gear\n");
        pwmDisableChannel(&PWMD3, 1);
        pwmDisableChannel(&PWMD3, 3);
        pwmStop(&PWMD3);
        FakeSpeedConfig.frequency = PWM_FREQ_LOW;
        pwmStart(&PWMD3, &FakeSpeedConfig);
        ticks = (FakeSpeedConfig.frequency / f);
    }
    else if (FakeSpeedConfig.frequency == PWM_FREQ_LOW)
    {
        /* Switch to high gear */
        itmprintf("Fake Speed High Gear\n");
        pwmDisableChannel(&PWMD3, 1);
        pwmDisableChannel(&PWMD3, 3);
        pwmStop(&PWMD3);
        FakeSpeedConfig.frequency = PWM_FREQ_HIGH;
        pwmStart(&PWMD3, &FakeSpeedConfig);
        ticks = (FakeSpeedConfig.frequency / f);
    }
    pwmChangePeriod(&PWMD3, (pwmcnt_t)ticks);
    pwmEnableChannel(&PWMD3, 1, (pwmcnt_t)ticks / 2);
    if (speed > 0)
    {
        pwmEnableChannel(&PWMD3, 3, (pwmcnt_t)ticks / 2 - (pwmcnt_t)ticks / 4);
    }
    else if (speed < 0)
    {
        pwmEnableChannel(&PWMD3, 3, (pwmcnt_t)ticks / 2 + (pwmcnt_t)ticks / 4);
    }
    else
    {
        pwmDisableChannel(&PWMD3, 1);
        pwmDisableChannel(&PWMD3, 3);
    }


}
