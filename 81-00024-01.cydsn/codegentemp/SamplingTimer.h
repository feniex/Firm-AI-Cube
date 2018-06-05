/*******************************************************************************
* File Name: SamplingTimer.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the SamplingTimer
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

#if !defined(CY_TCPWM_SamplingTimer_H)
#define CY_TCPWM_SamplingTimer_H


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
} SamplingTimer_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  SamplingTimer_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define SamplingTimer_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define SamplingTimer_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define SamplingTimer_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define SamplingTimer_QUAD_ENCODING_MODES            (0lu)
#define SamplingTimer_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define SamplingTimer_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define SamplingTimer_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define SamplingTimer_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define SamplingTimer_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define SamplingTimer_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define SamplingTimer_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define SamplingTimer_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define SamplingTimer_TC_RUN_MODE                    (0lu)
#define SamplingTimer_TC_COUNTER_MODE                (0lu)
#define SamplingTimer_TC_COMP_CAP_MODE               (2lu)
#define SamplingTimer_TC_PRESCALER                   (0lu)

/* Signal modes */
#define SamplingTimer_TC_RELOAD_SIGNAL_MODE          (0lu)
#define SamplingTimer_TC_COUNT_SIGNAL_MODE           (3lu)
#define SamplingTimer_TC_START_SIGNAL_MODE           (0lu)
#define SamplingTimer_TC_STOP_SIGNAL_MODE            (0lu)
#define SamplingTimer_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define SamplingTimer_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define SamplingTimer_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define SamplingTimer_TC_START_SIGNAL_PRESENT        (0lu)
#define SamplingTimer_TC_STOP_SIGNAL_PRESENT         (0lu)
#define SamplingTimer_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define SamplingTimer_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define SamplingTimer_PWM_KILL_EVENT                 (0lu)
#define SamplingTimer_PWM_STOP_EVENT                 (0lu)
#define SamplingTimer_PWM_MODE                       (4lu)
#define SamplingTimer_PWM_OUT_N_INVERT               (0lu)
#define SamplingTimer_PWM_OUT_INVERT                 (0lu)
#define SamplingTimer_PWM_ALIGN                      (0lu)
#define SamplingTimer_PWM_RUN_MODE                   (0lu)
#define SamplingTimer_PWM_DEAD_TIME_CYCLE            (0lu)
#define SamplingTimer_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define SamplingTimer_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define SamplingTimer_PWM_COUNT_SIGNAL_MODE          (3lu)
#define SamplingTimer_PWM_START_SIGNAL_MODE          (0lu)
#define SamplingTimer_PWM_STOP_SIGNAL_MODE           (0lu)
#define SamplingTimer_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define SamplingTimer_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define SamplingTimer_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define SamplingTimer_PWM_START_SIGNAL_PRESENT       (0lu)
#define SamplingTimer_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define SamplingTimer_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define SamplingTimer_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define SamplingTimer_TC_PERIOD_VALUE                (12lu)
#define SamplingTimer_TC_COMPARE_VALUE               (65535lu)
#define SamplingTimer_TC_COMPARE_BUF_VALUE           (65535lu)
#define SamplingTimer_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define SamplingTimer_PWM_PERIOD_VALUE               (65535lu)
#define SamplingTimer_PWM_PERIOD_BUF_VALUE           (65535lu)
#define SamplingTimer_PWM_PERIOD_SWAP                (0lu)
#define SamplingTimer_PWM_COMPARE_VALUE              (65535lu)
#define SamplingTimer_PWM_COMPARE_BUF_VALUE          (65535lu)
#define SamplingTimer_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define SamplingTimer__LEFT 0
#define SamplingTimer__RIGHT 1
#define SamplingTimer__CENTER 2
#define SamplingTimer__ASYMMETRIC 3

#define SamplingTimer__X1 0
#define SamplingTimer__X2 1
#define SamplingTimer__X4 2

#define SamplingTimer__PWM 4
#define SamplingTimer__PWM_DT 5
#define SamplingTimer__PWM_PR 6

