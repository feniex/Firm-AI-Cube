/*******************************************************************************
* File Name: AckTimer.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the AckTimer
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

#if !defined(CY_TCPWM_AckTimer_H)
#define CY_TCPWM_AckTimer_H


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
} AckTimer_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  AckTimer_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define AckTimer_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define AckTimer_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define AckTimer_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define AckTimer_QUAD_ENCODING_MODES            (0lu)
#define AckTimer_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define AckTimer_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define AckTimer_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define AckTimer_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define AckTimer_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define AckTimer_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define AckTimer_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define AckTimer_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define AckTimer_TC_RUN_MODE                    (0lu)
#define AckTimer_TC_COUNTER_MODE                (0lu)
#define AckTimer_TC_COMP_CAP_MODE               (2lu)
#define AckTimer_TC_PRESCALER                   (0lu)

/* Signal modes */
#define AckTimer_TC_RELOAD_SIGNAL_MODE          (0lu)
#define AckTimer_TC_COUNT_SIGNAL_MODE           (3lu)
#define AckTimer_TC_START_SIGNAL_MODE           (0lu)
#define AckTimer_TC_STOP_SIGNAL_MODE            (0lu)
#define AckTimer_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define AckTimer_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define AckTimer_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define AckTimer_TC_START_SIGNAL_PRESENT        (0lu)
#define AckTimer_TC_STOP_SIGNAL_PRESENT         (0lu)
#define AckTimer_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define AckTimer_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define AckTimer_PWM_KILL_EVENT                 (0lu)
#define AckTimer_PWM_STOP_EVENT                 (0lu)
#define AckTimer_PWM_MODE                       (4lu)
#define AckTimer_PWM_OUT_N_INVERT               (0lu)
#define AckTimer_PWM_OUT_INVERT                 (0lu)
#define AckTimer_PWM_ALIGN                      (0lu)
#define AckTimer_PWM_RUN_MODE                   (0lu)
#define AckTimer_PWM_DEAD_TIME_CYCLE            (0lu)
#define AckTimer_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define AckTimer_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define AckTimer_PWM_COUNT_SIGNAL_MODE          (3lu)
#define AckTimer_PWM_START_SIGNAL_MODE          (0lu)
#define AckTimer_PWM_STOP_SIGNAL_MODE           (0lu)
#define AckTimer_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define AckTimer_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define AckTimer_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define AckTimer_PWM_START_SIGNAL_PRESENT       (0lu)
#define AckTimer_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define AckTimer_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define AckTimer_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define AckTimer_TC_PERIOD_VALUE                (2000lu)
#define AckTimer_TC_COMPARE_VALUE               (1000lu)
#define AckTimer_TC_COMPARE_BUF_VALUE           (65535lu)
#define AckTimer_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define AckTimer_PWM_PERIOD_VALUE               (1000lu)
#define AckTimer_PWM_PERIOD_BUF_VALUE           (65535lu)
#define AckTimer_PWM_PERIOD_SWAP                (0lu)
#define AckTimer_PWM_COMPARE_VALUE              (1000lu)
#define AckTimer_PWM_COMPARE_BUF_VALUE          (65535lu)
#define AckTimer_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define AckTimer__LEFT 0
#define AckTimer__RIGHT 1
#define AckTimer__CENTER 2
#define AckTimer__ASYMMETRIC 3

#define AckTimer__X1 0
#define AckTimer__X2 1
#define AckTimer__X4 2

#define AckTimer__PWM 4
#define AckTimer__PWM_DT 5
#define AckTimer__PWM_PR 6

#define AckTimer__INVERSE 1
#define AckTimer__DIRECT 0

#define AckTimer__CAPTURE 2
#define AckTimer__COMPARE 0

#define AckTimer__TRIG_LEVEL 3
#define AckTimer__TRIG_RISING 0
#define AckTimer__TRIG_FALLING 1
#define AckTimer__TRIG_BOTH 2

#define AckTimer__INTR_MASK_TC 1
#define AckTimer__INTR_MASK_CC_MATCH 2
#define AckTimer__INTR_MASK_NONE 0
#define AckTimer__INTR_MASK_TC_CC 3

#define AckTimer__UNCONFIG 8
#define AckTimer__TIMER 1
#define AckTimer__QUAD 3
#define AckTimer__PWM_SEL 7

#define AckTimer__COUNT_UP 0
#define AckTimer__COUNT_DOWN 1
#define AckTimer__COUNT_UPDOWN0 2
#define AckTimer__COUNT_UPDOWN1 3


