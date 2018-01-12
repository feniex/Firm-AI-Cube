/*******************************************************************************
* File Name: TimeoutTimer_PM.c
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

#include "TimeoutTimer.h"

static TimeoutTimer_BACKUP_STRUCT TimeoutTimer_backup;


/*******************************************************************************
* Function Name: TimeoutTimer_SaveConfig
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
void TimeoutTimer_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: TimeoutTimer_Sleep
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
void TimeoutTimer_Sleep(void)
{
    if(0u != (TimeoutTimer_BLOCK_CONTROL_REG & TimeoutTimer_MASK))
    {
        TimeoutTimer_backup.enableState = 1u;
    }
    else
    {
        TimeoutTimer_backup.enableState = 0u;
    }

    TimeoutTimer_Stop();
    TimeoutTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: TimeoutTimer_RestoreConfig
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
void TimeoutTimer_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: TimeoutTimer_Wakeup
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
void TimeoutTimer_Wakeup(void)
{
    TimeoutTimer_RestoreConfig();

    if(0u != TimeoutTimer_backup.enableState)
    {
        TimeoutTimer_Enable();
    }
}


/* [] END OF FILE */
