*****************************************************************************
** ChibiOS/RT HAL - PWM/ICU driver demo for STM32.                         **
*****************************************************************************

** TARGET **

The demo runs on a STM 32373C eval board.

** The Demo **

The application demonstrates the use of the STM32 PWM and ICU drivers. 
The pin PC10 is reconfigured from SPI3_CLK output to be the output of
TIM15_CH1.  The output of the PWM can be seen on PC10.

On the eval board, the CN11 pin 2 is used as the ICU input.  This is 
configured so that pin PA4 is configured for alternate function 2, TIM3_CH2
The ICU unit will measure the generated PWM.

PC10 must be connected to CN11 pin 2.

** Build Procedure **

The demo has been tested using the free Codesourcery GCC-based toolchain
and YAGARTO.
Just modify the TRGT line in the makefile in order to use different GCC ports.

** Notes **

Some files used by the demo are not part of ChibiOS/RT but are copyright of
ST Microelectronics and are licensed under a different license.
Also note that not all the files present in the ST library are distributed
with ChibiOS/RT, you can find the whole library on the ST web site:

                             http://www.st.com
