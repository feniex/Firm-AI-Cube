/*******************************************************************************
* File Name: motorControlPWM.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "motorControlPWM.h"

/* Error message for removed <resource> through optimization */
#ifdef motorControlPWM_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* motorControlPWM_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 motorControlPWM_initVar = 0u;


/*******************************************************************************
* Function Name: motorControlPWM_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  motorControlPWM_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void motorControlPWM_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(motorControlPWM_initVar == 0u)
    {
        motorControlPWM_Init();
        motorControlPWM_initVar = 1u;
    }
    motorControlPWM_Enable();

}


/*******************************************************************************
* Function Name: motorControlPWM_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  motorControlPWM_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void motorControlPWM_Init(void) 
{
    #if (motorControlPWM_UsingFixedFunction || motorControlPWM_UseControl)
        uint8 ctrl;
    #endif /* (motorControlPWM_UsingFixedFunction || motorControlPWM_UseControl) */

    #if(!motorControlPWM_UsingFixedFunction)
        #if(motorControlPWM_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 motorControlPWM_interruptState;
        #endif /* (motorControlPWM_UseStatus) */
    #endif /* (!motorControlPWM_UsingFixedFunction) */

    #if (motorControlPWM_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        motorControlPWM_CONTROL |= motorControlPWM_CFG0_MODE;
        #if (motorControlPWM_DeadBand2_4)
            motorControlPWM_CONTROL |= motorControlPWM_CFG0_DB;
        #endif /* (motorControlPWM_DeadBand2_4) */

        ctrl = motorControlPWM_CONTROL3 & ((uint8 )(~motorControlPWM_CTRL_CMPMODE1_MASK));
        motorControlPWM_CONTROL3 = ctrl | motorControlPWM_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        motorControlPWM_RT1 &= ((uint8)(~motorControlPWM_RT1_MASK));
        motorControlPWM_RT1 |= motorControlPWM_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        motorControlPWM_RT1 &= ((uint8)(~motorControlPWM_SYNCDSI_MASK));
        motorControlPWM_RT1 |= motorControlPWM_SYNCDSI_EN;

    #elif (motorControlPWM_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = motorControlPWM_CONTROL & ((uint8)(~motorControlPWM_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~motorControlPWM_CTRL_CMPMODE1_MASK));
        motorControlPWM_CONTROL = ctrl | motorControlPWM_DEFAULT_COMPARE2_MODE |
                                   motorControlPWM_DEFAULT_COMPARE1_MODE;
    #endif /* (motorControlPWM_UsingFixedFunction) */

    #if (!motorControlPWM_UsingFixedFunction)
        #if (motorControlPWM_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            motorControlPWM_AUX_CONTROLDP0 |= (motorControlPWM_AUX_CTRL_FIFO0_CLR);
        #else /* (motorControlPWM_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            motorControlPWM_AUX_CONTROLDP0 |= (motorControlPWM_AUX_CTRL_FIFO0_CLR);
            motorControlPWM_AUX_CONTROLDP1 |= (motorControlPWM_AUX_CTRL_FIFO0_CLR);
        #endif /* (motorControlPWM_Resolution == 8) */

        motorControlPWM_WriteCounter(motorControlPWM_INIT_PERIOD_VALUE);
    #endif /* (!motorControlPWM_UsingFixedFunction) */

    motorControlPWM_WritePeriod(motorControlPWM_INIT_PERIOD_VALUE);

        #if (motorControlPWM_UseOneCompareMode)
            motorControlPWM_WriteCompare(motorControlPWM_INIT_COMPARE_VALUE1);
        #else
            motorControlPWM_WriteCompare1(motorControlPWM_INIT_COMPARE_VALUE1);
            motorControlPWM_WriteCompare2(motorControlPWM_INIT_COMPARE_VALUE2);
        #endif /* (motorControlPWM_UseOneCompareMode) */

        #if (motorControlPWM_KillModeMinTime)
            motorControlPWM_WriteKillTime(motorControlPWM_MinimumKillTime);
        #endif /* (motorControlPWM_KillModeMinTime) */

        #if (motorControlPWM_DeadBandUsed)
            motorControlPWM_WriteDeadTime(motorControlPWM_INIT_DEAD_TIME);
        #endif /* (motorControlPWM_DeadBandUsed) */

    #if (motorControlPWM_UseStatus || motorControlPWM_UsingFixedFunction)
        motorControlPWM_SetInterruptMode(motorControlPWM_INIT_INTERRUPTS_MODE);
    #endif /* (motorControlPWM_UseStatus || motorControlPWM_UsingFixedFunction) */

    #if (motorControlPWM_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        motorControlPWM_GLOBAL_ENABLE |= motorControlPWM_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        motorControlPWM_CONTROL2 |= motorControlPWM_CTRL2_IRQ_SEL;
    #else
        #if(motorControlPWM_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            motorControlPWM_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            motorControlPWM_STATUS_AUX_CTRL |= motorControlPWM_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(motorControlPWM_interruptState);

            /* Clear the FIFO to enable the motorControlPWM_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            motorControlPWM_ClearFIFO();
        #endif /* (motorControlPWM_UseStatus) */
    #endif /* (motorControlPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: motorControlPWM_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void motorControlPWM_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (motorControlPWM_UsingFixedFunction)
        motorControlPWM_GLOBAL_ENABLE |= motorControlPWM_BLOCK_EN_MASK;
        motorControlPWM_GLOBAL_STBY_ENABLE |= motorControlPWM_BLOCK_STBY_EN_MASK;
    #endif /* (motorControlPWM_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (motorControlPWM_UseControl || motorControlPWM_UsingFixedFunction)
        motorControlPWM_CONTROL |= motorControlPWM_CTRL_ENABLE;
    #endif /* (motorControlPWM_UseControl || motorControlPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: motorControlPWM_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void motorControlPWM_Stop(void) 
{
    #if (motorControlPWM_UseControl || motorControlPWM_UsingFixedFunction)
        motorControlPWM_CONTROL &= ((uint8)(~motorControlPWM_CTRL_ENABLE));
    #endif /* (motorControlPWM_UseControl || motorControlPWM_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (motorControlPWM_UsingFixedFunction)
        motorControlPWM_GLOBAL_ENABLE &= ((uint8)(~motorControlPWM_BLOCK_EN_MASK));
        motorControlPWM_GLOBAL_STBY_ENABLE &= ((uint8)(~motorControlPWM_BLOCK_STBY_EN_MASK));
    #endif /* (motorControlPWM_UsingFixedFunction) */
}

