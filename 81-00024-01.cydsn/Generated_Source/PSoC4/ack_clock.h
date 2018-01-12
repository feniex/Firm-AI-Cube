/*******************************************************************************
* File Name: ack_clock.h
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

#if !defined(CY_CLOCK_ack_clock_H)
#define CY_CLOCK_ack_clock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void ack_clock_StartEx(uint32 alignClkDiv);
#define ack_clock_Start() \
    ack_clock_StartEx(ack_clock__PA_DIV_ID)

#else

void ack_clock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void ack_clock_Stop(void);

void ack_clock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 ack_clock_GetDividerRegister(void);
uint8  ack_clock_GetFractionalDividerRegister(void);

#define ack_clock_Enable()                         ack_clock_Start()
#define ack_clock_Disable()                        ack_clock_Stop()
#define ack_clock_SetDividerRegister(clkDivider, reset)  \
    ack_clock_SetFractionalDividerRegister((clkDivider), 0u)
#define ack_clock_SetDivider(clkDivider)           ack_clock_SetDividerRegister((clkDivider), 1u)
#define ack_clock_SetDividerValue(clkDivider)      ack_clock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define ack_clock_DIV_ID     ack_clock__DIV_ID

#define ack_clock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define ack_clock_CTRL_REG   (*(reg32 *)ack_clock__CTRL_REGISTER)
#define ack_clock_DIV_REG    (*(reg32 *)ack_clock__DIV_REGISTER)

#define ack_clock_CMD_DIV_SHIFT          (0u)
#define ack_clock_CMD_PA_DIV_SHIFT       (8u)
#define ack_clock_CMD_DISABLE_SHIFT      (30u)
#define ack_clock_CMD_ENABLE_SHIFT       (31u)

#define ack_clock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << ack_clock_CMD_DISABLE_SHIFT))
#define ack_clock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << ack_clock_CMD_ENABLE_SHIFT))

#define ack_clock_DIV_FRAC_MASK  (0x000000F8u)
#define ack_clock_DIV_FRAC_SHIFT (3u)
#define ack_clock_DIV_INT_MASK   (0xFFFFFF00u)
#define ack_clock_DIV_INT_SHIFT  (8u)

#else 

#define ack_clock_DIV_REG        (*(reg32 *)ack_clock__REGISTER)
#define ack_clock_ENABLE_REG     ack_clock_DIV_REG
#define ack_clock_DIV_FRAC_MASK  ack_clock__FRAC_MASK
#define ack_clock_DIV_FRAC_SHIFT (16u)
#define ack_clock_DIV_INT_MASK   ack_clock__DIVIDER_MASK
#define ack_clock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_ack_clock_H) */

/* [] END OF FILE */
