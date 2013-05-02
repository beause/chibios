/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012 Giovanni Di Sirio.

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

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for Genist Custom Board V2 board.
 */

/*
 * Board identifier.
 */
#define BOARD_GENIST_STM32F373_V2
#define BOARD_NAME                  "Genist Custom Board V2"

#define LSEDRV_HIGH     3
#define LSEDRV_MEDHIGH  2
#define LSEDRV_MEDLOW   1
#define LSEDRV_LOW      0
/*
 * Board oscillators-related settings.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                32768
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                8000000
#endif

#define LSEDRV                      (LSEDRV_HIGH << 3)


/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   300

/*
 * MCU type as defined in the ST header file stm32f37x.h.
 */
#define STM32F37X

/*
 * IO pins assignments.
 */
#define GPIOA_PWM_OUT               0
#define GPIOA_LS_PWM_P              1
#define GPIOA_SUPPLY_SENSE          2
#define GPIOA_RF_NIRQ               3
#define GPIOA_SPI1_NSS              4
#define GPIOA_SPI1_SCK              5
#define GPIOA_SPI1_MISO             6
#define GPIOA_SPI1_MOSI             7
#define GPIOA_I2C2_SMBA             8
#define GPIOA_I2C2_SCL              9
#define GPIOA_I2C2_SDA              10
#define GPIOA_PIN11                 11
#define GPIOA_PIN12                 12
#define GPIOA_SWDIO                 13
#define GPIOA_SWCLK                 14
#define GPIOA_JTAG_TDI              15

#define GPIOB_PWM_OUT               0
#define GPIOB_PIN1                  1
#define GPIOB_SDADC_4P              2
#define GPIOB_SWO                   3
#define GPIOB_PROX_1                4
#define GPIOB_PROX_2                5
#define GPIOB_LSM_SCL               6
#define GPIOB_LSM_SDA               7
#define GPIOB_HALL_A                8
#define GPIOB_HALL_B                9
#define GPIOB_VR_DIR                10
#define GPIOB_PIN11                 11
#define GPIOB_PIN12                 12
#define GPIOB_PIN13                 13
#define GPIOB_VAR_RUC1              14
#define GPIOB_VAR_RUC2              15

#define GPIOC_LED_1                 0
#define GPIOC_LED_2                 1
#define GPIOC_LED_3                 2
#define GPIOC_PIN3                  3
#define GPIOC_PIN4                  4
#define GPIOC_PIN5                  5
#define GPIOC_EXT_1                 6
#define GPIOC_EXT_2                 7
#define GPIOC_EXT_3                 8
#define GPIOC_EXT_4                 9
#define GPIOC_SPI3_SCK              10
#define GPIOC_SPI3_MISO             11
#define GPIOC_SPI3_MOSI             12
#define GPIOC_SPI3_NSS              13
#define GPIOC_OSC32_IN              14
#define GPIOC_OSC32_OUT             15

#define GPIOD_EXT_5                 0
#define GPIOD_HAZ_1                 1
#define GPIOD_HAZ_2                 2
#define GPIOD_SPI2_MISO             3
#define GPIOD_SPI2_MOSI             4
#define GPIOD_PIN5                  5
#define GPIOD_SPI2_NSS              6
#define GPIOD_SPI2_SCK              7
#define GPIOD_RS485_TX              8
#define GPIOD_RS485_RX              9
#define GPIOD_PIN10                 10
#define GPIOD_RS_485_RE             11
#define GPIOD_RS485_DE              12
#define GPIOD_EXT_6                 13
#define GPIOD_EXT_7                 14
#define GPIOD_EXT_8                 15

#define GPIOE_MCU_GOOD_PW           0
#define GPIOE_MCU_EN_CTL_OC1        1
#define GPIOE_ST_DIS1               2
#define GPIOE_ST_DIS2               3
#define GPIOE_RF_GP0                4
#define GPIOE_RF_GP1                5
#define GPIOE_RF_GP2                6
#define GPIOE_SENSE4                7
#define GPIOE_TEMP_P                8
#define GPIOE_TEMP_N                9
#define GPIOE_TEMP1_P               10
#define GPIOE_SENSE3                11
#define GPIOE_SENSE2                12
#define GPIOE_SENSE1                13
#define GPIOE_RF_GP3                14
#define GPIOE_SHUTDOWN_GP           15

#define GPIOF_OSC_IN                0
#define GPIOF_OSC_OUT               1
#define GPIOF_PIN2                  2
#define GPIOF_PIN3                  3
#define GPIOF_AIR_HEAT              4
#define GPIOF_PIN5                  5
#define GPIOF_LSM_DR                6
#define GPIOF_PIN7                  7
#define GPIOF_PIN8                  8
#define GPIOF_LSM_IN1               9
#define GPIOF_LSM_IN2               10
#define GPIOF_PIN11                 11
#define GPIOF_PIN12                 12
#define GPIOF_PIN13                 13
#define GPIOF_PIN14                 14
#define GPIOF_PIN15                 15

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_2M(n)            (0U << ((n) * 2))
#define PIN_OSPEED_25M(n)           (1U << ((n) * 2))
#define PIN_OSPEED_50M(n)           (2U << ((n) * 2))
#define PIN_OSPEED_100M(n)          (3U << ((n) * 2))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2))
#define PIN_AFIO_AF(n, v)           ((v##U) << ((n % 8) * 4))