#define SamplingTimer__INVERSE 1
#define SamplingTimer__DIRECT 0

#define SamplingTimer__CAPTURE 2
#define SamplingTimer__COMPARE 0

#define SamplingTimer__TRIG_LEVEL 3
#define SamplingTimer__TRIG_RISING 0
#define SamplingTimer__TRIG_FALLING 1
#define SamplingTimer__TRIG_BOTH 2

#define SamplingTimer__INTR_MASK_TC 1
#define SamplingTimer__INTR_MASK_CC_MATCH 2
#define SamplingTimer__INTR_MASK_NONE 0
#define SamplingTimer__INTR_MASK_TC_CC 3

#define SamplingTimer__UNCONFIG 8
#define SamplingTimer__TIMER 1
#define SamplingTimer__QUAD 3
#define SamplingTimer__PWM_SEL 7

#define SamplingTimer__COUNT_UP 0
#define SamplingTimer__COUNT_DOWN 1
#define SamplingTimer__COUNT_UPDOWN0 2
#define SamplingTimer__COUNT_UPDOWN1 3


/* Prescaler */
#define SamplingTimer_PRESCALE_DIVBY1                ((uint32)(0u << SamplingTimer_PRESCALER_SHIFT))
#define SamplingTimer_PRESCALE_DIVBY2                ((uint32)(1u << SamplingTimer_PRESCALER_SHIFT))
#define SamplingTimer_PRESCALE_DIVBY4                ((uint32)(2u << SamplingTimer_PRESCALER_SHIFT))
#define SamplingTimer_PRESCALE_DIVBY8                ((uint32)(3u << SamplingTimer_PRESCALER_SHIFT))
#define SamplingTimer_PRESCALE_DIVBY16               ((uint32)(4u << SamplingTimer_PRESCALER_SHIFT))
#define SamplingTimer_PRESCALE_DIVBY32               ((uint32)(5u << SamplingTimer_PRESCALER_SHIFT))
#define SamplingTimer_PRESCALE_DIVBY64               ((uint32)(6u << SamplingTimer_PRESCALER_SHIFT))
#define SamplingTimer_PRESCALE_DIVBY128              ((uint32)(7u << SamplingTimer_PRESCALER_SHIFT))

/* TCPWM set modes */
#define SamplingTimer_MODE_TIMER_COMPARE             ((uint32)(SamplingTimer__COMPARE         <<  \
                                                                  SamplingTimer_MODE_SHIFT))
#define SamplingTimer_MODE_TIMER_CAPTURE             ((uint32)(SamplingTimer__CAPTURE         <<  \
                                                                  SamplingTimer_MODE_SHIFT))
#define SamplingTimer_MODE_QUAD                      ((uint32)(SamplingTimer__QUAD            <<  \
                                                                  SamplingTimer_MODE_SHIFT))
#define SamplingTimer_MODE_PWM                       ((uint32)(SamplingTimer__PWM             <<  \
                                                                  SamplingTimer_MODE_SHIFT))
#define SamplingTimer_MODE_PWM_DT                    ((uint32)(SamplingTimer__PWM_DT          <<  \
                                                                  SamplingTimer_MODE_SHIFT))
#define SamplingTimer_MODE_PWM_PR                    ((uint32)(SamplingTimer__PWM_PR          <<  \
                                                                  SamplingTimer_MODE_SHIFT))

/* Quad Modes */
#define SamplingTimer_MODE_X1                        ((uint32)(SamplingTimer__X1              <<  \
                                                                  SamplingTimer_QUAD_MODE_SHIFT))
#define SamplingTimer_MODE_X2                        ((uint32)(SamplingTimer__X2              <<  \
                                                                  SamplingTimer_QUAD_MODE_SHIFT))
#define SamplingTimer_MODE_X4                        ((uint32)(SamplingTimer__X4              <<  \
                                                                  SamplingTimer_QUAD_MODE_SHIFT))

