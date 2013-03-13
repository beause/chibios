/*
    Copyright (C) 2013 Genist Systems

*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for Genist Custom board
 */

/*
 * Board identifier.
 */
#define BOARD_ST GENIST_CUSTOM_A
#define BOARD_NAME                  "Genist Custom Board"

/*
 * Board oscillators-related settings.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                32768
#endif

#define STM32_LSEDRV                (3 << 3)

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                8000000
#endif

/*
 * MCU type as defined in the ST header.
 */
#define STM32F37X

/*
 * IO pins assignments.
 */
#define GPIOA_XCVR_RST              0  /* MODIFIED */
#define GPIOA_RTD_SEL               1  /* MODIFIED */
#define GPIOA_LS_PWM                2  /* MODIFIED */
#define GPIOA_RTD                   3  /* MODIFIED */
#define GPIOA_AIR_CS                4  /* MODIFIED */
#define GPIOA_SPI1_CLK              5  /* MODIFIED */
#define GPIOA_SPI1_MISO             6  /* MODIFIED */
#define GPIOA_SPI1_MOSI             7  /* MODIFIED */
#define GPIOA_PIN8                  8
#define GPIOA_RS485_TX              9  /* MODIFIED */
#define GPIOA_RS485_RX              10 /* MODIFIED */
#define GPIOA_RS485_CTS             11 /* MODIFIED */
#define GPIOA_RS485_RTS             12 /* MODIFIED */
#define GPIOA_SWDIO                 13 /* MODIFIED */
#define GPIOA_SWCLK                 14 /* MODIFIED */
#define GPIOA_JTDI                  15 /* MODIFIED */

#define GPIOB_AIR_TEMP              0  /* MODIFIED */
#define GPIOB_HALL_B                1  /* MODIFIED */
#define GPIOB_HALL_A                2  /* MODIFIED */
#define GPIOB_SWO                   3
#define GPIOB_PIN4                  4
#define GPIOB_XCVR_INT              5  /* MODIFIED */
#define GPIOB_AIR_HEATER            6  /* MODIFIED */
#define GPIOB_XCVR_CS               7  /* MODIFIED */
#define GPIOB_EXTDRV_STAT           8  /* MODIFIED */
#define GPIOB_PWR_FAULT             9  /* MODIFIED */
#define GPIOB_PIN10                 10
#define GPIOB_PIN11                 11
#define GPIOB_PIN12                 12
#define GPIOB_PIN13                 13
#define GPIOB_VAR_RUC1              14 /* MODIFIED */
#define GPIOB_VAR_RUC2              15 /* MODIFIED */

#define GPIOC_EXTDRV_A4             0   /* MODIFIED */
#define GPIOC_EXTDRV_A3             1   /* MODIFIED */
#define GPIOC_EXTDRV_A2             2   /* MODIFIED */
#define GPIOC_EXTDRV_A1             3   /* MODIFIED */
#define GPIOC_PROX_A                4   /* MODIFIED */
#define GPIOC_PROX_B                5   /* MODIFIED */
#define GPIOC_EXTDRV_B4             6   /* MODIFIED */
#define GPIOC_EXTDRV_B3             7   /* MODIFIED */
#define GPIOC_EXTDRV_B2             8   /* MODIFIED */                 
#define GPIOC_EXTDRV_B1             9   /* MODIFIED */
#define GPIOC_SPI3_SCK              10  /* Zigbee MRF24J40 */
#define GPIOC_SPI3_MISO             11  /* Zigbee MRF24J40 */
#define GPIOC_SPI3_MOSI             12  /* Zigbee MRF24J40 */
#define GPIOC_LED_G                 13  /* MODIFIED */
#define GPIOC_LED_B                 14  /* MODIFIED */
#define GPIOC_LED_R                 15  /* MODIFIED */

#define GPIOD_PIN0                  0
#define GPIOD_PIN1                  1
#define GPIOD_PIN2                  2
#define GPIOD_PIN3                  3
#define GPIOD_PIN4                  4
#define GPIOD_PIN5		    5
#define GPIOD_PIN6		    6
#define GPIOD_PIN7                  7
#define GPIOD_PIN8                  8
#define GPIOD_PIN9                  9
#define GPIOD_PIN10                 10
#define GPIOD_PIN11                 11
#define GPIOD_PIN12                 12
#define GPIOD_PIN13                 13
#define GPIOD_PIN14                 14
#define GPIOD_PIN15                 15

#define GPIOE_PIN0                  0
#define GPIOE_PIN1                  1
#define GPIOE_PIN2                  2
#define GPIOE_PIN3                  3
#define GPIOE_PIN4                  4
#define GPIOE_PIN5                  5
#define GPIOE_PIN6                  6
#define GPIOE_PIN7                  7
#define GPIOE_HAZZARD_A             8   /* MODIFIED */
#define GPIOE_HAZZARD_B             9   /* MODIFIED */
#define GPIOE_PIN10                 10
#define GPIOE_PIN11                 11
#define GPIOE_PIN12                 12
#define GPIOE_PIN13                 13
#define GPIOE_PIN14                 14
#define GPIOE_PIN15                 15

