/*******************************************************************************
* File Name: TimeoutTimer.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the TimeoutTimer
*  component.
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

#if !defined(CY_TCPWM_TimeoutTimer_H)
#define CY_TCPWM_TimeoutTimer_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} TimeoutTimer_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  TimeoutTimer_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define TimeoutTimer_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define TimeoutTimer_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define TimeoutTimer_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define TimeoutTimer_QUAD_ENCODING_MODES            (0lu)
#define TimeoutTimer_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define TimeoutTimer_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define TimeoutTimer_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define TimeoutTimer_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define TimeoutTimer_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define TimeoutTimer_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define TimeoutTimer_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define TimeoutTimer_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define TimeoutTimer_TC_RUN_MODE                    (0lu)
#define TimeoutTimer_TC_COUNTER_MODE                (0lu)
#define TimeoutTimer_TC_COMP_CAP_MODE               (2lu)
#define TimeoutTimer_TC_PRESCALER                   (0lu)

/* Signal modes */
#define TimeoutTimer_TC_RELOAD_SIGNAL_MODE          (0lu)
#define TimeoutTimer_TC_COUNT_SIGNAL_MODE           (3lu)
#define TimeoutTimer_TC_START_SIGNAL_MODE           (0lu)
#define TimeoutTimer_TC_STOP_SIGNAL_MODE            (0lu)
#define TimeoutTimer_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define TimeoutTimer_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define TimeoutTimer_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define TimeoutTimer_TC_START_SIGNAL_PRESENT        (0lu)
#define TimeoutTimer_TC_STOP_SIGNAL_PRESENT         (0lu)
#define TimeoutTimer_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define TimeoutTimer_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define TimeoutTimer_PWM_KILL_EVENT                 (0lu)
#define TimeoutTimer_PWM_STOP_EVENT                 (0lu)
#define TimeoutTimer_PWM_MODE                       (4lu)
#define TimeoutTimer_PWM_OUT_N_INVERT               (0lu)
#define TimeoutTimer_PWM_OUT_INVERT                 (0lu)
#define TimeoutTimer_PWM_ALIGN                      (0lu)
#define TimeoutTimer_PWM_RUN_MODE                   (0lu)
#define TimeoutTimer_PWM_DEAD_TIME_CYCLE            (0lu)
#define TimeoutTimer_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define TimeoutTimer_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define TimeoutTimer_PWM_COUNT_SIGNAL_MODE          (3lu)
#define TimeoutTimer_PWM_START_SIGNAL_MODE          (0lu)
#define TimeoutTimer_PWM_STOP_SIGNAL_MODE           (0lu)
#define TimeoutTimer_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define TimeoutTimer_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define TimeoutTimer_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define TimeoutTimer_PWM_START_SIGNAL_PRESENT       (0lu)
#define TimeoutTimer_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define TimeoutTimer_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define TimeoutTimer_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define TimeoutTimer_TC_PERIOD_VALUE                (1000lu)
#define TimeoutTimer_TC_COMPARE_VALUE               (1000lu)
#define TimeoutTimer_TC_COMPARE_BUF_VALUE           (65535lu)
#define TimeoutTimer_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define TimeoutTimer_PWM_PERIOD_VALUE               (1000lu)
#define TimeoutTimer_PWM_PERIOD_BUF_VALUE           (65535lu)
#define TimeoutTimer_PWM_PERIOD_SWAP                (0lu)
#define TimeoutTimer_PWM_COMPARE_VALUE              (1000lu)
#define TimeoutTimer_PWM_COMPARE_BUF_VALUE          (65535lu)
#define TimeoutTimer_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define TimeoutTimer__LEFT 0
#define TimeoutTimer__RIGHT 1
#define TimeoutTimer__CENTER 2
#define TimeoutTimer__ASYMMETRIC 3

#define TimeoutTimer__X1 0
#define TimeoutTimer__X2 1
#define TimeoutTimer__X4 2

#define TimeoutTimer__PWM 4
#define TimeoutTimer__PWM_DT 5
#define TimeoutTimer__PWM_PR 6

#define TimeoutTimer__INVERSE 1
#define TimeoutTimer__DIRECT 0

