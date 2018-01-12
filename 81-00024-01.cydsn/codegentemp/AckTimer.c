/*******************************************************************************
* File Name: AckTimer.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the AckTimer
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

#include "AckTimer.h"

uint8 AckTimer_initVar = 0u;


/*******************************************************************************
* Function Name: AckTimer_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default AckTimer configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void AckTimer_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (AckTimer__QUAD == AckTimer_CONFIG)
        AckTimer_CONTROL_REG = AckTimer_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        AckTimer_TRIG_CONTROL1_REG  = AckTimer_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        AckTimer_SetInterruptMode(AckTimer_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        AckTimer_SetCounterMode(AckTimer_COUNT_DOWN);
        AckTimer_WritePeriod(AckTimer_QUAD_PERIOD_INIT_VALUE);
        AckTimer_WriteCounter(AckTimer_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (AckTimer__QUAD == AckTimer_CONFIG) */

    #if (AckTimer__TIMER == AckTimer_CONFIG)
        AckTimer_CONTROL_REG = AckTimer_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        AckTimer_TRIG_CONTROL1_REG  = AckTimer_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        AckTimer_SetInterruptMode(AckTimer_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        AckTimer_WritePeriod(AckTimer_TC_PERIOD_VALUE );

        #if (AckTimer__COMPARE == AckTimer_TC_COMP_CAP_MODE)
            AckTimer_WriteCompare(AckTimer_TC_COMPARE_VALUE);

            #if (1u == AckTimer_TC_COMPARE_SWAP)
                AckTimer_SetCompareSwap(1u);
                AckTimer_WriteCompareBuf(AckTimer_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == AckTimer_TC_COMPARE_SWAP) */
        #endif  /* (AckTimer__COMPARE == AckTimer_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (AckTimer_CY_TCPWM_V2 && AckTimer_TIMER_UPDOWN_CNT_USED && !AckTimer_CY_TCPWM_4000)
            AckTimer_WriteCounter(1u);
        #elif(AckTimer__COUNT_DOWN == AckTimer_TC_COUNTER_MODE)
            AckTimer_WriteCounter(AckTimer_TC_PERIOD_VALUE);
        #else
            AckTimer_WriteCounter(0u);
        #endif /* (AckTimer_CY_TCPWM_V2 && AckTimer_TIMER_UPDOWN_CNT_USED && !AckTimer_CY_TCPWM_4000) */
    #endif  /* (AckTimer__TIMER == AckTimer_CONFIG) */

    #if (AckTimer__PWM_SEL == AckTimer_CONFIG)
        AckTimer_CONTROL_REG = AckTimer_CTRL_PWM_BASE_CONFIG;

        #if (AckTimer__PWM_PR == AckTimer_PWM_MODE)
            AckTimer_CONTROL_REG |= AckTimer_CTRL_PWM_RUN_MODE;
            AckTimer_WriteCounter(AckTimer_PWM_PR_INIT_VALUE);
        #else
            AckTimer_CONTROL_REG |= AckTimer_CTRL_PWM_ALIGN | AckTimer_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (AckTimer_CY_TCPWM_V2 && AckTimer_PWM_UPDOWN_CNT_USED && !AckTimer_CY_TCPWM_4000)
                AckTimer_WriteCounter(1u);
            #elif (AckTimer__RIGHT == AckTimer_PWM_ALIGN)
                AckTimer_WriteCounter(AckTimer_PWM_PERIOD_VALUE);
            #else 
                AckTimer_WriteCounter(0u);
            #endif  /* (AckTimer_CY_TCPWM_V2 && AckTimer_PWM_UPDOWN_CNT_USED && !AckTimer_CY_TCPWM_4000) */
        #endif  /* (AckTimer__PWM_PR == AckTimer_PWM_MODE) */

        #if (AckTimer__PWM_DT == AckTimer_PWM_MODE)
            AckTimer_CONTROL_REG |= AckTimer_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (AckTimer__PWM_DT == AckTimer_PWM_MODE) */

        #if (AckTimer__PWM == AckTimer_PWM_MODE)
            AckTimer_CONTROL_REG |= AckTimer_CTRL_PWM_PRESCALER;
        #endif  /* (AckTimer__PWM == AckTimer_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        AckTimer_TRIG_CONTROL1_REG  = AckTimer_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        AckTimer_SetInterruptMode(AckTimer_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (AckTimer__PWM_PR == AckTimer_PWM_MODE)
            AckTimer_TRIG_CONTROL2_REG =
                    (AckTimer_CC_MATCH_NO_CHANGE    |
                    AckTimer_OVERLOW_NO_CHANGE      |
                    AckTimer_UNDERFLOW_NO_CHANGE);
        #else
            #if (AckTimer__LEFT == AckTimer_PWM_ALIGN)
                AckTimer_TRIG_CONTROL2_REG = AckTimer_PWM_MODE_LEFT;
            #endif  /* ( AckTimer_PWM_LEFT == AckTimer_PWM_ALIGN) */

            #if (AckTimer__RIGHT == AckTimer_PWM_ALIGN)
                AckTimer_TRIG_CONTROL2_REG = AckTimer_PWM_MODE_RIGHT;
            #endif  /* ( AckTimer_PWM_RIGHT == AckTimer_PWM_ALIGN) */

            #if (AckTimer__CENTER == AckTimer_PWM_ALIGN)
                AckTimer_TRIG_CONTROL2_REG = AckTimer_PWM_MODE_CENTER;
            #endif  /* ( AckTimer_PWM_CENTER == AckTimer_PWM_ALIGN) */

            #if (AckTimer__ASYMMETRIC == AckTimer_PWM_ALIGN)
                AckTimer_TRIG_CONTROL2_REG = AckTimer_PWM_MODE_ASYM;
            #endif  /* (AckTimer__ASYMMETRIC == AckTimer_PWM_ALIGN) */
        #endif  /* (AckTimer__PWM_PR == AckTimer_PWM_MODE) */

        /* Set other values from customizer */
        AckTimer_WritePeriod(AckTimer_PWM_PERIOD_VALUE );
        AckTimer_WriteCompare(AckTimer_PWM_COMPARE_VALUE);

        #if (1u == AckTimer_PWM_COMPARE_SWAP)
            AckTimer_SetCompareSwap(1u);
            AckTimer_WriteCompareBuf(AckTimer_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == AckTimer_PWM_COMPARE_SWAP) */

        #if (1u == AckTimer_PWM_PERIOD_SWAP)
            AckTimer_SetPeriodSwap(1u);
            AckTimer_WritePeriodBuf(AckTimer_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == AckTimer_PWM_PERIOD_SWAP) */
    #endif  /* (AckTimer__PWM_SEL == AckTimer_CONFIG) */
    
}


