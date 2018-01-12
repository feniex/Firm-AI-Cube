/*******************************************************************************
* File Name: motorControlPWM.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_motorControlPWM_H)
#define CY_PWM_motorControlPWM_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 motorControlPWM_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define motorControlPWM_Resolution                     (8u)
#define motorControlPWM_UsingFixedFunction             (0u)
#define motorControlPWM_DeadBandMode                   (0u)
#define motorControlPWM_KillModeMinTime                (0u)
#define motorControlPWM_KillMode                       (0u)
#define motorControlPWM_PWMMode                        (0u)
#define motorControlPWM_PWMModeIsCenterAligned         (0u)
#define motorControlPWM_DeadBandUsed                   (0u)
#define motorControlPWM_DeadBand2_4                    (0u)

#if !defined(motorControlPWM_PWMUDB_genblk8_stsreg__REMOVED)
    #define motorControlPWM_UseStatus                  (0u)
#else
    #define motorControlPWM_UseStatus                  (0u)
#endif /* !defined(motorControlPWM_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(motorControlPWM_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define motorControlPWM_UseControl                 (1u)
#else
    #define motorControlPWM_UseControl                 (0u)
#endif /* !defined(motorControlPWM_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define motorControlPWM_UseOneCompareMode              (1u)
#define motorControlPWM_MinimumKillTime                (1u)
#define motorControlPWM_EnableMode                     (0u)

#define motorControlPWM_CompareMode1SW                 (1u)
#define motorControlPWM_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define motorControlPWM__B_PWM__DISABLED 0
#define motorControlPWM__B_PWM__ASYNCHRONOUS 1
#define motorControlPWM__B_PWM__SINGLECYCLE 2
#define motorControlPWM__B_PWM__LATCHED 3
#define motorControlPWM__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define motorControlPWM__B_PWM__DBMDISABLED 0
#define motorControlPWM__B_PWM__DBM_2_4_CLOCKS 1
#define motorControlPWM__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define motorControlPWM__B_PWM__ONE_OUTPUT 0
#define motorControlPWM__B_PWM__TWO_OUTPUTS 1
#define motorControlPWM__B_PWM__DUAL_EDGE 2
#define motorControlPWM__B_PWM__CENTER_ALIGN 3
#define motorControlPWM__B_PWM__DITHER 5
#define motorControlPWM__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define motorControlPWM__B_PWM__LESS_THAN 1
#define motorControlPWM__B_PWM__LESS_THAN_OR_EQUAL 2
#define motorControlPWM__B_PWM__GREATER_THAN 3
#define motorControlPWM__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define motorControlPWM__B_PWM__EQUAL 0
#define motorControlPWM__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!motorControlPWM_UsingFixedFunction)
        uint8 PWMUdb;               /* PWM Current Counter value  */
        #if(!motorControlPWM_PWMModeIsCenterAligned)
            uint8 PWMPeriod;
        #endif /* (!motorControlPWM_PWMModeIsCenterAligned) */
        #if (motorControlPWM_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (motorControlPWM_UseStatus) */

        /* Backup for Deadband parameters */
        #if(motorControlPWM_DeadBandMode == motorControlPWM__B_PWM__DBM_256_CLOCKS || \
            motorControlPWM_DeadBandMode == motorControlPWM__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(motorControlPWM_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (motorControlPWM_KillModeMinTime) */

        /* Backup control register */
        #if(motorControlPWM_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (motorControlPWM_UseControl) */

    #endif /* (!motorControlPWM_UsingFixedFunction) */

}motorControlPWM_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    motorControlPWM_Start(void) ;
void    motorControlPWM_Stop(void) ;

#if (motorControlPWM_UseStatus || motorControlPWM_UsingFixedFunction)
    void  motorControlPWM_SetInterruptMode(uint8 interruptMode) ;
    uint8 motorControlPWM_ReadStatusRegister(void) ;
