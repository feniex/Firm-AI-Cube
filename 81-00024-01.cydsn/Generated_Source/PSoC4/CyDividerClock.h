/*******************************************************************************
* File Name: CyDividerClock.h
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

#if !defined(CY_CLOCK_CyDividerClock_H)
#define CY_CLOCK_CyDividerClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void CyDividerClock_StartEx(uint32 alignClkDiv);
#define CyDividerClock_Start() \
    CyDividerClock_StartEx(CyDividerClock__PA_DIV_ID)

#else

void CyDividerClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void CyDividerClock_Stop(void);

void CyDividerClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 CyDividerClock_GetDividerRegister(void);
uint8  CyDividerClock_GetFractionalDividerRegister(void);

#define CyDividerClock_Enable()                         CyDividerClock_Start()
#define CyDividerClock_Disable()                        CyDividerClock_Stop()
#define CyDividerClock_SetDividerRegister(clkDivider, reset)  \
    CyDividerClock_SetFractionalDividerRegister((clkDivider), 0u)
#define CyDividerClock_SetDivider(clkDivider)           CyDividerClock_SetDividerRegister((clkDivider), 1u)
#define CyDividerClock_SetDividerValue(clkDivider)      CyDividerClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define CyDividerClock_DIV_ID     CyDividerClock__DIV_ID

#define CyDividerClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define CyDividerClock_CTRL_REG   (*(reg32 *)CyDividerClock__CTRL_REGISTER)
#define CyDividerClock_DIV_REG    (*(reg32 *)CyDividerClock__DIV_REGISTER)

#define CyDividerClock_CMD_DIV_SHIFT          (0u)
#define CyDividerClock_CMD_PA_DIV_SHIFT       (8u)
#define CyDividerClock_CMD_DISABLE_SHIFT      (30u)
#define CyDividerClock_CMD_ENABLE_SHIFT       (31u)

#define CyDividerClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << CyDividerClock_CMD_DISABLE_SHIFT))
#define CyDividerClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << CyDividerClock_CMD_ENABLE_SHIFT))

#define CyDividerClock_DIV_FRAC_MASK  (0x000000F8u)
#define CyDividerClock_DIV_FRAC_SHIFT (3u)
#define CyDividerClock_DIV_INT_MASK   (0xFFFFFF00u)
#define CyDividerClock_DIV_INT_SHIFT  (8u)

#else 

#define CyDividerClock_DIV_REG        (*(reg32 *)CyDividerClock__REGISTER)
#define CyDividerClock_ENABLE_REG     CyDividerClock_DIV_REG
#define CyDividerClock_DIV_FRAC_MASK  CyDividerClock__FRAC_MASK
#define CyDividerClock_DIV_FRAC_SHIFT (16u)
#define CyDividerClock_DIV_INT_MASK   CyDividerClock__DIVIDER_MASK
#define CyDividerClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_CyDividerClock_H) */

/* [] END OF FILE */
