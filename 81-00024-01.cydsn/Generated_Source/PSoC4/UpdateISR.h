/*******************************************************************************
* File Name: UpdateISR.h
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
#if !defined(CY_ISR_UpdateISR_H)
#define CY_ISR_UpdateISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void UpdateISR_Start(void);
void UpdateISR_StartEx(cyisraddress address);
void UpdateISR_Stop(void);

CY_ISR_PROTO(UpdateISR_Interrupt);

void UpdateISR_SetVector(cyisraddress address);
cyisraddress UpdateISR_GetVector(void);

void UpdateISR_SetPriority(uint8 priority);
uint8 UpdateISR_GetPriority(void);

void UpdateISR_Enable(void);
uint8 UpdateISR_GetState(void);
void UpdateISR_Disable(void);

void UpdateISR_SetPending(void);
void UpdateISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the UpdateISR ISR. */
#define UpdateISR_INTC_VECTOR            ((reg32 *) UpdateISR__INTC_VECT)

/* Address of the UpdateISR ISR priority. */
#define UpdateISR_INTC_PRIOR             ((reg32 *) UpdateISR__INTC_PRIOR_REG)

/* Priority of the UpdateISR interrupt. */
#define UpdateISR_INTC_PRIOR_NUMBER      UpdateISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable UpdateISR interrupt. */
#define UpdateISR_INTC_SET_EN            ((reg32 *) UpdateISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the UpdateISR interrupt. */
#define UpdateISR_INTC_CLR_EN            ((reg32 *) UpdateISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the UpdateISR interrupt state to pending. */
#define UpdateISR_INTC_SET_PD            ((reg32 *) UpdateISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the UpdateISR interrupt. */
#define UpdateISR_INTC_CLR_PD            ((reg32 *) UpdateISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_UpdateISR_H */


/* [] END OF FILE */