#endif /* (motorControlPWM_UseStatus || motorControlPWM_UsingFixedFunction) */

#define motorControlPWM_GetInterruptSource() motorControlPWM_ReadStatusRegister()

#if (motorControlPWM_UseControl)
    uint8 motorControlPWM_ReadControlRegister(void) ;
    void  motorControlPWM_WriteControlRegister(uint8 control)
          ;
#endif /* (motorControlPWM_UseControl) */

#if (motorControlPWM_UseOneCompareMode)
   #if (motorControlPWM_CompareMode1SW)
       void    motorControlPWM_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (motorControlPWM_CompareMode1SW) */
#else
    #if (motorControlPWM_CompareMode1SW)
        void    motorControlPWM_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (motorControlPWM_CompareMode1SW) */
    #if (motorControlPWM_CompareMode2SW)
        void    motorControlPWM_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (motorControlPWM_CompareMode2SW) */
#endif /* (motorControlPWM_UseOneCompareMode) */

#if (!motorControlPWM_UsingFixedFunction)
    uint8   motorControlPWM_ReadCounter(void) ;
    uint8 motorControlPWM_ReadCapture(void) ;

    #if (motorControlPWM_UseStatus)
            void motorControlPWM_ClearFIFO(void) ;
    #endif /* (motorControlPWM_UseStatus) */

    void    motorControlPWM_WriteCounter(uint8 counter)
            ;
#endif /* (!motorControlPWM_UsingFixedFunction) */

void    motorControlPWM_WritePeriod(uint8 period)
        ;
uint8 motorControlPWM_ReadPeriod(void) ;

#if (motorControlPWM_UseOneCompareMode)
    void    motorControlPWM_WriteCompare(uint8 compare)
            ;
    uint8 motorControlPWM_ReadCompare(void) ;
#else
    void    motorControlPWM_WriteCompare1(uint8 compare)
            ;
    uint8 motorControlPWM_ReadCompare1(void) ;
    void    motorControlPWM_WriteCompare2(uint8 compare)
            ;
    uint8 motorControlPWM_ReadCompare2(void) ;
#endif /* (motorControlPWM_UseOneCompareMode) */


#if (motorControlPWM_DeadBandUsed)
    void    motorControlPWM_WriteDeadTime(uint8 deadtime) ;
    uint8   motorControlPWM_ReadDeadTime(void) ;
#endif /* (motorControlPWM_DeadBandUsed) */

#if ( motorControlPWM_KillModeMinTime)
    void motorControlPWM_WriteKillTime(uint8 killtime) ;
    uint8 motorControlPWM_ReadKillTime(void) ;
#endif /* ( motorControlPWM_KillModeMinTime) */

void motorControlPWM_Init(void) ;
void motorControlPWM_Enable(void) ;
void motorControlPWM_Sleep(void) ;
void motorControlPWM_Wakeup(void) ;
void motorControlPWM_SaveConfig(void) ;
void motorControlPWM_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define motorControlPWM_INIT_PERIOD_VALUE          (255u)
#define motorControlPWM_INIT_COMPARE_VALUE1        (128u)
#define motorControlPWM_INIT_COMPARE_VALUE2        (63u)
#define motorControlPWM_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    motorControlPWM_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    motorControlPWM_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    motorControlPWM_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    motorControlPWM_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define motorControlPWM_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  motorControlPWM_CTRL_CMPMODE2_SHIFT)
#define motorControlPWM_DEFAULT_COMPARE1_MODE      (uint8)((uint8)5u <<  motorControlPWM_CTRL_CMPMODE1_SHIFT)
#define motorControlPWM_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (motorControlPWM_UsingFixedFunction)
   #define motorControlPWM_PERIOD_LSB              (*(reg16 *) motorControlPWM_PWMHW__PER0)
   #define motorControlPWM_PERIOD_LSB_PTR          ( (reg16 *) motorControlPWM_PWMHW__PER0)
   #define motorControlPWM_COMPARE1_LSB            (*(reg16 *) motorControlPWM_PWMHW__CNT_CMP0)
   #define motorControlPWM_COMPARE1_LSB_PTR        ( (reg16 *) motorControlPWM_PWMHW__CNT_CMP0)
   #define motorControlPWM_COMPARE2_LSB            (0x00u)
   #define motorControlPWM_COMPARE2_LSB_PTR        (0x00u)
   #define motorControlPWM_COUNTER_LSB             (*(reg16 *) motorControlPWM_PWMHW__CNT_CMP0)
   #define motorControlPWM_COUNTER_LSB_PTR         ( (reg16 *) motorControlPWM_PWMHW__CNT_CMP0)
   #define motorControlPWM_CAPTURE_LSB             (*(reg16 *) motorControlPWM_PWMHW__CAP0)
   #define motorControlPWM_CAPTURE_LSB_PTR         ( (reg16 *) motorControlPWM_PWMHW__CAP0)
   #define motorControlPWM_RT1                     (*(reg8 *)  motorControlPWM_PWMHW__RT1)
   #define motorControlPWM_RT1_PTR                 ( (reg8 *)  motorControlPWM_PWMHW__RT1)

