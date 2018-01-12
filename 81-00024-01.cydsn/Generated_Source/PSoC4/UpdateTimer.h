/*******************************************************************************
* File Name: UpdateTimer.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the UpdateTimer
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

#if !defined(CY_TCPWM_UpdateTimer_H)
#define CY_TCPWM_UpdateTimer_H


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
} UpdateTimer_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  UpdateTimer_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define UpdateTimer_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define UpdateTimer_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define UpdateTimer_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define UpdateTimer_QUAD_ENCODING_MODES            (0lu)
#define UpdateTimer_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define UpdateTimer_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define UpdateTimer_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define UpdateTimer_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define UpdateTimer_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define UpdateTimer_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define UpdateTimer_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define UpdateTimer_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define UpdateTimer_TC_RUN_MODE                    (0lu)
#define UpdateTimer_TC_COUNTER_MODE                (0lu)
#define UpdateTimer_TC_COMP_CAP_MODE               (2lu)
#define UpdateTimer_TC_PRESCALER                   (0lu)

/* Signal modes */
#define UpdateTimer_TC_RELOAD_SIGNAL_MODE          (0lu)
#define UpdateTimer_TC_COUNT_SIGNAL_MODE           (3lu)
#define UpdateTimer_TC_START_SIGNAL_MODE           (0lu)
#define UpdateTimer_TC_STOP_SIGNAL_MODE            (0lu)
#define UpdateTimer_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define UpdateTimer_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define UpdateTimer_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define UpdateTimer_TC_START_SIGNAL_PRESENT        (0lu)
#define UpdateTimer_TC_STOP_SIGNAL_PRESENT         (0lu)
#define UpdateTimer_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define UpdateTimer_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define UpdateTimer_PWM_KILL_EVENT                 (0lu)
#define UpdateTimer_PWM_STOP_EVENT                 (0lu)
#define UpdateTimer_PWM_MODE                       (4lu)
#define UpdateTimer_PWM_OUT_N_INVERT               (0lu)
#define UpdateTimer_PWM_OUT_INVERT                 (0lu)
#define UpdateTimer_PWM_ALIGN                      (0lu)
#define UpdateTimer_PWM_RUN_MODE                   (0lu)
#define UpdateTimer_PWM_DEAD_TIME_CYCLE            (0lu)
#define UpdateTimer_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define UpdateTimer_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define UpdateTimer_PWM_COUNT_SIGNAL_MODE          (3lu)
#define UpdateTimer_PWM_START_SIGNAL_MODE          (0lu)
#define UpdateTimer_PWM_STOP_SIGNAL_MODE           (0lu)
#define UpdateTimer_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define UpdateTimer_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define UpdateTimer_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define UpdateTimer_PWM_START_SIGNAL_PRESENT       (0lu)
#define UpdateTimer_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define UpdateTimer_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define UpdateTimer_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define UpdateTimer_TC_PERIOD_VALUE                (1000lu)
#define UpdateTimer_TC_COMPARE_VALUE               (65535lu)
#define UpdateTimer_TC_COMPARE_BUF_VALUE           (65535lu)
#define UpdateTimer_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define UpdateTimer_PWM_PERIOD_VALUE               (65535lu)
#define UpdateTimer_PWM_PERIOD_BUF_VALUE           (65535lu)
#define UpdateTimer_PWM_PERIOD_SWAP                (0lu)
#define UpdateTimer_PWM_COMPARE_VALUE              (65535lu)
#define UpdateTimer_PWM_COMPARE_BUF_VALUE          (65535lu)
#define UpdateTimer_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define UpdateTimer__LEFT 0
#define UpdateTimer__RIGHT 1
#define UpdateTimer__CENTER 2
#define UpdateTimer__ASYMMETRIC 3

#define UpdateTimer__X1 0
#define UpdateTimer__X2 1
#define UpdateTimer__X4 2

#define UpdateTimer__PWM 4
#define UpdateTimer__PWM_DT 5
#define UpdateTimer__PWM_PR 6