#define TimeoutTimer__CAPTURE 2
#define TimeoutTimer__COMPARE 0

#define TimeoutTimer__TRIG_LEVEL 3
#define TimeoutTimer__TRIG_RISING 0
#define TimeoutTimer__TRIG_FALLING 1
#define TimeoutTimer__TRIG_BOTH 2

#define TimeoutTimer__INTR_MASK_TC 1
#define TimeoutTimer__INTR_MASK_CC_MATCH 2
#define TimeoutTimer__INTR_MASK_NONE 0
#define TimeoutTimer__INTR_MASK_TC_CC 3

#define TimeoutTimer__UNCONFIG 8
#define TimeoutTimer__TIMER 1
#define TimeoutTimer__QUAD 3
#define TimeoutTimer__PWM_SEL 7

#define TimeoutTimer__COUNT_UP 0
#define TimeoutTimer__COUNT_DOWN 1
#define TimeoutTimer__COUNT_UPDOWN0 2
#define TimeoutTimer__COUNT_UPDOWN1 3


/* Prescaler */
#define TimeoutTimer_PRESCALE_DIVBY1                ((uint32)(0u << TimeoutTimer_PRESCALER_SHIFT))
#define TimeoutTimer_PRESCALE_DIVBY2                ((uint32)(1u << TimeoutTimer_PRESCALER_SHIFT))
#define TimeoutTimer_PRESCALE_DIVBY4                ((uint32)(2u << TimeoutTimer_PRESCALER_SHIFT))
#define TimeoutTimer_PRESCALE_DIVBY8                ((uint32)(3u << TimeoutTimer_PRESCALER_SHIFT))
#define TimeoutTimer_PRESCALE_DIVBY16               ((uint32)(4u << TimeoutTimer_PRESCALER_SHIFT))
#define TimeoutTimer_PRESCALE_DIVBY32               ((uint32)(5u << TimeoutTimer_PRESCALER_SHIFT))
#define TimeoutTimer_PRESCALE_DIVBY64               ((uint32)(6u << TimeoutTimer_PRESCALER_SHIFT))
#define TimeoutTimer_PRESCALE_DIVBY128              ((uint32)(7u << TimeoutTimer_PRESCALER_SHIFT))

/* TCPWM set modes */
#define TimeoutTimer_MODE_TIMER_COMPARE             ((uint32)(TimeoutTimer__COMPARE         <<  \
                                                                  TimeoutTimer_MODE_SHIFT))
#define TimeoutTimer_MODE_TIMER_CAPTURE             ((uint32)(TimeoutTimer__CAPTURE         <<  \
                                                                  TimeoutTimer_MODE_SHIFT))
#define TimeoutTimer_MODE_QUAD                      ((uint32)(TimeoutTimer__QUAD            <<  \
                                                                  TimeoutTimer_MODE_SHIFT))
#define TimeoutTimer_MODE_PWM                       ((uint32)(TimeoutTimer__PWM             <<  \
                                                                  TimeoutTimer_MODE_SHIFT))
#define TimeoutTimer_MODE_PWM_DT                    ((uint32)(TimeoutTimer__PWM_DT          <<  \
                                                                  TimeoutTimer_MODE_SHIFT))
#define TimeoutTimer_MODE_PWM_PR                    ((uint32)(TimeoutTimer__PWM_PR          <<  \
                                                                  TimeoutTimer_MODE_SHIFT))

/* Quad Modes */
#define TimeoutTimer_MODE_X1                        ((uint32)(TimeoutTimer__X1              <<  \
                                                                  TimeoutTimer_QUAD_MODE_SHIFT))
#define TimeoutTimer_MODE_X2                        ((uint32)(TimeoutTimer__X2              <<  \
                                                                  TimeoutTimer_QUAD_MODE_SHIFT))
#define TimeoutTimer_MODE_X4                        ((uint32)(TimeoutTimer__X4              <<  \
                                                                  TimeoutTimer_QUAD_MODE_SHIFT))

/* Counter modes */
#define TimeoutTimer_COUNT_UP                       ((uint32)(TimeoutTimer__COUNT_UP        <<  \
                                                                  TimeoutTimer_UPDOWN_SHIFT))