#else
   #if (motorControlPWM_Resolution == 8u) /* 8bit - PWM */

       #if(motorControlPWM_PWMModeIsCenterAligned)
           #define motorControlPWM_PERIOD_LSB      (*(reg8 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
           #define motorControlPWM_PERIOD_LSB_PTR  ((reg8 *)   motorControlPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #else
           #define motorControlPWM_PERIOD_LSB      (*(reg8 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
           #define motorControlPWM_PERIOD_LSB_PTR  ((reg8 *)   motorControlPWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
       #endif /* (motorControlPWM_PWMModeIsCenterAligned) */

       #define motorControlPWM_COMPARE1_LSB        (*(reg8 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define motorControlPWM_COMPARE1_LSB_PTR    ((reg8 *)   motorControlPWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define motorControlPWM_COMPARE2_LSB        (*(reg8 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define motorControlPWM_COMPARE2_LSB_PTR    ((reg8 *)   motorControlPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define motorControlPWM_COUNTERCAP_LSB      (*(reg8 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define motorControlPWM_COUNTERCAP_LSB_PTR  ((reg8 *)   motorControlPWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define motorControlPWM_COUNTER_LSB         (*(reg8 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define motorControlPWM_COUNTER_LSB_PTR     ((reg8 *)   motorControlPWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define motorControlPWM_CAPTURE_LSB         (*(reg8 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__F1_REG)
       #define motorControlPWM_CAPTURE_LSB_PTR     ((reg8 *)   motorControlPWM_PWMUDB_sP8_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(motorControlPWM_PWMModeIsCenterAligned)
               #define motorControlPWM_PERIOD_LSB      (*(reg16 *) motorControlPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
               #define motorControlPWM_PERIOD_LSB_PTR  ((reg16 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #else
               #define motorControlPWM_PERIOD_LSB      (*(reg16 *) motorControlPWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
               #define motorControlPWM_PERIOD_LSB_PTR  ((reg16 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
            #endif /* (motorControlPWM_PWMModeIsCenterAligned) */

            #define motorControlPWM_COMPARE1_LSB       (*(reg16 *) motorControlPWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define motorControlPWM_COMPARE1_LSB_PTR   ((reg16 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define motorControlPWM_COMPARE2_LSB       (*(reg16 *) motorControlPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define motorControlPWM_COMPARE2_LSB_PTR   ((reg16 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define motorControlPWM_COUNTERCAP_LSB     (*(reg16 *) motorControlPWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define motorControlPWM_COUNTERCAP_LSB_PTR ((reg16 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define motorControlPWM_COUNTER_LSB        (*(reg16 *) motorControlPWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define motorControlPWM_COUNTER_LSB_PTR    ((reg16 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define motorControlPWM_CAPTURE_LSB        (*(reg16 *) motorControlPWM_PWMUDB_sP8_pwmdp_u0__F1_REG)
            #define motorControlPWM_CAPTURE_LSB_PTR    ((reg16 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__F1_REG)
        #else
            #if(motorControlPWM_PWMModeIsCenterAligned)
               #define motorControlPWM_PERIOD_LSB      (*(reg16 *) motorControlPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
               #define motorControlPWM_PERIOD_LSB_PTR  ((reg16 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #else
               #define motorControlPWM_PERIOD_LSB      (*(reg16 *) motorControlPWM_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
               #define motorControlPWM_PERIOD_LSB_PTR  ((reg16 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
            #endif /* (motorControlPWM_PWMModeIsCenterAligned) */

            #define motorControlPWM_COMPARE1_LSB       (*(reg16 *) motorControlPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define motorControlPWM_COMPARE1_LSB_PTR   ((reg16 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define motorControlPWM_COMPARE2_LSB       (*(reg16 *) motorControlPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define motorControlPWM_COMPARE2_LSB_PTR   ((reg16 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define motorControlPWM_COUNTERCAP_LSB     (*(reg16 *) motorControlPWM_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define motorControlPWM_COUNTERCAP_LSB_PTR ((reg16 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define motorControlPWM_COUNTER_LSB        (*(reg16 *) motorControlPWM_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define motorControlPWM_COUNTER_LSB_PTR    ((reg16 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define motorControlPWM_CAPTURE_LSB        (*(reg16 *) motorControlPWM_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
            #define motorControlPWM_CAPTURE_LSB_PTR    ((reg16 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define motorControlPWM_AUX_CONTROLDP1          (*(reg8 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)
       #define motorControlPWM_AUX_CONTROLDP1_PTR      ((reg8 *)   motorControlPWM_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (motorControlPWM_Resolution == 8) */

   #define motorControlPWM_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
   #define motorControlPWM_AUX_CONTROLDP0          (*(reg8 *)  motorControlPWM_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)
   #define motorControlPWM_AUX_CONTROLDP0_PTR      ((reg8 *)   motorControlPWM_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (motorControlPWM_UsingFixedFunction) */