/*******************************************************************************
* Function Name: AckTimer_Enable
********************************************************************************
*
* Summary:
*  Enables the AckTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void AckTimer_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    AckTimer_BLOCK_CONTROL_REG |= AckTimer_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (AckTimer__PWM_SEL == AckTimer_CONFIG)
        #if (0u == AckTimer_PWM_START_SIGNAL_PRESENT)
            AckTimer_TriggerCommand(AckTimer_MASK, AckTimer_CMD_START);
        #endif /* (0u == AckTimer_PWM_START_SIGNAL_PRESENT) */
    #endif /* (AckTimer__PWM_SEL == AckTimer_CONFIG) */

    #if (AckTimer__TIMER == AckTimer_CONFIG)
        #if (0u == AckTimer_TC_START_SIGNAL_PRESENT)
            AckTimer_TriggerCommand(AckTimer_MASK, AckTimer_CMD_START);
        #endif /* (0u == AckTimer_TC_START_SIGNAL_PRESENT) */
    #endif /* (AckTimer__TIMER == AckTimer_CONFIG) */
    
    #if (AckTimer__QUAD == AckTimer_CONFIG)
        #if (0u != AckTimer_QUAD_AUTO_START)
            AckTimer_TriggerCommand(AckTimer_MASK, AckTimer_CMD_RELOAD);
        #endif /* (0u != AckTimer_QUAD_AUTO_START) */
    #endif  /* (AckTimer__QUAD == AckTimer_CONFIG) */
}


