/*******************************************************************************
* File Name: pwmClock_1.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_pwmClock_1_H)
#define CY_CLOCK_pwmClock_1_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void pwmClock_1_StartEx(uint32 alignClkDiv);
#define pwmClock_1_Start() \
    pwmClock_1_StartEx(pwmClock_1__PA_DIV_ID)

#else

void pwmClock_1_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void pwmClock_1_Stop(void);

void pwmClock_1_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 pwmClock_1_GetDividerRegister(void);
uint8  pwmClock_1_GetFractionalDividerRegister(void);

#define pwmClock_1_Enable()                         pwmClock_1_Start()
#define pwmClock_1_Disable()                        pwmClock_1_Stop()
#define pwmClock_1_SetDividerRegister(clkDivider, reset)  \
    pwmClock_1_SetFractionalDividerRegister((clkDivider), 0u)
#define pwmClock_1_SetDivider(clkDivider)           pwmClock_1_SetDividerRegister((clkDivider), 1u)
#define pwmClock_1_SetDividerValue(clkDivider)      pwmClock_1_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define pwmClock_1_DIV_ID     pwmClock_1__DIV_ID

#define pwmClock_1_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define pwmClock_1_CTRL_REG   (*(reg32 *)pwmClock_1__CTRL_REGISTER)
#define pwmClock_1_DIV_REG    (*(reg32 *)pwmClock_1__DIV_REGISTER)

#define pwmClock_1_CMD_DIV_SHIFT          (0u)
#define pwmClock_1_CMD_PA_DIV_SHIFT       (8u)
#define pwmClock_1_CMD_DISABLE_SHIFT      (30u)
#define pwmClock_1_CMD_ENABLE_SHIFT       (31u)

#define pwmClock_1_CMD_DISABLE_MASK       ((uint32)((uint32)1u << pwmClock_1_CMD_DISABLE_SHIFT))
#define pwmClock_1_CMD_ENABLE_MASK        ((uint32)((uint32)1u << pwmClock_1_CMD_ENABLE_SHIFT))

#define pwmClock_1_DIV_FRAC_MASK  (0x000000F8u)
#define pwmClock_1_DIV_FRAC_SHIFT (3u)
#define pwmClock_1_DIV_INT_MASK   (0xFFFFFF00u)
#define pwmClock_1_DIV_INT_SHIFT  (8u)

#else 

#define pwmClock_1_DIV_REG        (*(reg32 *)pwmClock_1__REGISTER)
#define pwmClock_1_ENABLE_REG     pwmClock_1_DIV_REG
#define pwmClock_1_DIV_FRAC_MASK  pwmClock_1__FRAC_MASK
#define pwmClock_1_DIV_FRAC_SHIFT (16u)
#define pwmClock_1_DIV_INT_MASK   pwmClock_1__DIVIDER_MASK
#define pwmClock_1_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_pwmClock_1_H) */

/* [] END OF FILE */