/*
 * GPIOA setup:
 *
 * PA0  - PWM_OUT                   (analog).
 * PA1  - LS_PWM_P                  (analog).
 * PA2  - SUPPLY_SENSE              (analog).
 * PA3  - RF_NIRQ                   (input pullup).
 * PA4  - SPI1_NSS                  (output pushpull maximum).
 * PA5  - SPI1_SCK                  (alternate 5).
 * PA6  - SPI1_MISO                 (alternate 5).
 * PA7  - SPI1_MOSI                 (alternate 5).
 * PA8  - I2C2_SMBA                 (alternate 4).
 * PA9  - I2C2_SCL                  (alternate 4).
 * PA10 - I2C2_SDA                  (alternate 4).
 * PA11 - PIN11                     (input pullup).
 * PA12 - PIN12                     (input pullup).
 * PA13 - SWDIO                     (alternate 0).
 * PA14 - SWCLK                     (alternate 0).
 * PA15 - JTAG_TDI                  (alternate 0).
 */
#define VAL_GPIOA_MODER             (PIN_MODE_ANALOG(GPIOA_PWM_OUT) |       \
                                     PIN_MODE_ANALOG(GPIOA_LS_PWM_P) |      \
                                     PIN_MODE_ANALOG(GPIOA_SUPPLY_SENSE) |  \
                                     PIN_MODE_INPUT(GPIOA_RF_NIRQ) |        \
                                     PIN_MODE_OUTPUT(GPIOA_SPI1_NSS) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SPI1_SCK) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_SPI1_MISO) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_SPI1_MOSI) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_I2C2_SMBA) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_I2C2_SCL) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_I2C2_SDA) |   \
                                     PIN_MODE_INPUT(GPIOA_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOA_PIN12) |          \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_JTAG_TDI))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_PWM_OUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_LS_PWM_P) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SUPPLY_SENSE) |\
                                     PIN_OTYPE_PUSHPULL(GPIOA_RF_NIRQ) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SPI1_NSS) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SPI1_SCK) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SPI1_MISO) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SPI1_MOSI) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_I2C2_SMBA) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_I2C2_SCL) |   \
                                     PIN_OTYPE_OPENDRAIN(GPIOA_I2C2_SDA) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_JTAG_TDI))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_2M(GPIOA_PWM_OUT) |         \
                                     PIN_OSPEED_2M(GPIOA_LS_PWM_P) |        \
                                     PIN_OSPEED_2M(GPIOA_SUPPLY_SENSE) |    \
                                     PIN_OSPEED_2M(GPIOA_RF_NIRQ) |         \
                                     PIN_OSPEED_100M(GPIOA_SPI1_NSS) |      \
                                     PIN_OSPEED_100M(GPIOA_SPI1_SCK) |      \
                                     PIN_OSPEED_100M(GPIOA_SPI1_MISO) |     \
                                     PIN_OSPEED_100M(GPIOA_SPI1_MOSI) |     \
                                     PIN_OSPEED_2M(GPIOA_I2C2_SMBA) |       \
                                     PIN_OSPEED_100M(GPIOA_I2C2_SCL) |      \
                                     PIN_OSPEED_100M(GPIOA_I2C2_SDA) |      \
                                     PIN_OSPEED_2M(GPIOA_PIN11) |           \
                                     PIN_OSPEED_100M(GPIOA_PIN12) |         \
                                     PIN_OSPEED_100M(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_100M(GPIOA_SWCLK) |         \
                                     PIN_OSPEED_100M(GPIOA_JTAG_TDI))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_PWM_OUT) |    \
                                     PIN_PUPDR_FLOATING(GPIOA_LS_PWM_P) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_SUPPLY_SENSE) |\
                                     PIN_PUPDR_PULLUP(GPIOA_RF_NIRQ) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_SPI1_NSS) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_SPI1_SCK) |   \
                                     PIN_PUPDR_PULLUP(GPIOA_SPI1_MISO) |    \
                                     PIN_PUPDR_FLOATING(GPIOA_SPI1_MOSI) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_I2C2_SMBA) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_I2C2_SCL) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_I2C2_SDA) |   \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN12) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWDIO) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWCLK) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_JTAG_TDI))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_PWM_OUT) |          \
                                     PIN_ODR_HIGH(GPIOA_LS_PWM_P) |         \
                                     PIN_ODR_HIGH(GPIOA_SUPPLY_SENSE) |     \
                                     PIN_ODR_HIGH(GPIOA_RF_NIRQ) |          \
                                     PIN_ODR_HIGH(GPIOA_SPI1_NSS) |         \
                                     PIN_ODR_HIGH(GPIOA_SPI1_SCK) |         \
                                     PIN_ODR_HIGH(GPIOA_SPI1_MISO) |        \
                                     PIN_ODR_HIGH(GPIOA_SPI1_MOSI) |        \
                                     PIN_ODR_HIGH(GPIOA_I2C2_SMBA) |        \
                                     PIN_ODR_HIGH(GPIOA_I2C2_SCL) |         \
                                     PIN_ODR_HIGH(GPIOA_I2C2_SDA) |         \
                                     PIN_ODR_HIGH(GPIOA_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOA_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOA_SWDIO) |            \
                                     PIN_ODR_HIGH(GPIOA_SWCLK) |            \
                                     PIN_ODR_HIGH(GPIOA_JTAG_TDI))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_PWM_OUT, 0) |        \
                                     PIN_AFIO_AF(GPIOA_LS_PWM_P, 0) |       \
                                     PIN_AFIO_AF(GPIOA_SUPPLY_SENSE, 0) |   \
                                     PIN_AFIO_AF(GPIOA_RF_NIRQ, 0) |        \
                                     PIN_AFIO_AF(GPIOA_SPI1_NSS, 0) |       \
                                     PIN_AFIO_AF(GPIOA_SPI1_SCK, 5) |       \
                                     PIN_AFIO_AF(GPIOA_SPI1_MISO, 5) |      \
                                     PIN_AFIO_AF(GPIOA_SPI1_MOSI, 5))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_I2C2_SMBA, 4) |      \
                                     PIN_AFIO_AF(GPIOA_I2C2_SCL, 4) |       \
                                     PIN_AFIO_AF(GPIOA_I2C2_SDA, 4) |       \
                                     PIN_AFIO_AF(GPIOA_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOA_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0) |          \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0) |          \
                                     PIN_AFIO_AF(GPIOA_JTAG_TDI, 0))