/*******************************************************************************
* Function Name: AckTimer_Start
********************************************************************************
*
* Summary:
*  Initializes the AckTimer with default customizer
*  values when called the first time and enables the AckTimer.
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
*  AckTimer_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time AckTimer_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the AckTimer_Start() routine.
*
*******************************************************************************/
void AckTimer_Start(void)
{
    if (0u == AckTimer_initVar)
    {
        AckTimer_Init();
        AckTimer_initVar = 1u;
    }

    AckTimer_Enable();
}


/*******************************************************************************
* Function Name: AckTimer_Stop
********************************************************************************
*
* Summary:
*  Disables the AckTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void AckTimer_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    AckTimer_BLOCK_CONTROL_REG &= (uint32)~AckTimer_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: AckTimer_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the AckTimer. This function is used when
*  configured as a generic AckTimer and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the AckTimer to operate in
*   Values:
*   - AckTimer_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - AckTimer_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - AckTimer_MODE_QUAD - Quadrature decoder
*         - AckTimer_MODE_PWM - PWM
*         - AckTimer_MODE_PWM_DT - PWM with dead time
*         - AckTimer_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void AckTimer_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    AckTimer_CONTROL_REG &= (uint32)~AckTimer_MODE_MASK;
    AckTimer_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: AckTimer_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - AckTimer_MODE_X1 - Counts on phi 1 rising
*         - AckTimer_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - AckTimer_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void AckTimer_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    AckTimer_CONTROL_REG &= (uint32)~AckTimer_QUAD_MODE_MASK;
    AckTimer_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: AckTimer_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - AckTimer_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - AckTimer_PRESCALE_DIVBY2    - Divide by 2
*         - AckTimer_PRESCALE_DIVBY4    - Divide by 4
*         - AckTimer_PRESCALE_DIVBY8    - Divide by 8
*         - AckTimer_PRESCALE_DIVBY16   - Divide by 16
*         - AckTimer_PRESCALE_DIVBY32   - Divide by 32
*         - AckTimer_PRESCALE_DIVBY64   - Divide by 64
*         - AckTimer_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void AckTimer_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    AckTimer_CONTROL_REG &= (uint32)~AckTimer_PRESCALER_MASK;
    AckTimer_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: AckTimer_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the AckTimer runs
*  continuously or stops when terminal count is reached.  By default the
*  AckTimer operates in the continuous mode.
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
void AckTimer_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    AckTimer_CONTROL_REG &= (uint32)~AckTimer_ONESHOT_MASK;
    AckTimer_CONTROL_REG |= ((uint32)((oneShotEnable & AckTimer_1BIT_MASK) <<
                                                               AckTimer_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: AckTimer_SetPWMMode
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
void AckTimer_SetPWMMode(uint32 modeMask)
{
    AckTimer_TRIG_CONTROL2_REG = (modeMask & AckTimer_6BIT_MASK);
}



/*******************************************************************************
* Function Name: AckTimer_SetPWMSyncKill
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
void AckTimer_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    AckTimer_CONTROL_REG &= (uint32)~AckTimer_PWM_SYNC_KILL_MASK;
    AckTimer_CONTROL_REG |= ((uint32)((syncKillEnable & AckTimer_1BIT_MASK)  <<
                                               AckTimer_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: AckTimer_SetPWMStopOnKill
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
void AckTimer_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    AckTimer_CONTROL_REG &= (uint32)~AckTimer_PWM_STOP_KILL_MASK;
    AckTimer_CONTROL_REG |= ((uint32)((stopOnKillEnable & AckTimer_1BIT_MASK)  <<
                                                         AckTimer_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: AckTimer_SetPWMDeadTime
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
void AckTimer_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    AckTimer_CONTROL_REG &= (uint32)~AckTimer_PRESCALER_MASK;
    AckTimer_CONTROL_REG |= ((uint32)((deadTime & AckTimer_8BIT_MASK) <<
                                                          AckTimer_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: AckTimer_SetPWMInvert
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
*         - AckTimer_INVERT_LINE   - Inverts the line output
*         - AckTimer_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void AckTimer_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    AckTimer_CONTROL_REG &= (uint32)~AckTimer_INV_OUT_MASK;
    AckTimer_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: AckTimer_WriteCounter
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
void AckTimer_WriteCounter(uint32 count)
{
    AckTimer_COUNTER_REG = (count & AckTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: AckTimer_ReadCounter
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
uint32 AckTimer_ReadCounter(void)
{
    return (AckTimer_COUNTER_REG & AckTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: AckTimer_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - AckTimer_COUNT_UP       - Counts up
*     - AckTimer_COUNT_DOWN     - Counts down
*     - AckTimer_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - AckTimer_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void AckTimer_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    AckTimer_CONTROL_REG &= (uint32)~AckTimer_UPDOWN_MASK;
    AckTimer_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: AckTimer_WritePeriod
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
void AckTimer_WritePeriod(uint32 period)
{
    AckTimer_PERIOD_REG = (period & AckTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: AckTimer_ReadPeriod
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
uint32 AckTimer_ReadPeriod(void)
{
    return (AckTimer_PERIOD_REG & AckTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: AckTimer_SetCompareSwap
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
void AckTimer_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    AckTimer_CONTROL_REG &= (uint32)~AckTimer_RELOAD_CC_MASK;
    AckTimer_CONTROL_REG |= (swapEnable & AckTimer_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: AckTimer_WritePeriodBuf
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
void AckTimer_WritePeriodBuf(uint32 periodBuf)
{
    AckTimer_PERIOD_BUF_REG = (periodBuf & AckTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: AckTimer_ReadPeriodBuf
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
uint32 AckTimer_ReadPeriodBuf(void)
{
    return (AckTimer_PERIOD_BUF_REG & AckTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: AckTimer_SetPeriodSwap
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
void AckTimer_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    AckTimer_CONTROL_REG &= (uint32)~AckTimer_RELOAD_PERIOD_MASK;
    AckTimer_CONTROL_REG |= ((uint32)((swapEnable & AckTimer_1BIT_MASK) <<
                                                            AckTimer_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: AckTimer_WriteCompare
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
void AckTimer_WriteCompare(uint32 compare)
{
    #if (AckTimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (AckTimer_CY_TCPWM_4000) */

    #if (AckTimer_CY_TCPWM_4000)
        currentMode = ((AckTimer_CONTROL_REG & AckTimer_UPDOWN_MASK) >> AckTimer_UPDOWN_SHIFT);

        if (((uint32)AckTimer__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)AckTimer__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (AckTimer_CY_TCPWM_4000) */
    
    AckTimer_COMP_CAP_REG = (compare & AckTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: AckTimer_ReadCompare
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
uint32 AckTimer_ReadCompare(void)
{
    #if (AckTimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (AckTimer_CY_TCPWM_4000) */

    #if (AckTimer_CY_TCPWM_4000)
        currentMode = ((AckTimer_CONTROL_REG & AckTimer_UPDOWN_MASK) >> AckTimer_UPDOWN_SHIFT);
        
        regVal = AckTimer_COMP_CAP_REG;
        
        if (((uint32)AckTimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)AckTimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & AckTimer_16BIT_MASK);
    #else
        return (AckTimer_COMP_CAP_REG & AckTimer_16BIT_MASK);
    #endif /* (AckTimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: AckTimer_WriteCompareBuf
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
void AckTimer_WriteCompareBuf(uint32 compareBuf)
{
    #if (AckTimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (AckTimer_CY_TCPWM_4000) */

    #if (AckTimer_CY_TCPWM_4000)
        currentMode = ((AckTimer_CONTROL_REG & AckTimer_UPDOWN_MASK) >> AckTimer_UPDOWN_SHIFT);

        if (((uint32)AckTimer__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)AckTimer__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (AckTimer_CY_TCPWM_4000) */
    
    AckTimer_COMP_CAP_BUF_REG = (compareBuf & AckTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: AckTimer_ReadCompareBuf
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
uint32 AckTimer_ReadCompareBuf(void)
{
    #if (AckTimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (AckTimer_CY_TCPWM_4000) */

    #if (AckTimer_CY_TCPWM_4000)
        currentMode = ((AckTimer_CONTROL_REG & AckTimer_UPDOWN_MASK) >> AckTimer_UPDOWN_SHIFT);

        regVal = AckTimer_COMP_CAP_BUF_REG;
        
        if (((uint32)AckTimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)AckTimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & AckTimer_16BIT_MASK);
    #else
        return (AckTimer_COMP_CAP_BUF_REG & AckTimer_16BIT_MASK);
    #endif /* (AckTimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: AckTimer_ReadCapture
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
uint32 AckTimer_ReadCapture(void)
{
    return (AckTimer_COMP_CAP_REG & AckTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: AckTimer_ReadCaptureBuf
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
uint32 AckTimer_ReadCaptureBuf(void)
{
    return (AckTimer_COMP_CAP_BUF_REG & AckTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: AckTimer_SetCaptureMode
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
*     - AckTimer_TRIG_LEVEL     - Level
*     - AckTimer_TRIG_RISING    - Rising edge
*     - AckTimer_TRIG_FALLING   - Falling edge
*     - AckTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void AckTimer_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    AckTimer_TRIG_CONTROL1_REG &= (uint32)~AckTimer_CAPTURE_MASK;
    AckTimer_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: AckTimer_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - AckTimer_TRIG_LEVEL     - Level
*     - AckTimer_TRIG_RISING    - Rising edge
*     - AckTimer_TRIG_FALLING   - Falling edge
*     - AckTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void AckTimer_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    AckTimer_TRIG_CONTROL1_REG &= (uint32)~AckTimer_RELOAD_MASK;
    AckTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << AckTimer_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: AckTimer_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - AckTimer_TRIG_LEVEL     - Level
*     - AckTimer_TRIG_RISING    - Rising edge
*     - AckTimer_TRIG_FALLING   - Falling edge
*     - AckTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void AckTimer_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    AckTimer_TRIG_CONTROL1_REG &= (uint32)~AckTimer_START_MASK;
    AckTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << AckTimer_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: AckTimer_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - AckTimer_TRIG_LEVEL     - Level
*     - AckTimer_TRIG_RISING    - Rising edge
*     - AckTimer_TRIG_FALLING   - Falling edge
*     - AckTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void AckTimer_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    AckTimer_TRIG_CONTROL1_REG &= (uint32)~AckTimer_STOP_MASK;
    AckTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << AckTimer_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: AckTimer_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - AckTimer_TRIG_LEVEL     - Level
*     - AckTimer_TRIG_RISING    - Rising edge
*     - AckTimer_TRIG_FALLING   - Falling edge
*     - AckTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void AckTimer_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    AckTimer_TRIG_CONTROL1_REG &= (uint32)~AckTimer_COUNT_MASK;
    AckTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << AckTimer_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: AckTimer_TriggerCommand
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
*     - AckTimer_CMD_CAPTURE    - Trigger Capture/Switch command
*     - AckTimer_CMD_RELOAD     - Trigger Reload/Index command
*     - AckTimer_CMD_STOP       - Trigger Stop/Kill command
*     - AckTimer_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void AckTimer_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    AckTimer_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: AckTimer_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the AckTimer.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - AckTimer_STATUS_DOWN    - Set if counting down
*     - AckTimer_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 AckTimer_ReadStatus(void)
{
    return ((AckTimer_STATUS_REG >> AckTimer_RUNNING_STATUS_SHIFT) |
            (AckTimer_STATUS_REG & AckTimer_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: AckTimer_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - AckTimer_INTR_MASK_TC       - Terminal count mask
*     - AckTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void AckTimer_SetInterruptMode(uint32 interruptMask)
{
    AckTimer_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: AckTimer_GetInterruptSourceMasked
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
*     - AckTimer_INTR_MASK_TC       - Terminal count mask
*     - AckTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 AckTimer_GetInterruptSourceMasked(void)
{
    return (AckTimer_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: AckTimer_GetInterruptSource
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
*     - AckTimer_INTR_MASK_TC       - Terminal count mask
*     - AckTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 AckTimer_GetInterruptSource(void)
{
    return (AckTimer_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: AckTimer_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - AckTimer_INTR_MASK_TC       - Terminal count mask
*     - AckTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void AckTimer_ClearInterrupt(uint32 interruptMask)
{
    AckTimer_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: AckTimer_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - AckTimer_INTR_MASK_TC       - Terminal count mask
*     - AckTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void AckTimer_SetInterrupt(uint32 interruptMask)
{
    AckTimer_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