/* Counter modes */
#define SamplingTimer_COUNT_UP                       ((uint32)(SamplingTimer__COUNT_UP        <<  \
                                                                  SamplingTimer_UPDOWN_SHIFT))
#define SamplingTimer_COUNT_DOWN                     ((uint32)(SamplingTimer__COUNT_DOWN      <<  \
                                                                  SamplingTimer_UPDOWN_SHIFT))
#define SamplingTimer_COUNT_UPDOWN0                  ((uint32)(SamplingTimer__COUNT_UPDOWN0   <<  \
                                                                  SamplingTimer_UPDOWN_SHIFT))
#define SamplingTimer_COUNT_UPDOWN1                  ((uint32)(SamplingTimer__COUNT_UPDOWN1   <<  \
                                                                  SamplingTimer_UPDOWN_SHIFT))

/* PWM output invert */
#define SamplingTimer_INVERT_LINE                    ((uint32)(SamplingTimer__INVERSE         <<  \
                                                                  SamplingTimer_INV_OUT_SHIFT))
#define SamplingTimer_INVERT_LINE_N                  ((uint32)(SamplingTimer__INVERSE         <<  \
                                                                  SamplingTimer_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define SamplingTimer_TRIG_RISING                    ((uint32)SamplingTimer__TRIG_RISING)
#define SamplingTimer_TRIG_FALLING                   ((uint32)SamplingTimer__TRIG_FALLING)
#define SamplingTimer_TRIG_BOTH                      ((uint32)SamplingTimer__TRIG_BOTH)
#define SamplingTimer_TRIG_LEVEL                     ((uint32)SamplingTimer__TRIG_LEVEL)

/* Interrupt mask */
#define SamplingTimer_INTR_MASK_TC                   ((uint32)SamplingTimer__INTR_MASK_TC)
#define SamplingTimer_INTR_MASK_CC_MATCH             ((uint32)SamplingTimer__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define SamplingTimer_CC_MATCH_SET                   (0x00u)
#define SamplingTimer_CC_MATCH_CLEAR                 (0x01u)
#define SamplingTimer_CC_MATCH_INVERT                (0x02u)
#define SamplingTimer_CC_MATCH_NO_CHANGE             (0x03u)
#define SamplingTimer_OVERLOW_SET                    (0x00u)
#define SamplingTimer_OVERLOW_CLEAR                  (0x04u)
#define SamplingTimer_OVERLOW_INVERT                 (0x08u)
#define SamplingTimer_OVERLOW_NO_CHANGE              (0x0Cu)
#define SamplingTimer_UNDERFLOW_SET                  (0x00u)
#define SamplingTimer_UNDERFLOW_CLEAR                (0x10u)
#define SamplingTimer_UNDERFLOW_INVERT               (0x20u)
#define SamplingTimer_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define SamplingTimer_PWM_MODE_LEFT                  (SamplingTimer_CC_MATCH_CLEAR        |   \
                                                         SamplingTimer_OVERLOW_SET           |   \
                                                         SamplingTimer_UNDERFLOW_NO_CHANGE)
#define SamplingTimer_PWM_MODE_RIGHT                 (SamplingTimer_CC_MATCH_SET          |   \
                                                         SamplingTimer_OVERLOW_NO_CHANGE     |   \
                                                         SamplingTimer_UNDERFLOW_CLEAR)
#define SamplingTimer_PWM_MODE_ASYM                  (SamplingTimer_CC_MATCH_INVERT       |   \
                                                         SamplingTimer_OVERLOW_SET           |   \
                                                         SamplingTimer_UNDERFLOW_CLEAR)

#if (SamplingTimer_CY_TCPWM_V2)
    #if(SamplingTimer_CY_TCPWM_4000)
        #define SamplingTimer_PWM_MODE_CENTER                (SamplingTimer_CC_MATCH_INVERT       |   \
                                                                 SamplingTimer_OVERLOW_NO_CHANGE     |   \
                                                                 SamplingTimer_UNDERFLOW_CLEAR)
    #else
        #define SamplingTimer_PWM_MODE_CENTER                (SamplingTimer_CC_MATCH_INVERT       |   \
                                                                 SamplingTimer_OVERLOW_SET           |   \
                                                                 SamplingTimer_UNDERFLOW_CLEAR)
    #endif /* (SamplingTimer_CY_TCPWM_4000) */
