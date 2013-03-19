/*
    Copyright (C) 2013 Genist
*/

#ifndef _MS5803_H_
#define _MS5803_H_



#define MS5803_CMD_RESET              0x1e
#define MS5803_CMD_CONVERTD1_OSR256   0x40
#define MS5803_CMD_CONVERTD1_OSR512   0x42
#define MS5803_CMD_CONVERTD1_OSR1024  0x44
#define MS5803_CMD_CONVERTD1_OSR2048  0x46
#define MS5803_CMD_CONVERTD1_OSR4096  0x48
#define MS5803_CMD_CONVERTD2_OSR256   0x50
#define MS5803_CMD_CONVERTD2_OSR512   0x52
#define MS5803_CMD_CONVERTD2_OSR1024  0x54
#define MS5803_CMD_CONVERTD2_OSR2048  0x56
#define MS5803_CMD_CONVERTD2_OSR4096  0x58
#define MS5803_CMD_ADC_READ           0x0
#define MS5803_CMD_PROM_READ(n) (0xa0 | ((n & 7) << 1))

#define MS5803_CMD_RESET_WAIT_MILLISEC   3 /* actually 2.8ms */
#define MS5803_CMD_CONVERT_WAIT_MILLISEC 10 /* actually 8.22ms */
#define MS5803_NUM_PROM_VALS_START_IDX   0
#define MS5803_NUM_PROM_VALS             8 /* 8 16 bit values */
#define MS5803_NUM_COEFF                 6

extern bool_t ms5803_resetAndReadCoefficients();
extern float ms5803_readPressure();

#endif /* _MS5803_H_ */
