/*******************************************************************************
* File Name: SecondsTimer.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the SecondsTimer
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

#if !defined(CY_TCPWM_SecondsTimer_H)
#define CY_TCPWM_SecondsTimer_H


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
} SecondsTimer_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  SecondsTimer_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define SecondsTimer_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define SecondsTimer_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define SecondsTimer_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define SecondsTimer_QUAD_ENCODING_MODES            (0lu)
#define SecondsTimer_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define SecondsTimer_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define SecondsTimer_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define SecondsTimer_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define SecondsTimer_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define SecondsTimer_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define SecondsTimer_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define SecondsTimer_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define SecondsTimer_TC_RUN_MODE                    (0lu)
#define SecondsTimer_TC_COUNTER_MODE                (0lu)
#define SecondsTimer_TC_COMP_CAP_MODE               (2lu)
#define SecondsTimer_TC_PRESCALER                   (0lu)

/* Signal modes */
#define SecondsTimer_TC_RELOAD_SIGNAL_MODE          (0lu)
#define SecondsTimer_TC_COUNT_SIGNAL_MODE           (3lu)
#define SecondsTimer_TC_START_SIGNAL_MODE           (0lu)
#define SecondsTimer_TC_STOP_SIGNAL_MODE            (0lu)
#define SecondsTimer_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define SecondsTimer_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define SecondsTimer_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define SecondsTimer_TC_START_SIGNAL_PRESENT        (0lu)
#define SecondsTimer_TC_STOP_SIGNAL_PRESENT         (0lu)
#define SecondsTimer_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define SecondsTimer_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define SecondsTimer_PWM_KILL_EVENT                 (0lu)
#define SecondsTimer_PWM_STOP_EVENT                 (0lu)
#define SecondsTimer_PWM_MODE                       (4lu)
#define SecondsTimer_PWM_OUT_N_INVERT               (0lu)
#define SecondsTimer_PWM_OUT_INVERT                 (0lu)
#define SecondsTimer_PWM_ALIGN                      (0lu)
#define SecondsTimer_PWM_RUN_MODE                   (0lu)
#define SecondsTimer_PWM_DEAD_TIME_CYCLE            (0lu)
#define SecondsTimer_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define SecondsTimer_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define SecondsTimer_PWM_COUNT_SIGNAL_MODE          (3lu)
#define SecondsTimer_PWM_START_SIGNAL_MODE          (0lu)
#define SecondsTimer_PWM_STOP_SIGNAL_MODE           (0lu)
#define SecondsTimer_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define SecondsTimer_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define SecondsTimer_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define SecondsTimer_PWM_START_SIGNAL_PRESENT       (0lu)
#define SecondsTimer_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define SecondsTimer_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define SecondsTimer_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define SecondsTimer_TC_PERIOD_VALUE                (1000lu)
#define SecondsTimer_TC_COMPARE_VALUE               (65535lu)
#define SecondsTimer_TC_COMPARE_BUF_VALUE           (65535lu)
#define SecondsTimer_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define SecondsTimer_PWM_PERIOD_VALUE               (65535lu)
#define SecondsTimer_PWM_PERIOD_BUF_VALUE           (65535lu)
#define SecondsTimer_PWM_PERIOD_SWAP                (0lu)
#define SecondsTimer_PWM_COMPARE_VALUE              (65535lu)
#define SecondsTimer_PWM_COMPARE_BUF_VALUE          (65535lu)
#define SecondsTimer_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define SecondsTimer__LEFT 0
#define SecondsTimer__RIGHT 1
#define SecondsTimer__CENTER 2
#define SecondsTimer__ASYMMETRIC 3

#define SecondsTimer__X1 0
#define SecondsTimer__X2 1
#define SecondsTimer__X4 2

#define SecondsTimer__PWM 4
#define SecondsTimer__PWM_DT 5
#define SecondsTimer__PWM_PR 6

#define SecondsTimer__INVERSE 1
#define SecondsTimer__DIRECT 0