/*
 * GPIOB setup:
 *
 * PB0  - PWM_OUT                   (analog).
 * PB1  - PIN1                      (input pullup).
 * PB2  - SDADC_4P                  (analog).
 * PB3  - SWO                       (alternate 0).
 * PB4  - PROX_1                    (input pullup).
 * PB5  - PROX_2                    (input pullup).
 * PB6  - LSM_SCL                   (alternate 4).
 * PB7  - LSM_SDA                   (alternate 4).
 * PB8  - HALL_A                    (input pullup).
 * PB9  - HALL_B                    (input pullup).
 * PB10 - VR_DIR                    (input pullup).
 * PB11 - PIN11                     (input pullup).
 * PB12 - PIN12                     (input pullup).
 * PB13 - PIN13                     (input pullup).
 * PB14 - VAR_RUC1                  (input pullup).
 * PB15 - VAR_RUC2                  (input pullup).
 */
#define VAL_GPIOB_MODER             (PIN_MODE_ANALOG(GPIOB_PWM_OUT) |       \
                                     PIN_MODE_INPUT(GPIOB_PIN1) |           \
                                     PIN_MODE_ANALOG(GPIOB_SDADC_4P) |      \
                                     PIN_MODE_ALTERNATE(GPIOB_SWO) |        \
                                     PIN_MODE_INPUT(GPIOB_PROX_1) |         \
                                     PIN_MODE_INPUT(GPIOB_PROX_2) |         \
                                     PIN_MODE_ALTERNATE(GPIOB_LSM_SCL) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_LSM_SDA) |    \
                                     PIN_MODE_INPUT(GPIOB_HALL_A) |         \
                                     PIN_MODE_INPUT(GPIOB_HALL_B) |         \
                                     PIN_MODE_INPUT(GPIOB_VR_DIR) |         \
                                     PIN_MODE_INPUT(GPIOB_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOB_VAR_RUC1) |       \
                                     PIN_MODE_INPUT(GPIOB_VAR_RUC2))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_PWM_OUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SDADC_4P) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SWO) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PROX_1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PROX_2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_LSM_SCL) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_LSM_SDA) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_HALL_A) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_HALL_B) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_VR_DIR) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_VAR_RUC1) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_VAR_RUC2))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_2M(GPIOB_PWM_OUT) |         \
                                     PIN_OSPEED_2M(GPIOB_PIN1) |            \
                                     PIN_OSPEED_2M(GPIOB_SDADC_4P) |        \
                                     PIN_OSPEED_100M(GPIOB_SWO) |           \
                                     PIN_OSPEED_2M(GPIOB_PROX_1) |          \
                                     PIN_OSPEED_2M(GPIOB_PROX_2) |          \
                                     PIN_OSPEED_2M(GPIOB_LSM_SCL) |         \
                                     PIN_OSPEED_2M(GPIOB_LSM_SDA) |         \
                                     PIN_OSPEED_2M(GPIOB_HALL_A) |          \
                                     PIN_OSPEED_2M(GPIOB_HALL_B) |          \
                                     PIN_OSPEED_2M(GPIOB_VR_DIR) |          \
                                     PIN_OSPEED_2M(GPIOB_PIN11) |           \
                                     PIN_OSPEED_2M(GPIOB_PIN12) |           \
                                     PIN_OSPEED_2M(GPIOB_PIN13) |           \
                                     PIN_OSPEED_2M(GPIOB_VAR_RUC1) |        \
                                     PIN_OSPEED_2M(GPIOB_VAR_RUC2))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_PULLUP(GPIOB_PWM_OUT) |      \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_SDADC_4P) |     \
                                     PIN_PUPDR_PULLDOWN(GPIOB_SWO) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PROX_1) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_PROX_2) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_LSM_SCL) |      \
                                     PIN_PUPDR_PULLUP(GPIOB_LSM_SDA) |      \
                                     PIN_PUPDR_PULLUP(GPIOB_HALL_A) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_HALL_B) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_VR_DIR) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_VAR_RUC1) |     \
                                     PIN_PUPDR_PULLUP(GPIOB_VAR_RUC2))
