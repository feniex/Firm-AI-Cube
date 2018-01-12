/*******************************************************************************
* File Name: .h
* Version 3.10
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_UART_FF_H)
#define CY_SCB_PVT_UART_FF_H

#include "UART_FF.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define UART_FF_SetI2CExtClkInterruptMode(interruptMask) UART_FF_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define UART_FF_ClearI2CExtClkInterruptSource(interruptMask) UART_FF_CLEAR_INTR_I2C_EC(interruptMask)
#define UART_FF_GetI2CExtClkInterruptSource()                (UART_FF_INTR_I2C_EC_REG)
#define UART_FF_GetI2CExtClkInterruptMode()                  (UART_FF_INTR_I2C_EC_MASK_REG)
#define UART_FF_GetI2CExtClkInterruptSourceMasked()          (UART_FF_INTR_I2C_EC_MASKED_REG)

#if (!UART_FF_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define UART_FF_SetSpiExtClkInterruptMode(interruptMask) \
                                                                UART_FF_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define UART_FF_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                UART_FF_CLEAR_INTR_SPI_EC(interruptMask)
    #define UART_FF_GetExtSpiClkInterruptSource()                 (UART_FF_INTR_SPI_EC_REG)
    #define UART_FF_GetExtSpiClkInterruptMode()                   (UART_FF_INTR_SPI_EC_MASK_REG)
    #define UART_FF_GetExtSpiClkInterruptSourceMasked()           (UART_FF_INTR_SPI_EC_MASKED_REG)
#endif /* (!UART_FF_CY_SCBIP_V1) */

#if(UART_FF_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void UART_FF_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (UART_FF_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (UART_FF_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_UART_FF_CUSTOM_INTR_HANDLER)
    extern cyisraddress UART_FF_customIntrHandler;
#endif /* !defined (CY_REMOVE_UART_FF_CUSTOM_INTR_HANDLER) */
#endif /* (UART_FF_SCB_IRQ_INTERNAL) */

extern UART_FF_BACKUP_STRUCT UART_FF_backup;

#if(UART_FF_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 UART_FF_scbMode;
    extern uint8 UART_FF_scbEnableWake;
    extern uint8 UART_FF_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 UART_FF_mode;
    extern uint8 UART_FF_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * UART_FF_rxBuffer;
    extern uint8   UART_FF_rxDataBits;
    extern uint32  UART_FF_rxBufferSize;

    extern volatile uint8 * UART_FF_txBuffer;
    extern uint8   UART_FF_txDataBits;
    extern uint32  UART_FF_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 UART_FF_numberOfAddr;
    extern uint8 UART_FF_subAddrSize;
#endif /* (UART_FF_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(UART_FF_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define UART_FF_SCB_MODE_I2C_RUNTM_CFG     (UART_FF_SCB_MODE_I2C      == UART_FF_scbMode)
    #define UART_FF_SCB_MODE_SPI_RUNTM_CFG     (UART_FF_SCB_MODE_SPI      == UART_FF_scbMode)
    #define UART_FF_SCB_MODE_UART_RUNTM_CFG    (UART_FF_SCB_MODE_UART     == UART_FF_scbMode)
    #define UART_FF_SCB_MODE_EZI2C_RUNTM_CFG   (UART_FF_SCB_MODE_EZI2C    == UART_FF_scbMode)
    #define UART_FF_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (UART_FF_SCB_MODE_UNCONFIG == UART_FF_scbMode)

    /* Defines wakeup enable */
    #define UART_FF_SCB_WAKE_ENABLE_CHECK       (0u != UART_FF_scbEnableWake)
#endif /* (UART_FF_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!UART_FF_CY_SCBIP_V1)
    #define UART_FF_SCB_PINS_NUMBER    (7u)
#else
    #define UART_FF_SCB_PINS_NUMBER    (2u)
#endif /* (!UART_FF_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_UART_FF_H) */


/* [] END OF FILE */
