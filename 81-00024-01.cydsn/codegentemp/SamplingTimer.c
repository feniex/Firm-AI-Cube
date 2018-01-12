/*******************************************************************************
* File Name: SamplingTimer.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the SamplingTimer
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

#include "SamplingTimer.h"

uint8 SamplingTimer_initVar = 0u;


/*******************************************************************************
* Function Name: SamplingTimer_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default SamplingTimer configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SamplingTimer_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (SamplingTimer__QUAD == SamplingTimer_CONFIG)
        SamplingTimer_CONTROL_REG = SamplingTimer_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        SamplingTimer_TRIG_CONTROL1_REG  = SamplingTimer_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        SamplingTimer_SetInterruptMode(SamplingTimer_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        SamplingTimer_SetCounterMode(SamplingTimer_COUNT_DOWN);
        SamplingTimer_WritePeriod(SamplingTimer_QUAD_PERIOD_INIT_VALUE);
        SamplingTimer_WriteCounter(SamplingTimer_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (SamplingTimer__QUAD == SamplingTimer_CONFIG) */

    #if (SamplingTimer__TIMER == SamplingTimer_CONFIG)
        SamplingTimer_CONTROL_REG = SamplingTimer_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        SamplingTimer_TRIG_CONTROL1_REG  = SamplingTimer_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        SamplingTimer_SetInterruptMode(SamplingTimer_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        SamplingTimer_WritePeriod(SamplingTimer_TC_PERIOD_VALUE );

        #if (SamplingTimer__COMPARE == SamplingTimer_TC_COMP_CAP_MODE)
            SamplingTimer_WriteCompare(SamplingTimer_TC_COMPARE_VALUE);

            #if (1u == SamplingTimer_TC_COMPARE_SWAP)
                SamplingTimer_SetCompareSwap(1u);
                SamplingTimer_WriteCompareBuf(SamplingTimer_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == SamplingTimer_TC_COMPARE_SWAP) */
        #endif  /* (SamplingTimer__COMPARE == SamplingTimer_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (SamplingTimer_CY_TCPWM_V2 && SamplingTimer_TIMER_UPDOWN_CNT_USED && !SamplingTimer_CY_TCPWM_4000)
            SamplingTimer_WriteCounter(1u);
        #elif(SamplingTimer__COUNT_DOWN == SamplingTimer_TC_COUNTER_MODE)
            SamplingTimer_WriteCounter(SamplingTimer_TC_PERIOD_VALUE);
        #else
            SamplingTimer_WriteCounter(0u);
        #endif /* (SamplingTimer_CY_TCPWM_V2 && SamplingTimer_TIMER_UPDOWN_CNT_USED && !SamplingTimer_CY_TCPWM_4000) */
    #endif  /* (SamplingTimer__TIMER == SamplingTimer_CONFIG) */

    #if (SamplingTimer__PWM_SEL == SamplingTimer_CONFIG)
        SamplingTimer_CONTROL_REG = SamplingTimer_CTRL_PWM_BASE_CONFIG;

        #if (SamplingTimer__PWM_PR == SamplingTimer_PWM_MODE)
            SamplingTimer_CONTROL_REG |= SamplingTimer_CTRL_PWM_RUN_MODE;
            SamplingTimer_WriteCounter(SamplingTimer_PWM_PR_INIT_VALUE);
        #else
            SamplingTimer_CONTROL_REG |= SamplingTimer_CTRL_PWM_ALIGN | SamplingTimer_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (SamplingTimer_CY_TCPWM_V2 && SamplingTimer_PWM_UPDOWN_CNT_USED && !SamplingTimer_CY_TCPWM_4000)
                SamplingTimer_WriteCounter(1u);
            #elif (SamplingTimer__RIGHT == SamplingTimer_PWM_ALIGN)
                SamplingTimer_WriteCounter(SamplingTimer_PWM_PERIOD_VALUE);
            #else 
                SamplingTimer_WriteCounter(0u);
            #endif  /* (SamplingTimer_CY_TCPWM_V2 && SamplingTimer_PWM_UPDOWN_CNT_USED && !SamplingTimer_CY_TCPWM_4000) */
        #endif  /* (SamplingTimer__PWM_PR == SamplingTimer_PWM_MODE) */

        #if (SamplingTimer__PWM_DT == SamplingTimer_PWM_MODE)
            SamplingTimer_CONTROL_REG |= SamplingTimer_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (SamplingTimer__PWM_DT == SamplingTimer_PWM_MODE) */

        #if (SamplingTimer__PWM == SamplingTimer_PWM_MODE)
            SamplingTimer_CONTROL_REG |= SamplingTimer_CTRL_PWM_PRESCALER;
        #endif  /* (SamplingTimer__PWM == SamplingTimer_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        SamplingTimer_TRIG_CONTROL1_REG  = SamplingTimer_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        SamplingTimer_SetInterruptMode(SamplingTimer_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (SamplingTimer__PWM_PR == SamplingTimer_PWM_MODE)
            SamplingTimer_TRIG_CONTROL2_REG =
                    (SamplingTimer_CC_MATCH_NO_CHANGE    |
                    SamplingTimer_OVERLOW_NO_CHANGE      |
                    SamplingTimer_UNDERFLOW_NO_CHANGE);
        #else
            #if (SamplingTimer__LEFT == SamplingTimer_PWM_ALIGN)
                SamplingTimer_TRIG_CONTROL2_REG = SamplingTimer_PWM_MODE_LEFT;
            #endif  /* ( SamplingTimer_PWM_LEFT == SamplingTimer_PWM_ALIGN) */

            #if (SamplingTimer__RIGHT == SamplingTimer_PWM_ALIGN)
                SamplingTimer_TRIG_CONTROL2_REG = SamplingTimer_PWM_MODE_RIGHT;
            #endif  /* ( SamplingTimer_PWM_RIGHT == SamplingTimer_PWM_ALIGN) */

            #if (SamplingTimer__CENTER == SamplingTimer_PWM_ALIGN)
                SamplingTimer_TRIG_CONTROL2_REG = SamplingTimer_PWM_MODE_CENTER;
            #endif  /* ( SamplingTimer_PWM_CENTER == SamplingTimer_PWM_ALIGN) */

            #if (SamplingTimer__ASYMMETRIC == SamplingTimer_PWM_ALIGN)
                SamplingTimer_TRIG_CONTROL2_REG = SamplingTimer_PWM_MODE_ASYM;
            #endif  /* (SamplingTimer__ASYMMETRIC == SamplingTimer_PWM_ALIGN) */
        #endif  /* (SamplingTimer__PWM_PR == SamplingTimer_PWM_MODE) */

        /* Set other values from customizer */
        SamplingTimer_WritePeriod(SamplingTimer_PWM_PERIOD_VALUE );
        SamplingTimer_WriteCompare(SamplingTimer_PWM_COMPARE_VALUE);

        #if (1u == SamplingTimer_PWM_COMPARE_SWAP)
            SamplingTimer_SetCompareSwap(1u);
            SamplingTimer_WriteCompareBuf(SamplingTimer_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == SamplingTimer_PWM_COMPARE_SWAP) */

        #if (1u == SamplingTimer_PWM_PERIOD_SWAP)
            SamplingTimer_SetPeriodSwap(1u);
            SamplingTimer_WritePeriodBuf(SamplingTimer_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == SamplingTimer_PWM_PERIOD_SWAP) */
    #endif  /* (SamplingTimer__PWM_SEL == SamplingTimer_CONFIG) */
    
}