#define GPIOF_PIN0                  0
#define GPIOF_PIN1                  1
#define GPIOF_PIN2                  2
#define GPIOF_PIN3                  3
#define GPIOF_PIN4                  4
#define GPIOF_PIN5                  5
#define GPIOF_PIN6                  6
#define GPIOF_PIN7                  7
#define GPIOF_PIN8                  8
#define GPIOF_PIN9                  9
#define GPIOF_PIN10                 10
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
 * PA0  - XCVR_RST            (output pushpull).
 * PA1  - RTD_SEL             (output pushpull).
 * PA2  - LS_PWM              (input floating).
 * PA3  - RTD                 (analog).  ADC_IN3
 * PA4  - AIR_CS              (output pullup).
 * PA5  - SPI1_CLK            (alternate).
 * PA6  - SPI1_MISO           (alternate).
 * PA7  - SPI1_MOSI           (alternate).
 * PA8  - PIN8                (input floating).
 * PA9  - RS485_TX            (output).
 * PA10 - RS485_RX            (input).
 * PA11 - RS485_CTS           (input).
 * PA12 - RS485_RTS           (output).
 * PA13 - SWDIO               (alternate 0).
 * PA14 - SWCLK               (alternate 0).
 * PA15 - TDI                 (alternate 0).
 */
#define VAL_GPIOA_MODER             (PIN_MODE_OUTPUT(   GPIOA_XCVR_RST) |      \
                                     PIN_MODE_OUTPUT(   GPIOA_RTD_SEL) |       \
                                     PIN_MODE_INPUT(    GPIOA_LS_PWM) |         \
                                     PIN_MODE_INPUT(    GPIOA_RTD) |            \
                                     PIN_MODE_INPUT(    GPIOA_AIR_CS) |         \
                                     PIN_MODE_ALTERNATE(GPIOA_SPI1_CLK) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_SPI1_MISO) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_SPI1_MOSI) |  \
                                     PIN_MODE_INPUT(    GPIOA_PIN8) |           \
                                     PIN_MODE_OUTPUT(   GPIOA_RS485_TX) |      \
                                     PIN_MODE_INPUT(    GPIOA_RS485_RX) |       \
                                     PIN_MODE_INPUT(    GPIOA_RS485_CTS) |      \
                                     PIN_MODE_OUTPUT(   GPIOA_RS485_RTS) |     \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_JTDI))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_XCVR_RST) |\
                                     PIN_OTYPE_PUSHPULL(GPIOA_RTD_SEL) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_LS_PWM) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RTD) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_AIR_CS) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SPI1_CLK) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SPI1_MISO) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SPI1_MOSI) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN8) |   \
                                     PIN_OTYPE_OPENDRAIN(GPIOA_RS485_TX) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RS485_RX) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RS485_CTS) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RS485_RTS) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_JTDI))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_2M(  GPIOA_XCVR_RST) |     \
                                     PIN_OSPEED_2M(  GPIOA_RTD_SEL) |         \
                                     PIN_OSPEED_2M(  GPIOA_LS_PWM) |      \
                                     PIN_OSPEED_2M(  GPIOA_RTD) |            \
                                     PIN_OSPEED_2M(  GPIOA_AIR_CS) |            \
                                     PIN_OSPEED_100M(GPIOA_SPI1_CLK) |          \
                                     PIN_OSPEED_2M(  GPIOA_SPI1_MISO) |            \
                                     PIN_OSPEED_100M(GPIOA_SPI1_MOSI) |     \
                                     PIN_OSPEED_2M(  GPIOA_PIN8) |        \
                                     PIN_OSPEED_100M(GPIOA_RS485_TX) |      \
                                     PIN_OSPEED_100M(GPIOA_RS485_RX) |      \
                                     PIN_OSPEED_100M(GPIOA_RS485_CTS) |        \
                                     PIN_OSPEED_2M(  GPIOA_RS485_RTS) |          \
                                     PIN_OSPEED_100M(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_100M(GPIOA_SWCLK) |         \
                                     PIN_OSPEED_100M(GPIOA_JTDI))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_XCVR_RST) |\
                                     PIN_PUPDR_FLOATING(GPIOA_RTD_SEL) |    \
                                     PIN_PUPDR_FLOATING(GPIOA_LS_PWM) | \
                                     PIN_PUPDR_PULLUP(  GPIOA_RTD) |         \
                                     PIN_PUPDR_PULLUP(  GPIOA_AIR_CS) |         \
                                     PIN_PUPDR_FLOATING(GPIOA_SPI1_CLK) |       \
                                     PIN_PUPDR_PULLUP(  GPIOA_SPI1_MISO) |         \
                                     PIN_PUPDR_FLOATING(GPIOA_SPI1_MOSI) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN8) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_RS485_TX) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_RS485_RX) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_RS485_CTS) |     \
                                     PIN_PUPDR_FLOATING(GPIOA_RS485_RTS) |     \
                                     PIN_PUPDR_PULLUP(  GPIOA_SWDIO) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWCLK) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_JTDI))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_XCVR_RST) |      \
                                     PIN_ODR_HIGH(GPIOA_RTD_SEL) |          \
                                     PIN_ODR_HIGH(GPIOA_LS_PWM) |       \
                                     PIN_ODR_HIGH(GPIOA_RTD) |             \
                                     PIN_ODR_HIGH(GPIOA_AIR_CS) |             \
                                     PIN_ODR_HIGH(GPIOA_SPI1_CLK) |             \
                                     PIN_ODR_HIGH(GPIOA_SPI1_MISO) |             \
                                     PIN_ODR_LOW( GPIOA_SPI1_MOSI) |         \
                                     PIN_ODR_HIGH(GPIOA_PIN8) |         \
                                     PIN_ODR_HIGH(GPIOA_RS485_TX) |         \
                                     PIN_ODR_HIGH(GPIOA_RS485_RX) |         \
                                     PIN_ODR_HIGH(GPIOA_RS485_CTS) |           \
                                     PIN_ODR_HIGH(GPIOA_RS485_RTS) |           \
                                     PIN_ODR_HIGH(GPIOA_SWDIO) |            \
                                     PIN_ODR_HIGH(GPIOA_SWCLK) |            \
                                     PIN_ODR_HIGH(GPIOA_JTDI))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_XCVR_RST, 0) |    \
                                     PIN_AFIO_AF(GPIOA_RTD_SEL, 0) |        \
                                     PIN_AFIO_AF(GPIOA_LS_PWM, 0) |     \
                                     PIN_AFIO_AF(GPIOA_RTD, 0) |           \
                                     PIN_AFIO_AF(GPIOA_AIR_CS, 5) |           \
                                     PIN_AFIO_AF(GPIOA_SPI1_CLK, 5) |           \
                                     PIN_AFIO_AF(GPIOA_SPI1_MISO, 5) |           \
                                     PIN_AFIO_AF(GPIOA_SPI1_MOSI, 5))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_PIN8, 0) |       \
                                     PIN_AFIO_AF(GPIOA_RS485_TX, 0) |       \
                                     PIN_AFIO_AF(GPIOA_RS485_RX, 0) |       \
                                     PIN_AFIO_AF(GPIOA_RS485_CTS, 0) |        \
                                     PIN_AFIO_AF(GPIOA_RS485_RTS, 0) |        \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0) |          \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0) |          \
                                     PIN_AFIO_AF(GPIOA_JTDI, 0))

