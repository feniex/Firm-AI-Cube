/*******************************************************************************
* File Name: pwmClock.h
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

#if !defined(CY_CLOCK_pwmClock_H)
#define CY_CLOCK_pwmClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void pwmClock_StartEx(uint32 alignClkDiv);
#define pwmClock_Start() \
    pwmClock_StartEx(pwmClock__PA_DIV_ID)

#else

void pwmClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void pwmClock_Stop(void);

void pwmClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 pwmClock_GetDividerRegister(void);
uint8  pwmClock_GetFractionalDividerRegister(void);

#define pwmClock_Enable()                         pwmClock_Start()
#define pwmClock_Disable()                        pwmClock_Stop()
#define pwmClock_SetDividerRegister(clkDivider, reset)  \
    pwmClock_SetFractionalDividerRegister((clkDivider), 0u)
#define pwmClock_SetDivider(clkDivider)           pwmClock_SetDividerRegister((clkDivider), 1u)
#define pwmClock_SetDividerValue(clkDivider)      pwmClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define pwmClock_DIV_ID     pwmClock__DIV_ID

#define pwmClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define pwmClock_CTRL_REG   (*(reg32 *)pwmClock__CTRL_REGISTER)
#define pwmClock_DIV_REG    (*(reg32 *)pwmClock__DIV_REGISTER)

#define pwmClock_CMD_DIV_SHIFT          (0u)
#define pwmClock_CMD_PA_DIV_SHIFT       (8u)
#define pwmClock_CMD_DISABLE_SHIFT      (30u)
#define pwmClock_CMD_ENABLE_SHIFT       (31u)

#define pwmClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << pwmClock_CMD_DISABLE_SHIFT))
#define pwmClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << pwmClock_CMD_ENABLE_SHIFT))

#define pwmClock_DIV_FRAC_MASK  (0x000000F8u)
#define pwmClock_DIV_FRAC_SHIFT (3u)
#define pwmClock_DIV_INT_MASK   (0xFFFFFF00u)
#define pwmClock_DIV_INT_SHIFT  (8u)

#else 

#define pwmClock_DIV_REG        (*(reg32 *)pwmClock__REGISTER)
#define pwmClock_ENABLE_REG     pwmClock_DIV_REG
#define pwmClock_DIV_FRAC_MASK  pwmClock__FRAC_MASK
#define pwmClock_DIV_FRAC_SHIFT (16u)
#define pwmClock_DIV_INT_MASK   pwmClock__DIVIDER_MASK
#define pwmClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_pwmClock_H) */

/* [] END OF FILE */
