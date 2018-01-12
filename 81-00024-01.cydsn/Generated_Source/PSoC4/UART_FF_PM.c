/*******************************************************************************
* File Name: UART_FF_PM.c
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

#include "UART_FF.h"
#include "UART_FF_PVT.h"

#if(UART_FF_SCB_MODE_I2C_INC)
    #include "UART_FF_I2C_PVT.h"
#endif /* (UART_FF_SCB_MODE_I2C_INC) */

#if(UART_FF_SCB_MODE_EZI2C_INC)
    #include "UART_FF_EZI2C_PVT.h"
#endif /* (UART_FF_SCB_MODE_EZI2C_INC) */

#if(UART_FF_SCB_MODE_SPI_INC || UART_FF_SCB_MODE_UART_INC)
    #include "UART_FF_SPI_UART_PVT.h"
#endif /* (UART_FF_SCB_MODE_SPI_INC || UART_FF_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(UART_FF_SCB_MODE_UNCONFIG_CONST_CFG || \
   (UART_FF_SCB_MODE_I2C_CONST_CFG   && (!UART_FF_I2C_WAKE_ENABLE_CONST))   || \
   (UART_FF_SCB_MODE_EZI2C_CONST_CFG && (!UART_FF_EZI2C_WAKE_ENABLE_CONST)) || \
   (UART_FF_SCB_MODE_SPI_CONST_CFG   && (!UART_FF_SPI_WAKE_ENABLE_CONST))   || \
   (UART_FF_SCB_MODE_UART_CONST_CFG  && (!UART_FF_UART_WAKE_ENABLE_CONST)))

    UART_FF_BACKUP_STRUCT UART_FF_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: UART_FF_Sleep
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
void UART_FF_Sleep(void)
{
#if(UART_FF_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART_FF_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART_FF_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_FF_I2CSaveConfig();
        }
        else if(UART_FF_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_FF_EzI2CSaveConfig();
        }
    #if(!UART_FF_CY_SCBIP_V1)
        else if(UART_FF_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_FF_SpiSaveConfig();
        }
        else if(UART_FF_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_FF_UartSaveConfig();
        }
    #endif /* (!UART_FF_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        UART_FF_backup.enableState = (uint8) UART_FF_GET_CTRL_ENABLED;

        if(0u != UART_FF_backup.enableState)
        {
            UART_FF_Stop();
        }
    }

#else

    #if (UART_FF_SCB_MODE_I2C_CONST_CFG && UART_FF_I2C_WAKE_ENABLE_CONST)
        UART_FF_I2CSaveConfig();

    #elif (UART_FF_SCB_MODE_EZI2C_CONST_CFG && UART_FF_EZI2C_WAKE_ENABLE_CONST)
        UART_FF_EzI2CSaveConfig();

    #elif (UART_FF_SCB_MODE_SPI_CONST_CFG && UART_FF_SPI_WAKE_ENABLE_CONST)
        UART_FF_SpiSaveConfig();

    #elif (UART_FF_SCB_MODE_UART_CONST_CFG && UART_FF_UART_WAKE_ENABLE_CONST)
        UART_FF_UartSaveConfig();

    #else

        UART_FF_backup.enableState = (uint8) UART_FF_GET_CTRL_ENABLED;

        if(0u != UART_FF_backup.enableState)
        {
            UART_FF_Stop();
        }

    #endif /* defined (UART_FF_SCB_MODE_I2C_CONST_CFG) && (UART_FF_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART_FF_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UART_FF_Wakeup
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
void UART_FF_Wakeup(void)
{
#if(UART_FF_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART_FF_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART_FF_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_FF_I2CRestoreConfig();
        }
        else if(UART_FF_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_FF_EzI2CRestoreConfig();
        }
    #if(!UART_FF_CY_SCBIP_V1)
        else if(UART_FF_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_FF_SpiRestoreConfig();
        }
        else if(UART_FF_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_FF_UartRestoreConfig();
        }
    #endif /* (!UART_FF_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != UART_FF_backup.enableState)
        {
            UART_FF_Enable();
        }
    }

#else

    #if (UART_FF_SCB_MODE_I2C_CONST_CFG  && UART_FF_I2C_WAKE_ENABLE_CONST)
        UART_FF_I2CRestoreConfig();

    #elif (UART_FF_SCB_MODE_EZI2C_CONST_CFG && UART_FF_EZI2C_WAKE_ENABLE_CONST)
        UART_FF_EzI2CRestoreConfig();

    #elif (UART_FF_SCB_MODE_SPI_CONST_CFG && UART_FF_SPI_WAKE_ENABLE_CONST)
        UART_FF_SpiRestoreConfig();

    #elif (UART_FF_SCB_MODE_UART_CONST_CFG && UART_FF_UART_WAKE_ENABLE_CONST)
        UART_FF_UartRestoreConfig();

    #else

        if(0u != UART_FF_backup.enableState)
        {
            UART_FF_Enable();
        }

    #endif /* (UART_FF_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART_FF_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