#define UpdateTimer__INVERSE 1
#define UpdateTimer__DIRECT 0

#define UpdateTimer__CAPTURE 2
#define UpdateTimer__COMPARE 0

#define UpdateTimer__TRIG_LEVEL 3
#define UpdateTimer__TRIG_RISING 0
#define UpdateTimer__TRIG_FALLING 1
#define UpdateTimer__TRIG_BOTH 2

#define UpdateTimer__INTR_MASK_TC 1
#define UpdateTimer__INTR_MASK_CC_MATCH 2
#define UpdateTimer__INTR_MASK_NONE 0
#define UpdateTimer__INTR_MASK_TC_CC 3

#define UpdateTimer__UNCONFIG 8
#define UpdateTimer__TIMER 1
#define UpdateTimer__QUAD 3
#define UpdateTimer__PWM_SEL 7

#define UpdateTimer__COUNT_UP 0
#define UpdateTimer__COUNT_DOWN 1
#define UpdateTimer__COUNT_UPDOWN0 2
#define UpdateTimer__COUNT_UPDOWN1 3


/* Prescaler */
#define UpdateTimer_PRESCALE_DIVBY1                ((uint32)(0u << UpdateTimer_PRESCALER_SHIFT))
#define UpdateTimer_PRESCALE_DIVBY2                ((uint32)(1u << UpdateTimer_PRESCALER_SHIFT))
#define UpdateTimer_PRESCALE_DIVBY4                ((uint32)(2u << UpdateTimer_PRESCALER_SHIFT))
#define UpdateTimer_PRESCALE_DIVBY8                ((uint32)(3u << UpdateTimer_PRESCALER_SHIFT))
#define UpdateTimer_PRESCALE_DIVBY16               ((uint32)(4u << UpdateTimer_PRESCALER_SHIFT))
#define UpdateTimer_PRESCALE_DIVBY32               ((uint32)(5u << UpdateTimer_PRESCALER_SHIFT))
#define UpdateTimer_PRESCALE_DIVBY64               ((uint32)(6u << UpdateTimer_PRESCALER_SHIFT))
#define UpdateTimer_PRESCALE_DIVBY128              ((uint32)(7u << UpdateTimer_PRESCALER_SHIFT))

/* TCPWM set modes */
#define UpdateTimer_MODE_TIMER_COMPARE             ((uint32)(UpdateTimer__COMPARE         <<  \
                                                                  UpdateTimer_MODE_SHIFT))
#define UpdateTimer_MODE_TIMER_CAPTURE             ((uint32)(UpdateTimer__CAPTURE         <<  \
                                                                  UpdateTimer_MODE_SHIFT))
#define UpdateTimer_MODE_QUAD                      ((uint32)(UpdateTimer__QUAD            <<  \
                                                                  UpdateTimer_MODE_SHIFT))
#define UpdateTimer_MODE_PWM                       ((uint32)(UpdateTimer__PWM             <<  \
                                                                  UpdateTimer_MODE_SHIFT))
#define UpdateTimer_MODE_PWM_DT                    ((uint32)(UpdateTimer__PWM_DT          <<  \
                                                                  UpdateTimer_MODE_SHIFT))
#define UpdateTimer_MODE_PWM_PR                    ((uint32)(UpdateTimer__PWM_PR          <<  \
                                                                  UpdateTimer_MODE_SHIFT))

/* Quad Modes */
#define UpdateTimer_MODE_X1                        ((uint32)(UpdateTimer__X1              <<  \
                                                                  UpdateTimer_QUAD_MODE_SHIFT))
#define UpdateTimer_MODE_X2                        ((uint32)(UpdateTimer__X2              <<  \
                                                                  UpdateTimer_QUAD_MODE_SHIFT))
#define UpdateTimer_MODE_X4                        ((uint32)(UpdateTimer__X4              <<  \
                                                                  UpdateTimer_QUAD_MODE_SHIFT))