/*
 * GPIOB setup:
 *
 * PB0  - AIR_TEMP                 (analog). ADC_IN8/SDADC_AIN6P
 * PB1  - HALL_B                   (input).
 * PB2  - HALL_A                   (input pullup).
 * PB3  - SWO                      (input).
 * PB4  - PIN4                     (input floating).
 * PB5  - XCVR_INT                 (input).
 * PB6  - AIR_HEATER               (output).
 * PB7  - XCVR_CS                  (output).
 * PB8  - EXTDRV_STAT              (input pullup).
 * PB9  - PWR_FAULT                (input pullup).
 * PB10 - PIN10                    (input floating).
 * PB11 - PIN11                    (input floating).
 * PB12 - PIN12                    (input floating).
 * PB13 - PIN13                    (input floating).
 * PB14 - VAR_RUC1                 (input pullup).
 * PB15 - VAR_RUC2                 (input pullup).
 */
#define VAL_GPIOB_MODER             (PIN_MODE_ANALOG(   GPIOB_AIR_TEMP) |        \
                                     PIN_MODE_INPUT(    GPIOB_HALL_B) |    \
                                     PIN_MODE_INPUT(    GPIOB_HALL_A) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_SWO) |        \
                                     PIN_MODE_INPUT(    GPIOB_PIN4) |          \
                                     PIN_MODE_INPUT(    GPIOB_XCVR_INT) |           \
                                     PIN_MODE_OUTPUT(   GPIOB_AIR_HEATER) |   \
                                     PIN_MODE_OUTPUT(   GPIOB_XCVR_CS) |   \
                                     PIN_MODE_INPUT(    GPIOB_EXTDRV_STAT) |           \
                                     PIN_MODE_INPUT(    GPIOB_PWR_FAULT) |           \
                                     PIN_MODE_INPUT(    GPIOB_PIN10) |          \
                                     PIN_MODE_INPUT(    GPIOB_PIN11) |          \
                                     PIN_MODE_INPUT(    GPIOB_PIN12) |          \
                                     PIN_MODE_INPUT(    GPIOB_PIN13) |          \
                                     PIN_MODE_INPUT(    GPIOB_VAR_RUC1) |          \
                                     PIN_MODE_INPUT(    GPIOB_VAR_RUC2))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL( GPIOB_AIR_TEMP) |     \
                                     PIN_OTYPE_PUSHPULL( GPIOB_HALL_B) | \
                                     PIN_OTYPE_PUSHPULL( GPIOB_HALL_A) |       \
                                     PIN_OTYPE_PUSHPULL( GPIOB_SWO) |        \
                                     PIN_OTYPE_PUSHPULL( GPIOB_PIN4) |      \
                                     PIN_OTYPE_PUSHPULL( GPIOB_XCVR_INT) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_AIR_HEATER) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_XCVR_CS) |  \
                                     PIN_OTYPE_PUSHPULL( GPIOB_EXTDRV_STAT) |       \
                                     PIN_OTYPE_PUSHPULL( GPIOB_PWR_FAULT) |       \
                                     PIN_OTYPE_PUSHPULL( GPIOB_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL( GPIOB_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL( GPIOB_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL( GPIOB_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL( GPIOB_VAR_RUC1) |      \
                                     PIN_OTYPE_PUSHPULL( GPIOB_VAR_RUC2))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_2M(GPIOB_AIR_TEMP) |          \
                                     PIN_OSPEED_2M(GPIOB_HALL_B) |      \
                                     PIN_OSPEED_2M(GPIOB_HALL_A) |            \
                                     PIN_OSPEED_2M(GPIOB_SWO) |           \
                                     PIN_OSPEED_2M(GPIOB_PIN4) |         \
                                     PIN_OSPEED_2M(GPIOB_XCVR_INT) |            \
                                     PIN_OSPEED_2M(GPIOB_AIR_HEATER) |      \
                                     PIN_OSPEED_2M(GPIOB_XCVR_CS) |      \
                                     PIN_OSPEED_2M(GPIOB_EXTDRV_STAT) |            \
                                     PIN_OSPEED_2M(GPIOB_PWR_FAULT) |            \
                                     PIN_OSPEED_2M(GPIOB_PIN10) |           \
                                     PIN_OSPEED_2M(GPIOB_PIN11) |           \
                                     PIN_OSPEED_2M(GPIOB_PIN12) |           \
                                     PIN_OSPEED_2M(GPIOB_PIN13) |           \
                                     PIN_OSPEED_2M(GPIOB_VAR_RUC1) |           \
                                     PIN_OSPEED_2M(GPIOB_VAR_RUC2))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_PULLUP(GPIOB_AIR_TEMP) |     \
                                     PIN_PUPDR_PULLUP(GPIOB_HALL_B) | \
                                     PIN_PUPDR_PULLUP(GPIOB_HALL_A) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_SWO) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN4) |      \
                                     PIN_PUPDR_PULLUP(GPIOB_XCVR_INT) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_AIR_HEATER) |   \
                                     PIN_PUPDR_PULLUP(GPIOB_XCVR_CS) |   \
                                     PIN_PUPDR_PULLUP(GPIOB_EXTDRV_STAT) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_PWR_FAULT) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_VAR_RUC1) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_VAR_RUC2))
