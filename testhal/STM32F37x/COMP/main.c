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


static COMPConfig compcfg = {
  .comp_enable          = COMP1_EN | COMP2_EN,
  .comp1_inv_in_src     = COMP1_INPUT_SRC_12_VREFINT,
  .comp2_inv_in_src     = COMP2_INPUT_SRC_12_VREFINT,
  .comp1_hysteresis     = COMP_HYSTERESIS_MED,
  .comp2_hysteresis     = COMP_HYSTERESIS_MED,
  .comp1_lock           = FALSE,
  .comp2_lock           = FALSE,
  .comp1_opmode         = COMP_PWR_MED_SPEED,
  .comp2_opmode         = COMP_PWR_MED_SPEED,
  .comp1_output_pol     = COMP_OUTPUT_POL_NOT_INV,
  .comp2_output_pol     = COMP_OUTPUT_POL_NOT_INV,
  .comp1_output_sel     = COMP1_OUTPUT_DEST_TIM3_IC1,
  .comp2_output_sel     = COMP2_OUTPUT_DEST_TIM4_IC1,
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
   * Initializes the COMP driver
   */
  compStart(&COMPD1, &compcfg);

  while (TRUE) {
    chThdSleepMilliseconds(500);
  }

  return 0;
}