#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(GPIOB_PWM_OUT) |          \
                                     PIN_ODR_HIGH(GPIOB_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOB_SDADC_4P) |         \
                                     PIN_ODR_HIGH(GPIOB_SWO) |              \
                                     PIN_ODR_HIGH(GPIOB_PROX_1) |           \
                                     PIN_ODR_HIGH(GPIOB_PROX_2) |           \
                                     PIN_ODR_HIGH(GPIOB_LSM_SCL) |          \
                                     PIN_ODR_HIGH(GPIOB_LSM_SDA) |          \
                                     PIN_ODR_HIGH(GPIOB_HALL_A) |           \
                                     PIN_ODR_HIGH(GPIOB_HALL_B) |           \
                                     PIN_ODR_HIGH(GPIOB_VR_DIR) |           \
                                     PIN_ODR_HIGH(GPIOB_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOB_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOB_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOB_VAR_RUC1) |         \
                                     PIN_ODR_HIGH(GPIOB_VAR_RUC2))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_PWM_OUT, 0) |        \
                                     PIN_AFIO_AF(GPIOB_PIN1, 0) |           \
                                     PIN_AFIO_AF(GPIOB_SDADC_4P, 0) |       \
                                     PIN_AFIO_AF(GPIOB_SWO, 0) |            \
                                     PIN_AFIO_AF(GPIOB_PROX_1, 0) |         \
                                     PIN_AFIO_AF(GPIOB_PROX_2, 0) |         \
                                     PIN_AFIO_AF(GPIOB_LSM_SCL, 4) |        \
                                     PIN_AFIO_AF(GPIOB_LSM_SDA, 4))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_HALL_A, 0) |         \
                                     PIN_AFIO_AF(GPIOB_HALL_B, 0) |         \
                                     PIN_AFIO_AF(GPIOB_VR_DIR, 0) |         \
                                     PIN_AFIO_AF(GPIOB_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOB_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOB_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOB_VAR_RUC1, 0) |       \
                                     PIN_AFIO_AF(GPIOB_VAR_RUC2, 0))

/*
 * GPIOC setup:
 *
 * PC0  - LED_1                     (output opendrain minimum).
 * PC1  - LED_2                     (output opendrain minimum).
 * PC2  - LED_3                     (output opendrain minimum).
 * PC3  - PIN3                      (input pullup).
 * PC4  - PIN4                      (input pullup).
 * PC5  - PIN5                      (input pullup).
 * PC6  - EXT_1                     (output pushpull minimum).
 * PC7  - EXT_2                     (output pushpull minimum).
 * PC8  - EXT_3                     (output pushpull minimum).
 * PC9  - EXT_4                     (output pushpull minimum).
 * PC10 - SPI3_SCK                  (alternate 6).
 * PC11 - SPI3_MISO                 (alternate 6).
 * PC12 - SPI3_MOSI                 (alternate 6).
 * PC13 - SPI3_NSS                  (output pushpull minimum).
 * PC14 - OSC32_IN                  (input floating).
 * PC15 - OSC32_OUT                 (input floating).
 */
#define VAL_GPIOC_MODER             (PIN_MODE_OUTPUT(GPIOC_LED_1) |         \
                                     PIN_MODE_OUTPUT(GPIOC_LED_2) |         \
                                     PIN_MODE_OUTPUT(GPIOC_LED_3) |         \
                                     PIN_MODE_INPUT(GPIOC_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN5) |           \
                                     PIN_MODE_OUTPUT(GPIOC_EXT_1) |         \
                                     PIN_MODE_OUTPUT(GPIOC_EXT_2) |         \
                                     PIN_MODE_OUTPUT(GPIOC_EXT_3) |         \
                                     PIN_MODE_OUTPUT(GPIOC_EXT_4) |         \
                                     PIN_MODE_ALTERNATE(GPIOC_SPI3_SCK) |   \
                                     PIN_MODE_ALTERNATE(GPIOC_SPI3_MISO) |  \
                                     PIN_MODE_ALTERNATE(GPIOC_SPI3_MOSI) |  \
                                     PIN_MODE_OUTPUT(GPIOC_SPI3_NSS) |      \
                                     PIN_MODE_INPUT(GPIOC_OSC32_IN) |       \
                                     PIN_MODE_INPUT(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_OPENDRAIN(GPIOC_LED_1) |     \
                                     PIN_OTYPE_OPENDRAIN(GPIOC_LED_2) |     \
                                     PIN_OTYPE_OPENDRAIN(GPIOC_LED_3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_EXT_1) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_EXT_2) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_EXT_3) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_EXT_4) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SPI3_SCK) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SPI3_MISO) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SPI3_MOSI) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SPI3_NSS) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_IN) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_2M(GPIOC_LED_1) |           \
                                     PIN_OSPEED_2M(GPIOC_LED_2) |           \
                                     PIN_OSPEED_2M(GPIOC_LED_3) |           \
                                     PIN_OSPEED_2M(GPIOC_PIN3) |            \
                                     PIN_OSPEED_2M(GPIOC_PIN4) |            \
                                     PIN_OSPEED_2M(GPIOC_PIN5) |            \
                                     PIN_OSPEED_2M(GPIOC_EXT_1) |           \
                                     PIN_OSPEED_2M(GPIOC_EXT_2) |           \
                                     PIN_OSPEED_2M(GPIOC_EXT_3) |           \
                                     PIN_OSPEED_2M(GPIOC_EXT_4) |           \
                                     PIN_OSPEED_2M(GPIOC_SPI3_SCK) |        \
                                     PIN_OSPEED_2M(GPIOC_SPI3_MISO) |       \
                                     PIN_OSPEED_2M(GPIOC_SPI3_MOSI) |       \
                                     PIN_OSPEED_2M(GPIOC_SPI3_NSS) |        \
                                     PIN_OSPEED_100M(GPIOC_OSC32_IN) |      \
                                     PIN_OSPEED_100M(GPIOC_OSC32_OUT))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_FLOATING(GPIOC_LED_1) |      \
                                     PIN_PUPDR_FLOATING(GPIOC_LED_2) |      \
                                     PIN_PUPDR_FLOATING(GPIOC_LED_3) |      \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_EXT_1) |        \
                                     PIN_PUPDR_PULLUP(GPIOC_EXT_2) |        \
                                     PIN_PUPDR_PULLUP(GPIOC_EXT_3) |        \
                                     PIN_PUPDR_PULLUP(GPIOC_EXT_4) |        \
                                     PIN_PUPDR_PULLUP(GPIOC_SPI3_SCK) |     \
                                     PIN_PUPDR_PULLUP(GPIOC_SPI3_MISO) |    \
                                     PIN_PUPDR_PULLUP(GPIOC_SPI3_MOSI) |    \
                                     PIN_PUPDR_PULLUP(GPIOC_SPI3_NSS) |     \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_IN) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_OUT))
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_LED_1) |            \
                                     PIN_ODR_HIGH(GPIOC_LED_2) |            \
                                     PIN_ODR_HIGH(GPIOC_LED_3) |            \
                                     PIN_ODR_HIGH(GPIOC_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOC_EXT_1) |            \
                                     PIN_ODR_HIGH(GPIOC_EXT_2) |            \
                                     PIN_ODR_HIGH(GPIOC_EXT_3) |            \
                                     PIN_ODR_HIGH(GPIOC_EXT_4) |            \
                                     PIN_ODR_HIGH(GPIOC_SPI3_SCK) |         \
                                     PIN_ODR_HIGH(GPIOC_SPI3_MISO) |        \
                                     PIN_ODR_HIGH(GPIOC_SPI3_MOSI) |        \
                                     PIN_ODR_HIGH(GPIOC_SPI3_NSS) |         \
                                     PIN_ODR_HIGH(GPIOC_OSC32_IN) |         \
                                     PIN_ODR_HIGH(GPIOC_OSC32_OUT))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_LED_1, 0) |          \
                                     PIN_AFIO_AF(GPIOC_LED_2, 0) |          \
                                     PIN_AFIO_AF(GPIOC_LED_3, 0) |          \
                                     PIN_AFIO_AF(GPIOC_PIN3, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOC_EXT_1, 0) |          \
                                     PIN_AFIO_AF(GPIOC_EXT_2, 0))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_EXT_3, 0) |          \
                                     PIN_AFIO_AF(GPIOC_EXT_4, 0) |          \
                                     PIN_AFIO_AF(GPIOC_SPI3_SCK, 6) |       \
                                     PIN_AFIO_AF(GPIOC_SPI3_MISO, 6) |      \
                                     PIN_AFIO_AF(GPIOC_SPI3_MOSI, 6) |      \
                                     PIN_AFIO_AF(GPIOC_SPI3_NSS, 0) |       \
                                     PIN_AFIO_AF(GPIOC_OSC32_IN, 0) |       \
                                     PIN_AFIO_AF(GPIOC_OSC32_OUT, 0))