#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(GPIOB_AIR_TEMP) |           \
                                     PIN_ODR_HIGH(GPIOB_HALL_B) |       \
                                     PIN_ODR_HIGH(GPIOB_HALL_A) |             \
                                     PIN_ODR_HIGH(GPIOB_SWO) |              \
                                     PIN_ODR_HIGH(GPIOB_PIN4) |            \
                                     PIN_ODR_HIGH(GPIOB_XCVR_INT) |             \
                                     PIN_ODR_HIGH(GPIOB_AIR_HEATER) |         \
                                     PIN_ODR_HIGH(GPIOB_XCVR_CS) |         \
                                     PIN_ODR_HIGH(GPIOB_EXTDRV_STAT) |             \
                                     PIN_ODR_HIGH(GPIOB_PWR_FAULT) |             \
                                     PIN_ODR_HIGH(GPIOB_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOB_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOB_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOB_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOB_VAR_RUC1) |            \
                                     PIN_ODR_HIGH(GPIOB_VAR_RUC2))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_AIR_TEMP, 0) |         \
                                     PIN_AFIO_AF(GPIOB_HALL_B, 0) |     \
                                     PIN_AFIO_AF(GPIOB_HALL_A, 0) |           \
                                     PIN_AFIO_AF(GPIOB_SWO, 0) |            \
                                     PIN_AFIO_AF(GPIOB_PIN4, 0) |          \
                                     PIN_AFIO_AF(GPIOB_XCVR_INT, 0) |           \
                                     PIN_AFIO_AF(GPIOB_AIR_HEATER, 0) |       \
                                     PIN_AFIO_AF(GPIOB_XCVR_CS, 0))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_EXTDRV_STAT, 0) |           \
                                     PIN_AFIO_AF(GPIOB_PWR_FAULT, 0) |           \
                                     PIN_AFIO_AF(GPIOB_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOB_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOB_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOB_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOB_VAR_RUC1, 0) |          \
                                     PIN_AFIO_AF(GPIOB_VAR_RUC2, 0))

