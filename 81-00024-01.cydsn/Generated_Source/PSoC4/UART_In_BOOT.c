/*******************************************************************************
* File Name: UART_In_BOOT.c
* Version 3.10
*
* Description:
*  This file provides the source code of the bootloader communication APIs
*  for the SCB Component Unconfigured mode.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_In_BOOT.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_In_BTLDR_COMM_ENABLED) && \
                                (UART_In_SCB_MODE_UNCONFIG_CONST_CFG)

/*******************************************************************************
* Function Name: UART_In_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStart function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_In_CyBtldrCommStart(void)
{
    if (UART_In_SCB_MODE_I2C_RUNTM_CFG)
    {
        UART_In_I2CCyBtldrCommStart();
    }
    else if (UART_In_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        UART_In_EzI2CCyBtldrCommStart();
    }
#if (!UART_In_CY_SCBIP_V1)
    else if (UART_In_SCB_MODE_SPI_RUNTM_CFG)
    {
        UART_In_SpiCyBtldrCommStart();
    }
    else if (UART_In_SCB_MODE_UART_RUNTM_CFG)
    {
        UART_In_UartCyBtldrCommStart();
    }
#endif /* (!UART_In_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: UART_In_CyBtldrCommStop
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStop function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_In_CyBtldrCommStop(void)
{
    if (UART_In_SCB_MODE_I2C_RUNTM_CFG)
    {
        UART_In_I2CCyBtldrCommStop();
    }
    else if (UART_In_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        UART_In_EzI2CCyBtldrCommStop();
    }
#if (!UART_In_CY_SCBIP_V1)
    else if (UART_In_SCB_MODE_SPI_RUNTM_CFG)
    {
        UART_In_SpiCyBtldrCommStop();
    }
    else if (UART_In_SCB_MODE_UART_RUNTM_CFG)
    {
        UART_In_UartCyBtldrCommStop();
    }
#endif /* (!UART_In_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: UART_In_CyBtldrCommReset
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommReset function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_In_CyBtldrCommReset(void)
{
    if(UART_In_SCB_MODE_I2C_RUNTM_CFG)
    {
        UART_In_I2CCyBtldrCommReset();
    }
    else if(UART_In_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        UART_In_EzI2CCyBtldrCommReset();
    }
#if (!UART_In_CY_SCBIP_V1)
    else if(UART_In_SCB_MODE_SPI_RUNTM_CFG)
    {
        UART_In_SpiCyBtldrCommReset();
    }
    else if(UART_In_SCB_MODE_UART_RUNTM_CFG)
    {
        UART_In_UartCyBtldrCommReset();
    }
#endif /* (!UART_In_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: UART_In_CyBtldrCommRead
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommRead function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to storage for the block of data to be read from the
*            bootloader host
*  size:     Number of bytes to be read.
*  count:    Pointer to the variable to write the number of bytes actually
*            read.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus UART_In_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(UART_In_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = UART_In_I2CCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(UART_In_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = UART_In_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
    }
#if (!UART_In_CY_SCBIP_V1)
    else if(UART_In_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = UART_In_SpiCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(UART_In_SCB_MODE_UART_RUNTM_CFG)
    {
        status = UART_In_UartCyBtldrCommRead(pData, size, count, timeOut);
    }
#endif /* (!UART_In_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}


/*******************************************************************************
* Function Name: UART_In_CyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommWrite  function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to the block of data to be written to the bootloader host.
*  size:     Number of bytes to be written.
*  count:    Pointer to the variable to write the number of bytes actually
*            written.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus UART_In_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(UART_In_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = UART_In_I2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(UART_In_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = UART_In_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
#if (!UART_In_CY_SCBIP_V1)
    else if(UART_In_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = UART_In_SpiCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(UART_In_SCB_MODE_UART_RUNTM_CFG)
    {
        status = UART_In_UartCyBtldrCommWrite(pData, size, count, timeOut);
    }
#endif /* (!UART_In_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_In_BTLDR_COMM_MODE_ENABLED) */


/* [] END OF FILE */
