/*******************************************************************************
* File Name: UART_FF_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_UART_FF_H)
#define CY_SCB_SPI_UART_PVT_UART_FF_H

#include "UART_FF_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (UART_FF_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  UART_FF_rxBufferHead;
    extern volatile uint32  UART_FF_rxBufferTail;
    extern volatile uint8   UART_FF_rxBufferOverflow;
#endif /* (UART_FF_INTERNAL_RX_SW_BUFFER_CONST) */

#if (UART_FF_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  UART_FF_txBufferHead;
    extern volatile uint32  UART_FF_txBufferTail;
#endif /* (UART_FF_INTERNAL_TX_SW_BUFFER_CONST) */

#if (UART_FF_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 UART_FF_rxBufferInternal[UART_FF_INTERNAL_RX_BUFFER_SIZE];
#endif /* (UART_FF_INTERNAL_RX_SW_BUFFER) */

#if (UART_FF_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 UART_FF_txBufferInternal[UART_FF_TX_BUFFER_SIZE];
#endif /* (UART_FF_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void UART_FF_SpiPostEnable(void);
void UART_FF_SpiStop(void);

#if (UART_FF_SCB_MODE_SPI_CONST_CFG)
    void UART_FF_SpiInit(void);
#endif /* (UART_FF_SCB_MODE_SPI_CONST_CFG) */

#if (UART_FF_SPI_WAKE_ENABLE_CONST)
    void UART_FF_SpiSaveConfig(void);
    void UART_FF_SpiRestoreConfig(void);
#endif /* (UART_FF_SPI_WAKE_ENABLE_CONST) */

void UART_FF_UartPostEnable(void);
void UART_FF_UartStop(void);

#if (UART_FF_SCB_MODE_UART_CONST_CFG)
    void UART_FF_UartInit(void);
#endif /* (UART_FF_SCB_MODE_UART_CONST_CFG) */

#if (UART_FF_UART_WAKE_ENABLE_CONST)
    void UART_FF_UartSaveConfig(void);
    void UART_FF_UartRestoreConfig(void);
#endif /* (UART_FF_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in UART_FF_SetPins() */
#define UART_FF_UART_RX_PIN_ENABLE    (UART_FF_UART_RX)
#define UART_FF_UART_TX_PIN_ENABLE    (UART_FF_UART_TX)

/* UART RTS and CTS position to be used in  UART_FF_SetPins() */
#define UART_FF_UART_RTS_PIN_ENABLE    (0x10u)
#define UART_FF_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define UART_FF_SpiUartEnableIntRx(intSourceMask)  UART_FF_SetRxInterruptMode(intSourceMask)
#define UART_FF_SpiUartEnableIntTx(intSourceMask)  UART_FF_SetTxInterruptMode(intSourceMask)
uint32  UART_FF_SpiUartDisableIntRx(void);
uint32  UART_FF_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_UART_FF_H) */


/* [] END OF FILE */