/*
 * GPIOD setup:
 *
 * PD0  - EXT_5                     (output pushpull minimum).
 * PD1  - HAZ_1                     (input pullup).
 * PD2  - HAZ_2                     (input pullup).
 * PD3  - SPI2_MISO                 (alternate 5).
 * PD4  - SPI2_MOSI                 (alternate 5).
 * PD5  - PIN5                      (input pullup).
 * PD6  - SPI2_NSS                  (output pushpull minimum).
 * PD7  - SPI2_SCK                  (input pullup).
 * PD8  - RS485_TX                  (alternate 7).
 * PD9  - RS485_RX                  (alternate 7).
 * PD10 - PIN10                     (input pullup).
 * PD11 - RS_485_RE                 (alternate 7).
 * PD12 - RS485_DE                  (alternate 7).
 * PD13 - EXT_6                     (output pushpull minimum).
 * PD14 - EXT_7                     (output pushpull minimum).
 * PD15 - EXT_8                     (output pushpull minimum).
 */
#define VAL_GPIOD_MODER             (PIN_MODE_OUTPUT(GPIOD_EXT_5) |         \
                                     PIN_MODE_INPUT(GPIOD_HAZ_1) |          \
                                     PIN_MODE_INPUT(GPIOD_HAZ_2) |          \
                                     PIN_MODE_ALTERNATE(GPIOD_SPI2_MISO) |  \
                                     PIN_MODE_ALTERNATE(GPIOD_SPI2_MOSI) |  \
                                     PIN_MODE_INPUT(GPIOD_PIN5) |           \
                                     PIN_MODE_OUTPUT(GPIOD_SPI2_NSS) |      \
                                     PIN_MODE_INPUT(GPIOD_SPI2_SCK) |       \
                                     PIN_MODE_ALTERNATE(GPIOD_RS485_TX) |   \
                                     PIN_MODE_ALTERNATE(GPIOD_RS485_RX) |   \
                                     PIN_MODE_INPUT(GPIOD_PIN10) |          \
                                     PIN_MODE_ALTERNATE(GPIOD_RS_485_RE) |  \
                                     PIN_MODE_ALTERNATE(GPIOD_RS485_DE) |   \
                                     PIN_MODE_OUTPUT(GPIOD_EXT_6) |         \
                                     PIN_MODE_OUTPUT(GPIOD_EXT_7) |         \
                                     PIN_MODE_OUTPUT(GPIOD_EXT_8))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_EXT_5) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_HAZ_1) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_HAZ_2) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_SPI2_MISO) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_SPI2_MOSI) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_SPI2_NSS) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_SPI2_SCK) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_RS485_TX) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_RS485_RX) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_RS_485_RE) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_RS485_DE) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_EXT_6) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_EXT_7) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_EXT_8))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_2M(GPIOD_EXT_5) |           \
                                     PIN_OSPEED_2M(GPIOD_HAZ_1) |           \
                                     PIN_OSPEED_2M(GPIOD_HAZ_2) |           \
                                     PIN_OSPEED_2M(GPIOD_SPI2_MISO) |       \
                                     PIN_OSPEED_2M(GPIOD_SPI2_MOSI) |       \
                                     PIN_OSPEED_2M(GPIOD_PIN5) |            \
                                     PIN_OSPEED_2M(GPIOD_SPI2_NSS) |        \
                                     PIN_OSPEED_2M(GPIOD_SPI2_SCK) |        \
                                     PIN_OSPEED_2M(GPIOD_RS485_TX) |        \
                                     PIN_OSPEED_2M(GPIOD_RS485_RX) |        \
                                     PIN_OSPEED_2M(GPIOD_PIN10) |           \
                                     PIN_OSPEED_2M(GPIOD_RS_485_RE) |       \
                                     PIN_OSPEED_2M(GPIOD_RS485_DE) |        \
                                     PIN_OSPEED_2M(GPIOD_EXT_6) |           \
                                     PIN_OSPEED_2M(GPIOD_EXT_7) |           \
                                     PIN_OSPEED_2M(GPIOD_EXT_8))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_PULLUP(GPIOD_EXT_5) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_HAZ_1) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_HAZ_2) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_SPI2_MISO) |    \
                                     PIN_PUPDR_PULLUP(GPIOD_SPI2_MOSI) |    \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_SPI2_NSS) |     \
                                     PIN_PUPDR_PULLUP(GPIOD_SPI2_SCK) |     \
                                     PIN_PUPDR_PULLUP(GPIOD_RS485_TX) |     \
                                     PIN_PUPDR_PULLUP(GPIOD_RS485_RX) |     \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_RS_485_RE) |    \
                                     PIN_PUPDR_PULLUP(GPIOD_RS485_DE) |     \
                                     PIN_PUPDR_PULLUP(GPIOD_EXT_6) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_EXT_7) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_EXT_8))