/*
 * GPIOC setup:
 *
 * PC0  - EXTDRV_A4           (output opendrain maximum).
 * PC1  - EXTDRV_A3           (output opendrain maximum).
 * PC2  - EXTDRV_A2           (output opendrain maximum).
 * PC3  - EXTDRV_A1           (output opendrain maximum).
 * PC4  - PROX_A              (input pullup).
 * PC5  - PROX_B              (input pullup).
 * PC6  - EXTDRV_B4           (output pullup).
 * PC7  - EXTDRV_B3           (output pullup).
 * PC8  - EXTDRV_B2           (output pullup).
 * PC9  - EXTDRV_B1           (output pullup).
 * PC10 - SPI3_SCK            (alternate 6).
 * PC11 - SPI3_MISO           (alternate 6).
 * PC12 - SPI3_MOSI           (alternate 6).
 * PC13 - LED_G               (output opendrain).
 * PC14 - LED_B               (output opendrain).
 * PC15 - LED_R               (output opendrain).
 */
#define VAL_GPIOC_MODER             (PIN_MODE_OUTPUT(GPIOC_EXTDRV_A4) |          \
                                     PIN_MODE_OUTPUT(GPIOC_EXTDRV_A3) |          \
                                     PIN_MODE_OUTPUT(GPIOC_EXTDRV_A2) |          \
                                     PIN_MODE_OUTPUT(GPIOC_EXTDRV_A1) |          \
                                     PIN_MODE_INPUT(GPIOC_PROX_A) |           \
                                     PIN_MODE_INPUT(GPIOC_PROX_B) |\
                                     PIN_MODE_OUTPUT(GPIOC_EXTDRV_B4) |           \
                                     PIN_MODE_OUTPUT(GPIOC_EXTDRV_B3) |           \
                                     PIN_MODE_OUTPUT(GPIOC_EXTDRV_B2) |           \
                                     PIN_MODE_OUTPUT(GPIOC_EXTDRV_B1) |           \
                                     PIN_MODE_ALTERNATE( GPIOC_SPI3_SCK) |   \
                                     PIN_MODE_ALTERNATE( GPIOC_SPI3_MISO) |  \
                                     PIN_MODE_ALTERNATE( GPIOC_SPI3_MOSI) |  \
                                     PIN_MODE_OUTPUT(GPIOC_LED_G) |          \
                                     PIN_MODE_OUTPUT(GPIOC_LED_B) |       \
                                     PIN_MODE_OUTPUT(GPIOC_LED_R))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_EXTDRV_A4) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_EXTDRV_A3) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_EXTDRV_A2) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_EXTDRV_A1) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PROX_A) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PROX_B) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_EXTDRV_B4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_EXTDRV_B3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_EXTDRV_B2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_EXTDRV_B1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SPI3_SCK) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SPI3_MISO) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SPI3_MOSI) |  \
                                     PIN_OTYPE_OPENDRAIN(GPIOC_LED_G) |      \
                                     PIN_OTYPE_OPENDRAIN(GPIOC_LED_B) |   \
                                     PIN_OTYPE_OPENDRAIN(GPIOC_LED_R))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_2M(GPIOC_EXTDRV_A4) |          \
                                     PIN_OSPEED_2M(GPIOC_EXTDRV_A3) |          \
                                     PIN_OSPEED_2M(GPIOC_EXTDRV_A2) |          \
                                     PIN_OSPEED_2M(GPIOC_EXTDRV_A1) |          \
                                     PIN_OSPEED_2M(GPIOC_PROX_A) |            \
                                     PIN_OSPEED_2M(GPIOC_PROX_B) |\
                                     PIN_OSPEED_2M(GPIOC_EXTDRV_B4) |            \
                                     PIN_OSPEED_2M(GPIOC_EXTDRV_B3) |            \
                                     PIN_OSPEED_2M(GPIOC_EXTDRV_B2) |            \
                                     PIN_OSPEED_2M(GPIOC_EXTDRV_B1) |            \
                                     PIN_OSPEED_2M(GPIOC_SPI3_SCK) |      \
                                     PIN_OSPEED_2M(GPIOC_SPI3_MISO) |     \
                                     PIN_OSPEED_2M(GPIOC_SPI3_MOSI) |     \
                                     PIN_OSPEED_2M(GPIOC_LED_G) |           \
                                     PIN_OSPEED_2M(GPIOC_LED_B) |      \
                                     PIN_OSPEED_2M(GPIOC_LED_R))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_FLOATING(GPIOC_EXTDRV_A4) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_EXTDRV_A3) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_EXTDRV_A2) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_EXTDRV_A1) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_PROX_A) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_PROX_B) |\
                                     PIN_PUPDR_FLOATING(GPIOC_EXTDRV_B4) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_EXTDRV_B3) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_EXTDRV_B2) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_EXTDRV_B1) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_SPI3_SCK) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_SPI3_MISO) |    \
                                     PIN_PUPDR_FLOATING(GPIOC_SPI3_MOSI) |  \
                                     PIN_PUPDR_FLOATING(GPIOC_LED_G) |        \
                                     PIN_PUPDR_FLOATING(GPIOC_LED_B) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_LED_R))
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_EXTDRV_A4) |             \
                                     PIN_ODR_HIGH(GPIOC_EXTDRV_A3) |             \
                                     PIN_ODR_HIGH(GPIOC_EXTDRV_A2) |             \
                                     PIN_ODR_HIGH(GPIOC_EXTDRV_A1) |             \
                                     PIN_ODR_HIGH(GPIOC_PROX_A) |             \
                                     PIN_ODR_HIGH(GPIOC_PROX_B) |   \
                                     PIN_ODR_HIGH(GPIOC_EXTDRV_B4) |             \
                                     PIN_ODR_HIGH(GPIOC_EXTDRV_B3) |             \
                                     PIN_ODR_HIGH(GPIOC_EXTDRV_B2) |             \
                                     PIN_ODR_HIGH(GPIOC_EXTDRV_B1) |             \
                                     PIN_ODR_HIGH(GPIOC_SPI3_SCK) |         \
                                     PIN_ODR_HIGH(GPIOC_SPI3_MISO) |        \
                                     PIN_ODR_HIGH(GPIOC_SPI3_MOSI) |        \
                                     PIN_ODR_HIGH(GPIOC_LED_G) |            \
                                     PIN_ODR_HIGH(GPIOC_LED_B) |         \
                                     PIN_ODR_HIGH(GPIOC_LED_R))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_EXTDRV_A4, 0) |           \
                                     PIN_AFIO_AF(GPIOC_EXTDRV_A3, 0) |           \
                                     PIN_AFIO_AF(GPIOC_EXTDRV_A2, 0) |           \
                                     PIN_AFIO_AF(GPIOC_EXTDRV_A1, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PROX_A, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PROX_B, 0) | \
                                     PIN_AFIO_AF(GPIOC_EXTDRV_B4, 0) |           \
                                     PIN_AFIO_AF(GPIOC_EXTDRV_B3, 0))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_EXTDRV_B2, 0) |           \
                                     PIN_AFIO_AF(GPIOC_EXTDRV_B1, 0) |           \
                                     PIN_AFIO_AF(GPIOC_SPI3_SCK, 6) |       \
                                     PIN_AFIO_AF(GPIOC_SPI3_MISO, 6) |      \
                                     PIN_AFIO_AF(GPIOC_SPI3_MOSI, 6) |      \
                                     PIN_AFIO_AF(GPIOC_LED_G, 0) |          \
                                     PIN_AFIO_AF(GPIOC_LED_B, 0) |       \
                                     PIN_AFIO_AF(GPIOC_LED_R, 0))

