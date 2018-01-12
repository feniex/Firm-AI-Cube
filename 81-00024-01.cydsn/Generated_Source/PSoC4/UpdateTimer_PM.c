/*******************************************************************************
* File Name: UpdateTimer_PM.c
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

#include "UpdateTimer.h"

static UpdateTimer_BACKUP_STRUCT UpdateTimer_backup;


/*******************************************************************************
* Function Name: UpdateTimer_SaveConfig
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
void UpdateTimer_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: UpdateTimer_Sleep
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
void UpdateTimer_Sleep(void)
{
    if(0u != (UpdateTimer_BLOCK_CONTROL_REG & UpdateTimer_MASK))
    {
        UpdateTimer_backup.enableState = 1u;
    }
    else
    {
        UpdateTimer_backup.enableState = 0u;
    }

    UpdateTimer_Stop();
    UpdateTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: UpdateTimer_RestoreConfig
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
void UpdateTimer_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: UpdateTimer_Wakeup
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
void UpdateTimer_Wakeup(void)
{
    UpdateTimer_RestoreConfig();

    if(0u != UpdateTimer_backup.enableState)
    {
        UpdateTimer_Enable();
    }
}


/* [] END OF FILE */
