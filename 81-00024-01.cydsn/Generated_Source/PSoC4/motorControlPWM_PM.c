/*******************************************************************************
* File Name: motorControlPWM_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "motorControlPWM.h"

static motorControlPWM_backupStruct motorControlPWM_backup;


/*******************************************************************************
* Function Name: motorControlPWM_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  motorControlPWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void motorControlPWM_SaveConfig(void) 
{

    #if(!motorControlPWM_UsingFixedFunction)
        #if(!motorControlPWM_PWMModeIsCenterAligned)
            motorControlPWM_backup.PWMPeriod = motorControlPWM_ReadPeriod();
        #endif /* (!motorControlPWM_PWMModeIsCenterAligned) */
        motorControlPWM_backup.PWMUdb = motorControlPWM_ReadCounter();
        #if (motorControlPWM_UseStatus)
            motorControlPWM_backup.InterruptMaskValue = motorControlPWM_STATUS_MASK;
        #endif /* (motorControlPWM_UseStatus) */

        #if(motorControlPWM_DeadBandMode == motorControlPWM__B_PWM__DBM_256_CLOCKS || \
            motorControlPWM_DeadBandMode == motorControlPWM__B_PWM__DBM_2_4_CLOCKS)
            motorControlPWM_backup.PWMdeadBandValue = motorControlPWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(motorControlPWM_KillModeMinTime)
             motorControlPWM_backup.PWMKillCounterPeriod = motorControlPWM_ReadKillTime();
        #endif /* (motorControlPWM_KillModeMinTime) */

        #if(motorControlPWM_UseControl)
            motorControlPWM_backup.PWMControlRegister = motorControlPWM_ReadControlRegister();
        #endif /* (motorControlPWM_UseControl) */
    #endif  /* (!motorControlPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: motorControlPWM_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  motorControlPWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void motorControlPWM_RestoreConfig(void) 
{
        #if(!motorControlPWM_UsingFixedFunction)
            #if(!motorControlPWM_PWMModeIsCenterAligned)
                motorControlPWM_WritePeriod(motorControlPWM_backup.PWMPeriod);
            #endif /* (!motorControlPWM_PWMModeIsCenterAligned) */

            motorControlPWM_WriteCounter(motorControlPWM_backup.PWMUdb);

            #if (motorControlPWM_UseStatus)
                motorControlPWM_STATUS_MASK = motorControlPWM_backup.InterruptMaskValue;
            #endif /* (motorControlPWM_UseStatus) */

            #if(motorControlPWM_DeadBandMode == motorControlPWM__B_PWM__DBM_256_CLOCKS || \
                motorControlPWM_DeadBandMode == motorControlPWM__B_PWM__DBM_2_4_CLOCKS)
                motorControlPWM_WriteDeadTime(motorControlPWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(motorControlPWM_KillModeMinTime)
                motorControlPWM_WriteKillTime(motorControlPWM_backup.PWMKillCounterPeriod);
            #endif /* (motorControlPWM_KillModeMinTime) */

            #if(motorControlPWM_UseControl)
                motorControlPWM_WriteControlRegister(motorControlPWM_backup.PWMControlRegister);
            #endif /* (motorControlPWM_UseControl) */
        #endif  /* (!motorControlPWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: motorControlPWM_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  motorControlPWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void motorControlPWM_Sleep(void) 
{
    #if(motorControlPWM_UseControl)
        if(motorControlPWM_CTRL_ENABLE == (motorControlPWM_CONTROL & motorControlPWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            motorControlPWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            motorControlPWM_backup.PWMEnableState = 0u;
        }
    #endif /* (motorControlPWM_UseControl) */

    /* Stop component */
    motorControlPWM_Stop();

    /* Save registers configuration */
    motorControlPWM_SaveConfig();
}


/*******************************************************************************
* Function Name: motorControlPWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  motorControlPWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void motorControlPWM_Wakeup(void) 
{
     /* Restore registers values */
    motorControlPWM_RestoreConfig();

    if(motorControlPWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        motorControlPWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
