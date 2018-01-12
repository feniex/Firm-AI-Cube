/*******************************************************************************
* File Name: UART_In_PINS.h
* Version 3.10
*
* Description:
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_UART_In_H)
#define CY_SCB_PINS_UART_In_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define UART_In_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define UART_In_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define UART_In_REMOVE_TX_SDA_MISO_PIN      (1u)
#define UART_In_REMOVE_SCLK_PIN      (1u)
#define UART_In_REMOVE_SS0_PIN      (1u)
#define UART_In_REMOVE_SS1_PIN                 (1u)
#define UART_In_REMOVE_SS2_PIN                 (1u)
#define UART_In_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define UART_In_REMOVE_I2C_PINS                (1u)
#define UART_In_REMOVE_SPI_MASTER_PINS         (1u)
#define UART_In_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define UART_In_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define UART_In_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define UART_In_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define UART_In_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define UART_In_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define UART_In_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define UART_In_REMOVE_SPI_SLAVE_PINS          (1u)
#define UART_In_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define UART_In_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define UART_In_REMOVE_UART_TX_PIN             (0u)
#define UART_In_REMOVE_UART_RX_TX_PIN          (1u)
#define UART_In_REMOVE_UART_RX_PIN             (0u)
#define UART_In_REMOVE_UART_RX_WAKE_PIN        (1u)
#define UART_In_REMOVE_UART_RTS_PIN            (1u)
#define UART_In_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define UART_In_RX_WAKE_SCL_MOSI_PIN (0u == UART_In_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define UART_In_RX_SCL_MOSI_PIN     (0u == UART_In_REMOVE_RX_SCL_MOSI_PIN)
#define UART_In_TX_SDA_MISO_PIN     (0u == UART_In_REMOVE_TX_SDA_MISO_PIN)
#define UART_In_SCLK_PIN     (0u == UART_In_REMOVE_SCLK_PIN)
#define UART_In_SS0_PIN     (0u == UART_In_REMOVE_SS0_PIN)
#define UART_In_SS1_PIN                (0u == UART_In_REMOVE_SS1_PIN)
#define UART_In_SS2_PIN                (0u == UART_In_REMOVE_SS2_PIN)
#define UART_In_SS3_PIN                (0u == UART_In_REMOVE_SS3_PIN)

/* Mode defined pins */
#define UART_In_I2C_PINS               (0u == UART_In_REMOVE_I2C_PINS)
#define UART_In_SPI_MASTER_PINS        (0u == UART_In_REMOVE_SPI_MASTER_PINS)
#define UART_In_SPI_MASTER_SCLK_PIN    (0u == UART_In_REMOVE_SPI_MASTER_SCLK_PIN)
#define UART_In_SPI_MASTER_MOSI_PIN    (0u == UART_In_REMOVE_SPI_MASTER_MOSI_PIN)
#define UART_In_SPI_MASTER_MISO_PIN    (0u == UART_In_REMOVE_SPI_MASTER_MISO_PIN)
#define UART_In_SPI_MASTER_SS0_PIN     (0u == UART_In_REMOVE_SPI_MASTER_SS0_PIN)
#define UART_In_SPI_MASTER_SS1_PIN     (0u == UART_In_REMOVE_SPI_MASTER_SS1_PIN)
#define UART_In_SPI_MASTER_SS2_PIN     (0u == UART_In_REMOVE_SPI_MASTER_SS2_PIN)
#define UART_In_SPI_MASTER_SS3_PIN     (0u == UART_In_REMOVE_SPI_MASTER_SS3_PIN)
#define UART_In_SPI_SLAVE_PINS         (0u == UART_In_REMOVE_SPI_SLAVE_PINS)
#define UART_In_SPI_SLAVE_MOSI_PIN     (0u == UART_In_REMOVE_SPI_SLAVE_MOSI_PIN)
#define UART_In_SPI_SLAVE_MISO_PIN     (0u == UART_In_REMOVE_SPI_SLAVE_MISO_PIN)
#define UART_In_UART_TX_PIN            (0u == UART_In_REMOVE_UART_TX_PIN)
#define UART_In_UART_RX_TX_PIN         (0u == UART_In_REMOVE_UART_RX_TX_PIN)
#define UART_In_UART_RX_PIN            (0u == UART_In_REMOVE_UART_RX_PIN)
#define UART_In_UART_RX_WAKE_PIN       (0u == UART_In_REMOVE_UART_RX_WAKE_PIN)
#define UART_In_UART_RTS_PIN           (0u == UART_In_REMOVE_UART_RTS_PIN)
#define UART_In_UART_CTS_PIN           (0u == UART_In_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (UART_In_RX_WAKE_SCL_MOSI_PIN)
    #include "UART_In_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (UART_In_RX_SCL_MOSI) */

