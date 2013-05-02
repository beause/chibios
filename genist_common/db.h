/**
 * db.h
 *
 *  Created on: 2013-04-30
 *      Author: jeromeg
 */
#include "ch.h"

#ifndef DB_H_
#define DB_H_
#define PI ((float) 3.14159)
#define SEC_PER_HOUR 3600

float dbGetWheelScaleFactor(void);
int32_t dbGetPressureUpperThreshold(void);
int32_t dbGetPressureLowerThreshold(void);
int32_t dbGetHighSpeedUpperThreshold(void);
int32_t dbGetHighSpeedLowerThreshold(void);
int32_t dbGetLowSpeedUpperThreshold(void);
int32_t dbGetLowSpeedLowerThreshold(void);
int32_t dbGetReversedUpperThreshold(void);
int32_t dbGetReversedLowerThreshold(void);
int8_t dbGetSensorIndex(void);
#endif /* DB_H_ */
