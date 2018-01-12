/*******************************************************************************
* File Name: UART_Out_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_UART_Out_H)
#define CY_SCB_SPI_UART_PVT_UART_Out_H

#include "UART_Out_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (UART_Out_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  UART_Out_rxBufferHead;
    extern volatile uint32  UART_Out_rxBufferTail;
    extern volatile uint8   UART_Out_rxBufferOverflow;
#endif /* (UART_Out_INTERNAL_RX_SW_BUFFER_CONST) */

#if (UART_Out_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  UART_Out_txBufferHead;
    extern volatile uint32  UART_Out_txBufferTail;
#endif /* (UART_Out_INTERNAL_TX_SW_BUFFER_CONST) */

#if (UART_Out_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 UART_Out_rxBufferInternal[UART_Out_INTERNAL_RX_BUFFER_SIZE];
#endif /* (UART_Out_INTERNAL_RX_SW_BUFFER) */

#if (UART_Out_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 UART_Out_txBufferInternal[UART_Out_TX_BUFFER_SIZE];
#endif /* (UART_Out_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void UART_Out_SpiPostEnable(void);
void UART_Out_SpiStop(void);

#if (UART_Out_SCB_MODE_SPI_CONST_CFG)
    void UART_Out_SpiInit(void);
#endif /* (UART_Out_SCB_MODE_SPI_CONST_CFG) */

#if (UART_Out_SPI_WAKE_ENABLE_CONST)
    void UART_Out_SpiSaveConfig(void);
    void UART_Out_SpiRestoreConfig(void);
#endif /* (UART_Out_SPI_WAKE_ENABLE_CONST) */

void UART_Out_UartPostEnable(void);
void UART_Out_UartStop(void);

#if (UART_Out_SCB_MODE_UART_CONST_CFG)
    void UART_Out_UartInit(void);
#endif /* (UART_Out_SCB_MODE_UART_CONST_CFG) */

#if (UART_Out_UART_WAKE_ENABLE_CONST)
    void UART_Out_UartSaveConfig(void);
    void UART_Out_UartRestoreConfig(void);
#endif /* (UART_Out_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in UART_Out_SetPins() */
#define UART_Out_UART_RX_PIN_ENABLE    (UART_Out_UART_RX)
#define UART_Out_UART_TX_PIN_ENABLE    (UART_Out_UART_TX)

/* UART RTS and CTS position to be used in  UART_Out_SetPins() */
#define UART_Out_UART_RTS_PIN_ENABLE    (0x10u)
#define UART_Out_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define UART_Out_SpiUartEnableIntRx(intSourceMask)  UART_Out_SetRxInterruptMode(intSourceMask)
#define UART_Out_SpiUartEnableIntTx(intSourceMask)  UART_Out_SetTxInterruptMode(intSourceMask)
uint32  UART_Out_SpiUartDisableIntRx(void);
uint32  UART_Out_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_UART_Out_H) */


/* [] END OF FILE */