/* Prescaler */
#define AckTimer_PRESCALE_DIVBY1                ((uint32)(0u << AckTimer_PRESCALER_SHIFT))
#define AckTimer_PRESCALE_DIVBY2                ((uint32)(1u << AckTimer_PRESCALER_SHIFT))
#define AckTimer_PRESCALE_DIVBY4                ((uint32)(2u << AckTimer_PRESCALER_SHIFT))
#define AckTimer_PRESCALE_DIVBY8                ((uint32)(3u << AckTimer_PRESCALER_SHIFT))
#define AckTimer_PRESCALE_DIVBY16               ((uint32)(4u << AckTimer_PRESCALER_SHIFT))
#define AckTimer_PRESCALE_DIVBY32               ((uint32)(5u << AckTimer_PRESCALER_SHIFT))
#define AckTimer_PRESCALE_DIVBY64               ((uint32)(6u << AckTimer_PRESCALER_SHIFT))
#define AckTimer_PRESCALE_DIVBY128              ((uint32)(7u << AckTimer_PRESCALER_SHIFT))

/* TCPWM set modes */
#define AckTimer_MODE_TIMER_COMPARE             ((uint32)(AckTimer__COMPARE         <<  \
                                                                  AckTimer_MODE_SHIFT))
#define AckTimer_MODE_TIMER_CAPTURE             ((uint32)(AckTimer__CAPTURE         <<  \
                                                                  AckTimer_MODE_SHIFT))
#define AckTimer_MODE_QUAD                      ((uint32)(AckTimer__QUAD            <<  \
                                                                  AckTimer_MODE_SHIFT))
#define AckTimer_MODE_PWM                       ((uint32)(AckTimer__PWM             <<  \
                                                                  AckTimer_MODE_SHIFT))
#define AckTimer_MODE_PWM_DT                    ((uint32)(AckTimer__PWM_DT          <<  \
                                                                  AckTimer_MODE_SHIFT))
#define AckTimer_MODE_PWM_PR                    ((uint32)(AckTimer__PWM_PR          <<  \
                                                                  AckTimer_MODE_SHIFT))

/* Quad Modes */
#define AckTimer_MODE_X1                        ((uint32)(AckTimer__X1              <<  \
                                                                  AckTimer_QUAD_MODE_SHIFT))
#define AckTimer_MODE_X2                        ((uint32)(AckTimer__X2              <<  \
                                                                  AckTimer_QUAD_MODE_SHIFT))
#define AckTimer_MODE_X4                        ((uint32)(AckTimer__X4              <<  \
                                                                  AckTimer_QUAD_MODE_SHIFT))

/* Counter modes */
#define AckTimer_COUNT_UP                       ((uint32)(AckTimer__COUNT_UP        <<  \
                                                                  AckTimer_UPDOWN_SHIFT))
#define AckTimer_COUNT_DOWN                     ((uint32)(AckTimer__COUNT_DOWN      <<  \
                                                                  AckTimer_UPDOWN_SHIFT))
#define AckTimer_COUNT_UPDOWN0                  ((uint32)(AckTimer__COUNT_UPDOWN0   <<  \
                                                                  AckTimer_UPDOWN_SHIFT))
#define AckTimer_COUNT_UPDOWN1                  ((uint32)(AckTimer__COUNT_UPDOWN1   <<  \
                                                                  AckTimer_UPDOWN_SHIFT))

/* PWM output invert */
#define AckTimer_INVERT_LINE                    ((uint32)(AckTimer__INVERSE         <<  \
                                                                  AckTimer_INV_OUT_SHIFT))
#define AckTimer_INVERT_LINE_N                  ((uint32)(AckTimer__INVERSE         <<  \
                                                                  AckTimer_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define AckTimer_TRIG_RISING                    ((uint32)AckTimer__TRIG_RISING)
#define AckTimer_TRIG_FALLING                   ((uint32)AckTimer__TRIG_FALLING)
#define AckTimer_TRIG_BOTH                      ((uint32)AckTimer__TRIG_BOTH)
#define AckTimer_TRIG_LEVEL                     ((uint32)AckTimer__TRIG_LEVEL)