/* Counter modes */
#define UpdateTimer_COUNT_UP                       ((uint32)(UpdateTimer__COUNT_UP        <<  \
                                                                  UpdateTimer_UPDOWN_SHIFT))
#define UpdateTimer_COUNT_DOWN                     ((uint32)(UpdateTimer__COUNT_DOWN      <<  \
                                                                  UpdateTimer_UPDOWN_SHIFT))
#define UpdateTimer_COUNT_UPDOWN0                  ((uint32)(UpdateTimer__COUNT_UPDOWN0   <<  \
                                                                  UpdateTimer_UPDOWN_SHIFT))
#define UpdateTimer_COUNT_UPDOWN1                  ((uint32)(UpdateTimer__COUNT_UPDOWN1   <<  \
                                                                  UpdateTimer_UPDOWN_SHIFT))

/* PWM output invert */
#define UpdateTimer_INVERT_LINE                    ((uint32)(UpdateTimer__INVERSE         <<  \
                                                                  UpdateTimer_INV_OUT_SHIFT))
#define UpdateTimer_INVERT_LINE_N                  ((uint32)(UpdateTimer__INVERSE         <<  \
                                                                  UpdateTimer_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define UpdateTimer_TRIG_RISING                    ((uint32)UpdateTimer__TRIG_RISING)
#define UpdateTimer_TRIG_FALLING                   ((uint32)UpdateTimer__TRIG_FALLING)
#define UpdateTimer_TRIG_BOTH                      ((uint32)UpdateTimer__TRIG_BOTH)
#define UpdateTimer_TRIG_LEVEL                     ((uint32)UpdateTimer__TRIG_LEVEL)

/* Interrupt mask */
#define UpdateTimer_INTR_MASK_TC                   ((uint32)UpdateTimer__INTR_MASK_TC)
#define UpdateTimer_INTR_MASK_CC_MATCH             ((uint32)UpdateTimer__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define UpdateTimer_CC_MATCH_SET                   (0x00u)
#define UpdateTimer_CC_MATCH_CLEAR                 (0x01u)
#define UpdateTimer_CC_MATCH_INVERT                (0x02u)
#define UpdateTimer_CC_MATCH_NO_CHANGE             (0x03u)
#define UpdateTimer_OVERLOW_SET                    (0x00u)
#define UpdateTimer_OVERLOW_CLEAR                  (0x04u)
#define UpdateTimer_OVERLOW_INVERT                 (0x08u)
#define UpdateTimer_OVERLOW_NO_CHANGE              (0x0Cu)
#define UpdateTimer_UNDERFLOW_SET                  (0x00u)
#define UpdateTimer_UNDERFLOW_CLEAR                (0x10u)
#define UpdateTimer_UNDERFLOW_INVERT               (0x20u)
#define UpdateTimer_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define UpdateTimer_PWM_MODE_LEFT                  (UpdateTimer_CC_MATCH_CLEAR        |   \
                                                         UpdateTimer_OVERLOW_SET           |   \
                                                         UpdateTimer_UNDERFLOW_NO_CHANGE)
#define UpdateTimer_PWM_MODE_RIGHT                 (UpdateTimer_CC_MATCH_SET          |   \
                                                         UpdateTimer_OVERLOW_NO_CHANGE     |   \
                                                         UpdateTimer_UNDERFLOW_CLEAR)
#define UpdateTimer_PWM_MODE_ASYM                  (UpdateTimer_CC_MATCH_INVERT       |   \
                                                         UpdateTimer_OVERLOW_SET           |   \
                                                         UpdateTimer_UNDERFLOW_CLEAR)

#if (UpdateTimer_CY_TCPWM_V2)
    #if(UpdateTimer_CY_TCPWM_4000)
        #define UpdateTimer_PWM_MODE_CENTER                (UpdateTimer_CC_MATCH_INVERT       |   \
                                                                 UpdateTimer_OVERLOW_NO_CHANGE     |   \
                                                                 UpdateTimer_UNDERFLOW_CLEAR)
    #else
        #define UpdateTimer_PWM_MODE_CENTER                (UpdateTimer_CC_MATCH_INVERT       |   \
                                                                 UpdateTimer_OVERLOW_SET           |   \
                                                                 UpdateTimer_UNDERFLOW_CLEAR)
    #endif /* (UpdateTimer_CY_TCPWM_4000) */