#define VAL_GPIOD_ODR               (PIN_ODR_HIGH(GPIOD_EXT_5) |            \
                                     PIN_ODR_HIGH(GPIOD_HAZ_1) |            \
                                     PIN_ODR_HIGH(GPIOD_HAZ_2) |            \
                                     PIN_ODR_HIGH(GPIOD_SPI2_MISO) |        \
                                     PIN_ODR_HIGH(GPIOD_SPI2_MOSI) |        \
                                     PIN_ODR_HIGH(GPIOD_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOD_SPI2_NSS) |         \
                                     PIN_ODR_HIGH(GPIOD_SPI2_SCK) |         \
                                     PIN_ODR_HIGH(GPIOD_RS485_TX) |         \
                                     PIN_ODR_HIGH(GPIOD_RS485_RX) |         \
                                     PIN_ODR_HIGH(GPIOD_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOD_RS_485_RE) |        \
                                     PIN_ODR_HIGH(GPIOD_RS485_DE) |         \
                                     PIN_ODR_HIGH(GPIOD_EXT_6) |            \
                                     PIN_ODR_HIGH(GPIOD_EXT_7) |            \
                                     PIN_ODR_HIGH(GPIOD_EXT_8))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_EXT_5, 0) |          \
                                     PIN_AFIO_AF(GPIOD_HAZ_1, 0) |          \
                                     PIN_AFIO_AF(GPIOD_HAZ_2, 0) |          \
                                     PIN_AFIO_AF(GPIOD_SPI2_MISO, 5) |      \
                                     PIN_AFIO_AF(GPIOD_SPI2_MOSI, 5) |      \
                                     PIN_AFIO_AF(GPIOD_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOD_SPI2_NSS, 0) |       \
                                     PIN_AFIO_AF(GPIOD_SPI2_SCK, 0))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_RS485_TX, 7) |       \
                                     PIN_AFIO_AF(GPIOD_RS485_RX, 7) |       \
                                     PIN_AFIO_AF(GPIOD_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOD_RS_485_RE, 7) |      \
                                     PIN_AFIO_AF(GPIOD_RS485_DE, 7) |       \
                                     PIN_AFIO_AF(GPIOD_EXT_6, 0) |          \
                                     PIN_AFIO_AF(GPIOD_EXT_7, 0) |          \
                                     PIN_AFIO_AF(GPIOD_EXT_8, 0))

/*
 * GPIOE setup:
 *
 * PE0  - MCU_GOOD_PW               (analog).
 * PE1  - MCU_EN_CTL_OC1            (output opendrain minimum).
 * PE2  - ST_DIS1                   (output pushpull minimum).
 * PE3  - ST_DIS2                   (output pushpull minimum).
 * PE4  - RF_GP0                    (input pullup).
 * PE5  - RF_GP1                    (input pullup).
 * PE6  - RF_GP2                    (input pullup).
 * PE7  - SENSE4                    (analog).
 * PE8  - TEMP_P                    (analog).
 * PE9  - TEMP_N                    (analog).
 * PE10 - TEMP1_P                   (analog).
 * PE11 - SENSE3                    (analog).
 * PE12 - SENSE2                    (analog).
 * PE13 - SENSE1                    (analog).
 * PE14 - RF_GP3                    (input pullup).
 * PE15 - SHUTDOWN_GP               (output pushpull minimum).
 */