#else
    #define SamplingTimer_PWM_MODE_CENTER                (SamplingTimer_CC_MATCH_INVERT       |   \
                                                             SamplingTimer_OVERLOW_NO_CHANGE     |   \
                                                             SamplingTimer_UNDERFLOW_CLEAR)
#endif /* (SamplingTimer_CY_TCPWM_NEW) */

/* Command operations without condition */
#define SamplingTimer_CMD_CAPTURE                    (0u)
#define SamplingTimer_CMD_RELOAD                     (8u)
#define SamplingTimer_CMD_STOP                       (16u)
#define SamplingTimer_CMD_START                      (24u)

/* Status */
#define SamplingTimer_STATUS_DOWN                    (1u)
#define SamplingTimer_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   SamplingTimer_Init(void);
void   SamplingTimer_Enable(void);
void   SamplingTimer_Start(void);
void   SamplingTimer_Stop(void);

void   SamplingTimer_SetMode(uint32 mode);
void   SamplingTimer_SetCounterMode(uint32 counterMode);
void   SamplingTimer_SetPWMMode(uint32 modeMask);
void   SamplingTimer_SetQDMode(uint32 qdMode);

void   SamplingTimer_SetPrescaler(uint32 prescaler);
void   SamplingTimer_TriggerCommand(uint32 mask, uint32 command);
void   SamplingTimer_SetOneShot(uint32 oneShotEnable);
uint32 SamplingTimer_ReadStatus(void);

void   SamplingTimer_SetPWMSyncKill(uint32 syncKillEnable);
void   SamplingTimer_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   SamplingTimer_SetPWMDeadTime(uint32 deadTime);
void   SamplingTimer_SetPWMInvert(uint32 mask);

void   SamplingTimer_SetInterruptMode(uint32 interruptMask);
uint32 SamplingTimer_GetInterruptSourceMasked(void);
uint32 SamplingTimer_GetInterruptSource(void);
void   SamplingTimer_ClearInterrupt(uint32 interruptMask);
void   SamplingTimer_SetInterrupt(uint32 interruptMask);

void   SamplingTimer_WriteCounter(uint32 count);
uint32 SamplingTimer_ReadCounter(void);

uint32 SamplingTimer_ReadCapture(void);
uint32 SamplingTimer_ReadCaptureBuf(void);

void   SamplingTimer_WritePeriod(uint32 period);
uint32 SamplingTimer_ReadPeriod(void);
void   SamplingTimer_WritePeriodBuf(uint32 periodBuf);
uint32 SamplingTimer_ReadPeriodBuf(void);

void   SamplingTimer_WriteCompare(uint32 compare);
uint32 SamplingTimer_ReadCompare(void);
void   SamplingTimer_WriteCompareBuf(uint32 compareBuf);
uint32 SamplingTimer_ReadCompareBuf(void);

void   SamplingTimer_SetPeriodSwap(uint32 swapEnable);
void   SamplingTimer_SetCompareSwap(uint32 swapEnable);

void   SamplingTimer_SetCaptureMode(uint32 triggerMode);
void   SamplingTimer_SetReloadMode(uint32 triggerMode);
void   SamplingTimer_SetStartMode(uint32 triggerMode);
void   SamplingTimer_SetStopMode(uint32 triggerMode);
void   SamplingTimer_SetCountMode(uint32 triggerMode);