#define SecondsTimer__CAPTURE 2
#define SecondsTimer__COMPARE 0

#define SecondsTimer__TRIG_LEVEL 3
#define SecondsTimer__TRIG_RISING 0
#define SecondsTimer__TRIG_FALLING 1
#define SecondsTimer__TRIG_BOTH 2

#define SecondsTimer__INTR_MASK_TC 1
#define SecondsTimer__INTR_MASK_CC_MATCH 2
#define SecondsTimer__INTR_MASK_NONE 0
#define SecondsTimer__INTR_MASK_TC_CC 3

#define SecondsTimer__UNCONFIG 8
#define SecondsTimer__TIMER 1
#define SecondsTimer__QUAD 3
#define SecondsTimer__PWM_SEL 7

#define SecondsTimer__COUNT_UP 0
#define SecondsTimer__COUNT_DOWN 1
#define SecondsTimer__COUNT_UPDOWN0 2
#define SecondsTimer__COUNT_UPDOWN1 3


/* Prescaler */
#define SecondsTimer_PRESCALE_DIVBY1                ((uint32)(0u << SecondsTimer_PRESCALER_SHIFT))
#define SecondsTimer_PRESCALE_DIVBY2                ((uint32)(1u << SecondsTimer_PRESCALER_SHIFT))
#define SecondsTimer_PRESCALE_DIVBY4                ((uint32)(2u << SecondsTimer_PRESCALER_SHIFT))
#define SecondsTimer_PRESCALE_DIVBY8                ((uint32)(3u << SecondsTimer_PRESCALER_SHIFT))
#define SecondsTimer_PRESCALE_DIVBY16               ((uint32)(4u << SecondsTimer_PRESCALER_SHIFT))
#define SecondsTimer_PRESCALE_DIVBY32               ((uint32)(5u << SecondsTimer_PRESCALER_SHIFT))
#define SecondsTimer_PRESCALE_DIVBY64               ((uint32)(6u << SecondsTimer_PRESCALER_SHIFT))
#define SecondsTimer_PRESCALE_DIVBY128              ((uint32)(7u << SecondsTimer_PRESCALER_SHIFT))

/* TCPWM set modes */
#define SecondsTimer_MODE_TIMER_COMPARE             ((uint32)(SecondsTimer__COMPARE         <<  \
                                                                  SecondsTimer_MODE_SHIFT))
#define SecondsTimer_MODE_TIMER_CAPTURE             ((uint32)(SecondsTimer__CAPTURE         <<  \
                                                                  SecondsTimer_MODE_SHIFT))
#define SecondsTimer_MODE_QUAD                      ((uint32)(SecondsTimer__QUAD            <<  \
                                                                  SecondsTimer_MODE_SHIFT))
#define SecondsTimer_MODE_PWM                       ((uint32)(SecondsTimer__PWM             <<  \
                                                                  SecondsTimer_MODE_SHIFT))
#define SecondsTimer_MODE_PWM_DT                    ((uint32)(SecondsTimer__PWM_DT          <<  \
                                                                  SecondsTimer_MODE_SHIFT))
#define SecondsTimer_MODE_PWM_PR                    ((uint32)(SecondsTimer__PWM_PR          <<  \
                                                                  SecondsTimer_MODE_SHIFT))

/* Quad Modes */
#define SecondsTimer_MODE_X1                        ((uint32)(SecondsTimer__X1              <<  \
                                                                  SecondsTimer_QUAD_MODE_SHIFT))
#define SecondsTimer_MODE_X2                        ((uint32)(SecondsTimer__X2              <<  \
                                                                  SecondsTimer_QUAD_MODE_SHIFT))
#define SecondsTimer_MODE_X4                        ((uint32)(SecondsTimer__X4              <<  \
                                                                  SecondsTimer_QUAD_MODE_SHIFT))

/* Counter modes */
#define SecondsTimer_COUNT_UP                       ((uint32)(SecondsTimer__COUNT_UP        <<  \
                                                                  SecondsTimer_UPDOWN_SHIFT))