#define VAL_GPIOE_MODER             (PIN_MODE_ANALOG(GPIOE_MCU_GOOD_PW) |   \
                                     PIN_MODE_OUTPUT(GPIOE_MCU_EN_CTL_OC1) |\
                                     PIN_MODE_OUTPUT(GPIOE_ST_DIS1) |       \
                                     PIN_MODE_OUTPUT(GPIOE_ST_DIS2) |       \
                                     PIN_MODE_INPUT(GPIOE_RF_GP0) |         \
                                     PIN_MODE_INPUT(GPIOE_RF_GP1) |         \
                                     PIN_MODE_INPUT(GPIOE_RF_GP2) |         \
                                     PIN_MODE_ANALOG(GPIOE_SENSE4) |        \
                                     PIN_MODE_ANALOG(GPIOE_TEMP_P) |        \
                                     PIN_MODE_ANALOG(GPIOE_TEMP_N) |        \
                                     PIN_MODE_ANALOG(GPIOE_TEMP1_P) |       \
                                     PIN_MODE_ANALOG(GPIOE_SENSE3) |        \
                                     PIN_MODE_ANALOG(GPIOE_SENSE2) |        \
                                     PIN_MODE_ANALOG(GPIOE_SENSE1) |        \
                                     PIN_MODE_INPUT(GPIOE_RF_GP3) |         \
                                     PIN_MODE_OUTPUT(GPIOE_SHUTDOWN_GP))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_MCU_GOOD_PW) |\
                                     PIN_OTYPE_OPENDRAIN(GPIOE_MCU_EN_CTL_OC1) |\
                                     PIN_OTYPE_PUSHPULL(GPIOE_ST_DIS1) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ST_DIS2) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_RF_GP0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_RF_GP1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_RF_GP2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_SENSE4) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_TEMP_P) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_TEMP_N) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_TEMP1_P) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_SENSE3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_SENSE2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_SENSE1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_RF_GP3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_SHUTDOWN_GP))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_2M(GPIOE_MCU_GOOD_PW) |     \
                                     PIN_OSPEED_2M(GPIOE_MCU_EN_CTL_OC1) |  \
                                     PIN_OSPEED_2M(GPIOE_ST_DIS1) |         \
                                     PIN_OSPEED_2M(GPIOE_ST_DIS2) |         \
                                     PIN_OSPEED_2M(GPIOE_RF_GP0) |          \
                                     PIN_OSPEED_2M(GPIOE_RF_GP1) |          \
                                     PIN_OSPEED_2M(GPIOE_RF_GP2) |          \
                                     PIN_OSPEED_2M(GPIOE_SENSE4) |          \
                                     PIN_OSPEED_2M(GPIOE_TEMP_P) |          \
                                     PIN_OSPEED_2M(GPIOE_TEMP_N) |          \
                                     PIN_OSPEED_2M(GPIOE_TEMP1_P) |         \
                                     PIN_OSPEED_2M(GPIOE_SENSE3) |          \
                                     PIN_OSPEED_2M(GPIOE_SENSE2) |          \
                                     PIN_OSPEED_2M(GPIOE_SENSE1) |          \
                                     PIN_OSPEED_2M(GPIOE_RF_GP3) |          \
                                     PIN_OSPEED_2M(GPIOE_SHUTDOWN_GP))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_FLOATING(GPIOE_MCU_GOOD_PW) |\
                                     PIN_PUPDR_FLOATING(GPIOE_MCU_EN_CTL_OC1) |\
                                     PIN_PUPDR_PULLUP(GPIOE_ST_DIS1) |      \
                                     PIN_PUPDR_PULLUP(GPIOE_ST_DIS2) |      \
                                     PIN_PUPDR_PULLUP(GPIOE_RF_GP0) |       \
                                     PIN_PUPDR_PULLUP(GPIOE_RF_GP1) |       \
                                     PIN_PUPDR_PULLUP(GPIOE_RF_GP2) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_SENSE4) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_TEMP_P) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_TEMP_N) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_TEMP1_P) |    \
                                     PIN_PUPDR_FLOATING(GPIOE_SENSE3) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_SENSE2) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_SENSE1) |     \
                                     PIN_PUPDR_PULLUP(GPIOE_RF_GP3) |       \
                                     PIN_PUPDR_PULLUP(GPIOE_SHUTDOWN_GP))
#define VAL_GPIOE_ODR               (PIN_ODR_HIGH(GPIOE_MCU_GOOD_PW) |      \
                                     PIN_ODR_HIGH(GPIOE_MCU_EN_CTL_OC1) |   \
                                     PIN_ODR_HIGH(GPIOE_ST_DIS1) |          \
                                     PIN_ODR_HIGH(GPIOE_ST_DIS2) |          \
                                     PIN_ODR_HIGH(GPIOE_RF_GP0) |           \
                                     PIN_ODR_HIGH(GPIOE_RF_GP1) |           \
                                     PIN_ODR_HIGH(GPIOE_RF_GP2) |           \
                                     PIN_ODR_HIGH(GPIOE_SENSE4) |           \
                                     PIN_ODR_HIGH(GPIOE_TEMP_P) |           \
                                     PIN_ODR_HIGH(GPIOE_TEMP_N) |           \
                                     PIN_ODR_HIGH(GPIOE_TEMP1_P) |          \
                                     PIN_ODR_HIGH(GPIOE_SENSE3) |           \
                                     PIN_ODR_HIGH(GPIOE_SENSE2) |           \
                                     PIN_ODR_HIGH(GPIOE_SENSE1) |           \
                                     PIN_ODR_HIGH(GPIOE_RF_GP3) |           \
                                     PIN_ODR_HIGH(GPIOE_SHUTDOWN_GP))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_MCU_GOOD_PW, 0) |    \
                                     PIN_AFIO_AF(GPIOE_MCU_EN_CTL_OC1, 0) | \
                                     PIN_AFIO_AF(GPIOE_ST_DIS1, 0) |        \
                                     PIN_AFIO_AF(GPIOE_ST_DIS2, 0) |        \
                                     PIN_AFIO_AF(GPIOE_RF_GP0, 0) |         \
                                     PIN_AFIO_AF(GPIOE_RF_GP1, 0) |         \
                                     PIN_AFIO_AF(GPIOE_RF_GP2, 0) |         \
                                     PIN_AFIO_AF(GPIOE_SENSE4, 0))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_TEMP_P, 0) |         \
                                     PIN_AFIO_AF(GPIOE_TEMP_N, 0) |         \
                                     PIN_AFIO_AF(GPIOE_TEMP1_P, 0) |        \
                                     PIN_AFIO_AF(GPIOE_SENSE3, 0) |         \
                                     PIN_AFIO_AF(GPIOE_SENSE2, 0) |         \
                                     PIN_AFIO_AF(GPIOE_SENSE1, 0) |         \
                                     PIN_AFIO_AF(GPIOE_RF_GP3, 0) |         \
                                     PIN_AFIO_AF(GPIOE_SHUTDOWN_GP, 0))

