/*******************************************************************************
* File Name: TimeoutTimer.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the TimeoutTimer
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

#include "TimeoutTimer.h"

uint8 TimeoutTimer_initVar = 0u;


/*******************************************************************************
* Function Name: TimeoutTimer_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default TimeoutTimer configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TimeoutTimer_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (TimeoutTimer__QUAD == TimeoutTimer_CONFIG)
        TimeoutTimer_CONTROL_REG = TimeoutTimer_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        TimeoutTimer_TRIG_CONTROL1_REG  = TimeoutTimer_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        TimeoutTimer_SetInterruptMode(TimeoutTimer_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        TimeoutTimer_SetCounterMode(TimeoutTimer_COUNT_DOWN);
        TimeoutTimer_WritePeriod(TimeoutTimer_QUAD_PERIOD_INIT_VALUE);
        TimeoutTimer_WriteCounter(TimeoutTimer_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (TimeoutTimer__QUAD == TimeoutTimer_CONFIG) */

    #if (TimeoutTimer__TIMER == TimeoutTimer_CONFIG)
        TimeoutTimer_CONTROL_REG = TimeoutTimer_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        TimeoutTimer_TRIG_CONTROL1_REG  = TimeoutTimer_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        TimeoutTimer_SetInterruptMode(TimeoutTimer_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        TimeoutTimer_WritePeriod(TimeoutTimer_TC_PERIOD_VALUE );

        #if (TimeoutTimer__COMPARE == TimeoutTimer_TC_COMP_CAP_MODE)
            TimeoutTimer_WriteCompare(TimeoutTimer_TC_COMPARE_VALUE);

            #if (1u == TimeoutTimer_TC_COMPARE_SWAP)
                TimeoutTimer_SetCompareSwap(1u);
                TimeoutTimer_WriteCompareBuf(TimeoutTimer_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == TimeoutTimer_TC_COMPARE_SWAP) */
        #endif  /* (TimeoutTimer__COMPARE == TimeoutTimer_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (TimeoutTimer_CY_TCPWM_V2 && TimeoutTimer_TIMER_UPDOWN_CNT_USED && !TimeoutTimer_CY_TCPWM_4000)
            TimeoutTimer_WriteCounter(1u);
        #elif(TimeoutTimer__COUNT_DOWN == TimeoutTimer_TC_COUNTER_MODE)
            TimeoutTimer_WriteCounter(TimeoutTimer_TC_PERIOD_VALUE);
        #else
            TimeoutTimer_WriteCounter(0u);
        #endif /* (TimeoutTimer_CY_TCPWM_V2 && TimeoutTimer_TIMER_UPDOWN_CNT_USED && !TimeoutTimer_CY_TCPWM_4000) */
    #endif  /* (TimeoutTimer__TIMER == TimeoutTimer_CONFIG) */

    #if (TimeoutTimer__PWM_SEL == TimeoutTimer_CONFIG)
        TimeoutTimer_CONTROL_REG = TimeoutTimer_CTRL_PWM_BASE_CONFIG;

        #if (TimeoutTimer__PWM_PR == TimeoutTimer_PWM_MODE)
            TimeoutTimer_CONTROL_REG |= TimeoutTimer_CTRL_PWM_RUN_MODE;
            TimeoutTimer_WriteCounter(TimeoutTimer_PWM_PR_INIT_VALUE);
        #else
            TimeoutTimer_CONTROL_REG |= TimeoutTimer_CTRL_PWM_ALIGN | TimeoutTimer_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (TimeoutTimer_CY_TCPWM_V2 && TimeoutTimer_PWM_UPDOWN_CNT_USED && !TimeoutTimer_CY_TCPWM_4000)
                TimeoutTimer_WriteCounter(1u);
            #elif (TimeoutTimer__RIGHT == TimeoutTimer_PWM_ALIGN)
                TimeoutTimer_WriteCounter(TimeoutTimer_PWM_PERIOD_VALUE);
            #else 
                TimeoutTimer_WriteCounter(0u);
            #endif  /* (TimeoutTimer_CY_TCPWM_V2 && TimeoutTimer_PWM_UPDOWN_CNT_USED && !TimeoutTimer_CY_TCPWM_4000) */
        #endif  /* (TimeoutTimer__PWM_PR == TimeoutTimer_PWM_MODE) */

        #if (TimeoutTimer__PWM_DT == TimeoutTimer_PWM_MODE)
            TimeoutTimer_CONTROL_REG |= TimeoutTimer_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (TimeoutTimer__PWM_DT == TimeoutTimer_PWM_MODE) */

        #if (TimeoutTimer__PWM == TimeoutTimer_PWM_MODE)
            TimeoutTimer_CONTROL_REG |= TimeoutTimer_CTRL_PWM_PRESCALER;
        #endif  /* (TimeoutTimer__PWM == TimeoutTimer_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        TimeoutTimer_TRIG_CONTROL1_REG  = TimeoutTimer_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        TimeoutTimer_SetInterruptMode(TimeoutTimer_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (TimeoutTimer__PWM_PR == TimeoutTimer_PWM_MODE)
            TimeoutTimer_TRIG_CONTROL2_REG =
                    (TimeoutTimer_CC_MATCH_NO_CHANGE    |
                    TimeoutTimer_OVERLOW_NO_CHANGE      |
                    TimeoutTimer_UNDERFLOW_NO_CHANGE);
        #else
            #if (TimeoutTimer__LEFT == TimeoutTimer_PWM_ALIGN)
                TimeoutTimer_TRIG_CONTROL2_REG = TimeoutTimer_PWM_MODE_LEFT;
            #endif  /* ( TimeoutTimer_PWM_LEFT == TimeoutTimer_PWM_ALIGN) */

            #if (TimeoutTimer__RIGHT == TimeoutTimer_PWM_ALIGN)
                TimeoutTimer_TRIG_CONTROL2_REG = TimeoutTimer_PWM_MODE_RIGHT;
            #endif  /* ( TimeoutTimer_PWM_RIGHT == TimeoutTimer_PWM_ALIGN) */

            #if (TimeoutTimer__CENTER == TimeoutTimer_PWM_ALIGN)
                TimeoutTimer_TRIG_CONTROL2_REG = TimeoutTimer_PWM_MODE_CENTER;
            #endif  /* ( TimeoutTimer_PWM_CENTER == TimeoutTimer_PWM_ALIGN) */

            #if (TimeoutTimer__ASYMMETRIC == TimeoutTimer_PWM_ALIGN)
                TimeoutTimer_TRIG_CONTROL2_REG = TimeoutTimer_PWM_MODE_ASYM;
            #endif  /* (TimeoutTimer__ASYMMETRIC == TimeoutTimer_PWM_ALIGN) */
        #endif  /* (TimeoutTimer__PWM_PR == TimeoutTimer_PWM_MODE) */

        /* Set other values from customizer */
        TimeoutTimer_WritePeriod(TimeoutTimer_PWM_PERIOD_VALUE );
        TimeoutTimer_WriteCompare(TimeoutTimer_PWM_COMPARE_VALUE);

        #if (1u == TimeoutTimer_PWM_COMPARE_SWAP)
            TimeoutTimer_SetCompareSwap(1u);
            TimeoutTimer_WriteCompareBuf(TimeoutTimer_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == TimeoutTimer_PWM_COMPARE_SWAP) */

        #if (1u == TimeoutTimer_PWM_PERIOD_SWAP)
            TimeoutTimer_SetPeriodSwap(1u);
            TimeoutTimer_WritePeriodBuf(TimeoutTimer_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == TimeoutTimer_PWM_PERIOD_SWAP) */
    #endif  /* (TimeoutTimer__PWM_SEL == TimeoutTimer_CONFIG) */
    
}


