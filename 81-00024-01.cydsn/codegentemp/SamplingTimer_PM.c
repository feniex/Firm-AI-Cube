/*******************************************************************************
* File Name: SamplingTimer_PM.c
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

#include "SamplingTimer.h"

static SamplingTimer_BACKUP_STRUCT SamplingTimer_backup;


/*******************************************************************************
* Function Name: SamplingTimer_SaveConfig
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
void SamplingTimer_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: SamplingTimer_Sleep
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
void SamplingTimer_Sleep(void)
{
    if(0u != (SamplingTimer_BLOCK_CONTROL_REG & SamplingTimer_MASK))
    {
        SamplingTimer_backup.enableState = 1u;
    }
    else
    {
        SamplingTimer_backup.enableState = 0u;
    }

    SamplingTimer_Stop();
    SamplingTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: SamplingTimer_RestoreConfig
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
void SamplingTimer_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: SamplingTimer_Wakeup
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
void SamplingTimer_Wakeup(void)
{
    SamplingTimer_RestoreConfig();

    if(0u != SamplingTimer_backup.enableState)
    {
        SamplingTimer_Enable();
    }
}


/* [] END OF FILE */