#if (UART_In_RX_SCL_MOSI_PIN)
    #include "UART_In_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (UART_In_RX_SCL_MOSI) */

#if (UART_In_TX_SDA_MISO_PIN)
    #include "UART_In_uart_tx_i2c_sda_spi_miso.h"
#endif /* (UART_In_TX_SDA_MISO) */

#if (UART_In_SCLK_PIN)
    #include "UART_In_spi_sclk.h"
#endif /* (UART_In_SCLK) */

#if (UART_In_SS0_PIN)
    #include "UART_In_spi_ss0.h"
#endif /* (UART_In_SS0_PIN) */

#if (UART_In_SS1_PIN)
    #include "UART_In_spi_ss1.h"
#endif /* (UART_In_SS1_PIN) */

#if (UART_In_SS2_PIN)
    #include "UART_In_spi_ss2.h"
#endif /* (UART_In_SS2_PIN) */

#if (UART_In_SS3_PIN)
    #include "UART_In_spi_ss3.h"
#endif /* (UART_In_SS3_PIN) */

#if (UART_In_I2C_PINS)
    #include "UART_In_scl.h"
    #include "UART_In_sda.h"
#endif /* (UART_In_I2C_PINS) */

#if (UART_In_SPI_MASTER_PINS)
#if (UART_In_SPI_MASTER_SCLK_PIN)
    #include "UART_In_sclk_m.h"
#endif /* (UART_In_SPI_MASTER_SCLK_PIN) */

#if (UART_In_SPI_MASTER_MOSI_PIN)
    #include "UART_In_mosi_m.h"
#endif /* (UART_In_SPI_MASTER_MOSI_PIN) */

#if (UART_In_SPI_MASTER_MISO_PIN)
    #include "UART_In_miso_m.h"
#endif /*(UART_In_SPI_MASTER_MISO_PIN) */
#endif /* (UART_In_SPI_MASTER_PINS) */

#if (UART_In_SPI_SLAVE_PINS)
    #include "UART_In_sclk_s.h"
    #include "UART_In_ss_s.h"

#if (UART_In_SPI_SLAVE_MOSI_PIN)
    #include "UART_In_mosi_s.h"
#endif /* (UART_In_SPI_SLAVE_MOSI_PIN) */

#if (UART_In_SPI_SLAVE_MISO_PIN)
    #include "UART_In_miso_s.h"
#endif /*(UART_In_SPI_SLAVE_MISO_PIN) */
#endif /* (UART_In_SPI_SLAVE_PINS) */

#if (UART_In_SPI_MASTER_SS0_PIN)
    #include "UART_In_ss0_m.h"
#endif /* (UART_In_SPI_MASTER_SS0_PIN) */

#if (UART_In_SPI_MASTER_SS1_PIN)
    #include "UART_In_ss1_m.h"
#endif /* (UART_In_SPI_MASTER_SS1_PIN) */

#if (UART_In_SPI_MASTER_SS2_PIN)
    #include "UART_In_ss2_m.h"
#endif /* (UART_In_SPI_MASTER_SS2_PIN) */

#if (UART_In_SPI_MASTER_SS3_PIN)
    #include "UART_In_ss3_m.h"