#define TimeoutTimer_COUNT_DOWN                     ((uint32)(TimeoutTimer__COUNT_DOWN      <<  \
                                                                  TimeoutTimer_UPDOWN_SHIFT))
#define TimeoutTimer_COUNT_UPDOWN0                  ((uint32)(TimeoutTimer__COUNT_UPDOWN0   <<  \
                                                                  TimeoutTimer_UPDOWN_SHIFT))
#define TimeoutTimer_COUNT_UPDOWN1                  ((uint32)(TimeoutTimer__COUNT_UPDOWN1   <<  \
                                                                  TimeoutTimer_UPDOWN_SHIFT))

/* PWM output invert */
#define TimeoutTimer_INVERT_LINE                    ((uint32)(TimeoutTimer__INVERSE         <<  \
                                                                  TimeoutTimer_INV_OUT_SHIFT))
#define TimeoutTimer_INVERT_LINE_N                  ((uint32)(TimeoutTimer__INVERSE         <<  \
                                                                  TimeoutTimer_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define TimeoutTimer_TRIG_RISING                    ((uint32)TimeoutTimer__TRIG_RISING)
#define TimeoutTimer_TRIG_FALLING                   ((uint32)TimeoutTimer__TRIG_FALLING)
#define TimeoutTimer_TRIG_BOTH                      ((uint32)TimeoutTimer__TRIG_BOTH)
#define TimeoutTimer_TRIG_LEVEL                     ((uint32)TimeoutTimer__TRIG_LEVEL)

/* Interrupt mask */
#define TimeoutTimer_INTR_MASK_TC                   ((uint32)TimeoutTimer__INTR_MASK_TC)
#define TimeoutTimer_INTR_MASK_CC_MATCH             ((uint32)TimeoutTimer__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define TimeoutTimer_CC_MATCH_SET                   (0x00u)
#define TimeoutTimer_CC_MATCH_CLEAR                 (0x01u)
#define TimeoutTimer_CC_MATCH_INVERT                (0x02u)
#define TimeoutTimer_CC_MATCH_NO_CHANGE             (0x03u)
#define TimeoutTimer_OVERLOW_SET                    (0x00u)
#define TimeoutTimer_OVERLOW_CLEAR                  (0x04u)
#define TimeoutTimer_OVERLOW_INVERT                 (0x08u)
#define TimeoutTimer_OVERLOW_NO_CHANGE              (0x0Cu)
#define TimeoutTimer_UNDERFLOW_SET                  (0x00u)
#define TimeoutTimer_UNDERFLOW_CLEAR                (0x10u)
#define TimeoutTimer_UNDERFLOW_INVERT               (0x20u)
#define TimeoutTimer_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define TimeoutTimer_PWM_MODE_LEFT                  (TimeoutTimer_CC_MATCH_CLEAR        |   \
                                                         TimeoutTimer_OVERLOW_SET           |   \
                                                         TimeoutTimer_UNDERFLOW_NO_CHANGE)
#define TimeoutTimer_PWM_MODE_RIGHT                 (TimeoutTimer_CC_MATCH_SET          |   \
                                                         TimeoutTimer_OVERLOW_NO_CHANGE     |   \
                                                         TimeoutTimer_UNDERFLOW_CLEAR)
#define TimeoutTimer_PWM_MODE_ASYM                  (TimeoutTimer_CC_MATCH_INVERT       |   \
                                                         TimeoutTimer_OVERLOW_SET           |   \
                                                         TimeoutTimer_UNDERFLOW_CLEAR)

#if (TimeoutTimer_CY_TCPWM_V2)
    #if(TimeoutTimer_CY_TCPWM_4000)
        #define TimeoutTimer_PWM_MODE_CENTER                (TimeoutTimer_CC_MATCH_INVERT       |   \
                                                                 TimeoutTimer_OVERLOW_NO_CHANGE     |   \
                                                                 TimeoutTimer_UNDERFLOW_CLEAR)
    #else
        #define TimeoutTimer_PWM_MODE_CENTER                (TimeoutTimer_CC_MATCH_INVERT       |   \
                                                                 TimeoutTimer_OVERLOW_SET           |   \
                                                                 TimeoutTimer_UNDERFLOW_CLEAR)
    #endif /* (TimeoutTimer_CY_TCPWM_4000) */