#else
    #define UpdateTimer_PWM_MODE_CENTER                (UpdateTimer_CC_MATCH_INVERT       |   \
                                                             UpdateTimer_OVERLOW_NO_CHANGE     |   \
                                                             UpdateTimer_UNDERFLOW_CLEAR)
#endif /* (UpdateTimer_CY_TCPWM_NEW) */

/* Command operations without condition */
#define UpdateTimer_CMD_CAPTURE                    (0u)
#define UpdateTimer_CMD_RELOAD                     (8u)
#define UpdateTimer_CMD_STOP                       (16u)
#define UpdateTimer_CMD_START                      (24u)

/* Status */
#define UpdateTimer_STATUS_DOWN                    (1u)
#define UpdateTimer_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   UpdateTimer_Init(void);
void   UpdateTimer_Enable(void);
void   UpdateTimer_Start(void);
void   UpdateTimer_Stop(void);

void   UpdateTimer_SetMode(uint32 mode);
void   UpdateTimer_SetCounterMode(uint32 counterMode);
void   UpdateTimer_SetPWMMode(uint32 modeMask);
void   UpdateTimer_SetQDMode(uint32 qdMode);

void   UpdateTimer_SetPrescaler(uint32 prescaler);
void   UpdateTimer_TriggerCommand(uint32 mask, uint32 command);
void   UpdateTimer_SetOneShot(uint32 oneShotEnable);
uint32 UpdateTimer_ReadStatus(void);

void   UpdateTimer_SetPWMSyncKill(uint32 syncKillEnable);
void   UpdateTimer_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   UpdateTimer_SetPWMDeadTime(uint32 deadTime);
void   UpdateTimer_SetPWMInvert(uint32 mask);

void   UpdateTimer_SetInterruptMode(uint32 interruptMask);
uint32 UpdateTimer_GetInterruptSourceMasked(void);
uint32 UpdateTimer_GetInterruptSource(void);
void   UpdateTimer_ClearInterrupt(uint32 interruptMask);
void   UpdateTimer_SetInterrupt(uint32 interruptMask);

void   UpdateTimer_WriteCounter(uint32 count);
uint32 UpdateTimer_ReadCounter(void);

uint32 UpdateTimer_ReadCapture(void);
uint32 UpdateTimer_ReadCaptureBuf(void);

void   UpdateTimer_WritePeriod(uint32 period);
uint32 UpdateTimer_ReadPeriod(void);
void   UpdateTimer_WritePeriodBuf(uint32 periodBuf);
uint32 UpdateTimer_ReadPeriodBuf(void);

void   UpdateTimer_WriteCompare(uint32 compare);
uint32 UpdateTimer_ReadCompare(void);
void   UpdateTimer_WriteCompareBuf(uint32 compareBuf);
uint32 UpdateTimer_ReadCompareBuf(void);

void   UpdateTimer_SetPeriodSwap(uint32 swapEnable);
void   UpdateTimer_SetCompareSwap(uint32 swapEnable);

void   UpdateTimer_SetCaptureMode(uint32 triggerMode);
void   UpdateTimer_SetReloadMode(uint32 triggerMode);
void   UpdateTimer_SetStartMode(uint32 triggerMode);
void   UpdateTimer_SetStopMode(uint32 triggerMode);
void   UpdateTimer_SetCountMode(uint32 triggerMode);