#define SecondsTimer_COUNT_DOWN                     ((uint32)(SecondsTimer__COUNT_DOWN      <<  \
                                                                  SecondsTimer_UPDOWN_SHIFT))
#define SecondsTimer_COUNT_UPDOWN0                  ((uint32)(SecondsTimer__COUNT_UPDOWN0   <<  \
                                                                  SecondsTimer_UPDOWN_SHIFT))
#define SecondsTimer_COUNT_UPDOWN1                  ((uint32)(SecondsTimer__COUNT_UPDOWN1   <<  \
                                                                  SecondsTimer_UPDOWN_SHIFT))

/* PWM output invert */
#define SecondsTimer_INVERT_LINE                    ((uint32)(SecondsTimer__INVERSE         <<  \
                                                                  SecondsTimer_INV_OUT_SHIFT))
#define SecondsTimer_INVERT_LINE_N                  ((uint32)(SecondsTimer__INVERSE         <<  \
                                                                  SecondsTimer_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define SecondsTimer_TRIG_RISING                    ((uint32)SecondsTimer__TRIG_RISING)
#define SecondsTimer_TRIG_FALLING                   ((uint32)SecondsTimer__TRIG_FALLING)
#define SecondsTimer_TRIG_BOTH                      ((uint32)SecondsTimer__TRIG_BOTH)
#define SecondsTimer_TRIG_LEVEL                     ((uint32)SecondsTimer__TRIG_LEVEL)

/* Interrupt mask */
#define SecondsTimer_INTR_MASK_TC                   ((uint32)SecondsTimer__INTR_MASK_TC)
#define SecondsTimer_INTR_MASK_CC_MATCH             ((uint32)SecondsTimer__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define SecondsTimer_CC_MATCH_SET                   (0x00u)
#define SecondsTimer_CC_MATCH_CLEAR                 (0x01u)
#define SecondsTimer_CC_MATCH_INVERT                (0x02u)
#define SecondsTimer_CC_MATCH_NO_CHANGE             (0x03u)
#define SecondsTimer_OVERLOW_SET                    (0x00u)
#define SecondsTimer_OVERLOW_CLEAR                  (0x04u)
#define SecondsTimer_OVERLOW_INVERT                 (0x08u)
#define SecondsTimer_OVERLOW_NO_CHANGE              (0x0Cu)
#define SecondsTimer_UNDERFLOW_SET                  (0x00u)
#define SecondsTimer_UNDERFLOW_CLEAR                (0x10u)
#define SecondsTimer_UNDERFLOW_INVERT               (0x20u)
#define SecondsTimer_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define SecondsTimer_PWM_MODE_LEFT                  (SecondsTimer_CC_MATCH_CLEAR        |   \
                                                         SecondsTimer_OVERLOW_SET           |   \
                                                         SecondsTimer_UNDERFLOW_NO_CHANGE)
#define SecondsTimer_PWM_MODE_RIGHT                 (SecondsTimer_CC_MATCH_SET          |   \
                                                         SecondsTimer_OVERLOW_NO_CHANGE     |   \
                                                         SecondsTimer_UNDERFLOW_CLEAR)
#define SecondsTimer_PWM_MODE_ASYM                  (SecondsTimer_CC_MATCH_INVERT       |   \
                                                         SecondsTimer_OVERLOW_SET           |   \
                                                         SecondsTimer_UNDERFLOW_CLEAR)

#if (SecondsTimer_CY_TCPWM_V2)
    #if(SecondsTimer_CY_TCPWM_4000)
        #define SecondsTimer_PWM_MODE_CENTER                (SecondsTimer_CC_MATCH_INVERT       |   \
                                                                 SecondsTimer_OVERLOW_NO_CHANGE     |   \
                                                                 SecondsTimer_UNDERFLOW_CLEAR)
    #else
        #define SecondsTimer_PWM_MODE_CENTER                (SecondsTimer_CC_MATCH_INVERT       |   \
                                                                 SecondsTimer_OVERLOW_SET           |   \
                                                                 SecondsTimer_UNDERFLOW_CLEAR)
    #endif /* (SecondsTimer_CY_TCPWM_4000) */
