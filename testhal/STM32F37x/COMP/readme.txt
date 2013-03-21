*****************************************************************************
** ChibiOS/RT HAL - COMP for STM32.                                        **
*****************************************************************************

** TARGET **

The demo runs on a STM 32373C eval board.

** The Demo **

The application demonstrates the use of the STM32 COMP driver.
The MCU is configured so that the Light Dependent Resistor (LD3) is connected
to comparator 1.

Comparator 1 is set to compare to 1/2 VREFINT.

A loop in main polls the value of the output of comparator 1 and displays the
value on LED1.

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