void   UpdateTimer_SaveConfig(void);
void   UpdateTimer_RestoreConfig(void);
void   UpdateTimer_Sleep(void);
void   UpdateTimer_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define UpdateTimer_BLOCK_CONTROL_REG              (*(reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define UpdateTimer_BLOCK_CONTROL_PTR              ( (reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define UpdateTimer_COMMAND_REG                    (*(reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define UpdateTimer_COMMAND_PTR                    ( (reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define UpdateTimer_INTRRUPT_CAUSE_REG             (*(reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define UpdateTimer_INTRRUPT_CAUSE_PTR             ( (reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define UpdateTimer_CONTROL_REG                    (*(reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__CTRL )
#define UpdateTimer_CONTROL_PTR                    ( (reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__CTRL )
#define UpdateTimer_STATUS_REG                     (*(reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__STATUS )
#define UpdateTimer_STATUS_PTR                     ( (reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__STATUS )
#define UpdateTimer_COUNTER_REG                    (*(reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__COUNTER )
#define UpdateTimer_COUNTER_PTR                    ( (reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__COUNTER )
#define UpdateTimer_COMP_CAP_REG                   (*(reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__CC )
#define UpdateTimer_COMP_CAP_PTR                   ( (reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__CC )
#define UpdateTimer_COMP_CAP_BUF_REG               (*(reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define UpdateTimer_COMP_CAP_BUF_PTR               ( (reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define UpdateTimer_PERIOD_REG                     (*(reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__PERIOD )
#define UpdateTimer_PERIOD_PTR                     ( (reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__PERIOD )
#define UpdateTimer_PERIOD_BUF_REG                 (*(reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define UpdateTimer_PERIOD_BUF_PTR                 ( (reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define UpdateTimer_TRIG_CONTROL0_REG              (*(reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define UpdateTimer_TRIG_CONTROL0_PTR              ( (reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define UpdateTimer_TRIG_CONTROL1_REG              (*(reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define UpdateTimer_TRIG_CONTROL1_PTR              ( (reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define UpdateTimer_TRIG_CONTROL2_REG              (*(reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define UpdateTimer_TRIG_CONTROL2_PTR              ( (reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define UpdateTimer_INTERRUPT_REQ_REG              (*(reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__INTR )
#define UpdateTimer_INTERRUPT_REQ_PTR              ( (reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__INTR )
#define UpdateTimer_INTERRUPT_SET_REG              (*(reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define UpdateTimer_INTERRUPT_SET_PTR              ( (reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define UpdateTimer_INTERRUPT_MASK_REG             (*(reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define UpdateTimer_INTERRUPT_MASK_PTR             ( (reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define UpdateTimer_INTERRUPT_MASKED_REG           (*(reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__INTR_MASKED )
#define UpdateTimer_INTERRUPT_MASKED_PTR           ( (reg32 *) UpdateTimer_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define UpdateTimer_MASK                           ((uint32)UpdateTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define UpdateTimer_RELOAD_CC_SHIFT                (0u)
#define UpdateTimer_RELOAD_PERIOD_SHIFT            (1u)
#define UpdateTimer_PWM_SYNC_KILL_SHIFT            (2u)
#define UpdateTimer_PWM_STOP_KILL_SHIFT            (3u)
#define UpdateTimer_PRESCALER_SHIFT                (8u)
#define UpdateTimer_UPDOWN_SHIFT                   (16u)
#define UpdateTimer_ONESHOT_SHIFT                  (18u)
#define UpdateTimer_QUAD_MODE_SHIFT                (20u)
#define UpdateTimer_INV_OUT_SHIFT                  (20u)
#define UpdateTimer_INV_COMPL_OUT_SHIFT            (21u)
#define UpdateTimer_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define UpdateTimer_RELOAD_CC_MASK                 ((uint32)(UpdateTimer_1BIT_MASK        <<  \
                                                                            UpdateTimer_RELOAD_CC_SHIFT))
#define UpdateTimer_RELOAD_PERIOD_MASK             ((uint32)(UpdateTimer_1BIT_MASK        <<  \
                                                                            UpdateTimer_RELOAD_PERIOD_SHIFT))
#define UpdateTimer_PWM_SYNC_KILL_MASK             ((uint32)(UpdateTimer_1BIT_MASK        <<  \
                                                                            UpdateTimer_PWM_SYNC_KILL_SHIFT))
#define UpdateTimer_PWM_STOP_KILL_MASK             ((uint32)(UpdateTimer_1BIT_MASK        <<  \
                                                                            UpdateTimer_PWM_STOP_KILL_SHIFT))
#define UpdateTimer_PRESCALER_MASK                 ((uint32)(UpdateTimer_8BIT_MASK        <<  \
                                                                            UpdateTimer_PRESCALER_SHIFT))
#define UpdateTimer_UPDOWN_MASK                    ((uint32)(UpdateTimer_2BIT_MASK        <<  \
                                                                            UpdateTimer_UPDOWN_SHIFT))
#define UpdateTimer_ONESHOT_MASK                   ((uint32)(UpdateTimer_1BIT_MASK        <<  \
                                                                            UpdateTimer_ONESHOT_SHIFT))