#else
    #define TimeoutTimer_PWM_MODE_CENTER                (TimeoutTimer_CC_MATCH_INVERT       |   \
                                                             TimeoutTimer_OVERLOW_NO_CHANGE     |   \
                                                             TimeoutTimer_UNDERFLOW_CLEAR)
#endif /* (TimeoutTimer_CY_TCPWM_NEW) */

/* Command operations without condition */
#define TimeoutTimer_CMD_CAPTURE                    (0u)
#define TimeoutTimer_CMD_RELOAD                     (8u)
#define TimeoutTimer_CMD_STOP                       (16u)
#define TimeoutTimer_CMD_START                      (24u)

/* Status */
#define TimeoutTimer_STATUS_DOWN                    (1u)
#define TimeoutTimer_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   TimeoutTimer_Init(void);
void   TimeoutTimer_Enable(void);
void   TimeoutTimer_Start(void);
void   TimeoutTimer_Stop(void);

void   TimeoutTimer_SetMode(uint32 mode);
void   TimeoutTimer_SetCounterMode(uint32 counterMode);
void   TimeoutTimer_SetPWMMode(uint32 modeMask);
void   TimeoutTimer_SetQDMode(uint32 qdMode);

void   TimeoutTimer_SetPrescaler(uint32 prescaler);
void   TimeoutTimer_TriggerCommand(uint32 mask, uint32 command);
void   TimeoutTimer_SetOneShot(uint32 oneShotEnable);
uint32 TimeoutTimer_ReadStatus(void);

void   TimeoutTimer_SetPWMSyncKill(uint32 syncKillEnable);
void   TimeoutTimer_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   TimeoutTimer_SetPWMDeadTime(uint32 deadTime);
void   TimeoutTimer_SetPWMInvert(uint32 mask);

void   TimeoutTimer_SetInterruptMode(uint32 interruptMask);
uint32 TimeoutTimer_GetInterruptSourceMasked(void);
uint32 TimeoutTimer_GetInterruptSource(void);
void   TimeoutTimer_ClearInterrupt(uint32 interruptMask);
void   TimeoutTimer_SetInterrupt(uint32 interruptMask);

void   TimeoutTimer_WriteCounter(uint32 count);
uint32 TimeoutTimer_ReadCounter(void);

uint32 TimeoutTimer_ReadCapture(void);
uint32 TimeoutTimer_ReadCaptureBuf(void);

void   TimeoutTimer_WritePeriod(uint32 period);
uint32 TimeoutTimer_ReadPeriod(void);
void   TimeoutTimer_WritePeriodBuf(uint32 periodBuf);
uint32 TimeoutTimer_ReadPeriodBuf(void);

void   TimeoutTimer_WriteCompare(uint32 compare);
uint32 TimeoutTimer_ReadCompare(void);
void   TimeoutTimer_WriteCompareBuf(uint32 compareBuf);
uint32 TimeoutTimer_ReadCompareBuf(void);

void   TimeoutTimer_SetPeriodSwap(uint32 swapEnable);
void   TimeoutTimer_SetCompareSwap(uint32 swapEnable);

void   TimeoutTimer_SetCaptureMode(uint32 triggerMode);
void   TimeoutTimer_SetReloadMode(uint32 triggerMode);
void   TimeoutTimer_SetStartMode(uint32 triggerMode);
void   TimeoutTimer_SetStopMode(uint32 triggerMode);
void   TimeoutTimer_SetCountMode(uint32 triggerMode);

