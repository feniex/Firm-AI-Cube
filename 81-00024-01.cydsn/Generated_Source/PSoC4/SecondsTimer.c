/*******************************************************************************
* File Name: SecondsTimer.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the SecondsTimer
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

#include "SecondsTimer.h"

uint8 SecondsTimer_initVar = 0u;


/*******************************************************************************
* Function Name: SecondsTimer_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default SecondsTimer configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SecondsTimer_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (SecondsTimer__QUAD == SecondsTimer_CONFIG)
        SecondsTimer_CONTROL_REG = SecondsTimer_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        SecondsTimer_TRIG_CONTROL1_REG  = SecondsTimer_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        SecondsTimer_SetInterruptMode(SecondsTimer_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        SecondsTimer_SetCounterMode(SecondsTimer_COUNT_DOWN);
        SecondsTimer_WritePeriod(SecondsTimer_QUAD_PERIOD_INIT_VALUE);
        SecondsTimer_WriteCounter(SecondsTimer_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (SecondsTimer__QUAD == SecondsTimer_CONFIG) */

    #if (SecondsTimer__TIMER == SecondsTimer_CONFIG)
        SecondsTimer_CONTROL_REG = SecondsTimer_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        SecondsTimer_TRIG_CONTROL1_REG  = SecondsTimer_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        SecondsTimer_SetInterruptMode(SecondsTimer_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        SecondsTimer_WritePeriod(SecondsTimer_TC_PERIOD_VALUE );

        #if (SecondsTimer__COMPARE == SecondsTimer_TC_COMP_CAP_MODE)
            SecondsTimer_WriteCompare(SecondsTimer_TC_COMPARE_VALUE);

            #if (1u == SecondsTimer_TC_COMPARE_SWAP)
                SecondsTimer_SetCompareSwap(1u);
                SecondsTimer_WriteCompareBuf(SecondsTimer_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == SecondsTimer_TC_COMPARE_SWAP) */
        #endif  /* (SecondsTimer__COMPARE == SecondsTimer_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (SecondsTimer_CY_TCPWM_V2 && SecondsTimer_TIMER_UPDOWN_CNT_USED && !SecondsTimer_CY_TCPWM_4000)
            SecondsTimer_WriteCounter(1u);
        #elif(SecondsTimer__COUNT_DOWN == SecondsTimer_TC_COUNTER_MODE)
            SecondsTimer_WriteCounter(SecondsTimer_TC_PERIOD_VALUE);
        #else
            SecondsTimer_WriteCounter(0u);
        #endif /* (SecondsTimer_CY_TCPWM_V2 && SecondsTimer_TIMER_UPDOWN_CNT_USED && !SecondsTimer_CY_TCPWM_4000) */
    #endif  /* (SecondsTimer__TIMER == SecondsTimer_CONFIG) */

    #if (SecondsTimer__PWM_SEL == SecondsTimer_CONFIG)
        SecondsTimer_CONTROL_REG = SecondsTimer_CTRL_PWM_BASE_CONFIG;

        #if (SecondsTimer__PWM_PR == SecondsTimer_PWM_MODE)
            SecondsTimer_CONTROL_REG |= SecondsTimer_CTRL_PWM_RUN_MODE;
            SecondsTimer_WriteCounter(SecondsTimer_PWM_PR_INIT_VALUE);
        #else
            SecondsTimer_CONTROL_REG |= SecondsTimer_CTRL_PWM_ALIGN | SecondsTimer_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (SecondsTimer_CY_TCPWM_V2 && SecondsTimer_PWM_UPDOWN_CNT_USED && !SecondsTimer_CY_TCPWM_4000)
                SecondsTimer_WriteCounter(1u);
            #elif (SecondsTimer__RIGHT == SecondsTimer_PWM_ALIGN)
                SecondsTimer_WriteCounter(SecondsTimer_PWM_PERIOD_VALUE);
            #else 
                SecondsTimer_WriteCounter(0u);
            #endif  /* (SecondsTimer_CY_TCPWM_V2 && SecondsTimer_PWM_UPDOWN_CNT_USED && !SecondsTimer_CY_TCPWM_4000) */
        #endif  /* (SecondsTimer__PWM_PR == SecondsTimer_PWM_MODE) */

        #if (SecondsTimer__PWM_DT == SecondsTimer_PWM_MODE)
            SecondsTimer_CONTROL_REG |= SecondsTimer_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (SecondsTimer__PWM_DT == SecondsTimer_PWM_MODE) */

        #if (SecondsTimer__PWM == SecondsTimer_PWM_MODE)
            SecondsTimer_CONTROL_REG |= SecondsTimer_CTRL_PWM_PRESCALER;
        #endif  /* (SecondsTimer__PWM == SecondsTimer_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        SecondsTimer_TRIG_CONTROL1_REG  = SecondsTimer_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        SecondsTimer_SetInterruptMode(SecondsTimer_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (SecondsTimer__PWM_PR == SecondsTimer_PWM_MODE)
            SecondsTimer_TRIG_CONTROL2_REG =
                    (SecondsTimer_CC_MATCH_NO_CHANGE    |
                    SecondsTimer_OVERLOW_NO_CHANGE      |
                    SecondsTimer_UNDERFLOW_NO_CHANGE);
        #else
            #if (SecondsTimer__LEFT == SecondsTimer_PWM_ALIGN)
                SecondsTimer_TRIG_CONTROL2_REG = SecondsTimer_PWM_MODE_LEFT;
            #endif  /* ( SecondsTimer_PWM_LEFT == SecondsTimer_PWM_ALIGN) */

            #if (SecondsTimer__RIGHT == SecondsTimer_PWM_ALIGN)
                SecondsTimer_TRIG_CONTROL2_REG = SecondsTimer_PWM_MODE_RIGHT;
            #endif  /* ( SecondsTimer_PWM_RIGHT == SecondsTimer_PWM_ALIGN) */

            #if (SecondsTimer__CENTER == SecondsTimer_PWM_ALIGN)
                SecondsTimer_TRIG_CONTROL2_REG = SecondsTimer_PWM_MODE_CENTER;
            #endif  /* ( SecondsTimer_PWM_CENTER == SecondsTimer_PWM_ALIGN) */

            #if (SecondsTimer__ASYMMETRIC == SecondsTimer_PWM_ALIGN)
                SecondsTimer_TRIG_CONTROL2_REG = SecondsTimer_PWM_MODE_ASYM;
            #endif  /* (SecondsTimer__ASYMMETRIC == SecondsTimer_PWM_ALIGN) */
        #endif  /* (SecondsTimer__PWM_PR == SecondsTimer_PWM_MODE) */

        /* Set other values from customizer */
        SecondsTimer_WritePeriod(SecondsTimer_PWM_PERIOD_VALUE );
        SecondsTimer_WriteCompare(SecondsTimer_PWM_COMPARE_VALUE);

        #if (1u == SecondsTimer_PWM_COMPARE_SWAP)
            SecondsTimer_SetCompareSwap(1u);
            SecondsTimer_WriteCompareBuf(SecondsTimer_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == SecondsTimer_PWM_COMPARE_SWAP) */

        #if (1u == SecondsTimer_PWM_PERIOD_SWAP)
            SecondsTimer_SetPeriodSwap(1u);
            SecondsTimer_WritePeriodBuf(SecondsTimer_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == SecondsTimer_PWM_PERIOD_SWAP) */
    #endif  /* (SecondsTimer__PWM_SEL == SecondsTimer_CONFIG) */
    
}


