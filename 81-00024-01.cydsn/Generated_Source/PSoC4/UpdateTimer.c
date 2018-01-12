/*******************************************************************************
* File Name: UpdateTimer.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the UpdateTimer
*  component
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

uint8 UpdateTimer_initVar = 0u;


/*******************************************************************************
* Function Name: UpdateTimer_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default UpdateTimer configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (UpdateTimer__QUAD == UpdateTimer_CONFIG)
        UpdateTimer_CONTROL_REG = UpdateTimer_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        UpdateTimer_TRIG_CONTROL1_REG  = UpdateTimer_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        UpdateTimer_SetInterruptMode(UpdateTimer_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        UpdateTimer_SetCounterMode(UpdateTimer_COUNT_DOWN);
        UpdateTimer_WritePeriod(UpdateTimer_QUAD_PERIOD_INIT_VALUE);
        UpdateTimer_WriteCounter(UpdateTimer_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (UpdateTimer__QUAD == UpdateTimer_CONFIG) */

    #if (UpdateTimer__TIMER == UpdateTimer_CONFIG)
        UpdateTimer_CONTROL_REG = UpdateTimer_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        UpdateTimer_TRIG_CONTROL1_REG  = UpdateTimer_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        UpdateTimer_SetInterruptMode(UpdateTimer_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        UpdateTimer_WritePeriod(UpdateTimer_TC_PERIOD_VALUE );

        #if (UpdateTimer__COMPARE == UpdateTimer_TC_COMP_CAP_MODE)
            UpdateTimer_WriteCompare(UpdateTimer_TC_COMPARE_VALUE);

            #if (1u == UpdateTimer_TC_COMPARE_SWAP)
                UpdateTimer_SetCompareSwap(1u);
                UpdateTimer_WriteCompareBuf(UpdateTimer_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == UpdateTimer_TC_COMPARE_SWAP) */
        #endif  /* (UpdateTimer__COMPARE == UpdateTimer_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (UpdateTimer_CY_TCPWM_V2 && UpdateTimer_TIMER_UPDOWN_CNT_USED && !UpdateTimer_CY_TCPWM_4000)
            UpdateTimer_WriteCounter(1u);
        #elif(UpdateTimer__COUNT_DOWN == UpdateTimer_TC_COUNTER_MODE)
            UpdateTimer_WriteCounter(UpdateTimer_TC_PERIOD_VALUE);
        #else
            UpdateTimer_WriteCounter(0u);
        #endif /* (UpdateTimer_CY_TCPWM_V2 && UpdateTimer_TIMER_UPDOWN_CNT_USED && !UpdateTimer_CY_TCPWM_4000) */
    #endif  /* (UpdateTimer__TIMER == UpdateTimer_CONFIG) */

    #if (UpdateTimer__PWM_SEL == UpdateTimer_CONFIG)
        UpdateTimer_CONTROL_REG = UpdateTimer_CTRL_PWM_BASE_CONFIG;

        #if (UpdateTimer__PWM_PR == UpdateTimer_PWM_MODE)
            UpdateTimer_CONTROL_REG |= UpdateTimer_CTRL_PWM_RUN_MODE;
            UpdateTimer_WriteCounter(UpdateTimer_PWM_PR_INIT_VALUE);
        #else
            UpdateTimer_CONTROL_REG |= UpdateTimer_CTRL_PWM_ALIGN | UpdateTimer_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (UpdateTimer_CY_TCPWM_V2 && UpdateTimer_PWM_UPDOWN_CNT_USED && !UpdateTimer_CY_TCPWM_4000)
                UpdateTimer_WriteCounter(1u);
            #elif (UpdateTimer__RIGHT == UpdateTimer_PWM_ALIGN)
                UpdateTimer_WriteCounter(UpdateTimer_PWM_PERIOD_VALUE);
            #else 
                UpdateTimer_WriteCounter(0u);
            #endif  /* (UpdateTimer_CY_TCPWM_V2 && UpdateTimer_PWM_UPDOWN_CNT_USED && !UpdateTimer_CY_TCPWM_4000) */
        #endif  /* (UpdateTimer__PWM_PR == UpdateTimer_PWM_MODE) */

        #if (UpdateTimer__PWM_DT == UpdateTimer_PWM_MODE)
            UpdateTimer_CONTROL_REG |= UpdateTimer_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (UpdateTimer__PWM_DT == UpdateTimer_PWM_MODE) */

        #if (UpdateTimer__PWM == UpdateTimer_PWM_MODE)
            UpdateTimer_CONTROL_REG |= UpdateTimer_CTRL_PWM_PRESCALER;
        #endif  /* (UpdateTimer__PWM == UpdateTimer_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        UpdateTimer_TRIG_CONTROL1_REG  = UpdateTimer_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        UpdateTimer_SetInterruptMode(UpdateTimer_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (UpdateTimer__PWM_PR == UpdateTimer_PWM_MODE)
            UpdateTimer_TRIG_CONTROL2_REG =
                    (UpdateTimer_CC_MATCH_NO_CHANGE    |
                    UpdateTimer_OVERLOW_NO_CHANGE      |
                    UpdateTimer_UNDERFLOW_NO_CHANGE);
        #else
            #if (UpdateTimer__LEFT == UpdateTimer_PWM_ALIGN)
                UpdateTimer_TRIG_CONTROL2_REG = UpdateTimer_PWM_MODE_LEFT;
            #endif  /* ( UpdateTimer_PWM_LEFT == UpdateTimer_PWM_ALIGN) */

            #if (UpdateTimer__RIGHT == UpdateTimer_PWM_ALIGN)
                UpdateTimer_TRIG_CONTROL2_REG = UpdateTimer_PWM_MODE_RIGHT;
            #endif  /* ( UpdateTimer_PWM_RIGHT == UpdateTimer_PWM_ALIGN) */

            #if (UpdateTimer__CENTER == UpdateTimer_PWM_ALIGN)
                UpdateTimer_TRIG_CONTROL2_REG = UpdateTimer_PWM_MODE_CENTER;
            #endif  /* ( UpdateTimer_PWM_CENTER == UpdateTimer_PWM_ALIGN) */

            #if (UpdateTimer__ASYMMETRIC == UpdateTimer_PWM_ALIGN)
                UpdateTimer_TRIG_CONTROL2_REG = UpdateTimer_PWM_MODE_ASYM;
            #endif  /* (UpdateTimer__ASYMMETRIC == UpdateTimer_PWM_ALIGN) */
        #endif  /* (UpdateTimer__PWM_PR == UpdateTimer_PWM_MODE) */

        /* Set other values from customizer */
        UpdateTimer_WritePeriod(UpdateTimer_PWM_PERIOD_VALUE );
        UpdateTimer_WriteCompare(UpdateTimer_PWM_COMPARE_VALUE);

        #if (1u == UpdateTimer_PWM_COMPARE_SWAP)
            UpdateTimer_SetCompareSwap(1u);
            UpdateTimer_WriteCompareBuf(UpdateTimer_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == UpdateTimer_PWM_COMPARE_SWAP) */

        #if (1u == UpdateTimer_PWM_PERIOD_SWAP)
            UpdateTimer_SetPeriodSwap(1u);
            UpdateTimer_WritePeriodBuf(UpdateTimer_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == UpdateTimer_PWM_PERIOD_SWAP) */
    #endif  /* (UpdateTimer__PWM_SEL == UpdateTimer_CONFIG) */
    
}