/*******************************************************************************
* Function Name: TimeoutTimer_Enable
********************************************************************************
*
* Summary:
*  Enables the TimeoutTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TimeoutTimer_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    TimeoutTimer_BLOCK_CONTROL_REG |= TimeoutTimer_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (TimeoutTimer__PWM_SEL == TimeoutTimer_CONFIG)
        #if (0u == TimeoutTimer_PWM_START_SIGNAL_PRESENT)
            TimeoutTimer_TriggerCommand(TimeoutTimer_MASK, TimeoutTimer_CMD_START);
        #endif /* (0u == TimeoutTimer_PWM_START_SIGNAL_PRESENT) */
    #endif /* (TimeoutTimer__PWM_SEL == TimeoutTimer_CONFIG) */

    #if (TimeoutTimer__TIMER == TimeoutTimer_CONFIG)
        #if (0u == TimeoutTimer_TC_START_SIGNAL_PRESENT)
            TimeoutTimer_TriggerCommand(TimeoutTimer_MASK, TimeoutTimer_CMD_START);
        #endif /* (0u == TimeoutTimer_TC_START_SIGNAL_PRESENT) */
    #endif /* (TimeoutTimer__TIMER == TimeoutTimer_CONFIG) */
    
    #if (TimeoutTimer__QUAD == TimeoutTimer_CONFIG)
        #if (0u != TimeoutTimer_QUAD_AUTO_START)
            TimeoutTimer_TriggerCommand(TimeoutTimer_MASK, TimeoutTimer_CMD_RELOAD);
        #endif /* (0u != TimeoutTimer_QUAD_AUTO_START) */
    #endif  /* (TimeoutTimer__QUAD == TimeoutTimer_CONFIG) */
}