/*
 * GPIOD setup:
 *
 * PD0  - PIN0                (input floating).
 * PD1  - PIN1                (input floating).
 * PD2  - PIN2                (input floating).
 * PD3  - PIN3                (input floating).
 * PD4  - PIN4                (input floating).
 * PD5  - PIN5                (input floating).
 * PD6  - PIN6                (input floating).
 * PD7  - PIN7                (input floating).
 * PD8  - PIN8                (input floating).
 * PD9  - PIN9                (input floating).
 * PD10 - PIN10               (input floating).
 * PD11 - PIN11               (input floating)
 * PD12 - PIN12               (input floating).
 * PD13 - PIN13               (input floating).
 * PD14 - PIN14               (input floating).
 * PD15 - PIN15               (input floating).
 */
#define VAL_GPIOD_MODER             (PIN_MODE_INPUT(GPIOD_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN15))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_PIN0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN3) | \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN4) | \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN5) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN6) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN11) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN15))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_2M(GPIOD_PIN0) |        \
                                     PIN_OSPEED_2M(GPIOD_PIN1) |        \
                                     PIN_OSPEED_2M(GPIOD_PIN2) |        \
                                     PIN_OSPEED_2M(GPIOD_PIN3) |    \
                                     PIN_OSPEED_2M(GPIOD_PIN4) |    \
                                     PIN_OSPEED_2M(GPIOD_PIN5) |     \
                                     PIN_OSPEED_2M(GPIOD_PIN6) |     \
                                     PIN_OSPEED_2M(GPIOD_PIN7) |            \
                                     PIN_OSPEED_2M(GPIOD_PIN8) |            \
                                     PIN_OSPEED_2M(GPIOD_PIN9) |            \
                                     PIN_OSPEED_2M(GPIOD_PIN10) |           \
                                     PIN_OSPEED_2M(GPIOD_PIN11) |     \
                                     PIN_OSPEED_2M(GPIOD_PIN12) |           \
                                     PIN_OSPEED_2M(GPIOD_PIN13) |           \
                                     PIN_OSPEED_2M(GPIOD_PIN14) |           \
                                     PIN_OSPEED_2M(GPIOD_PIN15))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_FLOATING(GPIOD_PIN0) |     \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN1) |     \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN2) |     \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN3) | \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN4) | \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN5) |  \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN6) |  \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN7) |         \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN8) |         \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN9) |         \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN10) |        \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN11) |  \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN12) |        \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN13) |        \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN14) |        \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN15))
