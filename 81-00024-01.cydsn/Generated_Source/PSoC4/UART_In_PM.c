/*******************************************************************************
* File Name: UART_In_PM.c
* Version 3.10
*
* Description:
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_In.h"
#include "UART_In_PVT.h"

#if(UART_In_SCB_MODE_I2C_INC)
    #include "UART_In_I2C_PVT.h"
#endif /* (UART_In_SCB_MODE_I2C_INC) */

#if(UART_In_SCB_MODE_EZI2C_INC)
    #include "UART_In_EZI2C_PVT.h"
#endif /* (UART_In_SCB_MODE_EZI2C_INC) */

#if(UART_In_SCB_MODE_SPI_INC || UART_In_SCB_MODE_UART_INC)
    #include "UART_In_SPI_UART_PVT.h"
#endif /* (UART_In_SCB_MODE_SPI_INC || UART_In_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(UART_In_SCB_MODE_UNCONFIG_CONST_CFG || \
   (UART_In_SCB_MODE_I2C_CONST_CFG   && (!UART_In_I2C_WAKE_ENABLE_CONST))   || \
   (UART_In_SCB_MODE_EZI2C_CONST_CFG && (!UART_In_EZI2C_WAKE_ENABLE_CONST)) || \
   (UART_In_SCB_MODE_SPI_CONST_CFG   && (!UART_In_SPI_WAKE_ENABLE_CONST))   || \
   (UART_In_SCB_MODE_UART_CONST_CFG  && (!UART_In_UART_WAKE_ENABLE_CONST)))

    UART_In_BACKUP_STRUCT UART_In_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: UART_In_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component to enter Deep Sleep.
*  The "Enable wakeup from Sleep Mode" selection has an influence on
*  this function implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_In_Sleep(void)
{
#if(UART_In_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART_In_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART_In_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_In_I2CSaveConfig();
        }
        else if(UART_In_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_In_EzI2CSaveConfig();
        }
    #if(!UART_In_CY_SCBIP_V1)
        else if(UART_In_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_In_SpiSaveConfig();
        }
        else if(UART_In_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_In_UartSaveConfig();
        }
    #endif /* (!UART_In_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        UART_In_backup.enableState = (uint8) UART_In_GET_CTRL_ENABLED;

        if(0u != UART_In_backup.enableState)
        {
            UART_In_Stop();
        }
    }

#else

    #if (UART_In_SCB_MODE_I2C_CONST_CFG && UART_In_I2C_WAKE_ENABLE_CONST)
        UART_In_I2CSaveConfig();

    #elif (UART_In_SCB_MODE_EZI2C_CONST_CFG && UART_In_EZI2C_WAKE_ENABLE_CONST)
        UART_In_EzI2CSaveConfig();

    #elif (UART_In_SCB_MODE_SPI_CONST_CFG && UART_In_SPI_WAKE_ENABLE_CONST)
        UART_In_SpiSaveConfig();

    #elif (UART_In_SCB_MODE_UART_CONST_CFG && UART_In_UART_WAKE_ENABLE_CONST)
        UART_In_UartSaveConfig();

    #else

        UART_In_backup.enableState = (uint8) UART_In_GET_CTRL_ENABLED;

        if(0u != UART_In_backup.enableState)
        {
            UART_In_Stop();
        }

    #endif /* defined (UART_In_SCB_MODE_I2C_CONST_CFG) && (UART_In_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART_In_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UART_In_Wakeup
********************************************************************************
*
* Summary:
*  Prepares the component for the Active mode operation after exiting
*  Deep Sleep. The "Enable wakeup from Sleep Mode" option has an influence
*  on this function implementation.
*  This function should not be called after exiting Sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_In_Wakeup(void)
{
#if(UART_In_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART_In_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART_In_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_In_I2CRestoreConfig();
        }
        else if(UART_In_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_In_EzI2CRestoreConfig();
        }
    #if(!UART_In_CY_SCBIP_V1)
        else if(UART_In_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_In_SpiRestoreConfig();
        }
        else if(UART_In_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_In_UartRestoreConfig();
        }
    #endif /* (!UART_In_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != UART_In_backup.enableState)
        {
            UART_In_Enable();
        }
    }

#else

    #if (UART_In_SCB_MODE_I2C_CONST_CFG  && UART_In_I2C_WAKE_ENABLE_CONST)
        UART_In_I2CRestoreConfig();

    #elif (UART_In_SCB_MODE_EZI2C_CONST_CFG && UART_In_EZI2C_WAKE_ENABLE_CONST)
        UART_In_EzI2CRestoreConfig();

    #elif (UART_In_SCB_MODE_SPI_CONST_CFG && UART_In_SPI_WAKE_ENABLE_CONST)
        UART_In_SpiRestoreConfig();

    #elif (UART_In_SCB_MODE_UART_CONST_CFG && UART_In_UART_WAKE_ENABLE_CONST)
        UART_In_UartRestoreConfig();

    #else

        if(0u != UART_In_backup.enableState)
        {
            UART_In_Enable();
        }

    #endif /* (UART_In_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART_In_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