void   SamplingTimer_SaveConfig(void);
void   SamplingTimer_RestoreConfig(void);
void   SamplingTimer_Sleep(void);
void   SamplingTimer_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define SamplingTimer_BLOCK_CONTROL_REG              (*(reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define SamplingTimer_BLOCK_CONTROL_PTR              ( (reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define SamplingTimer_COMMAND_REG                    (*(reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define SamplingTimer_COMMAND_PTR                    ( (reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define SamplingTimer_INTRRUPT_CAUSE_REG             (*(reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define SamplingTimer_INTRRUPT_CAUSE_PTR             ( (reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define SamplingTimer_CONTROL_REG                    (*(reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__CTRL )
#define SamplingTimer_CONTROL_PTR                    ( (reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__CTRL )
#define SamplingTimer_STATUS_REG                     (*(reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__STATUS )
#define SamplingTimer_STATUS_PTR                     ( (reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__STATUS )
#define SamplingTimer_COUNTER_REG                    (*(reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__COUNTER )
#define SamplingTimer_COUNTER_PTR                    ( (reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__COUNTER )
#define SamplingTimer_COMP_CAP_REG                   (*(reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__CC )
#define SamplingTimer_COMP_CAP_PTR                   ( (reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__CC )
#define SamplingTimer_COMP_CAP_BUF_REG               (*(reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define SamplingTimer_COMP_CAP_BUF_PTR               ( (reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define SamplingTimer_PERIOD_REG                     (*(reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__PERIOD )
#define SamplingTimer_PERIOD_PTR                     ( (reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__PERIOD )
#define SamplingTimer_PERIOD_BUF_REG                 (*(reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define SamplingTimer_PERIOD_BUF_PTR                 ( (reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define SamplingTimer_TRIG_CONTROL0_REG              (*(reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define SamplingTimer_TRIG_CONTROL0_PTR              ( (reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define SamplingTimer_TRIG_CONTROL1_REG              (*(reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define SamplingTimer_TRIG_CONTROL1_PTR              ( (reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define SamplingTimer_TRIG_CONTROL2_REG              (*(reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define SamplingTimer_TRIG_CONTROL2_PTR              ( (reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define SamplingTimer_INTERRUPT_REQ_REG              (*(reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__INTR )
#define SamplingTimer_INTERRUPT_REQ_PTR              ( (reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__INTR )
#define SamplingTimer_INTERRUPT_SET_REG              (*(reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define SamplingTimer_INTERRUPT_SET_PTR              ( (reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define SamplingTimer_INTERRUPT_MASK_REG             (*(reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define SamplingTimer_INTERRUPT_MASK_PTR             ( (reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define SamplingTimer_INTERRUPT_MASKED_REG           (*(reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__INTR_MASKED )
#define SamplingTimer_INTERRUPT_MASKED_PTR           ( (reg32 *) SamplingTimer_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define SamplingTimer_MASK                           ((uint32)SamplingTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define SamplingTimer_RELOAD_CC_SHIFT                (0u)
#define SamplingTimer_RELOAD_PERIOD_SHIFT            (1u)
#define SamplingTimer_PWM_SYNC_KILL_SHIFT            (2u)
#define SamplingTimer_PWM_STOP_KILL_SHIFT            (3u)
#define SamplingTimer_PRESCALER_SHIFT                (8u)
#define SamplingTimer_UPDOWN_SHIFT                   (16u)
#define SamplingTimer_ONESHOT_SHIFT                  (18u)
#define SamplingTimer_QUAD_MODE_SHIFT                (20u)
#define SamplingTimer_INV_OUT_SHIFT                  (20u)
#define SamplingTimer_INV_COMPL_OUT_SHIFT            (21u)
#define SamplingTimer_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define SamplingTimer_RELOAD_CC_MASK                 ((uint32)(SamplingTimer_1BIT_MASK        <<  \
                                                                            SamplingTimer_RELOAD_CC_SHIFT))
#define SamplingTimer_RELOAD_PERIOD_MASK             ((uint32)(SamplingTimer_1BIT_MASK        <<  \
                                                                            SamplingTimer_RELOAD_PERIOD_SHIFT))
#define SamplingTimer_PWM_SYNC_KILL_MASK             ((uint32)(SamplingTimer_1BIT_MASK        <<  \
                                                                            SamplingTimer_PWM_SYNC_KILL_SHIFT))
#define SamplingTimer_PWM_STOP_KILL_MASK             ((uint32)(SamplingTimer_1BIT_MASK        <<  \
                                                                            SamplingTimer_PWM_STOP_KILL_SHIFT))
#define SamplingTimer_PRESCALER_MASK                 ((uint32)(SamplingTimer_8BIT_MASK        <<  \
                                                                            SamplingTimer_PRESCALER_SHIFT))
#define SamplingTimer_UPDOWN_MASK                    ((uint32)(SamplingTimer_2BIT_MASK        <<  \
                                                                            SamplingTimer_UPDOWN_SHIFT))
#define SamplingTimer_ONESHOT_MASK                   ((uint32)(SamplingTimer_1BIT_MASK        <<  \
                                                                            SamplingTimer_ONESHOT_SHIFT))
