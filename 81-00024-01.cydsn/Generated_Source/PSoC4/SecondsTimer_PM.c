/*******************************************************************************
* File Name: SecondsTimer_PM.c
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

#include "SecondsTimer.h"

static SecondsTimer_BACKUP_STRUCT SecondsTimer_backup;


/*******************************************************************************
* Function Name: SecondsTimer_SaveConfig
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
void SecondsTimer_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: SecondsTimer_Sleep
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
void SecondsTimer_Sleep(void)
{
    if(0u != (SecondsTimer_BLOCK_CONTROL_REG & SecondsTimer_MASK))
    {
        SecondsTimer_backup.enableState = 1u;
    }
    else
    {
        SecondsTimer_backup.enableState = 0u;
    }

    SecondsTimer_Stop();
    SecondsTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: SecondsTimer_RestoreConfig
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
void SecondsTimer_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: SecondsTimer_Wakeup
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
void SecondsTimer_Wakeup(void)
{
    SecondsTimer_RestoreConfig();

    if(0u != SecondsTimer_backup.enableState)
    {
        SecondsTimer_Enable();
    }
}


/* [] END OF FILE */
