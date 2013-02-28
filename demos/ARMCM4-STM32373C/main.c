/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012,2013 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ch.h"
#include "hal.h"
#include "test.h"

/*
 * This is a periodic thread that does absolutely nothing except flashing LEDs.
 */
static WORKING_AREA(waThread1, 128);
static WORKING_AREA(waThread2, 128);

unsigned char buf[2] = {
  0x00,
  0xff
};

static msg_t SPIThread(void *arg) {
  (void)arg;
  chRegSetThreadName("spi");
  while (TRUE) {
    spiSelect(&SPID3);
    spiSend(&SPID3, sizeof(buf), buf);
    spiUnselect(&SPID3);
    chThdSleepMilliseconds(125);
  }
}


static msg_t Thread1(void *arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (TRUE) {
    palSetPad(GPIOC, GPIOC_LED1);
    chThdSleepMilliseconds(125);
    palClearPad(GPIOC, GPIOC_LED1);
    palSetPad(GPIOC, GPIOC_LED2);
    chThdSleepMilliseconds(125);
    palClearPad(GPIOC, GPIOC_LED2);
    palSetPad(GPIOC, GPIOC_LED3);
    chThdSleepMilliseconds(125);
    palClearPad(GPIOC, GPIOC_LED3);
    palSetPad(GPIOC, GPIOC_LED4);
    chThdSleepMilliseconds(125);
    palClearPad(GPIOC, GPIOC_LED4);
  }
}

/*
 * SPI end transfer callback.
 */
static void spicb(SPIDriver *spip) {
 
  /* On transfer end just releases the slave select line.*/
  chSysLockFromIsr();
  spiUnselectI(spip);
  chSysUnlockFromIsr();
}


/*
 * SPI configuration structure.
 * Maximum speed (12MHz), CPHA=0, CPOL=0, 16bits frames, MSb transmitted first.
 * The slave select line is the pin GPIOA_SPI1NSS on the port GPIOA.
 */
static const SPIConfig spicfg = {
  spicb,
  /* HW dependent part.*/
  GPIOD,           /* chip select line port */
  GPIOD_LCD_CS,    /* chip select line pad number */
/* CR1 init data - BIDIMODE= 0: 2 line unidirectional mode
                   BIDIOE  = X: N/A (set to 0 )
                   CRCEN   = 1: CRC enabled
                   CRCNEXT = 0: next transmit from tx buffer
                   CRCLEN  = 0: CRC LEN (8/16) set to 0
                   RXONLY  = 0: Full Duplex
                   SSM     = 1: S/W slave mgmt. enabled
                   SSI     = 0: internal slave select
                   LSBFIRST= 0: MSB first
                   SPE     = 0: SPE Enable - enabled by ChibiOS/RT HAL
                   BR[2:0] = 1: div 4 - follows eval s/w lcd
                   MSTR    = 1: Master
                   CPOL    = 1: Clock Polarity when idle send 1s
                   CPHA    = 1: Clock Phase use 2nd clock transition

 */

  SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_CPOL | SPI_CR1_CPHA, // | SPI_CR1_CRCEN,
  /* CR2 init data - bit val desc
                      15 0   reserved
                      14 0   Last DMA transfer for transmission - data transfer even
                      13 0   Last DMA transfer for reception - data transfer even
                      12 1   FIFO reception threshold - RXNE event gen if FIFO level >= 1/4
                    11:8 0x7 data size - 8-bit
                       7 0   tx buf empty interrupt enable - disabled
                       6 0   rx buf empty interrupt enable - disabled
                       5 0   error interrupt enable - disabled
                       4 0   frame format - motorola mode
                       3 0   NSS pulse - no NSS pulse
                       2 1   SS output enabled
                       1 0   TX buffer DMA enable - disabled
                       0 0   RX buffer DMA enable - disabled */
  SPI_CR2_SSOE | SPI_CR2_FRXTH | SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2
};

/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();


  /*
   * Activates the serial driver 2 using the driver default configuration.
   * PA9(TX) and PA10(RX) are routed to USART1.
   */
  sdStart(&SD2, NULL);
  palSetPadMode(GPIOA, 9, PAL_MODE_ALTERNATE(7));
  palSetPadMode(GPIOA, 10, PAL_MODE_ALTERNATE(7));

  spiStart(&SPID3, &spicfg );

  /*
   * Creates the example thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, SPIThread, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state, when the button is
   * pressed the test procedure is launched.
   */
  while (TRUE) {
    if (palReadPad(GPIOA, GPIOA_KEY_BUTTON))
      TestThread(&SD2);
    chThdSleepMilliseconds(500);
  }
}
