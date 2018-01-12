/*******************************************************************************
* File Name: UART_Temperature_SPI_UART_PVT.h
* Version 3.10
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
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

#if !defined(CY_SCB_SPI_UART_PVT_UART_Temperature_H)
#define CY_SCB_SPI_UART_PVT_UART_Temperature_H

#include "UART_Temperature_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (UART_Temperature_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  UART_Temperature_rxBufferHead;
    extern volatile uint32  UART_Temperature_rxBufferTail;
    extern volatile uint8   UART_Temperature_rxBufferOverflow;
#endif /* (UART_Temperature_INTERNAL_RX_SW_BUFFER_CONST) */

#if (UART_Temperature_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  UART_Temperature_txBufferHead;
    extern volatile uint32  UART_Temperature_txBufferTail;
#endif /* (UART_Temperature_INTERNAL_TX_SW_BUFFER_CONST) */

#if (UART_Temperature_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 UART_Temperature_rxBufferInternal[UART_Temperature_INTERNAL_RX_BUFFER_SIZE];
#endif /* (UART_Temperature_INTERNAL_RX_SW_BUFFER) */

#if (UART_Temperature_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 UART_Temperature_txBufferInternal[UART_Temperature_TX_BUFFER_SIZE];
#endif /* (UART_Temperature_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void UART_Temperature_SpiPostEnable(void);
void UART_Temperature_SpiStop(void);

#if (UART_Temperature_SCB_MODE_SPI_CONST_CFG)
    void UART_Temperature_SpiInit(void);
#endif /* (UART_Temperature_SCB_MODE_SPI_CONST_CFG) */

#if (UART_Temperature_SPI_WAKE_ENABLE_CONST)
    void UART_Temperature_SpiSaveConfig(void);
    void UART_Temperature_SpiRestoreConfig(void);
#endif /* (UART_Temperature_SPI_WAKE_ENABLE_CONST) */

void UART_Temperature_UartPostEnable(void);
void UART_Temperature_UartStop(void);

#if (UART_Temperature_SCB_MODE_UART_CONST_CFG)
    void UART_Temperature_UartInit(void);
#endif /* (UART_Temperature_SCB_MODE_UART_CONST_CFG) */

#if (UART_Temperature_UART_WAKE_ENABLE_CONST)
    void UART_Temperature_UartSaveConfig(void);
    void UART_Temperature_UartRestoreConfig(void);
#endif /* (UART_Temperature_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in UART_Temperature_SetPins() */
#define UART_Temperature_UART_RX_PIN_ENABLE    (UART_Temperature_UART_RX)
#define UART_Temperature_UART_TX_PIN_ENABLE    (UART_Temperature_UART_TX)

/* UART RTS and CTS position to be used in  UART_Temperature_SetPins() */
#define UART_Temperature_UART_RTS_PIN_ENABLE    (0x10u)
#define UART_Temperature_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define UART_Temperature_SpiUartEnableIntRx(intSourceMask)  UART_Temperature_SetRxInterruptMode(intSourceMask)
#define UART_Temperature_SpiUartEnableIntTx(intSourceMask)  UART_Temperature_SetTxInterruptMode(intSourceMask)
uint32  UART_Temperature_SpiUartDisableIntRx(void);
uint32  UART_Temperature_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_UART_Temperature_H) */


/* [] END OF FILE */