#define SamplingTimer_QUAD_MODE_MASK                 ((uint32)(SamplingTimer_3BIT_MASK        <<  \
                                                                            SamplingTimer_QUAD_MODE_SHIFT))
#define SamplingTimer_INV_OUT_MASK                   ((uint32)(SamplingTimer_2BIT_MASK        <<  \
                                                                            SamplingTimer_INV_OUT_SHIFT))
#define SamplingTimer_MODE_MASK                      ((uint32)(SamplingTimer_3BIT_MASK        <<  \
                                                                            SamplingTimer_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define SamplingTimer_CAPTURE_SHIFT                  (0u)
#define SamplingTimer_COUNT_SHIFT                    (2u)
#define SamplingTimer_RELOAD_SHIFT                   (4u)
#define SamplingTimer_STOP_SHIFT                     (6u)
#define SamplingTimer_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define SamplingTimer_CAPTURE_MASK                   ((uint32)(SamplingTimer_2BIT_MASK        <<  \
                                                                  SamplingTimer_CAPTURE_SHIFT))
#define SamplingTimer_COUNT_MASK                     ((uint32)(SamplingTimer_2BIT_MASK        <<  \
                                                                  SamplingTimer_COUNT_SHIFT))
#define SamplingTimer_RELOAD_MASK                    ((uint32)(SamplingTimer_2BIT_MASK        <<  \
                                                                  SamplingTimer_RELOAD_SHIFT))
#define SamplingTimer_STOP_MASK                      ((uint32)(SamplingTimer_2BIT_MASK        <<  \
                                                                  SamplingTimer_STOP_SHIFT))
#define SamplingTimer_START_MASK                     ((uint32)(SamplingTimer_2BIT_MASK        <<  \
                                                                  SamplingTimer_START_SHIFT))

/* MASK */
#define SamplingTimer_1BIT_MASK                      ((uint32)0x01u)
#define SamplingTimer_2BIT_MASK                      ((uint32)0x03u)
#define SamplingTimer_3BIT_MASK                      ((uint32)0x07u)
#define SamplingTimer_6BIT_MASK                      ((uint32)0x3Fu)
#define SamplingTimer_8BIT_MASK                      ((uint32)0xFFu)
#define SamplingTimer_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define SamplingTimer_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define SamplingTimer_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(SamplingTimer_QUAD_ENCODING_MODES     << SamplingTimer_QUAD_MODE_SHIFT))       |\
         ((uint32)(SamplingTimer_CONFIG                  << SamplingTimer_MODE_SHIFT)))

#define SamplingTimer_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(SamplingTimer_PWM_STOP_EVENT          << SamplingTimer_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(SamplingTimer_PWM_OUT_INVERT          << SamplingTimer_INV_OUT_SHIFT))         |\
         ((uint32)(SamplingTimer_PWM_OUT_N_INVERT        << SamplingTimer_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(SamplingTimer_PWM_MODE                << SamplingTimer_MODE_SHIFT)))

#define SamplingTimer_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(SamplingTimer_PWM_RUN_MODE         << SamplingTimer_ONESHOT_SHIFT))
            
#define SamplingTimer_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(SamplingTimer_PWM_ALIGN            << SamplingTimer_UPDOWN_SHIFT))

