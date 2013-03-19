/*
    Copyright (C) 2013 Genist
*/

#include "ch.h"
#include "hal.h"
#include "test.h"
#include "ms5803.h"
#include "led.h"

/***
 **
 **  Redefine the 3 values below to move
 **  the MS5803 to another SPI port.
 **
 **/
#define MS5803_USE_SPI_DRIVER SPID1
#define MS5803_CS_ON_GPIO     GPIOA
#define MS5803_CS_ON_PAD      GPIOA_AIR_CS


static const uint8_t zero = 0;
static bool_t ms5803_initialized = FALSE;
static uint32_t promvals[MS5803_NUM_PROM_VALS];

/**
**  spiPressureSensorBinSem used to synchronize spi 
**  finished callback with thread.
**/
static BinarySemaphore spiPressureSensorBinSem;


/**
 *  @brief helper function to initiate a ChibiOS/RT HAL SPI 
 *          exchange operation, and waits for synchronization
 *          from callback.
 *  @param txp - pointer to value to send
 *  @param rxp - pointer to location for receive
 *
 */
static void mySPIExchange(uint8_t* txp, uint8_t* rxp) {
  spiStartExchange(&MS5803_USE_SPI_DRIVER, 1, txp, rxp);  /* send prom read command */
  if (chBSemWait(&spiPressureSensorBinSem) != RDY_OK) {
    chDbgPanic("ERROR - calibration sem reset");
  }
}


/**
 *  @brief calculates and returns CRC4
 *  @param n_prom 32 bit array of values
 *
 *  Copied from http://www.meas-spec.com/downloads/C-Code_Example_for_MS56xx,_MS57xx_(except_analog_sensor)_and_MS58xx_Series_Pressure_Sensors.pdf
 */
uint8_t crc4(uint32_t n_prom[]);

/**
 * @brief called when SPI action complete
 * @param spip pointer to SPI Driver that 
 *        completed.
 */
void spi_ms5803Callback(SPIDriver *spip) {
    chSysLockFromIsr();
    chBSemSignalI(&spiPressureSensorBinSem);
    chSysUnlockFromIsr();
}


SPIConfig spiPressureSensorConfig = {
  spi_ms5803Callback, /* callback */

  // ChibiOS/RT SPI HAL manually controls the 
  // chip select.  The 32F37x can control it by hardware,
  // but isn't used.
  MS5803_CS_ON_GPIO, /* chip select line port */
  MS5803_CS_ON_PAD,  /* chihp select line pad number */

  /* CR1
     bit#  value description
     15    0     BIDIMODE - 2 line unidir data mode
     14    0     BIDIOE - N/A
     13    0     CRCEN - disabled
     12    0     CRCNEXT - N/A
     11    0     CRCL - N/A
     10    0     Full duplex
      9    0     SSM S/W slave mgmt - disabled
      8    0     SSI Internal slave select N/A
      7    0     LSBFIRST - MSB first
      6    1     SPE - SPI enabled
      5-3  0     BAUD RATE  PCLK / 2  (MS5803 max 20MHz)  
                    (APB1 CLK is 36MHz)
      2    1     MSTR - Master configuration
      1    1     CPOL - 1 when idle
      0    1     CPHA - 2nd clock transition is 
                        the first data capture edge
   */
  0x0047,
  /* CR2 
     bit#  value description
     15    0     RESERVED
     14    1     LDMA_TX - # data to tx is odd
     13    1     LDMA_RX - # data to rx is odd
     12    1     FRXTH 0 1/4
     11-8  7     DS - 8 bit
      7    0     TXEIE - disabled
      6    0     RXNEIE - disabled
      5    0     ERRIE - disabled
      4    0     FRF - SPI Motorola mode
      3    1     NSSP : NSS pulse generated
      2    1     SSOE : enabled in master mode
      1    0     TXDMAEN - controlled by driver
      0    0     RXDMAEN - controlled by driver
   */
  0x770c
};

/**
 *  @brief helper function to send a conversion command to
 *          ms5803, then read the result.
 *  @param cmd - conversion cmd ( selects type of conversion
 *
 */
static uint32_t ms5803_convertAndRead(MS5803_CMDS cmd)
{
  uint8_t garbage, msb, midsb, lsb;

  spiSelect(&MS5803_USE_SPI_DRIVER);

  /* send conversion command */
  spiStartSend(&MS5803_USE_SPI_DRIVER, 1, &cmd);
  if (chBSemWait(&spiPressureSensorBinSem) != RDY_OK) {
    chDbgPanic("ERROR - calibration sem reset");
  }

  /* wait for conversion to finish */
  chThdSleepMilliseconds(MS5803_CMD_CONVERT_WAIT_MILLISEC);

  spiUnselect(&MS5803_USE_SPI_DRIVER);

  cmd = MS5803_CMD_ADC_READ;

  spiSelect(&MS5803_USE_SPI_DRIVER);

  /* read 24 bits */
  mySPIExchange(&cmd,  &garbage);  /* send adc read command */
  mySPIExchange(&zero, &msb);      /* send prom read command */
  mySPIExchange(&zero, &midsb);  /* send prom read command */
  mySPIExchange(&zero, &lsb);  /* send prom read command */

  return (((uint32_t) msb) << 16)  | 
         (((uint32_t) midsb) << 8) |
         ((uint32_t) lsb);
}


/**
 *   @brief Takes a measurement from the ms5803 pressure and temp sensor
 *          over the SPI bus. Initializes the ms5803 if necessary. 
 *          Adjusts reading using coefficients.
 */
