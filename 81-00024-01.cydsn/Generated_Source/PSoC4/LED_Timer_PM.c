/*******************************************************************************
* File Name: LED_Timer_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LED_Timer.h"

static LED_Timer_BACKUP_STRUCT LED_Timer_backup;


/*******************************************************************************
* Function Name: LED_Timer_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LED_Timer_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: LED_Timer_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LED_Timer_Sleep(void)
{
    if(0u != (LED_Timer_BLOCK_CONTROL_REG & LED_Timer_MASK))
    {
        LED_Timer_backup.enableState = 1u;
    }
    else
    {
        LED_Timer_backup.enableState = 0u;
    }

    LED_Timer_Stop();
    LED_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: LED_Timer_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LED_Timer_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: LED_Timer_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LED_Timer_Wakeup(void)
{
    LED_Timer_RestoreConfig();

    if(0u != LED_Timer_backup.enableState)
    {
        LED_Timer_Enable();
    }
}


/* [] END OF FILE */