#if (motorControlPWM_UseOneCompareMode)
    #if (motorControlPWM_CompareMode1SW)


        /*******************************************************************************
        * Function Name: motorControlPWM_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void motorControlPWM_SetCompareMode(uint8 comparemode) 
        {
            #if(motorControlPWM_UsingFixedFunction)

                #if(0 != motorControlPWM_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << motorControlPWM_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != motorControlPWM_CTRL_CMPMODE1_SHIFT) */

                motorControlPWM_CONTROL3 &= ((uint8)(~motorControlPWM_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                motorControlPWM_CONTROL3 |= comparemodemasked;

            #elif (motorControlPWM_UseControl)

                #if(0 != motorControlPWM_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << motorControlPWM_CTRL_CMPMODE1_SHIFT)) &
                                                motorControlPWM_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & motorControlPWM_CTRL_CMPMODE1_MASK;
                #endif /* (0 != motorControlPWM_CTRL_CMPMODE1_SHIFT) */

                #if(0 != motorControlPWM_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << motorControlPWM_CTRL_CMPMODE2_SHIFT)) &
                                               motorControlPWM_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & motorControlPWM_CTRL_CMPMODE2_MASK;
                #endif /* (0 != motorControlPWM_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                motorControlPWM_CONTROL &= ((uint8)(~(motorControlPWM_CTRL_CMPMODE1_MASK |
                                            motorControlPWM_CTRL_CMPMODE2_MASK)));
                motorControlPWM_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (motorControlPWM_UsingFixedFunction) */
        }
    #endif /* motorControlPWM_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (motorControlPWM_CompareMode1SW)


        /*******************************************************************************
        * Function Name: motorControlPWM_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void motorControlPWM_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != motorControlPWM_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << motorControlPWM_CTRL_CMPMODE1_SHIFT)) &
                                           motorControlPWM_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & motorControlPWM_CTRL_CMPMODE1_MASK;
            #endif /* (0 != motorControlPWM_CTRL_CMPMODE1_SHIFT) */

            #if (motorControlPWM_UseControl)
                motorControlPWM_CONTROL &= ((uint8)(~motorControlPWM_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                motorControlPWM_CONTROL |= comparemodemasked;
            #endif /* (motorControlPWM_UseControl) */
        }
    #endif /* motorControlPWM_CompareMode1SW */

#if (motorControlPWM_CompareMode2SW)


    /*******************************************************************************
    * Function Name: motorControlPWM_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void motorControlPWM_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != motorControlPWM_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << motorControlPWM_CTRL_CMPMODE2_SHIFT)) &
                                                 motorControlPWM_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & motorControlPWM_CTRL_CMPMODE2_MASK;
        #endif /* (0 != motorControlPWM_CTRL_CMPMODE2_SHIFT) */

        #if (motorControlPWM_UseControl)
            motorControlPWM_CONTROL &= ((uint8)(~motorControlPWM_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            motorControlPWM_CONTROL |= comparemodemasked;
        #endif /* (motorControlPWM_UseControl) */
    }
    #endif /*motorControlPWM_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!motorControlPWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: motorControlPWM_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void motorControlPWM_WriteCounter(uint8 counter) \
                                       
    {
        CY_SET_REG8(motorControlPWM_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: motorControlPWM_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint8 motorControlPWM_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(motorControlPWM_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG8(motorControlPWM_CAPTURE_LSB_PTR));
    }

    #if (motorControlPWM_UseStatus)


        /*******************************************************************************
        * Function Name: motorControlPWM_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void motorControlPWM_ClearFIFO(void) 
        {
            while(0u != (motorControlPWM_ReadStatusRegister() & motorControlPWM_STATUS_FIFONEMPTY))
            {
                (void)motorControlPWM_ReadCapture();
            }
        }

    #endif /* motorControlPWM_UseStatus */

#endif /* !motorControlPWM_UsingFixedFunction */


/*******************************************************************************
* Function Name: motorControlPWM_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void motorControlPWM_WritePeriod(uint8 period) 
{
    #if(motorControlPWM_UsingFixedFunction)
        CY_SET_REG16(motorControlPWM_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG8(motorControlPWM_PERIOD_LSB_PTR, period);
    #endif /* (motorControlPWM_UsingFixedFunction) */
}

#if (motorControlPWM_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: motorControlPWM_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void motorControlPWM_WriteCompare(uint8 compare) \
                                       
    {
        #if(motorControlPWM_UsingFixedFunction)
            CY_SET_REG16(motorControlPWM_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(motorControlPWM_COMPARE1_LSB_PTR, compare);
        #endif /* (motorControlPWM_UsingFixedFunction) */

        #if (motorControlPWM_PWMMode == motorControlPWM__B_PWM__DITHER)
            #if(motorControlPWM_UsingFixedFunction)
                CY_SET_REG16(motorControlPWM_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG8(motorControlPWM_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (motorControlPWM_UsingFixedFunction) */
        #endif /* (motorControlPWM_PWMMode == motorControlPWM__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: motorControlPWM_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void motorControlPWM_WriteCompare1(uint8 compare) \
                                        
    {
        #if(motorControlPWM_UsingFixedFunction)
            CY_SET_REG16(motorControlPWM_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(motorControlPWM_COMPARE1_LSB_PTR, compare);
        #endif /* (motorControlPWM_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: motorControlPWM_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void motorControlPWM_WriteCompare2(uint8 compare) \
                                        
    {
        #if(motorControlPWM_UsingFixedFunction)
            CY_SET_REG16(motorControlPWM_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG8(motorControlPWM_COMPARE2_LSB_PTR, compare);
        #endif /* (motorControlPWM_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (motorControlPWM_DeadBandUsed)


    /*******************************************************************************
    * Function Name: motorControlPWM_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void motorControlPWM_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!motorControlPWM_DeadBand2_4)
            CY_SET_REG8(motorControlPWM_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            motorControlPWM_DEADBAND_COUNT &= ((uint8)(~motorControlPWM_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(motorControlPWM_DEADBAND_COUNT_SHIFT)
                motorControlPWM_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << motorControlPWM_DEADBAND_COUNT_SHIFT)) &
                                                    motorControlPWM_DEADBAND_COUNT_MASK;
            #else
                motorControlPWM_DEADBAND_COUNT |= deadtime & motorControlPWM_DEADBAND_COUNT_MASK;
            #endif /* (motorControlPWM_DEADBAND_COUNT_SHIFT) */

        #endif /* (!motorControlPWM_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: motorControlPWM_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 motorControlPWM_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!motorControlPWM_DeadBand2_4)
            return (CY_GET_REG8(motorControlPWM_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(motorControlPWM_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(motorControlPWM_DEADBAND_COUNT & motorControlPWM_DEADBAND_COUNT_MASK)) >>
                                                                           motorControlPWM_DEADBAND_COUNT_SHIFT));
            #else
                return (motorControlPWM_DEADBAND_COUNT & motorControlPWM_DEADBAND_COUNT_MASK);
            #endif /* (motorControlPWM_DEADBAND_COUNT_SHIFT) */
        #endif /* (!motorControlPWM_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (motorControlPWM_UseStatus || motorControlPWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: motorControlPWM_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void motorControlPWM_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(motorControlPWM_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: motorControlPWM_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 motorControlPWM_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(motorControlPWM_STATUS_PTR));
    }

#endif /* (motorControlPWM_UseStatus || motorControlPWM_UsingFixedFunction) */


#if (motorControlPWM_UseControl)


    /*******************************************************************************
    * Function Name: motorControlPWM_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 motorControlPWM_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(motorControlPWM_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: motorControlPWM_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void motorControlPWM_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(motorControlPWM_CONTROL_PTR, control);
    }

#endif /* (motorControlPWM_UseControl) */


#if (!motorControlPWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: motorControlPWM_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint8 motorControlPWM_ReadCapture(void) 
    {
        return (CY_GET_REG8(motorControlPWM_CAPTURE_LSB_PTR));
    }

#endif /* (!motorControlPWM_UsingFixedFunction) */


#if (motorControlPWM_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: motorControlPWM_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint8 motorControlPWM_ReadCompare(void) 
    {
        #if(motorControlPWM_UsingFixedFunction)
            return ((uint8)CY_GET_REG16(motorControlPWM_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG8(motorControlPWM_COMPARE1_LSB_PTR));
        #endif /* (motorControlPWM_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: motorControlPWM_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint8 motorControlPWM_ReadCompare1(void) 
    {
        return (CY_GET_REG8(motorControlPWM_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: motorControlPWM_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint8 motorControlPWM_ReadCompare2(void) 
    {
        return (CY_GET_REG8(motorControlPWM_COMPARE2_LSB_PTR));
    }

#endif /* (motorControlPWM_UseOneCompareMode) */


/*******************************************************************************
* Function Name: motorControlPWM_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint8 motorControlPWM_ReadPeriod(void) 
{
    #if(motorControlPWM_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(motorControlPWM_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(motorControlPWM_PERIOD_LSB_PTR));
    #endif /* (motorControlPWM_UsingFixedFunction) */
}

#if ( motorControlPWM_KillModeMinTime)


    /*******************************************************************************
    * Function Name: motorControlPWM_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void motorControlPWM_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(motorControlPWM_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: motorControlPWM_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 motorControlPWM_ReadKillTime(void) 
    {
        return (CY_GET_REG8(motorControlPWM_KILLMODEMINTIME_PTR));
    }

#endif /* ( motorControlPWM_KillModeMinTime) */

/* [] END OF FILE */