/*******************************************************************************
* Function Name: UpdateTimer_Enable
********************************************************************************
*
* Summary:
*  Enables the UpdateTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    UpdateTimer_BLOCK_CONTROL_REG |= UpdateTimer_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (UpdateTimer__PWM_SEL == UpdateTimer_CONFIG)
        #if (0u == UpdateTimer_PWM_START_SIGNAL_PRESENT)
            UpdateTimer_TriggerCommand(UpdateTimer_MASK, UpdateTimer_CMD_START);
        #endif /* (0u == UpdateTimer_PWM_START_SIGNAL_PRESENT) */
    #endif /* (UpdateTimer__PWM_SEL == UpdateTimer_CONFIG) */

    #if (UpdateTimer__TIMER == UpdateTimer_CONFIG)
        #if (0u == UpdateTimer_TC_START_SIGNAL_PRESENT)
            UpdateTimer_TriggerCommand(UpdateTimer_MASK, UpdateTimer_CMD_START);
        #endif /* (0u == UpdateTimer_TC_START_SIGNAL_PRESENT) */
    #endif /* (UpdateTimer__TIMER == UpdateTimer_CONFIG) */
    
    #if (UpdateTimer__QUAD == UpdateTimer_CONFIG)
        #if (0u != UpdateTimer_QUAD_AUTO_START)
            UpdateTimer_TriggerCommand(UpdateTimer_MASK, UpdateTimer_CMD_RELOAD);
        #endif /* (0u != UpdateTimer_QUAD_AUTO_START) */
    #endif  /* (UpdateTimer__QUAD == UpdateTimer_CONFIG) */
}


