/*******************************************************************************
* File Name: overCurrentTimer_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "overCurrentTimer.h"

static overCurrentTimer_backupStruct overCurrentTimer_backup;


/*******************************************************************************
* Function Name: overCurrentTimer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  overCurrentTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void overCurrentTimer_SaveConfig(void) 
{
    #if (!overCurrentTimer_UsingFixedFunction)
        overCurrentTimer_backup.TimerUdb = overCurrentTimer_ReadCounter();
        overCurrentTimer_backup.InterruptMaskValue = overCurrentTimer_STATUS_MASK;
        #if (overCurrentTimer_UsingHWCaptureCounter)
            overCurrentTimer_backup.TimerCaptureCounter = overCurrentTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!overCurrentTimer_UDB_CONTROL_REG_REMOVED)
            overCurrentTimer_backup.TimerControlRegister = overCurrentTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: overCurrentTimer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  overCurrentTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void overCurrentTimer_RestoreConfig(void) 
{   
    #if (!overCurrentTimer_UsingFixedFunction)

        overCurrentTimer_WriteCounter(overCurrentTimer_backup.TimerUdb);
        overCurrentTimer_STATUS_MASK =overCurrentTimer_backup.InterruptMaskValue;
        #if (overCurrentTimer_UsingHWCaptureCounter)
            overCurrentTimer_SetCaptureCount(overCurrentTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!overCurrentTimer_UDB_CONTROL_REG_REMOVED)
            overCurrentTimer_WriteControlRegister(overCurrentTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: overCurrentTimer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  overCurrentTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void overCurrentTimer_Sleep(void) 
{
    #if(!overCurrentTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(overCurrentTimer_CTRL_ENABLE == (overCurrentTimer_CONTROL & overCurrentTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            overCurrentTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            overCurrentTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    overCurrentTimer_Stop();
    overCurrentTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: overCurrentTimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  overCurrentTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void overCurrentTimer_Wakeup(void) 
{
    overCurrentTimer_RestoreConfig();
    #if(!overCurrentTimer_UDB_CONTROL_REG_REMOVED)
        if(overCurrentTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                overCurrentTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
