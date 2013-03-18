/*
    Copyright (C) 2013 Genist
*/

#include "ch.h"
#include "hal.h"
#include "test.h"
#include "ms5803.h"
#include "led.h"

uint8_t crc4(uint16_t n_prom[]);

/**
**  spi2BinSem used to synchronize spi 
**  finished callback with thread.
**/
BinarySemaphore spi2BinSem;

void spi2callback(SPIDriver *spip) {
    chSysLockFromIsr();
    chBSemSignalI(&spi2BinSem);
    chSysUnlockFromIsr();
}

SPIConfig spi2PressureSensorConfig = {
  spi2callback, /* callback */
  GPIOA,        /* chip select line port */
  GPIOA_AIR_CS, /* chihp select line pad number */
  /* CR1
     bit#  value description
     15    0     BIDIMODE - 2 line unidir data mode
     14    0     BIDIOE - N/A
     13    0     CRCEN - disabled
     12    0     CRCNEXT - N/A
     11    0     CRCL - N/A
     10    0     Full duplex
      9    0     S/W slave mgmt - disabled
      8    0     Internal slave select N/A
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

void testMS5803()
{
  uint8_t  sendbuf[1];
  //  uint8_t  rxbuf[3];
  uint16_t promvals[MS5803_NUM_PROM_VALS];

  chBSemInit(&spi2BinSem, TRUE); /* init to taken */

  rccEnableGPIOAEN(); /* for SPI2 (pressure sense) */
  rccEnableGPIOCEN(); /* for LEDs / SPI3 (zigbee) */

  spiStart(&SPID1, &spi2PressureSensorConfig);

  spiSelect(&SPID1);

  switchLED(GPIOC, GPIOC_LED_G, FALSE);
  switchLED(GPIOC, GPIOC_LED_G, FALSE);
  switchLED(GPIOC, GPIOC_LED_G, FALSE);

  // send reset
  sendbuf[0] = MS5803_CMD_RESET;
  spiStartSend(&SPID1, 1, sendbuf);
  chThdSleepMilliseconds(MS5803_CMD_RESET_WAIT_MILLISEC);
  
  // read prom
  uint8_t idx;
  for (idx=MS5803_NUM_PROM_VALS_START_IDX;idx <= MS5803_NUM_PROM_VALS; idx++) {
    sendbuf[0] = MS5803_CMD_PROM_READ(idx);
    spiSelect(&SPID1);
    spiStartSend(&SPID1, 1, sendbuf);
    spiStartReceive(&SPID1, MS5803_PROM_NUM_BYTES_PER_VAL,
		    &promvals[idx - MS5803_NUM_PROM_VALS_START_IDX]);
    spiUnselect(&SPID1);

    if (chBSemWait(&spi2BinSem) != RDY_OK) {
      chDbgPanic("ERROR - calibration sem reset");
    }
  }

  // perform CRC 4 to see if we got the right values
  if (crc4(promvals) != (promvals[MS5803_NUM_PROM_VALS] & 0xf)) {
    switchLED(GPIOC, GPIOC_LED_R, TRUE);
  }
  else {
    switchLED(GPIOC, GPIOC_LED_G, TRUE);
  }
}


/**
 **  This function comes from Measurement Specialties, the 
 **  manufacturer of the MS5803 pressure sensor.
 **
 **/
uint8_t crc4(uint16_t n_prom[])
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
