/*******************************************************************************
* File Name: overCurrentTimerISR.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_overCurrentTimerISR_H)
#define CY_ISR_overCurrentTimerISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void overCurrentTimerISR_Start(void);
void overCurrentTimerISR_StartEx(cyisraddress address);
void overCurrentTimerISR_Stop(void);

CY_ISR_PROTO(overCurrentTimerISR_Interrupt);

void overCurrentTimerISR_SetVector(cyisraddress address);
cyisraddress overCurrentTimerISR_GetVector(void);

void overCurrentTimerISR_SetPriority(uint8 priority);
uint8 overCurrentTimerISR_GetPriority(void);

void overCurrentTimerISR_Enable(void);
uint8 overCurrentTimerISR_GetState(void);
void overCurrentTimerISR_Disable(void);

void overCurrentTimerISR_SetPending(void);
void overCurrentTimerISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the overCurrentTimerISR ISR. */
#define overCurrentTimerISR_INTC_VECTOR            ((reg32 *) overCurrentTimerISR__INTC_VECT)

/* Address of the overCurrentTimerISR ISR priority. */
#define overCurrentTimerISR_INTC_PRIOR             ((reg32 *) overCurrentTimerISR__INTC_PRIOR_REG)

/* Priority of the overCurrentTimerISR interrupt. */
#define overCurrentTimerISR_INTC_PRIOR_NUMBER      overCurrentTimerISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable overCurrentTimerISR interrupt. */
#define overCurrentTimerISR_INTC_SET_EN            ((reg32 *) overCurrentTimerISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the overCurrentTimerISR interrupt. */
#define overCurrentTimerISR_INTC_CLR_EN            ((reg32 *) overCurrentTimerISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the overCurrentTimerISR interrupt state to pending. */
#define overCurrentTimerISR_INTC_SET_PD            ((reg32 *) overCurrentTimerISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the overCurrentTimerISR interrupt. */
#define overCurrentTimerISR_INTC_CLR_PD            ((reg32 *) overCurrentTimerISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_overCurrentTimerISR_H */


/* [] END OF FILE */