void   TimeoutTimer_SaveConfig(void);
void   TimeoutTimer_RestoreConfig(void);
void   TimeoutTimer_Sleep(void);
void   TimeoutTimer_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define TimeoutTimer_BLOCK_CONTROL_REG              (*(reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define TimeoutTimer_BLOCK_CONTROL_PTR              ( (reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define TimeoutTimer_COMMAND_REG                    (*(reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define TimeoutTimer_COMMAND_PTR                    ( (reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define TimeoutTimer_INTRRUPT_CAUSE_REG             (*(reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define TimeoutTimer_INTRRUPT_CAUSE_PTR             ( (reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define TimeoutTimer_CONTROL_REG                    (*(reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__CTRL )
#define TimeoutTimer_CONTROL_PTR                    ( (reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__CTRL )
#define TimeoutTimer_STATUS_REG                     (*(reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__STATUS )
#define TimeoutTimer_STATUS_PTR                     ( (reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__STATUS )
#define TimeoutTimer_COUNTER_REG                    (*(reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__COUNTER )
#define TimeoutTimer_COUNTER_PTR                    ( (reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__COUNTER )
#define TimeoutTimer_COMP_CAP_REG                   (*(reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__CC )
#define TimeoutTimer_COMP_CAP_PTR                   ( (reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__CC )
#define TimeoutTimer_COMP_CAP_BUF_REG               (*(reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define TimeoutTimer_COMP_CAP_BUF_PTR               ( (reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define TimeoutTimer_PERIOD_REG                     (*(reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__PERIOD )
#define TimeoutTimer_PERIOD_PTR                     ( (reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__PERIOD )
#define TimeoutTimer_PERIOD_BUF_REG                 (*(reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define TimeoutTimer_PERIOD_BUF_PTR                 ( (reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define TimeoutTimer_TRIG_CONTROL0_REG              (*(reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define TimeoutTimer_TRIG_CONTROL0_PTR              ( (reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define TimeoutTimer_TRIG_CONTROL1_REG              (*(reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define TimeoutTimer_TRIG_CONTROL1_PTR              ( (reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define TimeoutTimer_TRIG_CONTROL2_REG              (*(reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define TimeoutTimer_TRIG_CONTROL2_PTR              ( (reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define TimeoutTimer_INTERRUPT_REQ_REG              (*(reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__INTR )
#define TimeoutTimer_INTERRUPT_REQ_PTR              ( (reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__INTR )
#define TimeoutTimer_INTERRUPT_SET_REG              (*(reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define TimeoutTimer_INTERRUPT_SET_PTR              ( (reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define TimeoutTimer_INTERRUPT_MASK_REG             (*(reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define TimeoutTimer_INTERRUPT_MASK_PTR             ( (reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define TimeoutTimer_INTERRUPT_MASKED_REG           (*(reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__INTR_MASKED )
#define TimeoutTimer_INTERRUPT_MASKED_PTR           ( (reg32 *) TimeoutTimer_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define TimeoutTimer_MASK                           ((uint32)TimeoutTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define TimeoutTimer_RELOAD_CC_SHIFT                (0u)
#define TimeoutTimer_RELOAD_PERIOD_SHIFT            (1u)
#define TimeoutTimer_PWM_SYNC_KILL_SHIFT            (2u)
#define TimeoutTimer_PWM_STOP_KILL_SHIFT            (3u)
#define TimeoutTimer_PRESCALER_SHIFT                (8u)
#define TimeoutTimer_UPDOWN_SHIFT                   (16u)
#define TimeoutTimer_ONESHOT_SHIFT                  (18u)
#define TimeoutTimer_QUAD_MODE_SHIFT                (20u)
#define TimeoutTimer_INV_OUT_SHIFT                  (20u)
#define TimeoutTimer_INV_COMPL_OUT_SHIFT            (21u)
#define TimeoutTimer_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define TimeoutTimer_RELOAD_CC_MASK                 ((uint32)(TimeoutTimer_1BIT_MASK        <<  \
                                                                            TimeoutTimer_RELOAD_CC_SHIFT))
#define TimeoutTimer_RELOAD_PERIOD_MASK             ((uint32)(TimeoutTimer_1BIT_MASK        <<  \
                                                                            TimeoutTimer_RELOAD_PERIOD_SHIFT))
#define TimeoutTimer_PWM_SYNC_KILL_MASK             ((uint32)(TimeoutTimer_1BIT_MASK        <<  \
                                                                            TimeoutTimer_PWM_SYNC_KILL_SHIFT))
#define TimeoutTimer_PWM_STOP_KILL_MASK             ((uint32)(TimeoutTimer_1BIT_MASK        <<  \
                                                                            TimeoutTimer_PWM_STOP_KILL_SHIFT))
#define TimeoutTimer_PRESCALER_MASK                 ((uint32)(TimeoutTimer_8BIT_MASK        <<  \
                                                                            TimeoutTimer_PRESCALER_SHIFT))
#define TimeoutTimer_UPDOWN_MASK                    ((uint32)(TimeoutTimer_2BIT_MASK        <<  \
                                                                            TimeoutTimer_UPDOWN_SHIFT))
#define TimeoutTimer_ONESHOT_MASK                   ((uint32)(TimeoutTimer_1BIT_MASK        <<  \
                                                                            TimeoutTimer_ONESHOT_SHIFT))