void ms5803_readPressureAndTemp(double* pressure, double* temp)
{
  double uncomp_pressure;
  double uncomp_temp;

  double dT; // difference between actual and measured temperature 
  double OFF; // offset at actual temperature 
  double SENS; // sensitivity at actual temperature

  if ((ms5803_initialized == FALSE) && 
      (ms5803_resetAndReadCoefficients() == FALSE)) {
     port_halt();
  }

  uncomp_pressure = (double) ms5803_convertAndRead(MS5803_CMD_CONVERTD1_OSR4096);
  uncomp_temp     = (double) ms5803_convertAndRead(MS5803_CMD_CONVERTD2_OSR4096);

  // calcualte 1st order pressure and temperature (MS5607 1st order algorithm) 
  dT       = uncomp_temp - promvals[MS5803_COEFFS_REF_TEMP] * 256.0;

  OFF      = promvals[MS5803_COEFFS_PRESSURE_OFFSET] * 131072.0 + 
    dT * promvals[MS5803_COEFFS_TEMP_COEFF_OF_PRESSURE_OFFSET] / 64.0;

  SENS     = promvals[MS5803_COEFFS_PRESSURE_SENSITIVITY] * 65536.0 + 
    dT * promvals[MS5803_COEFFS_TEMP_COEFF_OF_PRESSURE_SENS] / 128.0; 

  *temp    = (2000+ (dT*promvals[MS5803_COEFFS_TEMP_COEFF_OF_TEMP]) / 8388608.0) / 100.0;

  *pressure= (((uncomp_pressure * SENS) / 2097152.0 - OFF) / 32768.0) / 100.0;
}

/**
 *   @brief Uses SPI to reset ms5803 pressure sensor
 *          device.  Then reads factory coefficients.
 *          If CRC4 fails over factory prom, then
 *          halts.  Otherwise returns TRUE.
 */
bool_t ms5803_resetAndReadCoefficients()
{
  uint8_t  cmd;
  uint8_t  msb, lsb;
  uint8_t  garbage;

  //  uint8_t  rxbuf[3];
  chBSemInit(&spiPressureSensorBinSem, TRUE); /* init to taken */

  rccEnableGPIOAEN(); /* for SPI1 (pressure sense) */

  /* Enable and configure SPI port */
  spiStart(&MS5803_USE_SPI_DRIVER, &spiPressureSensorConfig);

  // send reset command to ms5803.c

  cmd = MS5803_CMD_RESET;

  spiSelect(&MS5803_USE_SPI_DRIVER);
  spiStartSend(&MS5803_USE_SPI_DRIVER, 1, &cmd);

  chThdSleepMilliseconds(MS5803_CMD_RESET_WAIT_MILLISEC);

  if (chBSemWait(&spiPressureSensorBinSem) != RDY_OK) {
    chDbgPanic("ERROR - calibration sem reset");
  }
  spiUnselect(&MS5803_USE_SPI_DRIVER);

  // read ms5803 prom values.  Prom values are 16-bits.
  // prom 0 is factory setting
  // prom 1-6 are coefficients
  // prom 7 bits 0-3 contain the CRC4 checksum
  uint8_t idx;

  for (idx=MS5803_NUM_PROM_VALS_START_IDX;idx < MS5803_NUM_PROM_VALS; idx++) {

    cmd = MS5803_CMD_PROM_READ(idx);

    spiSelect(&MS5803_USE_SPI_DRIVER);

    mySPIExchange( &cmd,  &garbage);  /* send prom read command */
    mySPIExchange( &zero, &msb);      /* send 0x0 to get msb */
    mySPIExchange( &zero, &lsb);      /* send 0x0 to get lsb */

    spiUnselect(&MS5803_USE_SPI_DRIVER);

    promvals[idx - MS5803_NUM_PROM_VALS_START_IDX] =  (uint32_t)
     (((uint16_t) msb) << 8 | (uint16_t) lsb);

  }

  // perform CRC 4 to see if we got the right values
  if (crc4(promvals) != (promvals[MS5803_NUM_PROM_VALS - 1] & 0xf)) {
    port_halt();
  }

  ms5803_initialized = TRUE;

  return TRUE;
}


/**
 **  This function comes from Measurement Specialties, the 
 **  manufacturer of the MS5803 pressure sensor.
 **
 **/
uint8_t crc4(uint32_t n_prom[])
{
  int cnt; // simple counter 
  unsigned int n_rem; // crc reminder 
  unsigned int crc_read; // original value of the crc 
  unsigned char n_bit; 

  n_rem = 0x00; 
  crc_read=n_prom[7]; //save read CRC 
  n_prom[7]=(0xFF00 & (n_prom[7])); //CRC byte is replaced by 0 
  for (cnt = 0; cnt < 16; cnt++) // operation is performed on bytes 
  { // choose LSB or MSB 
    if (cnt%2==1) n_rem ^= (unsigned short) ((n_prom[cnt>>1]) & 0x00FF); 
    else n_rem ^= (unsigned short) (n_prom[cnt>>1]>>8); 
    for (n_bit = 8; n_bit > 0; n_bit--) 
    { 
      if (n_rem & (0x8000)) 
      { 
	n_rem = (n_rem << 1) ^ 0x3000; 
      } 
      else 
      { 
	n_rem = (n_rem << 1); 
      } 
    } 
  } 
  n_rem= (0x000F & (n_rem >> 12)); // // final 4-bit reminder is CRC code 
  n_prom[7]=crc_read; // restore the crc_read to its original place 
  return (n_rem ^ 0x00); 
}
