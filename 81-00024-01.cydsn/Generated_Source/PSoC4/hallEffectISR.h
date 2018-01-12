/*******************************************************************************
* File Name: hallEffectISR.h
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
#if !defined(CY_ISR_hallEffectISR_H)
#define CY_ISR_hallEffectISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void hallEffectISR_Start(void);
void hallEffectISR_StartEx(cyisraddress address);
void hallEffectISR_Stop(void);

CY_ISR_PROTO(hallEffectISR_Interrupt);

void hallEffectISR_SetVector(cyisraddress address);
cyisraddress hallEffectISR_GetVector(void);

void hallEffectISR_SetPriority(uint8 priority);
uint8 hallEffectISR_GetPriority(void);

void hallEffectISR_Enable(void);
uint8 hallEffectISR_GetState(void);
void hallEffectISR_Disable(void);

void hallEffectISR_SetPending(void);
void hallEffectISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the hallEffectISR ISR. */
#define hallEffectISR_INTC_VECTOR            ((reg32 *) hallEffectISR__INTC_VECT)

/* Address of the hallEffectISR ISR priority. */
#define hallEffectISR_INTC_PRIOR             ((reg32 *) hallEffectISR__INTC_PRIOR_REG)

/* Priority of the hallEffectISR interrupt. */
#define hallEffectISR_INTC_PRIOR_NUMBER      hallEffectISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable hallEffectISR interrupt. */
#define hallEffectISR_INTC_SET_EN            ((reg32 *) hallEffectISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the hallEffectISR interrupt. */
#define hallEffectISR_INTC_CLR_EN            ((reg32 *) hallEffectISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the hallEffectISR interrupt state to pending. */
#define hallEffectISR_INTC_SET_PD            ((reg32 *) hallEffectISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the hallEffectISR interrupt. */
#define hallEffectISR_INTC_CLR_PD            ((reg32 *) hallEffectISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_hallEffectISR_H */


/* [] END OF FILE */