#define TimeoutTimer_QUAD_MODE_MASK                 ((uint32)(TimeoutTimer_3BIT_MASK        <<  \
                                                                            TimeoutTimer_QUAD_MODE_SHIFT))
#define TimeoutTimer_INV_OUT_MASK                   ((uint32)(TimeoutTimer_2BIT_MASK        <<  \
                                                                            TimeoutTimer_INV_OUT_SHIFT))
#define TimeoutTimer_MODE_MASK                      ((uint32)(TimeoutTimer_3BIT_MASK        <<  \
                                                                            TimeoutTimer_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define TimeoutTimer_CAPTURE_SHIFT                  (0u)
#define TimeoutTimer_COUNT_SHIFT                    (2u)
#define TimeoutTimer_RELOAD_SHIFT                   (4u)
#define TimeoutTimer_STOP_SHIFT                     (6u)
#define TimeoutTimer_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define TimeoutTimer_CAPTURE_MASK                   ((uint32)(TimeoutTimer_2BIT_MASK        <<  \
                                                                  TimeoutTimer_CAPTURE_SHIFT))
#define TimeoutTimer_COUNT_MASK                     ((uint32)(TimeoutTimer_2BIT_MASK        <<  \
                                                                  TimeoutTimer_COUNT_SHIFT))
#define TimeoutTimer_RELOAD_MASK                    ((uint32)(TimeoutTimer_2BIT_MASK        <<  \
                                                                  TimeoutTimer_RELOAD_SHIFT))
#define TimeoutTimer_STOP_MASK                      ((uint32)(TimeoutTimer_2BIT_MASK        <<  \
                                                                  TimeoutTimer_STOP_SHIFT))
#define TimeoutTimer_START_MASK                     ((uint32)(TimeoutTimer_2BIT_MASK        <<  \
                                                                  TimeoutTimer_START_SHIFT))

/* MASK */
#define TimeoutTimer_1BIT_MASK                      ((uint32)0x01u)
#define TimeoutTimer_2BIT_MASK                      ((uint32)0x03u)
#define TimeoutTimer_3BIT_MASK                      ((uint32)0x07u)
#define TimeoutTimer_6BIT_MASK                      ((uint32)0x3Fu)
#define TimeoutTimer_8BIT_MASK                      ((uint32)0xFFu)
#define TimeoutTimer_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define TimeoutTimer_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define TimeoutTimer_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(TimeoutTimer_QUAD_ENCODING_MODES     << TimeoutTimer_QUAD_MODE_SHIFT))       |\
         ((uint32)(TimeoutTimer_CONFIG                  << TimeoutTimer_MODE_SHIFT)))

#define TimeoutTimer_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(TimeoutTimer_PWM_STOP_EVENT          << TimeoutTimer_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(TimeoutTimer_PWM_OUT_INVERT          << TimeoutTimer_INV_OUT_SHIFT))         |\
         ((uint32)(TimeoutTimer_PWM_OUT_N_INVERT        << TimeoutTimer_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(TimeoutTimer_PWM_MODE                << TimeoutTimer_MODE_SHIFT)))

#define TimeoutTimer_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(TimeoutTimer_PWM_RUN_MODE         << TimeoutTimer_ONESHOT_SHIFT))
            
#define TimeoutTimer_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(TimeoutTimer_PWM_ALIGN            << TimeoutTimer_UPDOWN_SHIFT))