/* Interrupt mask */
#define AckTimer_INTR_MASK_TC                   ((uint32)AckTimer__INTR_MASK_TC)
#define AckTimer_INTR_MASK_CC_MATCH             ((uint32)AckTimer__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define AckTimer_CC_MATCH_SET                   (0x00u)
#define AckTimer_CC_MATCH_CLEAR                 (0x01u)
#define AckTimer_CC_MATCH_INVERT                (0x02u)
#define AckTimer_CC_MATCH_NO_CHANGE             (0x03u)
#define AckTimer_OVERLOW_SET                    (0x00u)
#define AckTimer_OVERLOW_CLEAR                  (0x04u)
#define AckTimer_OVERLOW_INVERT                 (0x08u)
#define AckTimer_OVERLOW_NO_CHANGE              (0x0Cu)
#define AckTimer_UNDERFLOW_SET                  (0x00u)
#define AckTimer_UNDERFLOW_CLEAR                (0x10u)
#define AckTimer_UNDERFLOW_INVERT               (0x20u)
#define AckTimer_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define AckTimer_PWM_MODE_LEFT                  (AckTimer_CC_MATCH_CLEAR        |   \
                                                         AckTimer_OVERLOW_SET           |   \
                                                         AckTimer_UNDERFLOW_NO_CHANGE)
#define AckTimer_PWM_MODE_RIGHT                 (AckTimer_CC_MATCH_SET          |   \
                                                         AckTimer_OVERLOW_NO_CHANGE     |   \
                                                         AckTimer_UNDERFLOW_CLEAR)
#define AckTimer_PWM_MODE_ASYM                  (AckTimer_CC_MATCH_INVERT       |   \
                                                         AckTimer_OVERLOW_SET           |   \
                                                         AckTimer_UNDERFLOW_CLEAR)

#if (AckTimer_CY_TCPWM_V2)
    #if(AckTimer_CY_TCPWM_4000)
        #define AckTimer_PWM_MODE_CENTER                (AckTimer_CC_MATCH_INVERT       |   \
                                                                 AckTimer_OVERLOW_NO_CHANGE     |   \
                                                                 AckTimer_UNDERFLOW_CLEAR)
    #else
        #define AckTimer_PWM_MODE_CENTER                (AckTimer_CC_MATCH_INVERT       |   \
                                                                 AckTimer_OVERLOW_SET           |   \
                                                                 AckTimer_UNDERFLOW_CLEAR)
    #endif /* (AckTimer_CY_TCPWM_4000) */
#else
    #define AckTimer_PWM_MODE_CENTER                (AckTimer_CC_MATCH_INVERT       |   \
                                                             AckTimer_OVERLOW_NO_CHANGE     |   \
                                                             AckTimer_UNDERFLOW_CLEAR)
#endif /* (AckTimer_CY_TCPWM_NEW) */

/* Command operations without condition */
#define AckTimer_CMD_CAPTURE                    (0u)
#define AckTimer_CMD_RELOAD                     (8u)
#define AckTimer_CMD_STOP                       (16u)
#define AckTimer_CMD_START                      (24u)

/* Status */
#define AckTimer_STATUS_DOWN                    (1u)
#define AckTimer_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   AckTimer_Init(void);
void   AckTimer_Enable(void);
void   AckTimer_Start(void);
void   AckTimer_Stop(void);

void   AckTimer_SetMode(uint32 mode);
void   AckTimer_SetCounterMode(uint32 counterMode);
void   AckTimer_SetPWMMode(uint32 modeMask);
void   AckTimer_SetQDMode(uint32 qdMode);

void   AckTimer_SetPrescaler(uint32 prescaler);
void   AckTimer_TriggerCommand(uint32 mask, uint32 command);
void   AckTimer_SetOneShot(uint32 oneShotEnable);
uint32 AckTimer_ReadStatus(void);

void   AckTimer_SetPWMSyncKill(uint32 syncKillEnable);
void   AckTimer_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   AckTimer_SetPWMDeadTime(uint32 deadTime);
void   AckTimer_SetPWMInvert(uint32 mask);

void   AckTimer_SetInterruptMode(uint32 interruptMask);
uint32 AckTimer_GetInterruptSourceMasked(void);
uint32 AckTimer_GetInterruptSource(void);
void   AckTimer_ClearInterrupt(uint32 interruptMask);
void   AckTimer_SetInterrupt(uint32 interruptMask);

void   AckTimer_WriteCounter(uint32 count);
uint32 AckTimer_ReadCounter(void);

uint32 AckTimer_ReadCapture(void);
uint32 AckTimer_ReadCaptureBuf(void);

void   AckTimer_WritePeriod(uint32 period);
uint32 AckTimer_ReadPeriod(void);
void   AckTimer_WritePeriodBuf(uint32 periodBuf);
uint32 AckTimer_ReadPeriodBuf(void);