/*******************************************************************************
* Function Name: UpdateTimer_Start
********************************************************************************
*
* Summary:
*  Initializes the UpdateTimer with default customizer
*  values when called the first time and enables the UpdateTimer.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  UpdateTimer_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time UpdateTimer_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the UpdateTimer_Start() routine.
*
*******************************************************************************/
void UpdateTimer_Start(void)
{
    if (0u == UpdateTimer_initVar)
    {
        UpdateTimer_Init();
        UpdateTimer_initVar = 1u;
    }

    UpdateTimer_Enable();
}


/*******************************************************************************
* Function Name: UpdateTimer_Stop
********************************************************************************
*
* Summary:
*  Disables the UpdateTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UpdateTimer_BLOCK_CONTROL_REG &= (uint32)~UpdateTimer_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UpdateTimer_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the UpdateTimer. This function is used when
*  configured as a generic UpdateTimer and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the UpdateTimer to operate in
*   Values:
*   - UpdateTimer_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - UpdateTimer_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - UpdateTimer_MODE_QUAD - Quadrature decoder
*         - UpdateTimer_MODE_PWM - PWM
*         - UpdateTimer_MODE_PWM_DT - PWM with dead time
*         - UpdateTimer_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UpdateTimer_CONTROL_REG &= (uint32)~UpdateTimer_MODE_MASK;
    UpdateTimer_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UpdateTimer_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - UpdateTimer_MODE_X1 - Counts on phi 1 rising
*         - UpdateTimer_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - UpdateTimer_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UpdateTimer_CONTROL_REG &= (uint32)~UpdateTimer_QUAD_MODE_MASK;
    UpdateTimer_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UpdateTimer_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - UpdateTimer_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - UpdateTimer_PRESCALE_DIVBY2    - Divide by 2
*         - UpdateTimer_PRESCALE_DIVBY4    - Divide by 4
*         - UpdateTimer_PRESCALE_DIVBY8    - Divide by 8
*         - UpdateTimer_PRESCALE_DIVBY16   - Divide by 16
*         - UpdateTimer_PRESCALE_DIVBY32   - Divide by 32
*         - UpdateTimer_PRESCALE_DIVBY64   - Divide by 64
*         - UpdateTimer_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UpdateTimer_CONTROL_REG &= (uint32)~UpdateTimer_PRESCALER_MASK;
    UpdateTimer_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UpdateTimer_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the UpdateTimer runs
*  continuously or stops when terminal count is reached.  By default the
*  UpdateTimer operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UpdateTimer_CONTROL_REG &= (uint32)~UpdateTimer_ONESHOT_MASK;
    UpdateTimer_CONTROL_REG |= ((uint32)((oneShotEnable & UpdateTimer_1BIT_MASK) <<
                                                               UpdateTimer_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UpdateTimer_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_SetPWMMode(uint32 modeMask)
{
    UpdateTimer_TRIG_CONTROL2_REG = (modeMask & UpdateTimer_6BIT_MASK);
}



/*******************************************************************************
* Function Name: UpdateTimer_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UpdateTimer_CONTROL_REG &= (uint32)~UpdateTimer_PWM_SYNC_KILL_MASK;
    UpdateTimer_CONTROL_REG |= ((uint32)((syncKillEnable & UpdateTimer_1BIT_MASK)  <<
                                               UpdateTimer_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UpdateTimer_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UpdateTimer_CONTROL_REG &= (uint32)~UpdateTimer_PWM_STOP_KILL_MASK;
    UpdateTimer_CONTROL_REG |= ((uint32)((stopOnKillEnable & UpdateTimer_1BIT_MASK)  <<
                                                         UpdateTimer_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UpdateTimer_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UpdateTimer_CONTROL_REG &= (uint32)~UpdateTimer_PRESCALER_MASK;
    UpdateTimer_CONTROL_REG |= ((uint32)((deadTime & UpdateTimer_8BIT_MASK) <<
                                                          UpdateTimer_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UpdateTimer_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - UpdateTimer_INVERT_LINE   - Inverts the line output
*         - UpdateTimer_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UpdateTimer_CONTROL_REG &= (uint32)~UpdateTimer_INV_OUT_MASK;
    UpdateTimer_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: UpdateTimer_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_WriteCounter(uint32 count)
{
    UpdateTimer_COUNTER_REG = (count & UpdateTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: UpdateTimer_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 UpdateTimer_ReadCounter(void)
{
    return (UpdateTimer_COUNTER_REG & UpdateTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: UpdateTimer_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - UpdateTimer_COUNT_UP       - Counts up
*     - UpdateTimer_COUNT_DOWN     - Counts down
*     - UpdateTimer_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - UpdateTimer_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UpdateTimer_CONTROL_REG &= (uint32)~UpdateTimer_UPDOWN_MASK;
    UpdateTimer_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UpdateTimer_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_WritePeriod(uint32 period)
{
    UpdateTimer_PERIOD_REG = (period & UpdateTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: UpdateTimer_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 UpdateTimer_ReadPeriod(void)
{
    return (UpdateTimer_PERIOD_REG & UpdateTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: UpdateTimer_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UpdateTimer_CONTROL_REG &= (uint32)~UpdateTimer_RELOAD_CC_MASK;
    UpdateTimer_CONTROL_REG |= (swapEnable & UpdateTimer_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UpdateTimer_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_WritePeriodBuf(uint32 periodBuf)
{
    UpdateTimer_PERIOD_BUF_REG = (periodBuf & UpdateTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: UpdateTimer_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 UpdateTimer_ReadPeriodBuf(void)
{
    return (UpdateTimer_PERIOD_BUF_REG & UpdateTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: UpdateTimer_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UpdateTimer_CONTROL_REG &= (uint32)~UpdateTimer_RELOAD_PERIOD_MASK;
    UpdateTimer_CONTROL_REG |= ((uint32)((swapEnable & UpdateTimer_1BIT_MASK) <<
                                                            UpdateTimer_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UpdateTimer_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void UpdateTimer_WriteCompare(uint32 compare)
{
    #if (UpdateTimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (UpdateTimer_CY_TCPWM_4000) */

    #if (UpdateTimer_CY_TCPWM_4000)
        currentMode = ((UpdateTimer_CONTROL_REG & UpdateTimer_UPDOWN_MASK) >> UpdateTimer_UPDOWN_SHIFT);

        if (((uint32)UpdateTimer__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)UpdateTimer__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (UpdateTimer_CY_TCPWM_4000) */
    
    UpdateTimer_COMP_CAP_REG = (compare & UpdateTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: UpdateTimer_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 UpdateTimer_ReadCompare(void)
{
    #if (UpdateTimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (UpdateTimer_CY_TCPWM_4000) */

    #if (UpdateTimer_CY_TCPWM_4000)
        currentMode = ((UpdateTimer_CONTROL_REG & UpdateTimer_UPDOWN_MASK) >> UpdateTimer_UPDOWN_SHIFT);
        
        regVal = UpdateTimer_COMP_CAP_REG;
        
        if (((uint32)UpdateTimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)UpdateTimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & UpdateTimer_16BIT_MASK);
    #else
        return (UpdateTimer_COMP_CAP_REG & UpdateTimer_16BIT_MASK);
    #endif /* (UpdateTimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: UpdateTimer_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void UpdateTimer_WriteCompareBuf(uint32 compareBuf)
{
    #if (UpdateTimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (UpdateTimer_CY_TCPWM_4000) */

    #if (UpdateTimer_CY_TCPWM_4000)
        currentMode = ((UpdateTimer_CONTROL_REG & UpdateTimer_UPDOWN_MASK) >> UpdateTimer_UPDOWN_SHIFT);

        if (((uint32)UpdateTimer__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)UpdateTimer__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (UpdateTimer_CY_TCPWM_4000) */
    
    UpdateTimer_COMP_CAP_BUF_REG = (compareBuf & UpdateTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: UpdateTimer_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 UpdateTimer_ReadCompareBuf(void)
{
    #if (UpdateTimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (UpdateTimer_CY_TCPWM_4000) */

    #if (UpdateTimer_CY_TCPWM_4000)
        currentMode = ((UpdateTimer_CONTROL_REG & UpdateTimer_UPDOWN_MASK) >> UpdateTimer_UPDOWN_SHIFT);

        regVal = UpdateTimer_COMP_CAP_BUF_REG;
        
        if (((uint32)UpdateTimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)UpdateTimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & UpdateTimer_16BIT_MASK);
    #else
        return (UpdateTimer_COMP_CAP_BUF_REG & UpdateTimer_16BIT_MASK);
    #endif /* (UpdateTimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: UpdateTimer_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 UpdateTimer_ReadCapture(void)
{
    return (UpdateTimer_COMP_CAP_REG & UpdateTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: UpdateTimer_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 UpdateTimer_ReadCaptureBuf(void)
{
    return (UpdateTimer_COMP_CAP_BUF_REG & UpdateTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: UpdateTimer_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - UpdateTimer_TRIG_LEVEL     - Level
*     - UpdateTimer_TRIG_RISING    - Rising edge
*     - UpdateTimer_TRIG_FALLING   - Falling edge
*     - UpdateTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UpdateTimer_TRIG_CONTROL1_REG &= (uint32)~UpdateTimer_CAPTURE_MASK;
    UpdateTimer_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UpdateTimer_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - UpdateTimer_TRIG_LEVEL     - Level
*     - UpdateTimer_TRIG_RISING    - Rising edge
*     - UpdateTimer_TRIG_FALLING   - Falling edge
*     - UpdateTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UpdateTimer_TRIG_CONTROL1_REG &= (uint32)~UpdateTimer_RELOAD_MASK;
    UpdateTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << UpdateTimer_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UpdateTimer_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - UpdateTimer_TRIG_LEVEL     - Level
*     - UpdateTimer_TRIG_RISING    - Rising edge
*     - UpdateTimer_TRIG_FALLING   - Falling edge
*     - UpdateTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UpdateTimer_TRIG_CONTROL1_REG &= (uint32)~UpdateTimer_START_MASK;
    UpdateTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << UpdateTimer_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UpdateTimer_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - UpdateTimer_TRIG_LEVEL     - Level
*     - UpdateTimer_TRIG_RISING    - Rising edge
*     - UpdateTimer_TRIG_FALLING   - Falling edge
*     - UpdateTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UpdateTimer_TRIG_CONTROL1_REG &= (uint32)~UpdateTimer_STOP_MASK;
    UpdateTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << UpdateTimer_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UpdateTimer_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - UpdateTimer_TRIG_LEVEL     - Level
*     - UpdateTimer_TRIG_RISING    - Rising edge
*     - UpdateTimer_TRIG_FALLING   - Falling edge
*     - UpdateTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UpdateTimer_TRIG_CONTROL1_REG &= (uint32)~UpdateTimer_COUNT_MASK;
    UpdateTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << UpdateTimer_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UpdateTimer_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - UpdateTimer_CMD_CAPTURE    - Trigger Capture/Switch command
*     - UpdateTimer_CMD_RELOAD     - Trigger Reload/Index command
*     - UpdateTimer_CMD_STOP       - Trigger Stop/Kill command
*     - UpdateTimer_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UpdateTimer_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UpdateTimer_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the UpdateTimer.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - UpdateTimer_STATUS_DOWN    - Set if counting down
*     - UpdateTimer_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 UpdateTimer_ReadStatus(void)
{
    return ((UpdateTimer_STATUS_REG >> UpdateTimer_RUNNING_STATUS_SHIFT) |
            (UpdateTimer_STATUS_REG & UpdateTimer_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: UpdateTimer_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - UpdateTimer_INTR_MASK_TC       - Terminal count mask
*     - UpdateTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_SetInterruptMode(uint32 interruptMask)
{
    UpdateTimer_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: UpdateTimer_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - UpdateTimer_INTR_MASK_TC       - Terminal count mask
*     - UpdateTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 UpdateTimer_GetInterruptSourceMasked(void)
{
    return (UpdateTimer_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: UpdateTimer_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - UpdateTimer_INTR_MASK_TC       - Terminal count mask
*     - UpdateTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 UpdateTimer_GetInterruptSource(void)
{
    return (UpdateTimer_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: UpdateTimer_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - UpdateTimer_INTR_MASK_TC       - Terminal count mask
*     - UpdateTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_ClearInterrupt(uint32 interruptMask)
{
    UpdateTimer_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: UpdateTimer_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - UpdateTimer_INTR_MASK_TC       - Terminal count mask
*     - UpdateTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void UpdateTimer_SetInterrupt(uint32 interruptMask)
{
    UpdateTimer_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
