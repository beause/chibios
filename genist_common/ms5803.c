/*
    Copyright (C) 2013 Genist
*/

#include "ch.h"
#include "hal.h"
#include "test.h"
#include "ms5803.h"
#include "led.h"
#include "threads.h"
#include "itmstream.h"

/***
 **
 **  Redefine the 3 values below to move
 **  the MS5803 to another SPI port.
 **
 **/
#define MS5803_USE_SPI_DRIVER SPID1
#define MS5803_CS_ON_GPIO     GPIOA
#define MS5803_CS_ON_PAD      GPIOA_AIR_CS

DECLARE_THREAD(ThreadPressureSensor, NORMALPRIO, 1024)

static const uint8_t zero = 0;
static bool_t ms5803_initialized = FALSE;
static uint32_t promvals[MS5803_NUM_PROM_VALS];
static int32_t AirTemp;
static int32_t Pressure;
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
static void mySPIExchange(const uint8_t* txp, uint8_t* rxp) {
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
    (void) spip;
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

  spiUnselect(&MS5803_USE_SPI_DRIVER);

  return (((uint32_t) msb) << 16)  | 
         (((uint32_t) midsb) << 8) |
         ((uint32_t) lsb);
}


/**
 *   @brief Takes a measurement from the ms5803 pressure and temp sensor
 *          over the SPI bus. Initializes the ms5803 if necessary. 
 *          Adjusts reading using coefficients.
 */
void ms5803_readPressureAndTemp(int64_t* pressure, int64_t* temp)
{
  uint32_t uncomp_pressure;
  uint32_t uncomp_temp;

  int32_t dT; // difference between actual and measured temperature 
  int64_t OFF; // offset at actual temperature 
  int64_t SENS; // sensitivity at actual temperature

  if ((ms5803_initialized == FALSE) && 
      (ms5803_resetAndReadCoefficients() == FALSE)) {
     port_halt();
  }

  uncomp_pressure = ms5803_convertAndRead(MS5803_CMD_CONVERTD1_OSR4096);
  uncomp_temp     = ms5803_convertAndRead(MS5803_CMD_CONVERTD2_OSR4096);


  int64_t c1 = promvals[MS5803_COEFFS_PRESSURE_SENSITIVITY];
  int64_t c2 = promvals[MS5803_COEFFS_PRESSURE_OFFSET];
  int64_t c3 = promvals[MS5803_COEFFS_TEMP_COEFF_OF_PRESSURE_SENS];
  int64_t c4 = promvals[MS5803_COEFFS_TEMP_COEFF_OF_PRESSURE_OFFSET];
  int64_t c5 = promvals[MS5803_COEFFS_REF_TEMP];
  int64_t c6 = promvals[MS5803_COEFFS_TEMP_COEFF_OF_TEMP];

  // calculations from ms5803-01BA datasheet
  // calculate 1st order pressure and temperature (MS5608 1st order algorithm) 
  dT       = uncomp_temp - c5 * 256; 
  OFF      = (c2 << 16) + (dT * c4) / (1 << 7);
  SENS     = (c1 << 15) + (c3 * dT) / (1 << 8); 

  *temp    = 2000 + (dT * c6) / (1 << 23);

  // 2nd order temp compensation
  int64_t t2    = 0;
  int64_t off2  = 0;
  int64_t sens2 = 0;

  if (*temp < 2000) {
    t2    = dT * dT / ( 1 << 31);
    off2  = 3 * (*temp - 2000) * (*temp - 2000);
    sens2 = 7 * (*temp - 2000) * (*temp - 2000) / 8;

    if (*temp < -1500) {
      sens2 = sens2 + 2 * (*temp + 1500) * (*temp + 1500);
    }

    *temp = *temp - t2;
    OFF   = OFF - off2;
    SENS  = SENS - sens2;
  }
  else if ( *temp >= 4500 ) {
      sens2 = sens2 - (*temp - 4500) * (*temp - 4500) / 8;
  }

  *pressure= ((((int64_t) uncomp_pressure) * SENS) / (1 << 21) - OFF) / 
                 (1 << 15);
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

static msg_t ThreadPressureSensor(void *arg)
{
    int64_t pressure, temp;

    (void) arg;
    chRegSetThreadName("ms5803");

    while (TRUE)
    {
        ms5803_readPressureAndTemp(&pressure, &temp);
        chSysLock();
        Pressure = (int32_t)pressure;
        AirTemp = (int32_t)temp;
        chSysUnlock();
        chThdSleepMilliseconds(1000);
    }
    return 0;
}

int32_t ReadAirTemp(void)
{
    int32_t ret;
    chSysLock();
    ret = AirTemp;
    chSysUnlock();
    return ret;
}

int32_t ReadPressure(void)
{
    int32_t ret;
    chSysLock();
    ret = Pressure;
    chSysUnlock();
    return ret;
}
