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

#if !defined(CY_SCB_PVT_UART_In_H)
#define CY_SCB_PVT_UART_In_H

#include "UART_In.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define UART_In_SetI2CExtClkInterruptMode(interruptMask) UART_In_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define UART_In_ClearI2CExtClkInterruptSource(interruptMask) UART_In_CLEAR_INTR_I2C_EC(interruptMask)
#define UART_In_GetI2CExtClkInterruptSource()                (UART_In_INTR_I2C_EC_REG)
#define UART_In_GetI2CExtClkInterruptMode()                  (UART_In_INTR_I2C_EC_MASK_REG)
#define UART_In_GetI2CExtClkInterruptSourceMasked()          (UART_In_INTR_I2C_EC_MASKED_REG)

#if (!UART_In_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define UART_In_SetSpiExtClkInterruptMode(interruptMask) \
                                                                UART_In_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define UART_In_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                UART_In_CLEAR_INTR_SPI_EC(interruptMask)
    #define UART_In_GetExtSpiClkInterruptSource()                 (UART_In_INTR_SPI_EC_REG)
    #define UART_In_GetExtSpiClkInterruptMode()                   (UART_In_INTR_SPI_EC_MASK_REG)
    #define UART_In_GetExtSpiClkInterruptSourceMasked()           (UART_In_INTR_SPI_EC_MASKED_REG)
#endif /* (!UART_In_CY_SCBIP_V1) */

#if(UART_In_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void UART_In_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (UART_In_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (UART_In_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_UART_In_CUSTOM_INTR_HANDLER)
    extern cyisraddress UART_In_customIntrHandler;
#endif /* !defined (CY_REMOVE_UART_In_CUSTOM_INTR_HANDLER) */
#endif /* (UART_In_SCB_IRQ_INTERNAL) */

extern UART_In_BACKUP_STRUCT UART_In_backup;

#if(UART_In_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 UART_In_scbMode;
    extern uint8 UART_In_scbEnableWake;
    extern uint8 UART_In_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 UART_In_mode;
    extern uint8 UART_In_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * UART_In_rxBuffer;
    extern uint8   UART_In_rxDataBits;
    extern uint32  UART_In_rxBufferSize;

    extern volatile uint8 * UART_In_txBuffer;
    extern uint8   UART_In_txDataBits;
    extern uint32  UART_In_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 UART_In_numberOfAddr;
    extern uint8 UART_In_subAddrSize;
#endif /* (UART_In_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(UART_In_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define UART_In_SCB_MODE_I2C_RUNTM_CFG     (UART_In_SCB_MODE_I2C      == UART_In_scbMode)
    #define UART_In_SCB_MODE_SPI_RUNTM_CFG     (UART_In_SCB_MODE_SPI      == UART_In_scbMode)
    #define UART_In_SCB_MODE_UART_RUNTM_CFG    (UART_In_SCB_MODE_UART     == UART_In_scbMode)
    #define UART_In_SCB_MODE_EZI2C_RUNTM_CFG   (UART_In_SCB_MODE_EZI2C    == UART_In_scbMode)
    #define UART_In_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (UART_In_SCB_MODE_UNCONFIG == UART_In_scbMode)

    /* Defines wakeup enable */
    #define UART_In_SCB_WAKE_ENABLE_CHECK       (0u != UART_In_scbEnableWake)
#endif /* (UART_In_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!UART_In_CY_SCBIP_V1)
    #define UART_In_SCB_PINS_NUMBER    (7u)
#else
    #define UART_In_SCB_PINS_NUMBER    (2u)
#endif /* (!UART_In_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_UART_In_H) */


/* [] END OF FILE */
