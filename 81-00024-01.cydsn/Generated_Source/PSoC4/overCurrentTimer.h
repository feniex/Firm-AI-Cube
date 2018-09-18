/*******************************************************************************
* File Name: overCurrentTimer.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_overCurrentTimer_H)
#define CY_TIMER_overCurrentTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 overCurrentTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define overCurrentTimer_Resolution                 8u
#define overCurrentTimer_UsingFixedFunction         0u
#define overCurrentTimer_UsingHWCaptureCounter      0u
#define overCurrentTimer_SoftwareCaptureMode        0u
#define overCurrentTimer_SoftwareTriggerMode        0u
#define overCurrentTimer_UsingHWEnable              0u
#define overCurrentTimer_EnableTriggerMode          0u
#define overCurrentTimer_InterruptOnCaptureCount    0u
#define overCurrentTimer_RunModeUsed                0u
#define overCurrentTimer_ControlRegRemoved          0u

#if defined(overCurrentTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define overCurrentTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (overCurrentTimer_UsingFixedFunction)
    #define overCurrentTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define overCurrentTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End overCurrentTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!overCurrentTimer_UsingFixedFunction)

        uint8 TimerUdb;
        uint8 InterruptMaskValue;
        #if (overCurrentTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!overCurrentTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}overCurrentTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    overCurrentTimer_Start(void) ;
void    overCurrentTimer_Stop(void) ;

void    overCurrentTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   overCurrentTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define overCurrentTimer_GetInterruptSource() overCurrentTimer_ReadStatusRegister()

#if(!overCurrentTimer_UDB_CONTROL_REG_REMOVED)
    uint8   overCurrentTimer_ReadControlRegister(void) ;
    void    overCurrentTimer_WriteControlRegister(uint8 control) ;
#endif /* (!overCurrentTimer_UDB_CONTROL_REG_REMOVED) */

uint8  overCurrentTimer_ReadPeriod(void) ;
void    overCurrentTimer_WritePeriod(uint8 period) ;
uint8  overCurrentTimer_ReadCounter(void) ;
void    overCurrentTimer_WriteCounter(uint8 counter) ;
uint8  overCurrentTimer_ReadCapture(void) ;
void    overCurrentTimer_SoftwareCapture(void) ;

#if(!overCurrentTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (overCurrentTimer_SoftwareCaptureMode)
        void    overCurrentTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!overCurrentTimer_UsingFixedFunction) */

    #if (overCurrentTimer_SoftwareTriggerMode)
        void    overCurrentTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (overCurrentTimer_SoftwareTriggerMode) */

    #if (overCurrentTimer_EnableTriggerMode)
        void    overCurrentTimer_EnableTrigger(void) ;
        void    overCurrentTimer_DisableTrigger(void) ;
    #endif /* (overCurrentTimer_EnableTriggerMode) */


    #if(overCurrentTimer_InterruptOnCaptureCount)
        void    overCurrentTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (overCurrentTimer_InterruptOnCaptureCount) */

    #if (overCurrentTimer_UsingHWCaptureCounter)
        void    overCurrentTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   overCurrentTimer_ReadCaptureCount(void) ;
    #endif /* (overCurrentTimer_UsingHWCaptureCounter) */

    void overCurrentTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void overCurrentTimer_Init(void)          ;
void overCurrentTimer_Enable(void)        ;
void overCurrentTimer_SaveConfig(void)    ;
void overCurrentTimer_RestoreConfig(void) ;
void overCurrentTimer_Sleep(void)         ;
void overCurrentTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define overCurrentTimer__B_TIMER__CM_NONE 0
#define overCurrentTimer__B_TIMER__CM_RISINGEDGE 1
#define overCurrentTimer__B_TIMER__CM_FALLINGEDGE 2
#define overCurrentTimer__B_TIMER__CM_EITHEREDGE 3
#define overCurrentTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define overCurrentTimer__B_TIMER__TM_NONE 0x00u
#define overCurrentTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define overCurrentTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define overCurrentTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define overCurrentTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define overCurrentTimer_INIT_PERIOD             49u
#define overCurrentTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << overCurrentTimer_CTRL_CAP_MODE_SHIFT))
#define overCurrentTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << overCurrentTimer_CTRL_TRIG_MODE_SHIFT))
#if (overCurrentTimer_UsingFixedFunction)
    #define overCurrentTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << overCurrentTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << overCurrentTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define overCurrentTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << overCurrentTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << overCurrentTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << overCurrentTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (overCurrentTimer_UsingFixedFunction) */
