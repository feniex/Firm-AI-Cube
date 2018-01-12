/*******************************************************************************
* File Name: CommTimeoutISR.h
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
#if !defined(CY_ISR_CommTimeoutISR_H)
#define CY_ISR_CommTimeoutISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void CommTimeoutISR_Start(void);
void CommTimeoutISR_StartEx(cyisraddress address);
void CommTimeoutISR_Stop(void);

CY_ISR_PROTO(CommTimeoutISR_Interrupt);

void CommTimeoutISR_SetVector(cyisraddress address);
cyisraddress CommTimeoutISR_GetVector(void);

void CommTimeoutISR_SetPriority(uint8 priority);
uint8 CommTimeoutISR_GetPriority(void);

void CommTimeoutISR_Enable(void);
uint8 CommTimeoutISR_GetState(void);
void CommTimeoutISR_Disable(void);

void CommTimeoutISR_SetPending(void);
void CommTimeoutISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the CommTimeoutISR ISR. */
#define CommTimeoutISR_INTC_VECTOR            ((reg32 *) CommTimeoutISR__INTC_VECT)

/* Address of the CommTimeoutISR ISR priority. */
#define CommTimeoutISR_INTC_PRIOR             ((reg32 *) CommTimeoutISR__INTC_PRIOR_REG)

/* Priority of the CommTimeoutISR interrupt. */
#define CommTimeoutISR_INTC_PRIOR_NUMBER      CommTimeoutISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable CommTimeoutISR interrupt. */
#define CommTimeoutISR_INTC_SET_EN            ((reg32 *) CommTimeoutISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the CommTimeoutISR interrupt. */
#define CommTimeoutISR_INTC_CLR_EN            ((reg32 *) CommTimeoutISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the CommTimeoutISR interrupt state to pending. */
#define CommTimeoutISR_INTC_SET_PD            ((reg32 *) CommTimeoutISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the CommTimeoutISR interrupt. */
#define CommTimeoutISR_INTC_CLR_PD            ((reg32 *) CommTimeoutISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_CommTimeoutISR_H */


/* [] END OF FILE */