#if(motorControlPWM_KillModeMinTime )
    #define motorControlPWM_KILLMODEMINTIME        (*(reg8 *)  motorControlPWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define motorControlPWM_KILLMODEMINTIME_PTR    ((reg8 *)   motorControlPWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (motorControlPWM_KillModeMinTime ) */

#if(motorControlPWM_DeadBandMode == motorControlPWM__B_PWM__DBM_256_CLOCKS)
    #define motorControlPWM_DEADBAND_COUNT         (*(reg8 *)  motorControlPWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define motorControlPWM_DEADBAND_COUNT_PTR     ((reg8 *)   motorControlPWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define motorControlPWM_DEADBAND_LSB_PTR       ((reg8 *)   motorControlPWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define motorControlPWM_DEADBAND_LSB           (*(reg8 *)  motorControlPWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(motorControlPWM_DeadBandMode == motorControlPWM__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (motorControlPWM_UsingFixedFunction)
        #define motorControlPWM_DEADBAND_COUNT         (*(reg8 *)  motorControlPWM_PWMHW__CFG0)
        #define motorControlPWM_DEADBAND_COUNT_PTR     ((reg8 *)   motorControlPWM_PWMHW__CFG0)
        #define motorControlPWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << motorControlPWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define motorControlPWM_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define motorControlPWM_DEADBAND_COUNT         (*(reg8 *)  motorControlPWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define motorControlPWM_DEADBAND_COUNT_PTR     ((reg8 *)   motorControlPWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define motorControlPWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << motorControlPWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define motorControlPWM_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (motorControlPWM_UsingFixedFunction) */
#endif /* (motorControlPWM_DeadBandMode == motorControlPWM__B_PWM__DBM_256_CLOCKS) */