#define SamplingTimer_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(SamplingTimer_PWM_KILL_EVENT      << SamplingTimer_PWM_SYNC_KILL_SHIFT))

#define SamplingTimer_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(SamplingTimer_PWM_DEAD_TIME_CYCLE  << SamplingTimer_PRESCALER_SHIFT))

#define SamplingTimer_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(SamplingTimer_PWM_PRESCALER        << SamplingTimer_PRESCALER_SHIFT))

#define SamplingTimer_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(SamplingTimer_TC_PRESCALER            << SamplingTimer_PRESCALER_SHIFT))       |\
         ((uint32)(SamplingTimer_TC_COUNTER_MODE         << SamplingTimer_UPDOWN_SHIFT))          |\
         ((uint32)(SamplingTimer_TC_RUN_MODE             << SamplingTimer_ONESHOT_SHIFT))         |\
         ((uint32)(SamplingTimer_TC_COMP_CAP_MODE        << SamplingTimer_MODE_SHIFT)))
        
#define SamplingTimer_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(SamplingTimer_QUAD_PHIA_SIGNAL_MODE   << SamplingTimer_COUNT_SHIFT))           |\
         ((uint32)(SamplingTimer_QUAD_INDEX_SIGNAL_MODE  << SamplingTimer_RELOAD_SHIFT))          |\
         ((uint32)(SamplingTimer_QUAD_STOP_SIGNAL_MODE   << SamplingTimer_STOP_SHIFT))            |\
         ((uint32)(SamplingTimer_QUAD_PHIB_SIGNAL_MODE   << SamplingTimer_START_SHIFT)))

#define SamplingTimer_PWM_SIGNALS_MODES                                                              \
        (((uint32)(SamplingTimer_PWM_SWITCH_SIGNAL_MODE  << SamplingTimer_CAPTURE_SHIFT))         |\
         ((uint32)(SamplingTimer_PWM_COUNT_SIGNAL_MODE   << SamplingTimer_COUNT_SHIFT))           |\
         ((uint32)(SamplingTimer_PWM_RELOAD_SIGNAL_MODE  << SamplingTimer_RELOAD_SHIFT))          |\
         ((uint32)(SamplingTimer_PWM_STOP_SIGNAL_MODE    << SamplingTimer_STOP_SHIFT))            |\
         ((uint32)(SamplingTimer_PWM_START_SIGNAL_MODE   << SamplingTimer_START_SHIFT)))

#define SamplingTimer_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(SamplingTimer_TC_CAPTURE_SIGNAL_MODE  << SamplingTimer_CAPTURE_SHIFT))         |\
         ((uint32)(SamplingTimer_TC_COUNT_SIGNAL_MODE    << SamplingTimer_COUNT_SHIFT))           |\
         ((uint32)(SamplingTimer_TC_RELOAD_SIGNAL_MODE   << SamplingTimer_RELOAD_SHIFT))          |\
         ((uint32)(SamplingTimer_TC_STOP_SIGNAL_MODE     << SamplingTimer_STOP_SHIFT))            |\
         ((uint32)(SamplingTimer_TC_START_SIGNAL_MODE    << SamplingTimer_START_SHIFT)))
        
#define SamplingTimer_TIMER_UPDOWN_CNT_USED                                                          \
                ((SamplingTimer__COUNT_UPDOWN0 == SamplingTimer_TC_COUNTER_MODE)                  ||\
                 (SamplingTimer__COUNT_UPDOWN1 == SamplingTimer_TC_COUNTER_MODE))

#define SamplingTimer_PWM_UPDOWN_CNT_USED                                                            \
                ((SamplingTimer__CENTER == SamplingTimer_PWM_ALIGN)                               ||\
                 (SamplingTimer__ASYMMETRIC == SamplingTimer_PWM_ALIGN))               
        
#define SamplingTimer_PWM_PR_INIT_VALUE              (1u)
#define SamplingTimer_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_SamplingTimer_H */

/* [] END OF FILE */