#else
    #define SecondsTimer_PWM_MODE_CENTER                (SecondsTimer_CC_MATCH_INVERT       |   \
                                                             SecondsTimer_OVERLOW_NO_CHANGE     |   \
                                                             SecondsTimer_UNDERFLOW_CLEAR)
#endif /* (SecondsTimer_CY_TCPWM_NEW) */

/* Command operations without condition */
#define SecondsTimer_CMD_CAPTURE                    (0u)
#define SecondsTimer_CMD_RELOAD                     (8u)
#define SecondsTimer_CMD_STOP                       (16u)
#define SecondsTimer_CMD_START                      (24u)

/* Status */
#define SecondsTimer_STATUS_DOWN                    (1u)
#define SecondsTimer_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   SecondsTimer_Init(void);
void   SecondsTimer_Enable(void);
void   SecondsTimer_Start(void);
void   SecondsTimer_Stop(void);

void   SecondsTimer_SetMode(uint32 mode);
void   SecondsTimer_SetCounterMode(uint32 counterMode);
void   SecondsTimer_SetPWMMode(uint32 modeMask);
void   SecondsTimer_SetQDMode(uint32 qdMode);

void   SecondsTimer_SetPrescaler(uint32 prescaler);
void   SecondsTimer_TriggerCommand(uint32 mask, uint32 command);
void   SecondsTimer_SetOneShot(uint32 oneShotEnable);
uint32 SecondsTimer_ReadStatus(void);

void   SecondsTimer_SetPWMSyncKill(uint32 syncKillEnable);
void   SecondsTimer_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   SecondsTimer_SetPWMDeadTime(uint32 deadTime);
void   SecondsTimer_SetPWMInvert(uint32 mask);

void   SecondsTimer_SetInterruptMode(uint32 interruptMask);
uint32 SecondsTimer_GetInterruptSourceMasked(void);
uint32 SecondsTimer_GetInterruptSource(void);
void   SecondsTimer_ClearInterrupt(uint32 interruptMask);
void   SecondsTimer_SetInterrupt(uint32 interruptMask);

void   SecondsTimer_WriteCounter(uint32 count);
uint32 SecondsTimer_ReadCounter(void);

uint32 SecondsTimer_ReadCapture(void);
uint32 SecondsTimer_ReadCaptureBuf(void);

void   SecondsTimer_WritePeriod(uint32 period);
uint32 SecondsTimer_ReadPeriod(void);
void   SecondsTimer_WritePeriodBuf(uint32 periodBuf);
uint32 SecondsTimer_ReadPeriodBuf(void);

void   SecondsTimer_WriteCompare(uint32 compare);
uint32 SecondsTimer_ReadCompare(void);
void   SecondsTimer_WriteCompareBuf(uint32 compareBuf);
uint32 SecondsTimer_ReadCompareBuf(void);

void   SecondsTimer_SetPeriodSwap(uint32 swapEnable);
void   SecondsTimer_SetCompareSwap(uint32 swapEnable);

void   SecondsTimer_SetCaptureMode(uint32 triggerMode);
void   SecondsTimer_SetReloadMode(uint32 triggerMode);
void   SecondsTimer_SetStartMode(uint32 triggerMode);
void   SecondsTimer_SetStopMode(uint32 triggerMode);
void   SecondsTimer_SetCountMode(uint32 triggerMode);