#if (motorControlPWM_UsingFixedFunction)
    #define motorControlPWM_STATUS                 (*(reg8 *) motorControlPWM_PWMHW__SR0)
    #define motorControlPWM_STATUS_PTR             ((reg8 *) motorControlPWM_PWMHW__SR0)
    #define motorControlPWM_STATUS_MASK            (*(reg8 *) motorControlPWM_PWMHW__SR0)
    #define motorControlPWM_STATUS_MASK_PTR        ((reg8 *) motorControlPWM_PWMHW__SR0)
    #define motorControlPWM_CONTROL                (*(reg8 *) motorControlPWM_PWMHW__CFG0)
    #define motorControlPWM_CONTROL_PTR            ((reg8 *) motorControlPWM_PWMHW__CFG0)
    #define motorControlPWM_CONTROL2               (*(reg8 *) motorControlPWM_PWMHW__CFG1)
    #define motorControlPWM_CONTROL3               (*(reg8 *) motorControlPWM_PWMHW__CFG2)
    #define motorControlPWM_GLOBAL_ENABLE          (*(reg8 *) motorControlPWM_PWMHW__PM_ACT_CFG)
    #define motorControlPWM_GLOBAL_ENABLE_PTR      ( (reg8 *) motorControlPWM_PWMHW__PM_ACT_CFG)
    #define motorControlPWM_GLOBAL_STBY_ENABLE     (*(reg8 *) motorControlPWM_PWMHW__PM_STBY_CFG)
    #define motorControlPWM_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) motorControlPWM_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define motorControlPWM_BLOCK_EN_MASK          (motorControlPWM_PWMHW__PM_ACT_MSK)
    #define motorControlPWM_BLOCK_STBY_EN_MASK     (motorControlPWM_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define motorControlPWM_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define motorControlPWM_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define motorControlPWM_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define motorControlPWM_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define motorControlPWM_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define motorControlPWM_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define motorControlPWM_CTRL_ENABLE            (uint8)((uint8)0x01u << motorControlPWM_CTRL_ENABLE_SHIFT)
    #define motorControlPWM_CTRL_RESET             (uint8)((uint8)0x01u << motorControlPWM_CTRL_RESET_SHIFT)
    #define motorControlPWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << motorControlPWM_CTRL_CMPMODE2_SHIFT)
    #define motorControlPWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << motorControlPWM_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define motorControlPWM_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define motorControlPWM_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << motorControlPWM_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define motorControlPWM_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define motorControlPWM_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define motorControlPWM_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define motorControlPWM_STATUS_TC_INT_EN_MASK_SHIFT            (motorControlPWM_STATUS_TC_SHIFT - 4u)
    #define motorControlPWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define motorControlPWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (motorControlPWM_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define motorControlPWM_STATUS_TC              (uint8)((uint8)0x01u << motorControlPWM_STATUS_TC_SHIFT)
    #define motorControlPWM_STATUS_CMP1            (uint8)((uint8)0x01u << motorControlPWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define motorControlPWM_STATUS_TC_INT_EN_MASK              (uint8)((uint8)motorControlPWM_STATUS_TC >> 4u)
    #define motorControlPWM_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)motorControlPWM_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define motorControlPWM_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define motorControlPWM_RT1_MASK              (uint8)((uint8)0x03u << motorControlPWM_RT1_SHIFT)
    #define motorControlPWM_SYNC                  (uint8)((uint8)0x03u << motorControlPWM_RT1_SHIFT)
    #define motorControlPWM_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define motorControlPWM_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << motorControlPWM_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define motorControlPWM_SYNCDSI_EN            (uint8)((uint8)0x0Fu << motorControlPWM_SYNCDSI_SHIFT)