/*******************************************************************************
* Function Name: SecondsTimer_Enable
********************************************************************************
*
* Summary:
*  Enables the SecondsTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SecondsTimer_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    SecondsTimer_BLOCK_CONTROL_REG |= SecondsTimer_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (SecondsTimer__PWM_SEL == SecondsTimer_CONFIG)
        #if (0u == SecondsTimer_PWM_START_SIGNAL_PRESENT)
            SecondsTimer_TriggerCommand(SecondsTimer_MASK, SecondsTimer_CMD_START);
        #endif /* (0u == SecondsTimer_PWM_START_SIGNAL_PRESENT) */
    #endif /* (SecondsTimer__PWM_SEL == SecondsTimer_CONFIG) */

    #if (SecondsTimer__TIMER == SecondsTimer_CONFIG)
        #if (0u == SecondsTimer_TC_START_SIGNAL_PRESENT)
            SecondsTimer_TriggerCommand(SecondsTimer_MASK, SecondsTimer_CMD_START);
        #endif /* (0u == SecondsTimer_TC_START_SIGNAL_PRESENT) */
    #endif /* (SecondsTimer__TIMER == SecondsTimer_CONFIG) */
    
    #if (SecondsTimer__QUAD == SecondsTimer_CONFIG)
        #if (0u != SecondsTimer_QUAD_AUTO_START)
            SecondsTimer_TriggerCommand(SecondsTimer_MASK, SecondsTimer_CMD_RELOAD);
        #endif /* (0u != SecondsTimer_QUAD_AUTO_START) */
    #endif  /* (SecondsTimer__QUAD == SecondsTimer_CONFIG) */
}