#define overCurrentTimer_INIT_CAPTURE_COUNT      (2u)
#define overCurrentTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << overCurrentTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (overCurrentTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define overCurrentTimer_STATUS         (*(reg8 *) overCurrentTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define overCurrentTimer_STATUS_MASK    (*(reg8 *) overCurrentTimer_TimerHW__SR0 )
    #define overCurrentTimer_CONTROL        (*(reg8 *) overCurrentTimer_TimerHW__CFG0)
    #define overCurrentTimer_CONTROL2       (*(reg8 *) overCurrentTimer_TimerHW__CFG1)
    #define overCurrentTimer_CONTROL2_PTR   ( (reg8 *) overCurrentTimer_TimerHW__CFG1)
    #define overCurrentTimer_RT1            (*(reg8 *) overCurrentTimer_TimerHW__RT1)
    #define overCurrentTimer_RT1_PTR        ( (reg8 *) overCurrentTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define overCurrentTimer_CONTROL3       (*(reg8 *) overCurrentTimer_TimerHW__CFG2)
        #define overCurrentTimer_CONTROL3_PTR   ( (reg8 *) overCurrentTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define overCurrentTimer_GLOBAL_ENABLE  (*(reg8 *) overCurrentTimer_TimerHW__PM_ACT_CFG)
    #define overCurrentTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) overCurrentTimer_TimerHW__PM_STBY_CFG)

    #define overCurrentTimer_CAPTURE_LSB         (* (reg16 *) overCurrentTimer_TimerHW__CAP0 )
    #define overCurrentTimer_CAPTURE_LSB_PTR       ((reg16 *) overCurrentTimer_TimerHW__CAP0 )
    #define overCurrentTimer_PERIOD_LSB          (* (reg16 *) overCurrentTimer_TimerHW__PER0 )
    #define overCurrentTimer_PERIOD_LSB_PTR        ((reg16 *) overCurrentTimer_TimerHW__PER0 )
    #define overCurrentTimer_COUNTER_LSB         (* (reg16 *) overCurrentTimer_TimerHW__CNT_CMP0 )
    #define overCurrentTimer_COUNTER_LSB_PTR       ((reg16 *) overCurrentTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define overCurrentTimer_BLOCK_EN_MASK                     overCurrentTimer_TimerHW__PM_ACT_MSK
    #define overCurrentTimer_BLOCK_STBY_EN_MASK                overCurrentTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define overCurrentTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define overCurrentTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define overCurrentTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define overCurrentTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define overCurrentTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define overCurrentTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << overCurrentTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define overCurrentTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define overCurrentTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << overCurrentTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define overCurrentTimer_CTRL_MODE_SHIFT                 0x01u
        #define overCurrentTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << overCurrentTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define overCurrentTimer_CTRL_RCOD_SHIFT        0x02u
        #define overCurrentTimer_CTRL_ENBL_SHIFT        0x00u
        #define overCurrentTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define overCurrentTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << overCurrentTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define overCurrentTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << overCurrentTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define overCurrentTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << overCurrentTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define overCurrentTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << overCurrentTimer_CTRL_RCOD_SHIFT))
        #define overCurrentTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << overCurrentTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define overCurrentTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define overCurrentTimer_RT1_MASK                        ((uint8)((uint8)0x03u << overCurrentTimer_RT1_SHIFT))
    #define overCurrentTimer_SYNC                            ((uint8)((uint8)0x03u << overCurrentTimer_RT1_SHIFT))
    #define overCurrentTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define overCurrentTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << overCurrentTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define overCurrentTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << overCurrentTimer_SYNCDSI_SHIFT))

    #define overCurrentTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << overCurrentTimer_CTRL_MODE_SHIFT))
    #define overCurrentTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << overCurrentTimer_CTRL_MODE_SHIFT))
    #define overCurrentTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << overCurrentTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define overCurrentTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define overCurrentTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define overCurrentTimer_STATUS_TC_INT_MASK_SHIFT        (overCurrentTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define overCurrentTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (overCurrentTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define overCurrentTimer_STATUS_TC                       ((uint8)((uint8)0x01u << overCurrentTimer_STATUS_TC_SHIFT))
    #define overCurrentTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << overCurrentTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define overCurrentTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << overCurrentTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define overCurrentTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << overCurrentTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define overCurrentTimer_STATUS              (* (reg8 *) overCurrentTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define overCurrentTimer_STATUS_MASK         (* (reg8 *) overCurrentTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define overCurrentTimer_STATUS_AUX_CTRL     (* (reg8 *) overCurrentTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define overCurrentTimer_CONTROL             (* (reg8 *) overCurrentTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(overCurrentTimer_Resolution <= 8u) /* 8-bit Timer */
        #define overCurrentTimer_CAPTURE_LSB         (* (reg8 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define overCurrentTimer_CAPTURE_LSB_PTR       ((reg8 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define overCurrentTimer_PERIOD_LSB          (* (reg8 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define overCurrentTimer_PERIOD_LSB_PTR        ((reg8 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define overCurrentTimer_COUNTER_LSB         (* (reg8 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define overCurrentTimer_COUNTER_LSB_PTR       ((reg8 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
    #elif(overCurrentTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define overCurrentTimer_CAPTURE_LSB         (* (reg16 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define overCurrentTimer_CAPTURE_LSB_PTR       ((reg16 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define overCurrentTimer_PERIOD_LSB          (* (reg16 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define overCurrentTimer_PERIOD_LSB_PTR        ((reg16 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define overCurrentTimer_COUNTER_LSB         (* (reg16 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define overCurrentTimer_COUNTER_LSB_PTR       ((reg16 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define overCurrentTimer_CAPTURE_LSB         (* (reg16 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define overCurrentTimer_CAPTURE_LSB_PTR       ((reg16 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define overCurrentTimer_PERIOD_LSB          (* (reg16 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define overCurrentTimer_PERIOD_LSB_PTR        ((reg16 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define overCurrentTimer_COUNTER_LSB         (* (reg16 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
            #define overCurrentTimer_COUNTER_LSB_PTR       ((reg16 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(overCurrentTimer_Resolution <= 24u)/* 24-bit Timer */
        #define overCurrentTimer_CAPTURE_LSB         (* (reg32 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define overCurrentTimer_CAPTURE_LSB_PTR       ((reg32 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define overCurrentTimer_PERIOD_LSB          (* (reg32 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define overCurrentTimer_PERIOD_LSB_PTR        ((reg32 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define overCurrentTimer_COUNTER_LSB         (* (reg32 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define overCurrentTimer_COUNTER_LSB_PTR       ((reg32 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define overCurrentTimer_CAPTURE_LSB         (* (reg32 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define overCurrentTimer_CAPTURE_LSB_PTR       ((reg32 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define overCurrentTimer_PERIOD_LSB          (* (reg32 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define overCurrentTimer_PERIOD_LSB_PTR        ((reg32 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define overCurrentTimer_COUNTER_LSB         (* (reg32 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define overCurrentTimer_COUNTER_LSB_PTR       ((reg32 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define overCurrentTimer_CAPTURE_LSB         (* (reg32 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define overCurrentTimer_CAPTURE_LSB_PTR       ((reg32 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define overCurrentTimer_PERIOD_LSB          (* (reg32 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define overCurrentTimer_PERIOD_LSB_PTR        ((reg32 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define overCurrentTimer_COUNTER_LSB         (* (reg32 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
            #define overCurrentTimer_COUNTER_LSB_PTR       ((reg32 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define overCurrentTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) overCurrentTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
    
    #if (overCurrentTimer_UsingHWCaptureCounter)
        #define overCurrentTimer_CAP_COUNT              (*(reg8 *) overCurrentTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define overCurrentTimer_CAP_COUNT_PTR          ( (reg8 *) overCurrentTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define overCurrentTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) overCurrentTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define overCurrentTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) overCurrentTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (overCurrentTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define overCurrentTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define overCurrentTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define overCurrentTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define overCurrentTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define overCurrentTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define overCurrentTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << overCurrentTimer_CTRL_INTCNT_SHIFT))
    #define overCurrentTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << overCurrentTimer_CTRL_TRIG_MODE_SHIFT))
    #define overCurrentTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << overCurrentTimer_CTRL_TRIG_EN_SHIFT))
    #define overCurrentTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << overCurrentTimer_CTRL_CAP_MODE_SHIFT))
    #define overCurrentTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << overCurrentTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define overCurrentTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define overCurrentTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define overCurrentTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define overCurrentTimer_STATUS_TC_INT_MASK_SHIFT       overCurrentTimer_STATUS_TC_SHIFT
    #define overCurrentTimer_STATUS_CAPTURE_INT_MASK_SHIFT  overCurrentTimer_STATUS_CAPTURE_SHIFT
    #define overCurrentTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define overCurrentTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define overCurrentTimer_STATUS_FIFOFULL_INT_MASK_SHIFT overCurrentTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define overCurrentTimer_STATUS_TC                      ((uint8)((uint8)0x01u << overCurrentTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define overCurrentTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << overCurrentTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define overCurrentTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << overCurrentTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define overCurrentTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << overCurrentTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define overCurrentTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << overCurrentTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define overCurrentTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << overCurrentTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define overCurrentTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << overCurrentTimer_STATUS_FIFOFULL_SHIFT))

    #define overCurrentTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define overCurrentTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define overCurrentTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define overCurrentTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define overCurrentTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define overCurrentTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_overCurrentTimer_H */


/* [] END OF FILE */