void   SecondsTimer_SaveConfig(void);
void   SecondsTimer_RestoreConfig(void);
void   SecondsTimer_Sleep(void);
void   SecondsTimer_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define SecondsTimer_BLOCK_CONTROL_REG              (*(reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define SecondsTimer_BLOCK_CONTROL_PTR              ( (reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define SecondsTimer_COMMAND_REG                    (*(reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define SecondsTimer_COMMAND_PTR                    ( (reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define SecondsTimer_INTRRUPT_CAUSE_REG             (*(reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define SecondsTimer_INTRRUPT_CAUSE_PTR             ( (reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define SecondsTimer_CONTROL_REG                    (*(reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__CTRL )
#define SecondsTimer_CONTROL_PTR                    ( (reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__CTRL )
#define SecondsTimer_STATUS_REG                     (*(reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__STATUS )
#define SecondsTimer_STATUS_PTR                     ( (reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__STATUS )
#define SecondsTimer_COUNTER_REG                    (*(reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__COUNTER )
#define SecondsTimer_COUNTER_PTR                    ( (reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__COUNTER )
#define SecondsTimer_COMP_CAP_REG                   (*(reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__CC )
#define SecondsTimer_COMP_CAP_PTR                   ( (reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__CC )
#define SecondsTimer_COMP_CAP_BUF_REG               (*(reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define SecondsTimer_COMP_CAP_BUF_PTR               ( (reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define SecondsTimer_PERIOD_REG                     (*(reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__PERIOD )
#define SecondsTimer_PERIOD_PTR                     ( (reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__PERIOD )
#define SecondsTimer_PERIOD_BUF_REG                 (*(reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define SecondsTimer_PERIOD_BUF_PTR                 ( (reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define SecondsTimer_TRIG_CONTROL0_REG              (*(reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define SecondsTimer_TRIG_CONTROL0_PTR              ( (reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define SecondsTimer_TRIG_CONTROL1_REG              (*(reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define SecondsTimer_TRIG_CONTROL1_PTR              ( (reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define SecondsTimer_TRIG_CONTROL2_REG              (*(reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define SecondsTimer_TRIG_CONTROL2_PTR              ( (reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define SecondsTimer_INTERRUPT_REQ_REG              (*(reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__INTR )
#define SecondsTimer_INTERRUPT_REQ_PTR              ( (reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__INTR )
#define SecondsTimer_INTERRUPT_SET_REG              (*(reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define SecondsTimer_INTERRUPT_SET_PTR              ( (reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define SecondsTimer_INTERRUPT_MASK_REG             (*(reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define SecondsTimer_INTERRUPT_MASK_PTR             ( (reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define SecondsTimer_INTERRUPT_MASKED_REG           (*(reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__INTR_MASKED )
#define SecondsTimer_INTERRUPT_MASKED_PTR           ( (reg32 *) SecondsTimer_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define SecondsTimer_MASK                           ((uint32)SecondsTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define SecondsTimer_RELOAD_CC_SHIFT                (0u)
#define SecondsTimer_RELOAD_PERIOD_SHIFT            (1u)
#define SecondsTimer_PWM_SYNC_KILL_SHIFT            (2u)
#define SecondsTimer_PWM_STOP_KILL_SHIFT            (3u)
#define SecondsTimer_PRESCALER_SHIFT                (8u)
#define SecondsTimer_UPDOWN_SHIFT                   (16u)
#define SecondsTimer_ONESHOT_SHIFT                  (18u)
#define SecondsTimer_QUAD_MODE_SHIFT                (20u)
#define SecondsTimer_INV_OUT_SHIFT                  (20u)
#define SecondsTimer_INV_COMPL_OUT_SHIFT            (21u)
#define SecondsTimer_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define SecondsTimer_RELOAD_CC_MASK                 ((uint32)(SecondsTimer_1BIT_MASK        <<  \
                                                                            SecondsTimer_RELOAD_CC_SHIFT))
#define SecondsTimer_RELOAD_PERIOD_MASK             ((uint32)(SecondsTimer_1BIT_MASK        <<  \
                                                                            SecondsTimer_RELOAD_PERIOD_SHIFT))
#define SecondsTimer_PWM_SYNC_KILL_MASK             ((uint32)(SecondsTimer_1BIT_MASK        <<  \
                                                                            SecondsTimer_PWM_SYNC_KILL_SHIFT))
#define SecondsTimer_PWM_STOP_KILL_MASK             ((uint32)(SecondsTimer_1BIT_MASK        <<  \
                                                                            SecondsTimer_PWM_STOP_KILL_SHIFT))
#define SecondsTimer_PRESCALER_MASK                 ((uint32)(SecondsTimer_8BIT_MASK        <<  \
                                                                            SecondsTimer_PRESCALER_SHIFT))
#define SecondsTimer_UPDOWN_MASK                    ((uint32)(SecondsTimer_2BIT_MASK        <<  \
                                                                            SecondsTimer_UPDOWN_SHIFT))
#define SecondsTimer_ONESHOT_MASK                   ((uint32)(SecondsTimer_1BIT_MASK        <<  \
                                                                            SecondsTimer_ONESHOT_SHIFT))