/*******************************************************************************
* Function Name: SecondsTimer_Start
********************************************************************************
*
* Summary:
*  Initializes the SecondsTimer with default customizer
*  values when called the first time and enables the SecondsTimer.
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
*  SecondsTimer_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time SecondsTimer_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the SecondsTimer_Start() routine.
*
*******************************************************************************/
void SecondsTimer_Start(void)
{
    if (0u == SecondsTimer_initVar)
    {
        SecondsTimer_Init();
        SecondsTimer_initVar = 1u;
    }

    SecondsTimer_Enable();
}


/*******************************************************************************
* Function Name: SecondsTimer_Stop
********************************************************************************
*
* Summary:
*  Disables the SecondsTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SecondsTimer_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SecondsTimer_BLOCK_CONTROL_REG &= (uint32)~SecondsTimer_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SecondsTimer_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the SecondsTimer. This function is used when
*  configured as a generic SecondsTimer and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the SecondsTimer to operate in
*   Values:
*   - SecondsTimer_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - SecondsTimer_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - SecondsTimer_MODE_QUAD - Quadrature decoder
*         - SecondsTimer_MODE_PWM - PWM
*         - SecondsTimer_MODE_PWM_DT - PWM with dead time
*         - SecondsTimer_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void SecondsTimer_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SecondsTimer_CONTROL_REG &= (uint32)~SecondsTimer_MODE_MASK;
    SecondsTimer_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SecondsTimer_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - SecondsTimer_MODE_X1 - Counts on phi 1 rising
*         - SecondsTimer_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - SecondsTimer_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void SecondsTimer_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SecondsTimer_CONTROL_REG &= (uint32)~SecondsTimer_QUAD_MODE_MASK;
    SecondsTimer_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SecondsTimer_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - SecondsTimer_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - SecondsTimer_PRESCALE_DIVBY2    - Divide by 2
*         - SecondsTimer_PRESCALE_DIVBY4    - Divide by 4
*         - SecondsTimer_PRESCALE_DIVBY8    - Divide by 8
*         - SecondsTimer_PRESCALE_DIVBY16   - Divide by 16
*         - SecondsTimer_PRESCALE_DIVBY32   - Divide by 32
*         - SecondsTimer_PRESCALE_DIVBY64   - Divide by 64
*         - SecondsTimer_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void SecondsTimer_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SecondsTimer_CONTROL_REG &= (uint32)~SecondsTimer_PRESCALER_MASK;
    SecondsTimer_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SecondsTimer_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the SecondsTimer runs
*  continuously or stops when terminal count is reached.  By default the
*  SecondsTimer operates in the continuous mode.
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
void SecondsTimer_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SecondsTimer_CONTROL_REG &= (uint32)~SecondsTimer_ONESHOT_MASK;
    SecondsTimer_CONTROL_REG |= ((uint32)((oneShotEnable & SecondsTimer_1BIT_MASK) <<
                                                               SecondsTimer_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SecondsTimer_SetPWMMode
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
void SecondsTimer_SetPWMMode(uint32 modeMask)
{
    SecondsTimer_TRIG_CONTROL2_REG = (modeMask & SecondsTimer_6BIT_MASK);
}



/*******************************************************************************
* Function Name: SecondsTimer_SetPWMSyncKill
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
void SecondsTimer_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SecondsTimer_CONTROL_REG &= (uint32)~SecondsTimer_PWM_SYNC_KILL_MASK;
    SecondsTimer_CONTROL_REG |= ((uint32)((syncKillEnable & SecondsTimer_1BIT_MASK)  <<
                                               SecondsTimer_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SecondsTimer_SetPWMStopOnKill
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
void SecondsTimer_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SecondsTimer_CONTROL_REG &= (uint32)~SecondsTimer_PWM_STOP_KILL_MASK;
    SecondsTimer_CONTROL_REG |= ((uint32)((stopOnKillEnable & SecondsTimer_1BIT_MASK)  <<
                                                         SecondsTimer_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SecondsTimer_SetPWMDeadTime
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
void SecondsTimer_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SecondsTimer_CONTROL_REG &= (uint32)~SecondsTimer_PRESCALER_MASK;
    SecondsTimer_CONTROL_REG |= ((uint32)((deadTime & SecondsTimer_8BIT_MASK) <<
                                                          SecondsTimer_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SecondsTimer_SetPWMInvert
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
*         - SecondsTimer_INVERT_LINE   - Inverts the line output
*         - SecondsTimer_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void SecondsTimer_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SecondsTimer_CONTROL_REG &= (uint32)~SecondsTimer_INV_OUT_MASK;
    SecondsTimer_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: SecondsTimer_WriteCounter
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
void SecondsTimer_WriteCounter(uint32 count)
{
    SecondsTimer_COUNTER_REG = (count & SecondsTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SecondsTimer_ReadCounter
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
uint32 SecondsTimer_ReadCounter(void)
{
    return (SecondsTimer_COUNTER_REG & SecondsTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SecondsTimer_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - SecondsTimer_COUNT_UP       - Counts up
*     - SecondsTimer_COUNT_DOWN     - Counts down
*     - SecondsTimer_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - SecondsTimer_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void SecondsTimer_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SecondsTimer_CONTROL_REG &= (uint32)~SecondsTimer_UPDOWN_MASK;
    SecondsTimer_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SecondsTimer_WritePeriod
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
void SecondsTimer_WritePeriod(uint32 period)
{
    SecondsTimer_PERIOD_REG = (period & SecondsTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SecondsTimer_ReadPeriod
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
uint32 SecondsTimer_ReadPeriod(void)
{
    return (SecondsTimer_PERIOD_REG & SecondsTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SecondsTimer_SetCompareSwap
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
void SecondsTimer_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SecondsTimer_CONTROL_REG &= (uint32)~SecondsTimer_RELOAD_CC_MASK;
    SecondsTimer_CONTROL_REG |= (swapEnable & SecondsTimer_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SecondsTimer_WritePeriodBuf
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
void SecondsTimer_WritePeriodBuf(uint32 periodBuf)
{
    SecondsTimer_PERIOD_BUF_REG = (periodBuf & SecondsTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SecondsTimer_ReadPeriodBuf
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
uint32 SecondsTimer_ReadPeriodBuf(void)
{
    return (SecondsTimer_PERIOD_BUF_REG & SecondsTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SecondsTimer_SetPeriodSwap
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
void SecondsTimer_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SecondsTimer_CONTROL_REG &= (uint32)~SecondsTimer_RELOAD_PERIOD_MASK;
    SecondsTimer_CONTROL_REG |= ((uint32)((swapEnable & SecondsTimer_1BIT_MASK) <<
                                                            SecondsTimer_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SecondsTimer_WriteCompare
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
void SecondsTimer_WriteCompare(uint32 compare)
{
    #if (SecondsTimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (SecondsTimer_CY_TCPWM_4000) */

    #if (SecondsTimer_CY_TCPWM_4000)
        currentMode = ((SecondsTimer_CONTROL_REG & SecondsTimer_UPDOWN_MASK) >> SecondsTimer_UPDOWN_SHIFT);

        if (((uint32)SecondsTimer__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)SecondsTimer__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (SecondsTimer_CY_TCPWM_4000) */
    
    SecondsTimer_COMP_CAP_REG = (compare & SecondsTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SecondsTimer_ReadCompare
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
uint32 SecondsTimer_ReadCompare(void)
{
    #if (SecondsTimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (SecondsTimer_CY_TCPWM_4000) */

    #if (SecondsTimer_CY_TCPWM_4000)
        currentMode = ((SecondsTimer_CONTROL_REG & SecondsTimer_UPDOWN_MASK) >> SecondsTimer_UPDOWN_SHIFT);
        
        regVal = SecondsTimer_COMP_CAP_REG;
        
        if (((uint32)SecondsTimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)SecondsTimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & SecondsTimer_16BIT_MASK);
    #else
        return (SecondsTimer_COMP_CAP_REG & SecondsTimer_16BIT_MASK);
    #endif /* (SecondsTimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: SecondsTimer_WriteCompareBuf
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
void SecondsTimer_WriteCompareBuf(uint32 compareBuf)
{
    #if (SecondsTimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (SecondsTimer_CY_TCPWM_4000) */

    #if (SecondsTimer_CY_TCPWM_4000)
        currentMode = ((SecondsTimer_CONTROL_REG & SecondsTimer_UPDOWN_MASK) >> SecondsTimer_UPDOWN_SHIFT);

        if (((uint32)SecondsTimer__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)SecondsTimer__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (SecondsTimer_CY_TCPWM_4000) */
    
    SecondsTimer_COMP_CAP_BUF_REG = (compareBuf & SecondsTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SecondsTimer_ReadCompareBuf
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
uint32 SecondsTimer_ReadCompareBuf(void)
{
    #if (SecondsTimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (SecondsTimer_CY_TCPWM_4000) */

    #if (SecondsTimer_CY_TCPWM_4000)
        currentMode = ((SecondsTimer_CONTROL_REG & SecondsTimer_UPDOWN_MASK) >> SecondsTimer_UPDOWN_SHIFT);

        regVal = SecondsTimer_COMP_CAP_BUF_REG;
        
        if (((uint32)SecondsTimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)SecondsTimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & SecondsTimer_16BIT_MASK);
    #else
        return (SecondsTimer_COMP_CAP_BUF_REG & SecondsTimer_16BIT_MASK);
    #endif /* (SecondsTimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: SecondsTimer_ReadCapture
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
uint32 SecondsTimer_ReadCapture(void)
{
    return (SecondsTimer_COMP_CAP_REG & SecondsTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SecondsTimer_ReadCaptureBuf
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
uint32 SecondsTimer_ReadCaptureBuf(void)
{
    return (SecondsTimer_COMP_CAP_BUF_REG & SecondsTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SecondsTimer_SetCaptureMode
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
*     - SecondsTimer_TRIG_LEVEL     - Level
*     - SecondsTimer_TRIG_RISING    - Rising edge
*     - SecondsTimer_TRIG_FALLING   - Falling edge
*     - SecondsTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SecondsTimer_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SecondsTimer_TRIG_CONTROL1_REG &= (uint32)~SecondsTimer_CAPTURE_MASK;
    SecondsTimer_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SecondsTimer_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SecondsTimer_TRIG_LEVEL     - Level
*     - SecondsTimer_TRIG_RISING    - Rising edge
*     - SecondsTimer_TRIG_FALLING   - Falling edge
*     - SecondsTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SecondsTimer_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SecondsTimer_TRIG_CONTROL1_REG &= (uint32)~SecondsTimer_RELOAD_MASK;
    SecondsTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SecondsTimer_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SecondsTimer_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SecondsTimer_TRIG_LEVEL     - Level
*     - SecondsTimer_TRIG_RISING    - Rising edge
*     - SecondsTimer_TRIG_FALLING   - Falling edge
*     - SecondsTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SecondsTimer_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SecondsTimer_TRIG_CONTROL1_REG &= (uint32)~SecondsTimer_START_MASK;
    SecondsTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SecondsTimer_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SecondsTimer_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SecondsTimer_TRIG_LEVEL     - Level
*     - SecondsTimer_TRIG_RISING    - Rising edge
*     - SecondsTimer_TRIG_FALLING   - Falling edge
*     - SecondsTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SecondsTimer_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SecondsTimer_TRIG_CONTROL1_REG &= (uint32)~SecondsTimer_STOP_MASK;
    SecondsTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SecondsTimer_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SecondsTimer_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SecondsTimer_TRIG_LEVEL     - Level
*     - SecondsTimer_TRIG_RISING    - Rising edge
*     - SecondsTimer_TRIG_FALLING   - Falling edge
*     - SecondsTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SecondsTimer_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SecondsTimer_TRIG_CONTROL1_REG &= (uint32)~SecondsTimer_COUNT_MASK;
    SecondsTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SecondsTimer_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SecondsTimer_TriggerCommand
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
*     - SecondsTimer_CMD_CAPTURE    - Trigger Capture/Switch command
*     - SecondsTimer_CMD_RELOAD     - Trigger Reload/Index command
*     - SecondsTimer_CMD_STOP       - Trigger Stop/Kill command
*     - SecondsTimer_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void SecondsTimer_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SecondsTimer_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SecondsTimer_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the SecondsTimer.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - SecondsTimer_STATUS_DOWN    - Set if counting down
*     - SecondsTimer_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 SecondsTimer_ReadStatus(void)
{
    return ((SecondsTimer_STATUS_REG >> SecondsTimer_RUNNING_STATUS_SHIFT) |
            (SecondsTimer_STATUS_REG & SecondsTimer_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: SecondsTimer_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - SecondsTimer_INTR_MASK_TC       - Terminal count mask
*     - SecondsTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void SecondsTimer_SetInterruptMode(uint32 interruptMask)
{
    SecondsTimer_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: SecondsTimer_GetInterruptSourceMasked
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
*     - SecondsTimer_INTR_MASK_TC       - Terminal count mask
*     - SecondsTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 SecondsTimer_GetInterruptSourceMasked(void)
{
    return (SecondsTimer_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: SecondsTimer_GetInterruptSource
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
*     - SecondsTimer_INTR_MASK_TC       - Terminal count mask
*     - SecondsTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 SecondsTimer_GetInterruptSource(void)
{
    return (SecondsTimer_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: SecondsTimer_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - SecondsTimer_INTR_MASK_TC       - Terminal count mask
*     - SecondsTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void SecondsTimer_ClearInterrupt(uint32 interruptMask)
{
    SecondsTimer_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: SecondsTimer_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - SecondsTimer_INTR_MASK_TC       - Terminal count mask
*     - SecondsTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void SecondsTimer_SetInterrupt(uint32 interruptMask)
{
    SecondsTimer_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