#define VAL_GPIOD_ODR               (PIN_ODR_HIGH(GPIOD_PIN0) |           \
                                     PIN_ODR_HIGH(GPIOD_PIN1) |           \
                                     PIN_ODR_HIGH(GPIOD_PIN2) |           \
                                     PIN_ODR_HIGH(GPIOD_PIN3) |       \
                                     PIN_ODR_HIGH(GPIOD_PIN4) |       \
                                     PIN_ODR_HIGH(GPIOD_PIN5) |        \
                                     PIN_ODR_HIGH(GPIOD_PIN6) |        \
                                     PIN_ODR_HIGH(GPIOD_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN10) |            \
                                     PIN_ODR_LOW(GPIOD_PIN11) |         \
                                     PIN_ODR_HIGH(GPIOD_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN15))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_PIN0, 0) |         \
                                     PIN_AFIO_AF(GPIOD_PIN1, 0) |         \
                                     PIN_AFIO_AF(GPIOD_PIN2, 0) |         \
                                     PIN_AFIO_AF(GPIOD_PIN3, 0) |     \
                                     PIN_AFIO_AF(GPIOD_PIN4, 0) |     \
                                     PIN_AFIO_AF(GPIOD_PIN5, 0) |      \
                                     PIN_AFIO_AF(GPIOD_PIN6, 0) |      \
                                     PIN_AFIO_AF(GPIOD_PIN7, 0))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOD_PIN11, 0) |      \
                                     PIN_AFIO_AF(GPIOD_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOD_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOD_PIN14, 0) |          \
                                     PIN_AFIO_AF(GPIOD_PIN15, 0))

/*
 * GPIOE setup:
 *
 * PE0  - PIN0                 (input floating).
 * PE1  - PIN1                 (input floating).
 * PE2  - PIN2                 (input floating).
 * PE3  - PIN3                 (input floating).
 * PE4  - PIN4                 (input floating).
 * PE5  - PIN5                 (input floating).
 * PE6  - PIN6                 (input floating).
 * PE7  - PIN7                 (input floating).
 * PE8  - HAZZARD_A            (input pullup).
 * PE9  - HAZZARD_B            (input pullup).
 * PE10 - PIN10                (input floating).
 * PE11 - PIN11                (input floating).
 * PE12 - PIN12                (input floating).
 * PE13 - PIN13                (input floating).
 * PE14 - PIN14                (input floating).
 * PE15 - PIN15                (input floating).
 */
#define VAL_GPIOE_MODER             (PIN_MODE_INPUT(GPIOE_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN2) |         \
                                     PIN_MODE_INPUT(GPIOE_PIN3) |      \
                                     PIN_MODE_INPUT(GPIOE_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN6) |        \
                                     PIN_MODE_INPUT(GPIOE_PIN7) |        \
                                     PIN_MODE_INPUT(GPIOE_HAZZARD_A) |     \
                                     PIN_MODE_INPUT(GPIOE_HAZZARD_B) |     \
                                     PIN_MODE_INPUT(GPIOE_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN12) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN14) |  \
                                     PIN_MODE_INPUT(GPIOE_PIN15))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN3) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN6) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_HAZZARD_A) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOE_HAZZARD_B) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN14) |\
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN15))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_2M(GPIOE_PIN0) |            \
                                     PIN_OSPEED_2M(GPIOE_PIN1) |            \
                                     PIN_OSPEED_2M(GPIOE_PIN2) |         \
                                     PIN_OSPEED_2M(GPIOE_PIN3) |     \
                                     PIN_OSPEED_2M(GPIOE_PIN4) |            \
                                     PIN_OSPEED_2M(GPIOE_PIN5) |            \
                                     PIN_OSPEED_2M(GPIOE_PIN6) |       \
                                     PIN_OSPEED_2M(GPIOE_PIN7) |          \
                                     PIN_OSPEED_2M(GPIOE_HAZZARD_A) |     \
                                     PIN_OSPEED_2M(GPIOE_HAZZARD_B) |     \
                                     PIN_OSPEED_2M(GPIOE_PIN10) |           \
                                     PIN_OSPEED_2M(GPIOE_PIN11) |           \
                                     PIN_OSPEED_2M(GPIOE_PIN12) |           \
                                     PIN_OSPEED_2M(GPIOE_PIN13) |           \
                                     PIN_OSPEED_2M(GPIOE_PIN14) |   \
                                     PIN_OSPEED_2M(GPIOE_PIN15))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_FLOATING(GPIOE_PIN0) |         \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN1) |         \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN2) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN3) |    \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN4) |         \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN5) |         \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN6) |    \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN7) |     \
                                     PIN_PUPDR_PULLUP(GPIOE_HAZZARD_A) |  \
                                     PIN_PUPDR_PULLUP(GPIOE_HAZZARD_B) |  \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN10) |        \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN11) |        \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN12) |        \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN13) |        \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN14) |\
                                     PIN_PUPDR_FLOATING(GPIOE_PIN15))
