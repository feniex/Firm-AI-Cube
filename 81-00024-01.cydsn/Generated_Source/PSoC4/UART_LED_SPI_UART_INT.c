/*******************************************************************************
* File Name: UART_LED_SPI_UART_INT.c
* Version 3.10
*
* Description:
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_LED_PVT.h"
#include "UART_LED_SPI_UART_PVT.h"


#if (UART_LED_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: UART_LED_SPI_UART_ISR
********************************************************************************
*
* Summary:
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(UART_LED_SPI_UART_ISR)
{
#if (UART_LED_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (UART_LED_INTERNAL_RX_SW_BUFFER_CONST) */

#if (UART_LED_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (UART_LED_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef UART_LED_SPI_UART_ISR_ENTRY_CALLBACK
    UART_LED_SPI_UART_ISR_EntryCallback();
#endif /* UART_LED_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != UART_LED_customIntrHandler)
    {
        UART_LED_customIntrHandler();
    }

    #if (UART_LED_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        UART_LED_ClearSpiExtClkInterruptSource(UART_LED_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (UART_LED_CHECK_RX_SW_BUFFER)
    {
        if (UART_LED_CHECK_INTR_RX_MASKED(UART_LED_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (UART_LED_rxBufferHead + 1u);

                /* Adjust local head index */
                if (UART_LED_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == UART_LED_rxBufferTail)
                {
                    #if (UART_LED_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        UART_LED_INTR_RX_MASK_REG &= ~UART_LED_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) UART_LED_RX_FIFO_RD_REG;
                        UART_LED_rxBufferOverflow = (uint8) UART_LED_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    UART_LED_PutWordInRxBuffer(locHead, UART_LED_RX_FIFO_RD_REG);

                    /* Move head index */
                    UART_LED_rxBufferHead = locHead;
                }
            }
            while(0u != UART_LED_GET_RX_FIFO_ENTRIES);

            UART_LED_ClearRxInterruptSource(UART_LED_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (UART_LED_CHECK_TX_SW_BUFFER)
    {
        if (UART_LED_CHECK_INTR_TX_MASKED(UART_LED_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (UART_LED_txBufferHead != UART_LED_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (UART_LED_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (UART_LED_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    UART_LED_TX_FIFO_WR_REG = UART_LED_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    UART_LED_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    UART_LED_DISABLE_INTR_TX(UART_LED_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (UART_LED_SPI_UART_FIFO_SIZE != UART_LED_GET_TX_FIFO_ENTRIES);

            UART_LED_ClearTxInterruptSource(UART_LED_INTR_TX_NOT_FULL);
        }
    }
    #endif
    
#ifdef UART_LED_SPI_UART_ISR_EXIT_CALLBACK
    UART_LED_SPI_UART_ISR_ExitCallback();
#endif /* UART_LED_SPI_UART_ISR_EXIT_CALLBACK */
    
}

#endif /* (UART_LED_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
