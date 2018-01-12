/*******************************************************************************
* File Name: UART_Temperature_PM.c
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

#include "UART_Temperature.h"
#include "UART_Temperature_PVT.h"

#if(UART_Temperature_SCB_MODE_I2C_INC)
    #include "UART_Temperature_I2C_PVT.h"
#endif /* (UART_Temperature_SCB_MODE_I2C_INC) */

#if(UART_Temperature_SCB_MODE_EZI2C_INC)
    #include "UART_Temperature_EZI2C_PVT.h"
#endif /* (UART_Temperature_SCB_MODE_EZI2C_INC) */

#if(UART_Temperature_SCB_MODE_SPI_INC || UART_Temperature_SCB_MODE_UART_INC)
    #include "UART_Temperature_SPI_UART_PVT.h"
#endif /* (UART_Temperature_SCB_MODE_SPI_INC || UART_Temperature_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(UART_Temperature_SCB_MODE_UNCONFIG_CONST_CFG || \
   (UART_Temperature_SCB_MODE_I2C_CONST_CFG   && (!UART_Temperature_I2C_WAKE_ENABLE_CONST))   || \
   (UART_Temperature_SCB_MODE_EZI2C_CONST_CFG && (!UART_Temperature_EZI2C_WAKE_ENABLE_CONST)) || \
   (UART_Temperature_SCB_MODE_SPI_CONST_CFG   && (!UART_Temperature_SPI_WAKE_ENABLE_CONST))   || \
   (UART_Temperature_SCB_MODE_UART_CONST_CFG  && (!UART_Temperature_UART_WAKE_ENABLE_CONST)))

    UART_Temperature_BACKUP_STRUCT UART_Temperature_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: UART_Temperature_Sleep
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
void UART_Temperature_Sleep(void)
{
#if(UART_Temperature_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART_Temperature_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART_Temperature_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_Temperature_I2CSaveConfig();
        }
        else if(UART_Temperature_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_Temperature_EzI2CSaveConfig();
        }
    #if(!UART_Temperature_CY_SCBIP_V1)
        else if(UART_Temperature_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_Temperature_SpiSaveConfig();
        }
        else if(UART_Temperature_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_Temperature_UartSaveConfig();
        }
    #endif /* (!UART_Temperature_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        UART_Temperature_backup.enableState = (uint8) UART_Temperature_GET_CTRL_ENABLED;

        if(0u != UART_Temperature_backup.enableState)
        {
            UART_Temperature_Stop();
        }
    }

#else

    #if (UART_Temperature_SCB_MODE_I2C_CONST_CFG && UART_Temperature_I2C_WAKE_ENABLE_CONST)
        UART_Temperature_I2CSaveConfig();

    #elif (UART_Temperature_SCB_MODE_EZI2C_CONST_CFG && UART_Temperature_EZI2C_WAKE_ENABLE_CONST)
        UART_Temperature_EzI2CSaveConfig();

    #elif (UART_Temperature_SCB_MODE_SPI_CONST_CFG && UART_Temperature_SPI_WAKE_ENABLE_CONST)
        UART_Temperature_SpiSaveConfig();

    #elif (UART_Temperature_SCB_MODE_UART_CONST_CFG && UART_Temperature_UART_WAKE_ENABLE_CONST)
        UART_Temperature_UartSaveConfig();

    #else

        UART_Temperature_backup.enableState = (uint8) UART_Temperature_GET_CTRL_ENABLED;

        if(0u != UART_Temperature_backup.enableState)
        {
            UART_Temperature_Stop();
        }

    #endif /* defined (UART_Temperature_SCB_MODE_I2C_CONST_CFG) && (UART_Temperature_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART_Temperature_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UART_Temperature_Wakeup
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
void UART_Temperature_Wakeup(void)
{
#if(UART_Temperature_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART_Temperature_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART_Temperature_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_Temperature_I2CRestoreConfig();
        }
        else if(UART_Temperature_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_Temperature_EzI2CRestoreConfig();
        }
    #if(!UART_Temperature_CY_SCBIP_V1)
        else if(UART_Temperature_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_Temperature_SpiRestoreConfig();
        }
        else if(UART_Temperature_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_Temperature_UartRestoreConfig();
        }
    #endif /* (!UART_Temperature_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != UART_Temperature_backup.enableState)
        {
            UART_Temperature_Enable();
        }
    }

#else

    #if (UART_Temperature_SCB_MODE_I2C_CONST_CFG  && UART_Temperature_I2C_WAKE_ENABLE_CONST)
        UART_Temperature_I2CRestoreConfig();

    #elif (UART_Temperature_SCB_MODE_EZI2C_CONST_CFG && UART_Temperature_EZI2C_WAKE_ENABLE_CONST)
        UART_Temperature_EzI2CRestoreConfig();

    #elif (UART_Temperature_SCB_MODE_SPI_CONST_CFG && UART_Temperature_SPI_WAKE_ENABLE_CONST)
        UART_Temperature_SpiRestoreConfig();

    #elif (UART_Temperature_SCB_MODE_UART_CONST_CFG && UART_Temperature_UART_WAKE_ENABLE_CONST)
        UART_Temperature_UartRestoreConfig();

    #else

        if(0u != UART_Temperature_backup.enableState)
        {
            UART_Temperature_Enable();
        }

    #endif /* (UART_Temperature_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART_Temperature_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