#define VAL_GPIOE_ODR               (PIN_ODR_HIGH(GPIOE_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN2) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN3) |        \
                                     PIN_ODR_HIGH(GPIOE_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN6) |          \
                                     PIN_ODR_HIGH(GPIOE_PIN7) |           \
                                     PIN_ODR_HIGH(GPIOE_HAZZARD_A) |        \
                                     PIN_ODR_HIGH(GPIOE_HAZZARD_B) |        \
                                     PIN_ODR_HIGH(GPIOE_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN12) |              \
                                     PIN_ODR_LOW(GPIOE_PIN13) |             \
                                     PIN_ODR_LOW(GPIOE_PIN14) |     \
                                     PIN_ODR_LOW(GPIOE_PIN15))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_PIN0, 0) |           \
                                     PIN_AFIO_AF(GPIOE_PIN1, 0) |           \
                                     PIN_AFIO_AF(GPIOE_PIN2, 0) |          \
                                     PIN_AFIO_AF(GPIOE_PIN3, 0) |      \
                                     PIN_AFIO_AF(GPIOE_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOE_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOE_PIN6, 0) |        \
                                     PIN_AFIO_AF(GPIOE_PIN7, 0))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_HAZZARD_A, 0) |      \
                                     PIN_AFIO_AF(GPIOE_HAZZARD_B, 0) |      \
                                     PIN_AFIO_AF(GPIOE_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOE_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOE_PIN12, 0) |            \
                                     PIN_AFIO_AF(GPIOE_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOE_PIN14, 0) |  \
                                     PIN_AFIO_AF(GPIOE_PIN15, 0))

/*
 * GPIOF setup:
 *
 * PF0  - PIN0                (input floating).
 * PF1  - PIN1                (input floating).
 * PF2  - PIN2                (input floating).
 * PF3  - PIN3                (input floating).
 * PF4  - PIN4                (input floating).
 * PF5  - PIN5                (input floating).
 * PF6  - PIN6                (input floating).
 * PF7  - PIN7                (input floating).
 * PF8  - PIN8                (input floating).
 * PF9  - PIN9                (input floating).
 * PF10 - PIN10               (input floating).
 * PF11 - PIN11               (input floating)
 * PF12 - PIN12               (input floating).
 * PF13 - PIN13               (input floating).
 * PF14 - PIN14               (input floating).
 * PF15 - PIN15               (input floating).
 */
#define VAL_GPIOF_MODER             (PIN_MODE_INPUT(GPIOF_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN15))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_PIN0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN3) | \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN4) | \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN5) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN6) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN11) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN15))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_2M(GPIOF_PIN0) |        \
                                     PIN_OSPEED_2M(GPIOF_PIN1) |        \
                                     PIN_OSPEED_2M(GPIOF_PIN2) |        \
                                     PIN_OSPEED_2M(GPIOF_PIN3) |    \
                                     PIN_OSPEED_2M(GPIOF_PIN4) |    \
                                     PIN_OSPEED_2M(GPIOF_PIN5) |     \
                                     PIN_OSPEED_2M(GPIOF_PIN6) |     \
                                     PIN_OSPEED_2M(GPIOF_PIN7) |            \
                                     PIN_OSPEED_2M(GPIOF_PIN8) |            \
                                     PIN_OSPEED_2M(GPIOF_PIN9) |            \
                                     PIN_OSPEED_2M(GPIOF_PIN10) |           \
                                     PIN_OSPEED_2M(GPIOF_PIN11) |     \
                                     PIN_OSPEED_2M(GPIOF_PIN12) |           \
                                     PIN_OSPEED_2M(GPIOF_PIN13) |           \
                                     PIN_OSPEED_2M(GPIOF_PIN14) |           \
                                     PIN_OSPEED_2M(GPIOF_PIN15))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_FLOATING(GPIOF_PIN0) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN1) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN2) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN3) | \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN4) | \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN5) |  \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN6) |  \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN7) |         \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN8) |         \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN9) |         \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN10) |        \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN11) |  \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN12) |        \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN13) |        \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN14) |        \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN15))
#define VAL_GPIOF_ODR               (PIN_ODR_HIGH(GPIOF_PIN0) |           \
                                     PIN_ODR_HIGH(GPIOF_PIN1) |           \
                                     PIN_ODR_HIGH(GPIOF_PIN2) |           \
                                     PIN_ODR_HIGH(GPIOF_PIN3) |       \
                                     PIN_ODR_HIGH(GPIOF_PIN4) |       \
                                     PIN_ODR_HIGH(GPIOF_PIN5) |        \
                                     PIN_ODR_HIGH(GPIOF_PIN6) |        \
                                     PIN_ODR_HIGH(GPIOF_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN10) |            \
                                     PIN_ODR_LOW(GPIOF_PIN11) |         \
                                     PIN_ODR_HIGH(GPIOF_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN15))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_PIN0, 0) |         \
                                     PIN_AFIO_AF(GPIOF_PIN1, 0) |         \
                                     PIN_AFIO_AF(GPIOF_PIN2, 0) |         \
                                     PIN_AFIO_AF(GPIOF_PIN3, 0) |     \
                                     PIN_AFIO_AF(GPIOF_PIN4, 0) |     \
                                     PIN_AFIO_AF(GPIOF_PIN5, 0) |      \
                                     PIN_AFIO_AF(GPIOF_PIN6, 0) |      \
                                     PIN_AFIO_AF(GPIOF_PIN7, 0))
#define VAL_GPIOF_AFRH              (PIN_AFIO_AF(GPIOF_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN11, 0) |      \
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