/*******************************************************************************
* Function Name: SamplingTimer_Enable
********************************************************************************
*
* Summary:
*  Enables the SamplingTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SamplingTimer_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    SamplingTimer_BLOCK_CONTROL_REG |= SamplingTimer_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (SamplingTimer__PWM_SEL == SamplingTimer_CONFIG)
        #if (0u == SamplingTimer_PWM_START_SIGNAL_PRESENT)
            SamplingTimer_TriggerCommand(SamplingTimer_MASK, SamplingTimer_CMD_START);
        #endif /* (0u == SamplingTimer_PWM_START_SIGNAL_PRESENT) */
    #endif /* (SamplingTimer__PWM_SEL == SamplingTimer_CONFIG) */

    #if (SamplingTimer__TIMER == SamplingTimer_CONFIG)
        #if (0u == SamplingTimer_TC_START_SIGNAL_PRESENT)
            SamplingTimer_TriggerCommand(SamplingTimer_MASK, SamplingTimer_CMD_START);
        #endif /* (0u == SamplingTimer_TC_START_SIGNAL_PRESENT) */
    #endif /* (SamplingTimer__TIMER == SamplingTimer_CONFIG) */
    
    #if (SamplingTimer__QUAD == SamplingTimer_CONFIG)
        #if (0u != SamplingTimer_QUAD_AUTO_START)
            SamplingTimer_TriggerCommand(SamplingTimer_MASK, SamplingTimer_CMD_RELOAD);
        #endif /* (0u != SamplingTimer_QUAD_AUTO_START) */
    #endif  /* (SamplingTimer__QUAD == SamplingTimer_CONFIG) */
}