#endif /* (UART_In_SPI_MASTER_SS3_PIN) */

#if (UART_In_UART_TX_PIN)
    #include "UART_In_tx.h"
#endif /* (UART_In_UART_TX_PIN) */

#if (UART_In_UART_RX_TX_PIN)
    #include "UART_In_rx_tx.h"
#endif /* (UART_In_UART_RX_TX_PIN) */

#if (UART_In_UART_RX_PIN)
    #include "UART_In_rx.h"
#endif /* (UART_In_UART_RX_PIN) */

#if (UART_In_UART_RX_WAKE_PIN)
    #include "UART_In_rx_wake.h"
#endif /* (UART_In_UART_RX_WAKE_PIN) */

#if (UART_In_UART_RTS_PIN)
    #include "UART_In_rts.h"
#endif /* (UART_In_UART_RTS_PIN) */

#if (UART_In_UART_CTS_PIN)
    #include "UART_In_cts.h"
#endif /* (UART_In_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (UART_In_RX_WAKE_SCL_MOSI_PIN)
    #define UART_In_RX_WAKE_SCL_MOSI_HSIOM_REG \
                            (*(reg32 *) UART_In_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define UART_In_RX_WAKE_SCL_MOSI_HSIOM_PTR \
                            ( (reg32 *) UART_In_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define UART_In_RX_WAKE_SCL_MOSI_HSIOM_MASK \
                            (UART_In_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define UART_In_RX_WAKE_SCL_MOSI_HSIOM_POS \
                            (UART_In_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)

    #define UART_In_RX_WAKE_SCL_MOSI_INTCFG_REG \
                            (*(reg32 *) UART_In_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define UART_In_RX_WAKE_SCL_MOSI_INTCFG_PTR \
                            ( (reg32 *) UART_In_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define UART_In_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (UART_In_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define UART_In_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK \
                            ((uint32) UART_In_INTCFG_TYPE_MASK << \
                                      UART_In_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#endif /* (UART_In_RX_WAKE_SCL_MOSI_PIN) */

#if (UART_In_RX_SCL_MOSI_PIN)
    #define UART_In_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) UART_In_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define UART_In_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) UART_In_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define UART_In_RX_SCL_MOSI_HSIOM_MASK  (UART_In_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define UART_In_RX_SCL_MOSI_HSIOM_POS   (UART_In_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
#endif /* (UART_In_RX_SCL_MOSI_PIN) */

#if (UART_In_TX_SDA_MISO_PIN)
    #define UART_In_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) UART_In_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define UART_In_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) UART_In_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define UART_In_TX_SDA_MISO_HSIOM_MASK  (UART_In_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define UART_In_TX_SDA_MISO_HSIOM_POS   (UART_In_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
#endif /* (UART_In_TX_SDA_MISO_PIN) */

#if (UART_In_SCLK_PIN)
    #define UART_In_SCLK_HSIOM_REG   (*(reg32 *) UART_In_spi_sclk__0__HSIOM)
    #define UART_In_SCLK_HSIOM_PTR   ( (reg32 *) UART_In_spi_sclk__0__HSIOM)
    #define UART_In_SCLK_HSIOM_MASK  (UART_In_spi_sclk__0__HSIOM_MASK)
    #define UART_In_SCLK_HSIOM_POS   (UART_In_spi_sclk__0__HSIOM_SHIFT)
#endif /* (UART_In_SCLK_PIN) */

#if (UART_In_SS0_PIN)
    #define UART_In_SS0_HSIOM_REG   (*(reg32 *) UART_In_spi_ss0__0__HSIOM)
    #define UART_In_SS0_HSIOM_PTR   ( (reg32 *) UART_In_spi_ss0__0__HSIOM)
    #define UART_In_SS0_HSIOM_MASK  (UART_In_spi_ss0__0__HSIOM_MASK)
    #define UART_In_SS0_HSIOM_POS   (UART_In_spi_ss0__0__HSIOM_SHIFT)
#endif /* (UART_In_SS0_PIN) */

#if (UART_In_SS1_PIN)
    #define UART_In_SS1_HSIOM_REG      (*(reg32 *) UART_In_spi_ss1__0__HSIOM)
    #define UART_In_SS1_HSIOM_PTR      ( (reg32 *) UART_In_spi_ss1__0__HSIOM)
    #define UART_In_SS1_HSIOM_MASK     (UART_In_spi_ss1__0__HSIOM_MASK)
    #define UART_In_SS1_HSIOM_POS      (UART_In_spi_ss1__0__HSIOM_SHIFT)
#endif /* (UART_In_SS1_PIN) */

#if (UART_In_SS2_PIN)
    #define UART_In_SS2_HSIOM_REG     (*(reg32 *) UART_In_spi_ss2__0__HSIOM)
    #define UART_In_SS2_HSIOM_PTR     ( (reg32 *) UART_In_spi_ss2__0__HSIOM)
    #define UART_In_SS2_HSIOM_MASK    (UART_In_spi_ss2__0__HSIOM_MASK)
    #define UART_In_SS2_HSIOM_POS     (UART_In_spi_ss2__0__HSIOM_SHIFT)
#endif /* (UART_In_SS2_PIN) */

#if (UART_In_SS3_PIN)
    #define UART_In_SS3_HSIOM_REG     (*(reg32 *) UART_In_spi_ss3__0__HSIOM)
    #define UART_In_SS3_HSIOM_PTR     ( (reg32 *) UART_In_spi_ss3__0__HSIOM)
    #define UART_In_SS3_HSIOM_MASK    (UART_In_spi_ss3__0__HSIOM_MASK)
    #define UART_In_SS3_HSIOM_POS     (UART_In_spi_ss3__0__HSIOM_SHIFT)
#endif /* (UART_In_SS3_PIN) */

#if (UART_In_I2C_PINS)
    #define UART_In_SCL_HSIOM_REG     (*(reg32 *) UART_In_scl__0__HSIOM)
    #define UART_In_SCL_HSIOM_PTR     ( (reg32 *) UART_In_scl__0__HSIOM)
    #define UART_In_SCL_HSIOM_MASK    (UART_In_scl__0__HSIOM_MASK)
    #define UART_In_SCL_HSIOM_POS     (UART_In_scl__0__HSIOM_SHIFT)

    #define UART_In_SDA_HSIOM_REG     (*(reg32 *) UART_In_sda__0__HSIOM)
    #define UART_In_SDA_HSIOM_PTR     ( (reg32 *) UART_In_sda__0__HSIOM)
    #define UART_In_SDA_HSIOM_MASK    (UART_In_sda__0__HSIOM_MASK)
    #define UART_In_SDA_HSIOM_POS     (UART_In_sda__0__HSIOM_SHIFT)
#endif /* (UART_In_I2C_PINS) */

#if (UART_In_SPI_MASTER_SCLK_PIN)
    #define UART_In_SCLK_M_HSIOM_REG   (*(reg32 *) UART_In_sclk_m__0__HSIOM)
    #define UART_In_SCLK_M_HSIOM_PTR   ( (reg32 *) UART_In_sclk_m__0__HSIOM)
    #define UART_In_SCLK_M_HSIOM_MASK  (UART_In_sclk_m__0__HSIOM_MASK)
    #define UART_In_SCLK_M_HSIOM_POS   (UART_In_sclk_m__0__HSIOM_SHIFT)
#endif /* (UART_In_SPI_MASTER_SCLK_PIN) */

#if (UART_In_SPI_MASTER_SS0_PIN)
    #define UART_In_SS0_M_HSIOM_REG    (*(reg32 *) UART_In_ss0_m__0__HSIOM)
    #define UART_In_SS0_M_HSIOM_PTR    ( (reg32 *) UART_In_ss0_m__0__HSIOM)
    #define UART_In_SS0_M_HSIOM_MASK   (UART_In_ss0_m__0__HSIOM_MASK)
    #define UART_In_SS0_M_HSIOM_POS    (UART_In_ss0_m__0__HSIOM_SHIFT)
#endif /* (UART_In_SPI_MASTER_SS0_PIN) */

#if (UART_In_SPI_MASTER_SS1_PIN)
    #define UART_In_SS1_M_HSIOM_REG    (*(reg32 *) UART_In_ss1_m__0__HSIOM)
    #define UART_In_SS1_M_HSIOM_PTR    ( (reg32 *) UART_In_ss1_m__0__HSIOM)
    #define UART_In_SS1_M_HSIOM_MASK   (UART_In_ss1_m__0__HSIOM_MASK)
    #define UART_In_SS1_M_HSIOM_POS    (UART_In_ss1_m__0__HSIOM_SHIFT)
#endif /* (UART_In_SPI_MASTER_SS1_PIN) */

#if (UART_In_SPI_MASTER_SS2_PIN)
    #define UART_In_SS2_M_HSIOM_REG    (*(reg32 *) UART_In_ss2_m__0__HSIOM)
    #define UART_In_SS2_M_HSIOM_PTR    ( (reg32 *) UART_In_ss2_m__0__HSIOM)
    #define UART_In_SS2_M_HSIOM_MASK   (UART_In_ss2_m__0__HSIOM_MASK)
    #define UART_In_SS2_M_HSIOM_POS    (UART_In_ss2_m__0__HSIOM_SHIFT)
#endif /* (UART_In_SPI_MASTER_SS2_PIN) */

#if (UART_In_SPI_MASTER_SS3_PIN)
    #define UART_In_SS3_M_HSIOM_REG    (*(reg32 *) UART_In_ss3_m__0__HSIOM)
    #define UART_In_SS3_M_HSIOM_PTR    ( (reg32 *) UART_In_ss3_m__0__HSIOM)
    #define UART_In_SS3_M_HSIOM_MASK   (UART_In_ss3_m__0__HSIOM_MASK)
    #define UART_In_SS3_M_HSIOM_POS    (UART_In_ss3_m__0__HSIOM_SHIFT)
#endif /* (UART_In_SPI_MASTER_SS3_PIN) */

#if (UART_In_UART_TX_PIN)
    #define UART_In_TX_HSIOM_REG   (*(reg32 *) UART_In_tx__0__HSIOM)
    #define UART_In_TX_HSIOM_PTR   ( (reg32 *) UART_In_tx_0__HSIOM)
    #define UART_In_TX_HSIOM_MASK  (UART_In_tx__0__HSIOM_MASK)
    #define UART_In_TX_HSIOM_POS   (UART_In_tx__0__HSIOM_SHIFT)
#endif /* (UART_In_UART_TX_PIN) */

#if (UART_In_UART_RTS_PIN)
    #define UART_In_RTS_HSIOM_REG  (*(reg32 *) UART_In_rts__0__HSIOM)
    #define UART_In_RTS_HSIOM_PTR  ( (reg32 *) UART_In_rts__0__HSIOM)
    #define UART_In_RTS_HSIOM_MASK (UART_In_rts__0__HSIOM_MASK)
    #define UART_In_RTS_HSIOM_POS  (UART_In_rts__0__HSIOM_SHIFT)
#endif /* (UART_In_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constants */
#define UART_In_HSIOM_DEF_SEL      (0x00u)
#define UART_In_HSIOM_GPIO_SEL     (0x00u)
#define UART_In_HSIOM_UART_SEL     (0x09u)
#define UART_In_HSIOM_I2C_SEL      (0x0Eu)
#define UART_In_HSIOM_SPI_SEL      (0x0Fu)

#define UART_In_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define UART_In_RX_SCL_MOSI_PIN_INDEX       (0u)
#define UART_In_TX_SDA_MISO_PIN_INDEX       (1u)
#define UART_In_SCLK_PIN_INDEX       (2u)
#define UART_In_SS0_PIN_INDEX       (3u)
#define UART_In_SS1_PIN_INDEX                  (4u)
#define UART_In_SS2_PIN_INDEX                  (5u)
#define UART_In_SS3_PIN_INDEX                  (6u)

#define UART_In_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << UART_In_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define UART_In_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << UART_In_RX_SCL_MOSI_PIN_INDEX)
#define UART_In_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << UART_In_TX_SDA_MISO_PIN_INDEX)
#define UART_In_SCLK_PIN_MASK     ((uint32) 0x01u << UART_In_SCLK_PIN_INDEX)
#define UART_In_SS0_PIN_MASK     ((uint32) 0x01u << UART_In_SS0_PIN_INDEX)
#define UART_In_SS1_PIN_MASK                ((uint32) 0x01u << UART_In_SS1_PIN_INDEX)
#define UART_In_SS2_PIN_MASK                ((uint32) 0x01u << UART_In_SS2_PIN_INDEX)
#define UART_In_SS3_PIN_MASK                ((uint32) 0x01u << UART_In_SS3_PIN_INDEX)

/* Pin interrupt constants */
#define UART_In_INTCFG_TYPE_MASK           (0x03u)
#define UART_In_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants */
#define UART_In_PIN_DM_ALG_HIZ  (0u)
#define UART_In_PIN_DM_DIG_HIZ  (1u)
#define UART_In_PIN_DM_OD_LO    (4u)
#define UART_In_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define UART_In_DM_MASK    (0x7u)
#define UART_In_DM_SIZE    (3)
#define UART_In_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) UART_In_DM_MASK << (UART_In_DM_SIZE * (pos)))) >> \
                                                              (UART_In_DM_SIZE * (pos)) )

#if (UART_In_TX_SDA_MISO_PIN)
    #define UART_In_CHECK_TX_SDA_MISO_PIN_USED \
                (UART_In_PIN_DM_ALG_HIZ != \
                    UART_In_GET_P4_PIN_DM(UART_In_uart_tx_i2c_sda_spi_miso_PC, \
                                                   UART_In_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (UART_In_TX_SDA_MISO_PIN) */

#if (UART_In_SS0_PIN)
    #define UART_In_CHECK_SS0_PIN_USED \
                (UART_In_PIN_DM_ALG_HIZ != \
                    UART_In_GET_P4_PIN_DM(UART_In_spi_ss0_PC, \
                                                   UART_In_spi_ss0_SHIFT))
#endif /* (UART_In_SS0_PIN) */

/* Set bits-mask in register */
#define UART_In_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define UART_In_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define UART_In_SET_HSIOM_SEL(reg, mask, pos, sel) UART_In_SET_REGISTER_BITS(reg, mask, pos, sel)
#define UART_In_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        UART_In_SET_REGISTER_BITS(reg, mask, pos, intType)
#define UART_In_SET_INP_DIS(reg, mask, val) UART_In_SET_REGISTER_BIT(reg, mask, val)

/* UART_In_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  UART_In_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (UART_In_CY_SCBIP_V0)
#if (UART_In_I2C_PINS)
    #define UART_In_SET_I2C_SCL_DR(val) UART_In_scl_Write(val)

    #define UART_In_SET_I2C_SCL_HSIOM_SEL(sel) \
                          UART_In_SET_HSIOM_SEL(UART_In_SCL_HSIOM_REG,  \
                                                         UART_In_SCL_HSIOM_MASK, \
                                                         UART_In_SCL_HSIOM_POS,  \
                                                         (sel))
    #define UART_In_WAIT_SCL_SET_HIGH  (0u == UART_In_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (UART_In_RX_WAKE_SCL_MOSI_PIN)
    #define UART_In_SET_I2C_SCL_DR(val) \
                            UART_In_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define UART_In_SET_I2C_SCL_HSIOM_SEL(sel) \
                    UART_In_SET_HSIOM_SEL(UART_In_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   UART_In_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   UART_In_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define UART_In_WAIT_SCL_SET_HIGH  (0u == UART_In_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (UART_In_RX_SCL_MOSI_PIN)
    #define UART_In_SET_I2C_SCL_DR(val) \
                            UART_In_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define UART_In_SET_I2C_SCL_HSIOM_SEL(sel) \
                            UART_In_SET_HSIOM_SEL(UART_In_RX_SCL_MOSI_HSIOM_REG,  \
                                                           UART_In_RX_SCL_MOSI_HSIOM_MASK, \
                                                           UART_In_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define UART_In_WAIT_SCL_SET_HIGH  (0u == UART_In_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define UART_In_SET_I2C_SCL_DR(val) \
                                                    do{ /* Does nothing */ }while(0)
    #define UART_In_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                    do{ /* Does nothing */ }while(0)

    #define UART_In_WAIT_SCL_SET_HIGH  (0u)
#endif /* (UART_In_I2C_PINS) */

/* SCB I2C: sda signal */
#if (UART_In_I2C_PINS)
    #define UART_In_WAIT_SDA_SET_HIGH  (0u == UART_In_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (UART_In_TX_SDA_MISO_PIN)
    #define UART_In_WAIT_SDA_SET_HIGH  (0u == UART_In_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define UART_In_WAIT_SDA_SET_HIGH  (0u)
#endif /* (UART_In_MOSI_SCL_RX_PIN) */
#endif /* (UART_In_CY_SCBIP_V0) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define UART_In_REMOVE_MOSI_SCL_RX_WAKE_PIN    UART_In_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define UART_In_REMOVE_MOSI_SCL_RX_PIN         UART_In_REMOVE_RX_SCL_MOSI_PIN
#define UART_In_REMOVE_MISO_SDA_TX_PIN         UART_In_REMOVE_TX_SDA_MISO_PIN
#ifndef UART_In_REMOVE_SCLK_PIN
#define UART_In_REMOVE_SCLK_PIN                UART_In_REMOVE_SCLK_PIN
#endif /* UART_In_REMOVE_SCLK_PIN */
#ifndef UART_In_REMOVE_SS0_PIN
#define UART_In_REMOVE_SS0_PIN                 UART_In_REMOVE_SS0_PIN
#endif /* UART_In_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define UART_In_MOSI_SCL_RX_WAKE_PIN   UART_In_RX_WAKE_SCL_MOSI_PIN
#define UART_In_MOSI_SCL_RX_PIN        UART_In_RX_SCL_MOSI_PIN
#define UART_In_MISO_SDA_TX_PIN        UART_In_TX_SDA_MISO_PIN
#ifndef UART_In_SCLK_PIN
#define UART_In_SCLK_PIN               UART_In_SCLK_PIN
#endif /* UART_In_SCLK_PIN */
#ifndef UART_In_SS0_PIN
#define UART_In_SS0_PIN                UART_In_SS0_PIN
#endif /* UART_In_SS0_PIN */

#if (UART_In_MOSI_SCL_RX_WAKE_PIN)
    #define UART_In_MOSI_SCL_RX_WAKE_HSIOM_REG     UART_In_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UART_In_MOSI_SCL_RX_WAKE_HSIOM_PTR     UART_In_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UART_In_MOSI_SCL_RX_WAKE_HSIOM_MASK    UART_In_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UART_In_MOSI_SCL_RX_WAKE_HSIOM_POS     UART_In_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define UART_In_MOSI_SCL_RX_WAKE_INTCFG_REG    UART_In_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UART_In_MOSI_SCL_RX_WAKE_INTCFG_PTR    UART_In_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define UART_In_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   UART_In_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UART_In_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  UART_In_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (UART_In_RX_WAKE_SCL_MOSI_PIN) */

#if (UART_In_MOSI_SCL_RX_PIN)
    #define UART_In_MOSI_SCL_RX_HSIOM_REG      UART_In_RX_SCL_MOSI_HSIOM_REG
    #define UART_In_MOSI_SCL_RX_HSIOM_PTR      UART_In_RX_SCL_MOSI_HSIOM_PTR
    #define UART_In_MOSI_SCL_RX_HSIOM_MASK     UART_In_RX_SCL_MOSI_HSIOM_MASK
    #define UART_In_MOSI_SCL_RX_HSIOM_POS      UART_In_RX_SCL_MOSI_HSIOM_POS
#endif /* (UART_In_MOSI_SCL_RX_PIN) */

#if (UART_In_MISO_SDA_TX_PIN)
    #define UART_In_MISO_SDA_TX_HSIOM_REG      UART_In_TX_SDA_MISO_HSIOM_REG
    #define UART_In_MISO_SDA_TX_HSIOM_PTR      UART_In_TX_SDA_MISO_HSIOM_REG
    #define UART_In_MISO_SDA_TX_HSIOM_MASK     UART_In_TX_SDA_MISO_HSIOM_REG
    #define UART_In_MISO_SDA_TX_HSIOM_POS      UART_In_TX_SDA_MISO_HSIOM_REG
#endif /* (UART_In_MISO_SDA_TX_PIN_PIN) */

#if (UART_In_SCLK_PIN)
    #ifndef UART_In_SCLK_HSIOM_REG
    #define UART_In_SCLK_HSIOM_REG     UART_In_SCLK_HSIOM_REG
    #define UART_In_SCLK_HSIOM_PTR     UART_In_SCLK_HSIOM_PTR
    #define UART_In_SCLK_HSIOM_MASK    UART_In_SCLK_HSIOM_MASK
    #define UART_In_SCLK_HSIOM_POS     UART_In_SCLK_HSIOM_POS
    #endif /* UART_In_SCLK_HSIOM_REG */
#endif /* (UART_In_SCLK_PIN) */

#if (UART_In_SS0_PIN)
    #ifndef UART_In_SS0_HSIOM_REG
    #define UART_In_SS0_HSIOM_REG      UART_In_SS0_HSIOM_REG
    #define UART_In_SS0_HSIOM_PTR      UART_In_SS0_HSIOM_PTR
    #define UART_In_SS0_HSIOM_MASK     UART_In_SS0_HSIOM_MASK
    #define UART_In_SS0_HSIOM_POS      UART_In_SS0_HSIOM_POS
    #endif /* UART_In_SS0_HSIOM_REG */
#endif /* (UART_In_SS0_PIN) */

#define UART_In_MOSI_SCL_RX_WAKE_PIN_INDEX UART_In_RX_WAKE_SCL_MOSI_PIN_INDEX
#define UART_In_MOSI_SCL_RX_PIN_INDEX      UART_In_RX_SCL_MOSI_PIN_INDEX
#define UART_In_MISO_SDA_TX_PIN_INDEX      UART_In_TX_SDA_MISO_PIN_INDEX
#ifndef UART_In_SCLK_PIN_INDEX
#define UART_In_SCLK_PIN_INDEX             UART_In_SCLK_PIN_INDEX
#endif /* UART_In_SCLK_PIN_INDEX */
#ifndef UART_In_SS0_PIN_INDEX
#define UART_In_SS0_PIN_INDEX              UART_In_SS0_PIN_INDEX
#endif /* UART_In_SS0_PIN_INDEX */

#define UART_In_MOSI_SCL_RX_WAKE_PIN_MASK UART_In_RX_WAKE_SCL_MOSI_PIN_MASK
#define UART_In_MOSI_SCL_RX_PIN_MASK      UART_In_RX_SCL_MOSI_PIN_MASK
#define UART_In_MISO_SDA_TX_PIN_MASK      UART_In_TX_SDA_MISO_PIN_MASK
#ifndef UART_In_SCLK_PIN_MASK
#define UART_In_SCLK_PIN_MASK             UART_In_SCLK_PIN_MASK
#endif /* UART_In_SCLK_PIN_MASK */
#ifndef UART_In_SS0_PIN_MASK
#define UART_In_SS0_PIN_MASK              UART_In_SS0_PIN_MASK
#endif /* UART_In_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_UART_In_H) */


/* [] END OF FILE */