#define TimeoutTimer_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(TimeoutTimer_PWM_KILL_EVENT      << TimeoutTimer_PWM_SYNC_KILL_SHIFT))

#define TimeoutTimer_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(TimeoutTimer_PWM_DEAD_TIME_CYCLE  << TimeoutTimer_PRESCALER_SHIFT))

#define TimeoutTimer_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(TimeoutTimer_PWM_PRESCALER        << TimeoutTimer_PRESCALER_SHIFT))

#define TimeoutTimer_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(TimeoutTimer_TC_PRESCALER            << TimeoutTimer_PRESCALER_SHIFT))       |\
         ((uint32)(TimeoutTimer_TC_COUNTER_MODE         << TimeoutTimer_UPDOWN_SHIFT))          |\
         ((uint32)(TimeoutTimer_TC_RUN_MODE             << TimeoutTimer_ONESHOT_SHIFT))         |\
         ((uint32)(TimeoutTimer_TC_COMP_CAP_MODE        << TimeoutTimer_MODE_SHIFT)))
        
#define TimeoutTimer_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(TimeoutTimer_QUAD_PHIA_SIGNAL_MODE   << TimeoutTimer_COUNT_SHIFT))           |\
         ((uint32)(TimeoutTimer_QUAD_INDEX_SIGNAL_MODE  << TimeoutTimer_RELOAD_SHIFT))          |\
         ((uint32)(TimeoutTimer_QUAD_STOP_SIGNAL_MODE   << TimeoutTimer_STOP_SHIFT))            |\
         ((uint32)(TimeoutTimer_QUAD_PHIB_SIGNAL_MODE   << TimeoutTimer_START_SHIFT)))

#define TimeoutTimer_PWM_SIGNALS_MODES                                                              \
        (((uint32)(TimeoutTimer_PWM_SWITCH_SIGNAL_MODE  << TimeoutTimer_CAPTURE_SHIFT))         |\
         ((uint32)(TimeoutTimer_PWM_COUNT_SIGNAL_MODE   << TimeoutTimer_COUNT_SHIFT))           |\
         ((uint32)(TimeoutTimer_PWM_RELOAD_SIGNAL_MODE  << TimeoutTimer_RELOAD_SHIFT))          |\
         ((uint32)(TimeoutTimer_PWM_STOP_SIGNAL_MODE    << TimeoutTimer_STOP_SHIFT))            |\
         ((uint32)(TimeoutTimer_PWM_START_SIGNAL_MODE   << TimeoutTimer_START_SHIFT)))

#define TimeoutTimer_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(TimeoutTimer_TC_CAPTURE_SIGNAL_MODE  << TimeoutTimer_CAPTURE_SHIFT))         |\
         ((uint32)(TimeoutTimer_TC_COUNT_SIGNAL_MODE    << TimeoutTimer_COUNT_SHIFT))           |\
         ((uint32)(TimeoutTimer_TC_RELOAD_SIGNAL_MODE   << TimeoutTimer_RELOAD_SHIFT))          |\
         ((uint32)(TimeoutTimer_TC_STOP_SIGNAL_MODE     << TimeoutTimer_STOP_SHIFT))            |\
         ((uint32)(TimeoutTimer_TC_START_SIGNAL_MODE    << TimeoutTimer_START_SHIFT)))
        
#define TimeoutTimer_TIMER_UPDOWN_CNT_USED                                                          \
                ((TimeoutTimer__COUNT_UPDOWN0 == TimeoutTimer_TC_COUNTER_MODE)                  ||\
                 (TimeoutTimer__COUNT_UPDOWN1 == TimeoutTimer_TC_COUNTER_MODE))

#define TimeoutTimer_PWM_UPDOWN_CNT_USED                                                            \
                ((TimeoutTimer__CENTER == TimeoutTimer_PWM_ALIGN)                               ||\
                 (TimeoutTimer__ASYMMETRIC == TimeoutTimer_PWM_ALIGN))               
        
#define TimeoutTimer_PWM_PR_INIT_VALUE              (1u)
#define TimeoutTimer_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_TimeoutTimer_H */

/* [] END OF FILE */