#define UpdateTimer_QUAD_MODE_MASK                 ((uint32)(UpdateTimer_3BIT_MASK        <<  \
                                                                            UpdateTimer_QUAD_MODE_SHIFT))
#define UpdateTimer_INV_OUT_MASK                   ((uint32)(UpdateTimer_2BIT_MASK        <<  \
                                                                            UpdateTimer_INV_OUT_SHIFT))
#define UpdateTimer_MODE_MASK                      ((uint32)(UpdateTimer_3BIT_MASK        <<  \
                                                                            UpdateTimer_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define UpdateTimer_CAPTURE_SHIFT                  (0u)
#define UpdateTimer_COUNT_SHIFT                    (2u)
#define UpdateTimer_RELOAD_SHIFT                   (4u)
#define UpdateTimer_STOP_SHIFT                     (6u)
#define UpdateTimer_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define UpdateTimer_CAPTURE_MASK                   ((uint32)(UpdateTimer_2BIT_MASK        <<  \
                                                                  UpdateTimer_CAPTURE_SHIFT))
#define UpdateTimer_COUNT_MASK                     ((uint32)(UpdateTimer_2BIT_MASK        <<  \
                                                                  UpdateTimer_COUNT_SHIFT))
#define UpdateTimer_RELOAD_MASK                    ((uint32)(UpdateTimer_2BIT_MASK        <<  \
                                                                  UpdateTimer_RELOAD_SHIFT))
#define UpdateTimer_STOP_MASK                      ((uint32)(UpdateTimer_2BIT_MASK        <<  \
                                                                  UpdateTimer_STOP_SHIFT))
#define UpdateTimer_START_MASK                     ((uint32)(UpdateTimer_2BIT_MASK        <<  \
                                                                  UpdateTimer_START_SHIFT))

/* MASK */
#define UpdateTimer_1BIT_MASK                      ((uint32)0x01u)
#define UpdateTimer_2BIT_MASK                      ((uint32)0x03u)
#define UpdateTimer_3BIT_MASK                      ((uint32)0x07u)
#define UpdateTimer_6BIT_MASK                      ((uint32)0x3Fu)
#define UpdateTimer_8BIT_MASK                      ((uint32)0xFFu)
#define UpdateTimer_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define UpdateTimer_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define UpdateTimer_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(UpdateTimer_QUAD_ENCODING_MODES     << UpdateTimer_QUAD_MODE_SHIFT))       |\
         ((uint32)(UpdateTimer_CONFIG                  << UpdateTimer_MODE_SHIFT)))

#define UpdateTimer_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(UpdateTimer_PWM_STOP_EVENT          << UpdateTimer_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(UpdateTimer_PWM_OUT_INVERT          << UpdateTimer_INV_OUT_SHIFT))         |\
         ((uint32)(UpdateTimer_PWM_OUT_N_INVERT        << UpdateTimer_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(UpdateTimer_PWM_MODE                << UpdateTimer_MODE_SHIFT)))

#define UpdateTimer_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(UpdateTimer_PWM_RUN_MODE         << UpdateTimer_ONESHOT_SHIFT))
            
#define UpdateTimer_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(UpdateTimer_PWM_ALIGN            << UpdateTimer_UPDOWN_SHIFT))

