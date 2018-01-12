/*******************************************************************************
* File Name: AckTimer_PM.c
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

#include "AckTimer.h"

static AckTimer_BACKUP_STRUCT AckTimer_backup;


/*******************************************************************************
* Function Name: AckTimer_SaveConfig
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
void AckTimer_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: AckTimer_Sleep
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
void AckTimer_Sleep(void)
{
    if(0u != (AckTimer_BLOCK_CONTROL_REG & AckTimer_MASK))
    {
        AckTimer_backup.enableState = 1u;
    }
    else
    {
        AckTimer_backup.enableState = 0u;
    }

    AckTimer_Stop();
    AckTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: AckTimer_RestoreConfig
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
void AckTimer_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: AckTimer_Wakeup
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
void AckTimer_Wakeup(void)
{
    AckTimer_RestoreConfig();

    if(0u != AckTimer_backup.enableState)
    {
        AckTimer_Enable();
    }
}


/* [] END OF FILE */