#else
    #define motorControlPWM_STATUS                (*(reg8 *)   motorControlPWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define motorControlPWM_STATUS_PTR            ((reg8 *)    motorControlPWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define motorControlPWM_STATUS_MASK           (*(reg8 *)   motorControlPWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define motorControlPWM_STATUS_MASK_PTR       ((reg8 *)    motorControlPWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define motorControlPWM_STATUS_AUX_CTRL       (*(reg8 *)   motorControlPWM_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define motorControlPWM_CONTROL               (*(reg8 *)   motorControlPWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define motorControlPWM_CONTROL_PTR           ((reg8 *)    motorControlPWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define motorControlPWM_CTRL_ENABLE_SHIFT      (0x07u)
    #define motorControlPWM_CTRL_RESET_SHIFT       (0x06u)
    #define motorControlPWM_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define motorControlPWM_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define motorControlPWM_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define motorControlPWM_CTRL_ENABLE            (uint8)((uint8)0x01u << motorControlPWM_CTRL_ENABLE_SHIFT)
    #define motorControlPWM_CTRL_RESET             (uint8)((uint8)0x01u << motorControlPWM_CTRL_RESET_SHIFT)
    #define motorControlPWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << motorControlPWM_CTRL_CMPMODE2_SHIFT)
    #define motorControlPWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << motorControlPWM_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define motorControlPWM_STATUS_KILL_SHIFT          (0x05u)
    #define motorControlPWM_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define motorControlPWM_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define motorControlPWM_STATUS_TC_SHIFT            (0x02u)
    #define motorControlPWM_STATUS_CMP2_SHIFT          (0x01u)
    #define motorControlPWM_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define motorControlPWM_STATUS_KILL_INT_EN_MASK_SHIFT          (motorControlPWM_STATUS_KILL_SHIFT)
    #define motorControlPWM_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (motorControlPWM_STATUS_FIFONEMPTY_SHIFT)
    #define motorControlPWM_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (motorControlPWM_STATUS_FIFOFULL_SHIFT)
    #define motorControlPWM_STATUS_TC_INT_EN_MASK_SHIFT            (motorControlPWM_STATUS_TC_SHIFT)
    #define motorControlPWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (motorControlPWM_STATUS_CMP2_SHIFT)
    #define motorControlPWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (motorControlPWM_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define motorControlPWM_STATUS_KILL            (uint8)((uint8)0x00u << motorControlPWM_STATUS_KILL_SHIFT )
    #define motorControlPWM_STATUS_FIFOFULL        (uint8)((uint8)0x01u << motorControlPWM_STATUS_FIFOFULL_SHIFT)
    #define motorControlPWM_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << motorControlPWM_STATUS_FIFONEMPTY_SHIFT)
    #define motorControlPWM_STATUS_TC              (uint8)((uint8)0x01u << motorControlPWM_STATUS_TC_SHIFT)
    #define motorControlPWM_STATUS_CMP2            (uint8)((uint8)0x01u << motorControlPWM_STATUS_CMP2_SHIFT)
    #define motorControlPWM_STATUS_CMP1            (uint8)((uint8)0x01u << motorControlPWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define motorControlPWM_STATUS_KILL_INT_EN_MASK            (motorControlPWM_STATUS_KILL)
    #define motorControlPWM_STATUS_FIFOFULL_INT_EN_MASK        (motorControlPWM_STATUS_FIFOFULL)
    #define motorControlPWM_STATUS_FIFONEMPTY_INT_EN_MASK      (motorControlPWM_STATUS_FIFONEMPTY)
    #define motorControlPWM_STATUS_TC_INT_EN_MASK              (motorControlPWM_STATUS_TC)
    #define motorControlPWM_STATUS_CMP2_INT_EN_MASK            (motorControlPWM_STATUS_CMP2)
    #define motorControlPWM_STATUS_CMP1_INT_EN_MASK            (motorControlPWM_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define motorControlPWM_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define motorControlPWM_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define motorControlPWM_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define motorControlPWM_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define motorControlPWM_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* motorControlPWM_UsingFixedFunction */

#endif  /* CY_PWM_motorControlPWM_H */


/* [] END OF FILE */