#define SecondsTimer_QUAD_MODE_MASK                 ((uint32)(SecondsTimer_3BIT_MASK        <<  \
                                                                            SecondsTimer_QUAD_MODE_SHIFT))
#define SecondsTimer_INV_OUT_MASK                   ((uint32)(SecondsTimer_2BIT_MASK        <<  \
                                                                            SecondsTimer_INV_OUT_SHIFT))
#define SecondsTimer_MODE_MASK                      ((uint32)(SecondsTimer_3BIT_MASK        <<  \
                                                                            SecondsTimer_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define SecondsTimer_CAPTURE_SHIFT                  (0u)
#define SecondsTimer_COUNT_SHIFT                    (2u)
#define SecondsTimer_RELOAD_SHIFT                   (4u)
#define SecondsTimer_STOP_SHIFT                     (6u)
#define SecondsTimer_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define SecondsTimer_CAPTURE_MASK                   ((uint32)(SecondsTimer_2BIT_MASK        <<  \
                                                                  SecondsTimer_CAPTURE_SHIFT))
#define SecondsTimer_COUNT_MASK                     ((uint32)(SecondsTimer_2BIT_MASK        <<  \
                                                                  SecondsTimer_COUNT_SHIFT))
#define SecondsTimer_RELOAD_MASK                    ((uint32)(SecondsTimer_2BIT_MASK        <<  \
                                                                  SecondsTimer_RELOAD_SHIFT))
#define SecondsTimer_STOP_MASK                      ((uint32)(SecondsTimer_2BIT_MASK        <<  \
                                                                  SecondsTimer_STOP_SHIFT))
#define SecondsTimer_START_MASK                     ((uint32)(SecondsTimer_2BIT_MASK        <<  \
                                                                  SecondsTimer_START_SHIFT))

/* MASK */
#define SecondsTimer_1BIT_MASK                      ((uint32)0x01u)
#define SecondsTimer_2BIT_MASK                      ((uint32)0x03u)
#define SecondsTimer_3BIT_MASK                      ((uint32)0x07u)
#define SecondsTimer_6BIT_MASK                      ((uint32)0x3Fu)
#define SecondsTimer_8BIT_MASK                      ((uint32)0xFFu)
#define SecondsTimer_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define SecondsTimer_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define SecondsTimer_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(SecondsTimer_QUAD_ENCODING_MODES     << SecondsTimer_QUAD_MODE_SHIFT))       |\
         ((uint32)(SecondsTimer_CONFIG                  << SecondsTimer_MODE_SHIFT)))

#define SecondsTimer_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(SecondsTimer_PWM_STOP_EVENT          << SecondsTimer_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(SecondsTimer_PWM_OUT_INVERT          << SecondsTimer_INV_OUT_SHIFT))         |\
         ((uint32)(SecondsTimer_PWM_OUT_N_INVERT        << SecondsTimer_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(SecondsTimer_PWM_MODE                << SecondsTimer_MODE_SHIFT)))

#define SecondsTimer_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(SecondsTimer_PWM_RUN_MODE         << SecondsTimer_ONESHOT_SHIFT))
            
#define SecondsTimer_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(SecondsTimer_PWM_ALIGN            << SecondsTimer_UPDOWN_SHIFT))