/*******************************************************************************
* Function Name: SamplingTimer_Start
********************************************************************************
*
* Summary:
*  Initializes the SamplingTimer with default customizer
*  values when called the first time and enables the SamplingTimer.
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
*  SamplingTimer_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time SamplingTimer_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the SamplingTimer_Start() routine.
*
*******************************************************************************/
void SamplingTimer_Start(void)
{
    if (0u == SamplingTimer_initVar)
    {
        SamplingTimer_Init();
        SamplingTimer_initVar = 1u;
    }

    SamplingTimer_Enable();
}


/*******************************************************************************
* Function Name: SamplingTimer_Stop
********************************************************************************
*
* Summary:
*  Disables the SamplingTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SamplingTimer_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SamplingTimer_BLOCK_CONTROL_REG &= (uint32)~SamplingTimer_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SamplingTimer_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the SamplingTimer. This function is used when
*  configured as a generic SamplingTimer and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the SamplingTimer to operate in
*   Values:
*   - SamplingTimer_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - SamplingTimer_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - SamplingTimer_MODE_QUAD - Quadrature decoder
*         - SamplingTimer_MODE_PWM - PWM
*         - SamplingTimer_MODE_PWM_DT - PWM with dead time
*         - SamplingTimer_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void SamplingTimer_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SamplingTimer_CONTROL_REG &= (uint32)~SamplingTimer_MODE_MASK;
    SamplingTimer_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SamplingTimer_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - SamplingTimer_MODE_X1 - Counts on phi 1 rising
*         - SamplingTimer_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - SamplingTimer_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void SamplingTimer_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SamplingTimer_CONTROL_REG &= (uint32)~SamplingTimer_QUAD_MODE_MASK;
    SamplingTimer_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SamplingTimer_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - SamplingTimer_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - SamplingTimer_PRESCALE_DIVBY2    - Divide by 2
*         - SamplingTimer_PRESCALE_DIVBY4    - Divide by 4
*         - SamplingTimer_PRESCALE_DIVBY8    - Divide by 8
*         - SamplingTimer_PRESCALE_DIVBY16   - Divide by 16
*         - SamplingTimer_PRESCALE_DIVBY32   - Divide by 32
*         - SamplingTimer_PRESCALE_DIVBY64   - Divide by 64
*         - SamplingTimer_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void SamplingTimer_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SamplingTimer_CONTROL_REG &= (uint32)~SamplingTimer_PRESCALER_MASK;
    SamplingTimer_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SamplingTimer_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the SamplingTimer runs
*  continuously or stops when terminal count is reached.  By default the
*  SamplingTimer operates in the continuous mode.
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
void SamplingTimer_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SamplingTimer_CONTROL_REG &= (uint32)~SamplingTimer_ONESHOT_MASK;
    SamplingTimer_CONTROL_REG |= ((uint32)((oneShotEnable & SamplingTimer_1BIT_MASK) <<
                                                               SamplingTimer_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SamplingTimer_SetPWMMode
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
void SamplingTimer_SetPWMMode(uint32 modeMask)
{
    SamplingTimer_TRIG_CONTROL2_REG = (modeMask & SamplingTimer_6BIT_MASK);
}



/*******************************************************************************
* Function Name: SamplingTimer_SetPWMSyncKill
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
void SamplingTimer_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SamplingTimer_CONTROL_REG &= (uint32)~SamplingTimer_PWM_SYNC_KILL_MASK;
    SamplingTimer_CONTROL_REG |= ((uint32)((syncKillEnable & SamplingTimer_1BIT_MASK)  <<
                                               SamplingTimer_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SamplingTimer_SetPWMStopOnKill
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
void SamplingTimer_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SamplingTimer_CONTROL_REG &= (uint32)~SamplingTimer_PWM_STOP_KILL_MASK;
    SamplingTimer_CONTROL_REG |= ((uint32)((stopOnKillEnable & SamplingTimer_1BIT_MASK)  <<
                                                         SamplingTimer_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SamplingTimer_SetPWMDeadTime
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
void SamplingTimer_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SamplingTimer_CONTROL_REG &= (uint32)~SamplingTimer_PRESCALER_MASK;
    SamplingTimer_CONTROL_REG |= ((uint32)((deadTime & SamplingTimer_8BIT_MASK) <<
                                                          SamplingTimer_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SamplingTimer_SetPWMInvert
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
*         - SamplingTimer_INVERT_LINE   - Inverts the line output
*         - SamplingTimer_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void SamplingTimer_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SamplingTimer_CONTROL_REG &= (uint32)~SamplingTimer_INV_OUT_MASK;
    SamplingTimer_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: SamplingTimer_WriteCounter
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
void SamplingTimer_WriteCounter(uint32 count)
{
    SamplingTimer_COUNTER_REG = (count & SamplingTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SamplingTimer_ReadCounter
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
uint32 SamplingTimer_ReadCounter(void)
{
    return (SamplingTimer_COUNTER_REG & SamplingTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SamplingTimer_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - SamplingTimer_COUNT_UP       - Counts up
*     - SamplingTimer_COUNT_DOWN     - Counts down
*     - SamplingTimer_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - SamplingTimer_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void SamplingTimer_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SamplingTimer_CONTROL_REG &= (uint32)~SamplingTimer_UPDOWN_MASK;
    SamplingTimer_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SamplingTimer_WritePeriod
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
void SamplingTimer_WritePeriod(uint32 period)
{
    SamplingTimer_PERIOD_REG = (period & SamplingTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SamplingTimer_ReadPeriod
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
uint32 SamplingTimer_ReadPeriod(void)
{
    return (SamplingTimer_PERIOD_REG & SamplingTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SamplingTimer_SetCompareSwap
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
void SamplingTimer_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SamplingTimer_CONTROL_REG &= (uint32)~SamplingTimer_RELOAD_CC_MASK;
    SamplingTimer_CONTROL_REG |= (swapEnable & SamplingTimer_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SamplingTimer_WritePeriodBuf
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
void SamplingTimer_WritePeriodBuf(uint32 periodBuf)
{
    SamplingTimer_PERIOD_BUF_REG = (periodBuf & SamplingTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SamplingTimer_ReadPeriodBuf
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
uint32 SamplingTimer_ReadPeriodBuf(void)
{
    return (SamplingTimer_PERIOD_BUF_REG & SamplingTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SamplingTimer_SetPeriodSwap
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
void SamplingTimer_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SamplingTimer_CONTROL_REG &= (uint32)~SamplingTimer_RELOAD_PERIOD_MASK;
    SamplingTimer_CONTROL_REG |= ((uint32)((swapEnable & SamplingTimer_1BIT_MASK) <<
                                                            SamplingTimer_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SamplingTimer_WriteCompare
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
void SamplingTimer_WriteCompare(uint32 compare)
{
    #if (SamplingTimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (SamplingTimer_CY_TCPWM_4000) */

    #if (SamplingTimer_CY_TCPWM_4000)
        currentMode = ((SamplingTimer_CONTROL_REG & SamplingTimer_UPDOWN_MASK) >> SamplingTimer_UPDOWN_SHIFT);

        if (((uint32)SamplingTimer__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)SamplingTimer__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (SamplingTimer_CY_TCPWM_4000) */
    
    SamplingTimer_COMP_CAP_REG = (compare & SamplingTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SamplingTimer_ReadCompare
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
uint32 SamplingTimer_ReadCompare(void)
{
    #if (SamplingTimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (SamplingTimer_CY_TCPWM_4000) */

    #if (SamplingTimer_CY_TCPWM_4000)
        currentMode = ((SamplingTimer_CONTROL_REG & SamplingTimer_UPDOWN_MASK) >> SamplingTimer_UPDOWN_SHIFT);
        
        regVal = SamplingTimer_COMP_CAP_REG;
        
        if (((uint32)SamplingTimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)SamplingTimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & SamplingTimer_16BIT_MASK);
    #else
        return (SamplingTimer_COMP_CAP_REG & SamplingTimer_16BIT_MASK);
    #endif /* (SamplingTimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: SamplingTimer_WriteCompareBuf
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
void SamplingTimer_WriteCompareBuf(uint32 compareBuf)
{
    #if (SamplingTimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (SamplingTimer_CY_TCPWM_4000) */

    #if (SamplingTimer_CY_TCPWM_4000)
        currentMode = ((SamplingTimer_CONTROL_REG & SamplingTimer_UPDOWN_MASK) >> SamplingTimer_UPDOWN_SHIFT);

        if (((uint32)SamplingTimer__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)SamplingTimer__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (SamplingTimer_CY_TCPWM_4000) */
    
    SamplingTimer_COMP_CAP_BUF_REG = (compareBuf & SamplingTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SamplingTimer_ReadCompareBuf
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
uint32 SamplingTimer_ReadCompareBuf(void)
{
    #if (SamplingTimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (SamplingTimer_CY_TCPWM_4000) */

    #if (SamplingTimer_CY_TCPWM_4000)
        currentMode = ((SamplingTimer_CONTROL_REG & SamplingTimer_UPDOWN_MASK) >> SamplingTimer_UPDOWN_SHIFT);

        regVal = SamplingTimer_COMP_CAP_BUF_REG;
        
        if (((uint32)SamplingTimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)SamplingTimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & SamplingTimer_16BIT_MASK);
    #else
        return (SamplingTimer_COMP_CAP_BUF_REG & SamplingTimer_16BIT_MASK);
    #endif /* (SamplingTimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: SamplingTimer_ReadCapture
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
uint32 SamplingTimer_ReadCapture(void)
{
    return (SamplingTimer_COMP_CAP_REG & SamplingTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SamplingTimer_ReadCaptureBuf
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
uint32 SamplingTimer_ReadCaptureBuf(void)
{
    return (SamplingTimer_COMP_CAP_BUF_REG & SamplingTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SamplingTimer_SetCaptureMode
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
*     - SamplingTimer_TRIG_LEVEL     - Level
*     - SamplingTimer_TRIG_RISING    - Rising edge
*     - SamplingTimer_TRIG_FALLING   - Falling edge
*     - SamplingTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SamplingTimer_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SamplingTimer_TRIG_CONTROL1_REG &= (uint32)~SamplingTimer_CAPTURE_MASK;
    SamplingTimer_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SamplingTimer_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SamplingTimer_TRIG_LEVEL     - Level
*     - SamplingTimer_TRIG_RISING    - Rising edge
*     - SamplingTimer_TRIG_FALLING   - Falling edge
*     - SamplingTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SamplingTimer_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SamplingTimer_TRIG_CONTROL1_REG &= (uint32)~SamplingTimer_RELOAD_MASK;
    SamplingTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SamplingTimer_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SamplingTimer_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SamplingTimer_TRIG_LEVEL     - Level
*     - SamplingTimer_TRIG_RISING    - Rising edge
*     - SamplingTimer_TRIG_FALLING   - Falling edge
*     - SamplingTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SamplingTimer_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SamplingTimer_TRIG_CONTROL1_REG &= (uint32)~SamplingTimer_START_MASK;
    SamplingTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SamplingTimer_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SamplingTimer_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SamplingTimer_TRIG_LEVEL     - Level
*     - SamplingTimer_TRIG_RISING    - Rising edge
*     - SamplingTimer_TRIG_FALLING   - Falling edge
*     - SamplingTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SamplingTimer_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SamplingTimer_TRIG_CONTROL1_REG &= (uint32)~SamplingTimer_STOP_MASK;
    SamplingTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SamplingTimer_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SamplingTimer_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SamplingTimer_TRIG_LEVEL     - Level
*     - SamplingTimer_TRIG_RISING    - Rising edge
*     - SamplingTimer_TRIG_FALLING   - Falling edge
*     - SamplingTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SamplingTimer_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SamplingTimer_TRIG_CONTROL1_REG &= (uint32)~SamplingTimer_COUNT_MASK;
    SamplingTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SamplingTimer_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SamplingTimer_TriggerCommand
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
*     - SamplingTimer_CMD_CAPTURE    - Trigger Capture/Switch command
*     - SamplingTimer_CMD_RELOAD     - Trigger Reload/Index command
*     - SamplingTimer_CMD_STOP       - Trigger Stop/Kill command
*     - SamplingTimer_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void SamplingTimer_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SamplingTimer_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SamplingTimer_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the SamplingTimer.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - SamplingTimer_STATUS_DOWN    - Set if counting down
*     - SamplingTimer_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 SamplingTimer_ReadStatus(void)
{
    return ((SamplingTimer_STATUS_REG >> SamplingTimer_RUNNING_STATUS_SHIFT) |
            (SamplingTimer_STATUS_REG & SamplingTimer_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: SamplingTimer_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - SamplingTimer_INTR_MASK_TC       - Terminal count mask
*     - SamplingTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void SamplingTimer_SetInterruptMode(uint32 interruptMask)
{
    SamplingTimer_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: SamplingTimer_GetInterruptSourceMasked
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
*     - SamplingTimer_INTR_MASK_TC       - Terminal count mask
*     - SamplingTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 SamplingTimer_GetInterruptSourceMasked(void)
{
    return (SamplingTimer_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: SamplingTimer_GetInterruptSource
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
*     - SamplingTimer_INTR_MASK_TC       - Terminal count mask
*     - SamplingTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 SamplingTimer_GetInterruptSource(void)
{
    return (SamplingTimer_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: SamplingTimer_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - SamplingTimer_INTR_MASK_TC       - Terminal count mask
*     - SamplingTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void SamplingTimer_ClearInterrupt(uint32 interruptMask)
{
    SamplingTimer_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: SamplingTimer_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - SamplingTimer_INTR_MASK_TC       - Terminal count mask
*     - SamplingTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void SamplingTimer_SetInterrupt(uint32 interruptMask)
{
    SamplingTimer_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
