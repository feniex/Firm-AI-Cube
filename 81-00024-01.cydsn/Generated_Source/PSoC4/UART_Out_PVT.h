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

#if !defined(CY_SCB_PVT_UART_Out_H)
#define CY_SCB_PVT_UART_Out_H

#include "UART_Out.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define UART_Out_SetI2CExtClkInterruptMode(interruptMask) UART_Out_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define UART_Out_ClearI2CExtClkInterruptSource(interruptMask) UART_Out_CLEAR_INTR_I2C_EC(interruptMask)
#define UART_Out_GetI2CExtClkInterruptSource()                (UART_Out_INTR_I2C_EC_REG)
#define UART_Out_GetI2CExtClkInterruptMode()                  (UART_Out_INTR_I2C_EC_MASK_REG)
#define UART_Out_GetI2CExtClkInterruptSourceMasked()          (UART_Out_INTR_I2C_EC_MASKED_REG)

#if (!UART_Out_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define UART_Out_SetSpiExtClkInterruptMode(interruptMask) \
                                                                UART_Out_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define UART_Out_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                UART_Out_CLEAR_INTR_SPI_EC(interruptMask)
    #define UART_Out_GetExtSpiClkInterruptSource()                 (UART_Out_INTR_SPI_EC_REG)
    #define UART_Out_GetExtSpiClkInterruptMode()                   (UART_Out_INTR_SPI_EC_MASK_REG)
    #define UART_Out_GetExtSpiClkInterruptSourceMasked()           (UART_Out_INTR_SPI_EC_MASKED_REG)
#endif /* (!UART_Out_CY_SCBIP_V1) */

#if(UART_Out_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void UART_Out_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (UART_Out_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (UART_Out_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_UART_Out_CUSTOM_INTR_HANDLER)
    extern cyisraddress UART_Out_customIntrHandler;
#endif /* !defined (CY_REMOVE_UART_Out_CUSTOM_INTR_HANDLER) */
#endif /* (UART_Out_SCB_IRQ_INTERNAL) */

extern UART_Out_BACKUP_STRUCT UART_Out_backup;

#if(UART_Out_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 UART_Out_scbMode;
    extern uint8 UART_Out_scbEnableWake;
    extern uint8 UART_Out_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 UART_Out_mode;
    extern uint8 UART_Out_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * UART_Out_rxBuffer;
    extern uint8   UART_Out_rxDataBits;
    extern uint32  UART_Out_rxBufferSize;

    extern volatile uint8 * UART_Out_txBuffer;
    extern uint8   UART_Out_txDataBits;
    extern uint32  UART_Out_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 UART_Out_numberOfAddr;
    extern uint8 UART_Out_subAddrSize;
#endif /* (UART_Out_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(UART_Out_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define UART_Out_SCB_MODE_I2C_RUNTM_CFG     (UART_Out_SCB_MODE_I2C      == UART_Out_scbMode)
    #define UART_Out_SCB_MODE_SPI_RUNTM_CFG     (UART_Out_SCB_MODE_SPI      == UART_Out_scbMode)
    #define UART_Out_SCB_MODE_UART_RUNTM_CFG    (UART_Out_SCB_MODE_UART     == UART_Out_scbMode)
    #define UART_Out_SCB_MODE_EZI2C_RUNTM_CFG   (UART_Out_SCB_MODE_EZI2C    == UART_Out_scbMode)
    #define UART_Out_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (UART_Out_SCB_MODE_UNCONFIG == UART_Out_scbMode)

    /* Defines wakeup enable */
    #define UART_Out_SCB_WAKE_ENABLE_CHECK       (0u != UART_Out_scbEnableWake)
#endif /* (UART_Out_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!UART_Out_CY_SCBIP_V1)
    #define UART_Out_SCB_PINS_NUMBER    (7u)
#else
    #define UART_Out_SCB_PINS_NUMBER    (2u)
#endif /* (!UART_Out_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_UART_Out_H) */


/* [] END OF FILE */