#define SecondsTimer_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(SecondsTimer_PWM_KILL_EVENT      << SecondsTimer_PWM_SYNC_KILL_SHIFT))

#define SecondsTimer_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(SecondsTimer_PWM_DEAD_TIME_CYCLE  << SecondsTimer_PRESCALER_SHIFT))

#define SecondsTimer_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(SecondsTimer_PWM_PRESCALER        << SecondsTimer_PRESCALER_SHIFT))

#define SecondsTimer_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(SecondsTimer_TC_PRESCALER            << SecondsTimer_PRESCALER_SHIFT))       |\
         ((uint32)(SecondsTimer_TC_COUNTER_MODE         << SecondsTimer_UPDOWN_SHIFT))          |\
         ((uint32)(SecondsTimer_TC_RUN_MODE             << SecondsTimer_ONESHOT_SHIFT))         |\
         ((uint32)(SecondsTimer_TC_COMP_CAP_MODE        << SecondsTimer_MODE_SHIFT)))
        
#define SecondsTimer_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(SecondsTimer_QUAD_PHIA_SIGNAL_MODE   << SecondsTimer_COUNT_SHIFT))           |\
         ((uint32)(SecondsTimer_QUAD_INDEX_SIGNAL_MODE  << SecondsTimer_RELOAD_SHIFT))          |\
         ((uint32)(SecondsTimer_QUAD_STOP_SIGNAL_MODE   << SecondsTimer_STOP_SHIFT))            |\
         ((uint32)(SecondsTimer_QUAD_PHIB_SIGNAL_MODE   << SecondsTimer_START_SHIFT)))

#define SecondsTimer_PWM_SIGNALS_MODES                                                              \
        (((uint32)(SecondsTimer_PWM_SWITCH_SIGNAL_MODE  << SecondsTimer_CAPTURE_SHIFT))         |\
         ((uint32)(SecondsTimer_PWM_COUNT_SIGNAL_MODE   << SecondsTimer_COUNT_SHIFT))           |\
         ((uint32)(SecondsTimer_PWM_RELOAD_SIGNAL_MODE  << SecondsTimer_RELOAD_SHIFT))          |\
         ((uint32)(SecondsTimer_PWM_STOP_SIGNAL_MODE    << SecondsTimer_STOP_SHIFT))            |\
         ((uint32)(SecondsTimer_PWM_START_SIGNAL_MODE   << SecondsTimer_START_SHIFT)))

#define SecondsTimer_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(SecondsTimer_TC_CAPTURE_SIGNAL_MODE  << SecondsTimer_CAPTURE_SHIFT))         |\
         ((uint32)(SecondsTimer_TC_COUNT_SIGNAL_MODE    << SecondsTimer_COUNT_SHIFT))           |\
         ((uint32)(SecondsTimer_TC_RELOAD_SIGNAL_MODE   << SecondsTimer_RELOAD_SHIFT))          |\
         ((uint32)(SecondsTimer_TC_STOP_SIGNAL_MODE     << SecondsTimer_STOP_SHIFT))            |\
         ((uint32)(SecondsTimer_TC_START_SIGNAL_MODE    << SecondsTimer_START_SHIFT)))
        
#define SecondsTimer_TIMER_UPDOWN_CNT_USED                                                          \
                ((SecondsTimer__COUNT_UPDOWN0 == SecondsTimer_TC_COUNTER_MODE)                  ||\
                 (SecondsTimer__COUNT_UPDOWN1 == SecondsTimer_TC_COUNTER_MODE))

#define SecondsTimer_PWM_UPDOWN_CNT_USED                                                            \
                ((SecondsTimer__CENTER == SecondsTimer_PWM_ALIGN)                               ||\
                 (SecondsTimer__ASYMMETRIC == SecondsTimer_PWM_ALIGN))               
        
#define SecondsTimer_PWM_PR_INIT_VALUE              (1u)
#define SecondsTimer_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_SecondsTimer_H */

/* [] END OF FILE */