void   AckTimer_WriteCompare(uint32 compare);
uint32 AckTimer_ReadCompare(void);
void   AckTimer_WriteCompareBuf(uint32 compareBuf);
uint32 AckTimer_ReadCompareBuf(void);

void   AckTimer_SetPeriodSwap(uint32 swapEnable);
void   AckTimer_SetCompareSwap(uint32 swapEnable);

void   AckTimer_SetCaptureMode(uint32 triggerMode);
void   AckTimer_SetReloadMode(uint32 triggerMode);
void   AckTimer_SetStartMode(uint32 triggerMode);
void   AckTimer_SetStopMode(uint32 triggerMode);
void   AckTimer_SetCountMode(uint32 triggerMode);

void   AckTimer_SaveConfig(void);
void   AckTimer_RestoreConfig(void);
void   AckTimer_Sleep(void);
void   AckTimer_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define AckTimer_BLOCK_CONTROL_REG              (*(reg32 *) AckTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define AckTimer_BLOCK_CONTROL_PTR              ( (reg32 *) AckTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define AckTimer_COMMAND_REG                    (*(reg32 *) AckTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define AckTimer_COMMAND_PTR                    ( (reg32 *) AckTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define AckTimer_INTRRUPT_CAUSE_REG             (*(reg32 *) AckTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define AckTimer_INTRRUPT_CAUSE_PTR             ( (reg32 *) AckTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define AckTimer_CONTROL_REG                    (*(reg32 *) AckTimer_cy_m0s8_tcpwm_1__CTRL )
#define AckTimer_CONTROL_PTR                    ( (reg32 *) AckTimer_cy_m0s8_tcpwm_1__CTRL )
#define AckTimer_STATUS_REG                     (*(reg32 *) AckTimer_cy_m0s8_tcpwm_1__STATUS )
#define AckTimer_STATUS_PTR                     ( (reg32 *) AckTimer_cy_m0s8_tcpwm_1__STATUS )
#define AckTimer_COUNTER_REG                    (*(reg32 *) AckTimer_cy_m0s8_tcpwm_1__COUNTER )
#define AckTimer_COUNTER_PTR                    ( (reg32 *) AckTimer_cy_m0s8_tcpwm_1__COUNTER )
#define AckTimer_COMP_CAP_REG                   (*(reg32 *) AckTimer_cy_m0s8_tcpwm_1__CC )
#define AckTimer_COMP_CAP_PTR                   ( (reg32 *) AckTimer_cy_m0s8_tcpwm_1__CC )
#define AckTimer_COMP_CAP_BUF_REG               (*(reg32 *) AckTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define AckTimer_COMP_CAP_BUF_PTR               ( (reg32 *) AckTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define AckTimer_PERIOD_REG                     (*(reg32 *) AckTimer_cy_m0s8_tcpwm_1__PERIOD )
#define AckTimer_PERIOD_PTR                     ( (reg32 *) AckTimer_cy_m0s8_tcpwm_1__PERIOD )
#define AckTimer_PERIOD_BUF_REG                 (*(reg32 *) AckTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define AckTimer_PERIOD_BUF_PTR                 ( (reg32 *) AckTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define AckTimer_TRIG_CONTROL0_REG              (*(reg32 *) AckTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define AckTimer_TRIG_CONTROL0_PTR              ( (reg32 *) AckTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define AckTimer_TRIG_CONTROL1_REG              (*(reg32 *) AckTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define AckTimer_TRIG_CONTROL1_PTR              ( (reg32 *) AckTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define AckTimer_TRIG_CONTROL2_REG              (*(reg32 *) AckTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define AckTimer_TRIG_CONTROL2_PTR              ( (reg32 *) AckTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define AckTimer_INTERRUPT_REQ_REG              (*(reg32 *) AckTimer_cy_m0s8_tcpwm_1__INTR )
#define AckTimer_INTERRUPT_REQ_PTR              ( (reg32 *) AckTimer_cy_m0s8_tcpwm_1__INTR )
#define AckTimer_INTERRUPT_SET_REG              (*(reg32 *) AckTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define AckTimer_INTERRUPT_SET_PTR              ( (reg32 *) AckTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define AckTimer_INTERRUPT_MASK_REG             (*(reg32 *) AckTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define AckTimer_INTERRUPT_MASK_PTR             ( (reg32 *) AckTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define AckTimer_INTERRUPT_MASKED_REG           (*(reg32 *) AckTimer_cy_m0s8_tcpwm_1__INTR_MASKED )
#define AckTimer_INTERRUPT_MASKED_PTR           ( (reg32 *) AckTimer_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define AckTimer_MASK                           ((uint32)AckTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define AckTimer_RELOAD_CC_SHIFT                (0u)
#define AckTimer_RELOAD_PERIOD_SHIFT            (1u)
#define AckTimer_PWM_SYNC_KILL_SHIFT            (2u)
#define AckTimer_PWM_STOP_KILL_SHIFT            (3u)
#define AckTimer_PRESCALER_SHIFT                (8u)
#define AckTimer_UPDOWN_SHIFT                   (16u)
#define AckTimer_ONESHOT_SHIFT                  (18u)
#define AckTimer_QUAD_MODE_SHIFT                (20u)
#define AckTimer_INV_OUT_SHIFT                  (20u)
#define AckTimer_INV_COMPL_OUT_SHIFT            (21u)
#define AckTimer_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define AckTimer_RELOAD_CC_MASK                 ((uint32)(AckTimer_1BIT_MASK        <<  \
                                                                            AckTimer_RELOAD_CC_SHIFT))
#define AckTimer_RELOAD_PERIOD_MASK             ((uint32)(AckTimer_1BIT_MASK        <<  \
                                                                            AckTimer_RELOAD_PERIOD_SHIFT))
#define AckTimer_PWM_SYNC_KILL_MASK             ((uint32)(AckTimer_1BIT_MASK        <<  \
                                                                            AckTimer_PWM_SYNC_KILL_SHIFT))