#define UpdateTimer_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(UpdateTimer_PWM_KILL_EVENT      << UpdateTimer_PWM_SYNC_KILL_SHIFT))

#define UpdateTimer_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(UpdateTimer_PWM_DEAD_TIME_CYCLE  << UpdateTimer_PRESCALER_SHIFT))

#define UpdateTimer_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(UpdateTimer_PWM_PRESCALER        << UpdateTimer_PRESCALER_SHIFT))

#define UpdateTimer_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(UpdateTimer_TC_PRESCALER            << UpdateTimer_PRESCALER_SHIFT))       |\
         ((uint32)(UpdateTimer_TC_COUNTER_MODE         << UpdateTimer_UPDOWN_SHIFT))          |\
         ((uint32)(UpdateTimer_TC_RUN_MODE             << UpdateTimer_ONESHOT_SHIFT))         |\
         ((uint32)(UpdateTimer_TC_COMP_CAP_MODE        << UpdateTimer_MODE_SHIFT)))
        
#define UpdateTimer_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(UpdateTimer_QUAD_PHIA_SIGNAL_MODE   << UpdateTimer_COUNT_SHIFT))           |\
         ((uint32)(UpdateTimer_QUAD_INDEX_SIGNAL_MODE  << UpdateTimer_RELOAD_SHIFT))          |\
         ((uint32)(UpdateTimer_QUAD_STOP_SIGNAL_MODE   << UpdateTimer_STOP_SHIFT))            |\
         ((uint32)(UpdateTimer_QUAD_PHIB_SIGNAL_MODE   << UpdateTimer_START_SHIFT)))

#define UpdateTimer_PWM_SIGNALS_MODES                                                              \
        (((uint32)(UpdateTimer_PWM_SWITCH_SIGNAL_MODE  << UpdateTimer_CAPTURE_SHIFT))         |\
         ((uint32)(UpdateTimer_PWM_COUNT_SIGNAL_MODE   << UpdateTimer_COUNT_SHIFT))           |\
         ((uint32)(UpdateTimer_PWM_RELOAD_SIGNAL_MODE  << UpdateTimer_RELOAD_SHIFT))          |\
         ((uint32)(UpdateTimer_PWM_STOP_SIGNAL_MODE    << UpdateTimer_STOP_SHIFT))            |\
         ((uint32)(UpdateTimer_PWM_START_SIGNAL_MODE   << UpdateTimer_START_SHIFT)))

#define UpdateTimer_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(UpdateTimer_TC_CAPTURE_SIGNAL_MODE  << UpdateTimer_CAPTURE_SHIFT))         |\
         ((uint32)(UpdateTimer_TC_COUNT_SIGNAL_MODE    << UpdateTimer_COUNT_SHIFT))           |\
         ((uint32)(UpdateTimer_TC_RELOAD_SIGNAL_MODE   << UpdateTimer_RELOAD_SHIFT))          |\
         ((uint32)(UpdateTimer_TC_STOP_SIGNAL_MODE     << UpdateTimer_STOP_SHIFT))            |\
         ((uint32)(UpdateTimer_TC_START_SIGNAL_MODE    << UpdateTimer_START_SHIFT)))
        
#define UpdateTimer_TIMER_UPDOWN_CNT_USED                                                          \
                ((UpdateTimer__COUNT_UPDOWN0 == UpdateTimer_TC_COUNTER_MODE)                  ||\
                 (UpdateTimer__COUNT_UPDOWN1 == UpdateTimer_TC_COUNTER_MODE))

#define UpdateTimer_PWM_UPDOWN_CNT_USED                                                            \
                ((UpdateTimer__CENTER == UpdateTimer_PWM_ALIGN)                               ||\
                 (UpdateTimer__ASYMMETRIC == UpdateTimer_PWM_ALIGN))               
        
#define UpdateTimer_PWM_PR_INIT_VALUE              (1u)
#define UpdateTimer_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_UpdateTimer_H */

/* [] END OF FILE */