/*
 * GPIOF setup:
 *
 * PF0  - OSC_IN                    (input floating).
 * PF1  - OSC_OUT                   (input floating).
 * PF2  - PIN2                      (input floating).
 * PF3  - PIN3                      (input floating).
 * PF4  - AIR_HEAT                  (output pushpull minimum).
 * PF5  - PIN5                      (input floating).
 * PF6  - LSM_DR                    (input floating).
 * PF7  - PIN7                      (input floating).
 * PF8  - PIN8                      (input floating).
 * PF9  - LSM_IN1                   (input floating).
 * PF10 - LSM_IN2                   (input floating).
 * PF11 - PIN11                     (input floating).
 * PF12 - PIN12                     (input floating).
 * PF13 - PIN13                     (input floating).
 * PF14 - PIN14                     (input floating).
 * PF15 - PIN15                     (input floating).
 */
#define VAL_GPIOF_MODER             (PIN_MODE_INPUT(GPIOF_OSC_IN) |         \
                                     PIN_MODE_INPUT(GPIOF_OSC_OUT) |        \
                                     PIN_MODE_INPUT(GPIOF_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN3) |           \
                                     PIN_MODE_OUTPUT(GPIOF_AIR_HEAT) |      \
                                     PIN_MODE_INPUT(GPIOF_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOF_LSM_DR) |         \
                                     PIN_MODE_INPUT(GPIOF_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOF_LSM_IN1) |        \
                                     PIN_MODE_INPUT(GPIOF_LSM_IN2) |        \
                                     PIN_MODE_INPUT(GPIOF_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN15))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_OSC_IN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_OSC_OUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_AIR_HEAT) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_LSM_DR) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_LSM_IN1) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOF_LSM_IN2) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN15))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_100M(GPIOF_OSC_IN) |        \
                                     PIN_OSPEED_100M(GPIOF_OSC_OUT) |       \
                                     PIN_OSPEED_2M(GPIOF_PIN2) |            \
                                     PIN_OSPEED_2M(GPIOF_PIN3) |            \
                                     PIN_OSPEED_2M(GPIOF_AIR_HEAT) |        \
                                     PIN_OSPEED_2M(GPIOF_PIN5) |            \
                                     PIN_OSPEED_2M(GPIOF_LSM_DR) |          \
                                     PIN_OSPEED_2M(GPIOF_PIN7) |            \
                                     PIN_OSPEED_2M(GPIOF_PIN8) |            \
                                     PIN_OSPEED_2M(GPIOF_LSM_IN1) |         \
                                     PIN_OSPEED_2M(GPIOF_LSM_IN2) |         \
                                     PIN_OSPEED_2M(GPIOF_PIN11) |           \
                                     PIN_OSPEED_2M(GPIOF_PIN12) |           \
                                     PIN_OSPEED_2M(GPIOF_PIN13) |           \
                                     PIN_OSPEED_2M(GPIOF_PIN14) |           \
                                     PIN_OSPEED_2M(GPIOF_PIN15))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_FLOATING(GPIOF_OSC_IN) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_OSC_OUT) |    \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_AIR_HEAT) |   \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_LSM_DR) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_LSM_IN1) |    \
                                     PIN_PUPDR_FLOATING(GPIOF_LSM_IN2) |    \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN15))
#define VAL_GPIOF_ODR               (PIN_ODR_HIGH(GPIOF_OSC_IN) |           \
                                     PIN_ODR_HIGH(GPIOF_OSC_OUT) |          \
                                     PIN_ODR_HIGH(GPIOF_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOF_AIR_HEAT) |         \
                                     PIN_ODR_HIGH(GPIOF_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOF_LSM_DR) |           \
                                     PIN_ODR_HIGH(GPIOF_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOF_LSM_IN1) |          \
                                     PIN_ODR_HIGH(GPIOF_LSM_IN2) |          \
                                     PIN_ODR_HIGH(GPIOF_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN15))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_OSC_IN, 0) |         \
                                     PIN_AFIO_AF(GPIOF_OSC_OUT, 0) |        \
                                     PIN_AFIO_AF(GPIOF_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN3, 0) |           \
                                     PIN_AFIO_AF(GPIOF_AIR_HEAT, 0) |       \
                                     PIN_AFIO_AF(GPIOF_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOF_LSM_DR, 0) |         \
                                     PIN_AFIO_AF(GPIOF_PIN7, 0))
#define VAL_GPIOF_AFRH              (PIN_AFIO_AF(GPIOF_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOF_LSM_IN1, 0) |        \
                                     PIN_AFIO_AF(GPIOF_LSM_IN2, 0) |        \
                                     PIN_AFIO_AF(GPIOF_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN14, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN15, 0))


#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