#define AckTimer_PWM_STOP_KILL_MASK             ((uint32)(AckTimer_1BIT_MASK        <<  \
                                                                            AckTimer_PWM_STOP_KILL_SHIFT))
#define AckTimer_PRESCALER_MASK                 ((uint32)(AckTimer_8BIT_MASK        <<  \
                                                                            AckTimer_PRESCALER_SHIFT))
#define AckTimer_UPDOWN_MASK                    ((uint32)(AckTimer_2BIT_MASK        <<  \
                                                                            AckTimer_UPDOWN_SHIFT))
#define AckTimer_ONESHOT_MASK                   ((uint32)(AckTimer_1BIT_MASK        <<  \
                                                                            AckTimer_ONESHOT_SHIFT))
#define AckTimer_QUAD_MODE_MASK                 ((uint32)(AckTimer_3BIT_MASK        <<  \
                                                                            AckTimer_QUAD_MODE_SHIFT))
#define AckTimer_INV_OUT_MASK                   ((uint32)(AckTimer_2BIT_MASK        <<  \
                                                                            AckTimer_INV_OUT_SHIFT))
#define AckTimer_MODE_MASK                      ((uint32)(AckTimer_3BIT_MASK        <<  \
                                                                            AckTimer_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define AckTimer_CAPTURE_SHIFT                  (0u)
#define AckTimer_COUNT_SHIFT                    (2u)
#define AckTimer_RELOAD_SHIFT                   (4u)
#define AckTimer_STOP_SHIFT                     (6u)
#define AckTimer_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define AckTimer_CAPTURE_MASK                   ((uint32)(AckTimer_2BIT_MASK        <<  \
                                                                  AckTimer_CAPTURE_SHIFT))
#define AckTimer_COUNT_MASK                     ((uint32)(AckTimer_2BIT_MASK        <<  \
                                                                  AckTimer_COUNT_SHIFT))
#define AckTimer_RELOAD_MASK                    ((uint32)(AckTimer_2BIT_MASK        <<  \
                                                                  AckTimer_RELOAD_SHIFT))
#define AckTimer_STOP_MASK                      ((uint32)(AckTimer_2BIT_MASK        <<  \
                                                                  AckTimer_STOP_SHIFT))
#define AckTimer_START_MASK                     ((uint32)(AckTimer_2BIT_MASK        <<  \
                                                                  AckTimer_START_SHIFT))

/* MASK */
#define AckTimer_1BIT_MASK                      ((uint32)0x01u)
#define AckTimer_2BIT_MASK                      ((uint32)0x03u)
#define AckTimer_3BIT_MASK                      ((uint32)0x07u)
#define AckTimer_6BIT_MASK                      ((uint32)0x3Fu)
#define AckTimer_8BIT_MASK                      ((uint32)0xFFu)
#define AckTimer_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define AckTimer_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define AckTimer_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(AckTimer_QUAD_ENCODING_MODES     << AckTimer_QUAD_MODE_SHIFT))       |\
         ((uint32)(AckTimer_CONFIG                  << AckTimer_MODE_SHIFT)))