/*******************************************************************************
* Function Name: TimeoutTimer_Start
********************************************************************************
*
* Summary:
*  Initializes the TimeoutTimer with default customizer
*  values when called the first time and enables the TimeoutTimer.
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
*  TimeoutTimer_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time TimeoutTimer_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the TimeoutTimer_Start() routine.
*
*******************************************************************************/
void TimeoutTimer_Start(void)
{
    if (0u == TimeoutTimer_initVar)
    {
        TimeoutTimer_Init();
        TimeoutTimer_initVar = 1u;
    }

    TimeoutTimer_Enable();
}


/*******************************************************************************
* Function Name: TimeoutTimer_Stop
********************************************************************************
*
* Summary:
*  Disables the TimeoutTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TimeoutTimer_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimeoutTimer_BLOCK_CONTROL_REG &= (uint32)~TimeoutTimer_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimeoutTimer_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the TimeoutTimer. This function is used when
*  configured as a generic TimeoutTimer and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the TimeoutTimer to operate in
*   Values:
*   - TimeoutTimer_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - TimeoutTimer_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - TimeoutTimer_MODE_QUAD - Quadrature decoder
*         - TimeoutTimer_MODE_PWM - PWM
*         - TimeoutTimer_MODE_PWM_DT - PWM with dead time
*         - TimeoutTimer_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void TimeoutTimer_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimeoutTimer_CONTROL_REG &= (uint32)~TimeoutTimer_MODE_MASK;
    TimeoutTimer_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimeoutTimer_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - TimeoutTimer_MODE_X1 - Counts on phi 1 rising
*         - TimeoutTimer_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - TimeoutTimer_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void TimeoutTimer_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimeoutTimer_CONTROL_REG &= (uint32)~TimeoutTimer_QUAD_MODE_MASK;
    TimeoutTimer_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimeoutTimer_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - TimeoutTimer_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - TimeoutTimer_PRESCALE_DIVBY2    - Divide by 2
*         - TimeoutTimer_PRESCALE_DIVBY4    - Divide by 4
*         - TimeoutTimer_PRESCALE_DIVBY8    - Divide by 8
*         - TimeoutTimer_PRESCALE_DIVBY16   - Divide by 16
*         - TimeoutTimer_PRESCALE_DIVBY32   - Divide by 32
*         - TimeoutTimer_PRESCALE_DIVBY64   - Divide by 64
*         - TimeoutTimer_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void TimeoutTimer_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimeoutTimer_CONTROL_REG &= (uint32)~TimeoutTimer_PRESCALER_MASK;
    TimeoutTimer_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimeoutTimer_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the TimeoutTimer runs
*  continuously or stops when terminal count is reached.  By default the
*  TimeoutTimer operates in the continuous mode.
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
void TimeoutTimer_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimeoutTimer_CONTROL_REG &= (uint32)~TimeoutTimer_ONESHOT_MASK;
    TimeoutTimer_CONTROL_REG |= ((uint32)((oneShotEnable & TimeoutTimer_1BIT_MASK) <<
                                                               TimeoutTimer_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimeoutTimer_SetPWMMode
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
void TimeoutTimer_SetPWMMode(uint32 modeMask)
{
    TimeoutTimer_TRIG_CONTROL2_REG = (modeMask & TimeoutTimer_6BIT_MASK);
}



/*******************************************************************************
* Function Name: TimeoutTimer_SetPWMSyncKill
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
void TimeoutTimer_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimeoutTimer_CONTROL_REG &= (uint32)~TimeoutTimer_PWM_SYNC_KILL_MASK;
    TimeoutTimer_CONTROL_REG |= ((uint32)((syncKillEnable & TimeoutTimer_1BIT_MASK)  <<
                                               TimeoutTimer_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimeoutTimer_SetPWMStopOnKill
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
void TimeoutTimer_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimeoutTimer_CONTROL_REG &= (uint32)~TimeoutTimer_PWM_STOP_KILL_MASK;
    TimeoutTimer_CONTROL_REG |= ((uint32)((stopOnKillEnable & TimeoutTimer_1BIT_MASK)  <<
                                                         TimeoutTimer_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimeoutTimer_SetPWMDeadTime
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
void TimeoutTimer_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimeoutTimer_CONTROL_REG &= (uint32)~TimeoutTimer_PRESCALER_MASK;
    TimeoutTimer_CONTROL_REG |= ((uint32)((deadTime & TimeoutTimer_8BIT_MASK) <<
                                                          TimeoutTimer_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimeoutTimer_SetPWMInvert
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
*         - TimeoutTimer_INVERT_LINE   - Inverts the line output
*         - TimeoutTimer_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void TimeoutTimer_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimeoutTimer_CONTROL_REG &= (uint32)~TimeoutTimer_INV_OUT_MASK;
    TimeoutTimer_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: TimeoutTimer_WriteCounter
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
void TimeoutTimer_WriteCounter(uint32 count)
{
    TimeoutTimer_COUNTER_REG = (count & TimeoutTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TimeoutTimer_ReadCounter
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
uint32 TimeoutTimer_ReadCounter(void)
{
    return (TimeoutTimer_COUNTER_REG & TimeoutTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TimeoutTimer_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - TimeoutTimer_COUNT_UP       - Counts up
*     - TimeoutTimer_COUNT_DOWN     - Counts down
*     - TimeoutTimer_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - TimeoutTimer_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void TimeoutTimer_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimeoutTimer_CONTROL_REG &= (uint32)~TimeoutTimer_UPDOWN_MASK;
    TimeoutTimer_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimeoutTimer_WritePeriod
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
void TimeoutTimer_WritePeriod(uint32 period)
{
    TimeoutTimer_PERIOD_REG = (period & TimeoutTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TimeoutTimer_ReadPeriod
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
uint32 TimeoutTimer_ReadPeriod(void)
{
    return (TimeoutTimer_PERIOD_REG & TimeoutTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TimeoutTimer_SetCompareSwap
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
void TimeoutTimer_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimeoutTimer_CONTROL_REG &= (uint32)~TimeoutTimer_RELOAD_CC_MASK;
    TimeoutTimer_CONTROL_REG |= (swapEnable & TimeoutTimer_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimeoutTimer_WritePeriodBuf
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
void TimeoutTimer_WritePeriodBuf(uint32 periodBuf)
{
    TimeoutTimer_PERIOD_BUF_REG = (periodBuf & TimeoutTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TimeoutTimer_ReadPeriodBuf
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
uint32 TimeoutTimer_ReadPeriodBuf(void)
{
    return (TimeoutTimer_PERIOD_BUF_REG & TimeoutTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TimeoutTimer_SetPeriodSwap
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
void TimeoutTimer_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimeoutTimer_CONTROL_REG &= (uint32)~TimeoutTimer_RELOAD_PERIOD_MASK;
    TimeoutTimer_CONTROL_REG |= ((uint32)((swapEnable & TimeoutTimer_1BIT_MASK) <<
                                                            TimeoutTimer_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimeoutTimer_WriteCompare
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
void TimeoutTimer_WriteCompare(uint32 compare)
{
    #if (TimeoutTimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (TimeoutTimer_CY_TCPWM_4000) */

    #if (TimeoutTimer_CY_TCPWM_4000)
        currentMode = ((TimeoutTimer_CONTROL_REG & TimeoutTimer_UPDOWN_MASK) >> TimeoutTimer_UPDOWN_SHIFT);

        if (((uint32)TimeoutTimer__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)TimeoutTimer__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (TimeoutTimer_CY_TCPWM_4000) */
    
    TimeoutTimer_COMP_CAP_REG = (compare & TimeoutTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TimeoutTimer_ReadCompare
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
uint32 TimeoutTimer_ReadCompare(void)
{
    #if (TimeoutTimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (TimeoutTimer_CY_TCPWM_4000) */

    #if (TimeoutTimer_CY_TCPWM_4000)
        currentMode = ((TimeoutTimer_CONTROL_REG & TimeoutTimer_UPDOWN_MASK) >> TimeoutTimer_UPDOWN_SHIFT);
        
        regVal = TimeoutTimer_COMP_CAP_REG;
        
        if (((uint32)TimeoutTimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)TimeoutTimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & TimeoutTimer_16BIT_MASK);
    #else
        return (TimeoutTimer_COMP_CAP_REG & TimeoutTimer_16BIT_MASK);
    #endif /* (TimeoutTimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: TimeoutTimer_WriteCompareBuf
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
void TimeoutTimer_WriteCompareBuf(uint32 compareBuf)
{
    #if (TimeoutTimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (TimeoutTimer_CY_TCPWM_4000) */

    #if (TimeoutTimer_CY_TCPWM_4000)
        currentMode = ((TimeoutTimer_CONTROL_REG & TimeoutTimer_UPDOWN_MASK) >> TimeoutTimer_UPDOWN_SHIFT);

        if (((uint32)TimeoutTimer__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)TimeoutTimer__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (TimeoutTimer_CY_TCPWM_4000) */
    
    TimeoutTimer_COMP_CAP_BUF_REG = (compareBuf & TimeoutTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TimeoutTimer_ReadCompareBuf
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
uint32 TimeoutTimer_ReadCompareBuf(void)
{
    #if (TimeoutTimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (TimeoutTimer_CY_TCPWM_4000) */

    #if (TimeoutTimer_CY_TCPWM_4000)
        currentMode = ((TimeoutTimer_CONTROL_REG & TimeoutTimer_UPDOWN_MASK) >> TimeoutTimer_UPDOWN_SHIFT);

        regVal = TimeoutTimer_COMP_CAP_BUF_REG;
        
        if (((uint32)TimeoutTimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)TimeoutTimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & TimeoutTimer_16BIT_MASK);
    #else
        return (TimeoutTimer_COMP_CAP_BUF_REG & TimeoutTimer_16BIT_MASK);
    #endif /* (TimeoutTimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: TimeoutTimer_ReadCapture
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
uint32 TimeoutTimer_ReadCapture(void)
{
    return (TimeoutTimer_COMP_CAP_REG & TimeoutTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TimeoutTimer_ReadCaptureBuf
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
uint32 TimeoutTimer_ReadCaptureBuf(void)
{
    return (TimeoutTimer_COMP_CAP_BUF_REG & TimeoutTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TimeoutTimer_SetCaptureMode
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
*     - TimeoutTimer_TRIG_LEVEL     - Level
*     - TimeoutTimer_TRIG_RISING    - Rising edge
*     - TimeoutTimer_TRIG_FALLING   - Falling edge
*     - TimeoutTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TimeoutTimer_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimeoutTimer_TRIG_CONTROL1_REG &= (uint32)~TimeoutTimer_CAPTURE_MASK;
    TimeoutTimer_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimeoutTimer_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TimeoutTimer_TRIG_LEVEL     - Level
*     - TimeoutTimer_TRIG_RISING    - Rising edge
*     - TimeoutTimer_TRIG_FALLING   - Falling edge
*     - TimeoutTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TimeoutTimer_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimeoutTimer_TRIG_CONTROL1_REG &= (uint32)~TimeoutTimer_RELOAD_MASK;
    TimeoutTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TimeoutTimer_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimeoutTimer_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TimeoutTimer_TRIG_LEVEL     - Level
*     - TimeoutTimer_TRIG_RISING    - Rising edge
*     - TimeoutTimer_TRIG_FALLING   - Falling edge
*     - TimeoutTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TimeoutTimer_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimeoutTimer_TRIG_CONTROL1_REG &= (uint32)~TimeoutTimer_START_MASK;
    TimeoutTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TimeoutTimer_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimeoutTimer_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TimeoutTimer_TRIG_LEVEL     - Level
*     - TimeoutTimer_TRIG_RISING    - Rising edge
*     - TimeoutTimer_TRIG_FALLING   - Falling edge
*     - TimeoutTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TimeoutTimer_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimeoutTimer_TRIG_CONTROL1_REG &= (uint32)~TimeoutTimer_STOP_MASK;
    TimeoutTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TimeoutTimer_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimeoutTimer_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TimeoutTimer_TRIG_LEVEL     - Level
*     - TimeoutTimer_TRIG_RISING    - Rising edge
*     - TimeoutTimer_TRIG_FALLING   - Falling edge
*     - TimeoutTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TimeoutTimer_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimeoutTimer_TRIG_CONTROL1_REG &= (uint32)~TimeoutTimer_COUNT_MASK;
    TimeoutTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TimeoutTimer_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimeoutTimer_TriggerCommand
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
*     - TimeoutTimer_CMD_CAPTURE    - Trigger Capture/Switch command
*     - TimeoutTimer_CMD_RELOAD     - Trigger Reload/Index command
*     - TimeoutTimer_CMD_STOP       - Trigger Stop/Kill command
*     - TimeoutTimer_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void TimeoutTimer_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimeoutTimer_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimeoutTimer_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the TimeoutTimer.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - TimeoutTimer_STATUS_DOWN    - Set if counting down
*     - TimeoutTimer_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 TimeoutTimer_ReadStatus(void)
{
    return ((TimeoutTimer_STATUS_REG >> TimeoutTimer_RUNNING_STATUS_SHIFT) |
            (TimeoutTimer_STATUS_REG & TimeoutTimer_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: TimeoutTimer_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - TimeoutTimer_INTR_MASK_TC       - Terminal count mask
*     - TimeoutTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void TimeoutTimer_SetInterruptMode(uint32 interruptMask)
{
    TimeoutTimer_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: TimeoutTimer_GetInterruptSourceMasked
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
*     - TimeoutTimer_INTR_MASK_TC       - Terminal count mask
*     - TimeoutTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 TimeoutTimer_GetInterruptSourceMasked(void)
{
    return (TimeoutTimer_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: TimeoutTimer_GetInterruptSource
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
*     - TimeoutTimer_INTR_MASK_TC       - Terminal count mask
*     - TimeoutTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 TimeoutTimer_GetInterruptSource(void)
{
    return (TimeoutTimer_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: TimeoutTimer_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - TimeoutTimer_INTR_MASK_TC       - Terminal count mask
*     - TimeoutTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void TimeoutTimer_ClearInterrupt(uint32 interruptMask)
{
    TimeoutTimer_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: TimeoutTimer_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - TimeoutTimer_INTR_MASK_TC       - Terminal count mask
*     - TimeoutTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void TimeoutTimer_SetInterrupt(uint32 interruptMask)
{
    TimeoutTimer_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