#define AckTimer_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(AckTimer_PWM_STOP_EVENT          << AckTimer_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(AckTimer_PWM_OUT_INVERT          << AckTimer_INV_OUT_SHIFT))         |\
         ((uint32)(AckTimer_PWM_OUT_N_INVERT        << AckTimer_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(AckTimer_PWM_MODE                << AckTimer_MODE_SHIFT)))

#define AckTimer_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(AckTimer_PWM_RUN_MODE         << AckTimer_ONESHOT_SHIFT))
            
#define AckTimer_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(AckTimer_PWM_ALIGN            << AckTimer_UPDOWN_SHIFT))

#define AckTimer_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(AckTimer_PWM_KILL_EVENT      << AckTimer_PWM_SYNC_KILL_SHIFT))

#define AckTimer_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(AckTimer_PWM_DEAD_TIME_CYCLE  << AckTimer_PRESCALER_SHIFT))

#define AckTimer_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(AckTimer_PWM_PRESCALER        << AckTimer_PRESCALER_SHIFT))

#define AckTimer_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(AckTimer_TC_PRESCALER            << AckTimer_PRESCALER_SHIFT))       |\
         ((uint32)(AckTimer_TC_COUNTER_MODE         << AckTimer_UPDOWN_SHIFT))          |\
         ((uint32)(AckTimer_TC_RUN_MODE             << AckTimer_ONESHOT_SHIFT))         |\
         ((uint32)(AckTimer_TC_COMP_CAP_MODE        << AckTimer_MODE_SHIFT)))
        
#define AckTimer_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(AckTimer_QUAD_PHIA_SIGNAL_MODE   << AckTimer_COUNT_SHIFT))           |\
         ((uint32)(AckTimer_QUAD_INDEX_SIGNAL_MODE  << AckTimer_RELOAD_SHIFT))          |\
         ((uint32)(AckTimer_QUAD_STOP_SIGNAL_MODE   << AckTimer_STOP_SHIFT))            |\
         ((uint32)(AckTimer_QUAD_PHIB_SIGNAL_MODE   << AckTimer_START_SHIFT)))

#define AckTimer_PWM_SIGNALS_MODES                                                              \
        (((uint32)(AckTimer_PWM_SWITCH_SIGNAL_MODE  << AckTimer_CAPTURE_SHIFT))         |\
         ((uint32)(AckTimer_PWM_COUNT_SIGNAL_MODE   << AckTimer_COUNT_SHIFT))           |\
         ((uint32)(AckTimer_PWM_RELOAD_SIGNAL_MODE  << AckTimer_RELOAD_SHIFT))          |\
         ((uint32)(AckTimer_PWM_STOP_SIGNAL_MODE    << AckTimer_STOP_SHIFT))            |\
         ((uint32)(AckTimer_PWM_START_SIGNAL_MODE   << AckTimer_START_SHIFT)))

#define AckTimer_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(AckTimer_TC_CAPTURE_SIGNAL_MODE  << AckTimer_CAPTURE_SHIFT))         |\
         ((uint32)(AckTimer_TC_COUNT_SIGNAL_MODE    << AckTimer_COUNT_SHIFT))           |\
         ((uint32)(AckTimer_TC_RELOAD_SIGNAL_MODE   << AckTimer_RELOAD_SHIFT))          |\
         ((uint32)(AckTimer_TC_STOP_SIGNAL_MODE     << AckTimer_STOP_SHIFT))            |\
         ((uint32)(AckTimer_TC_START_SIGNAL_MODE    << AckTimer_START_SHIFT)))
        
#define AckTimer_TIMER_UPDOWN_CNT_USED                                                          \
                ((AckTimer__COUNT_UPDOWN0 == AckTimer_TC_COUNTER_MODE)                  ||\
                 (AckTimer__COUNT_UPDOWN1 == AckTimer_TC_COUNTER_MODE))

#define AckTimer_PWM_UPDOWN_CNT_USED                                                            \
                ((AckTimer__CENTER == AckTimer_PWM_ALIGN)                               ||\
                 (AckTimer__ASYMMETRIC == AckTimer_PWM_ALIGN))               
        
#define AckTimer_PWM_PR_INIT_VALUE              (1u)
#define AckTimer_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_AckTimer_H */

/* [] END OF FILE */
