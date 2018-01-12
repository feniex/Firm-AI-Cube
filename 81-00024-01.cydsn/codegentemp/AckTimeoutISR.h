/*******************************************************************************
* File Name: AckTimeoutISR.h
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
#if !defined(CY_ISR_AckTimeoutISR_H)
#define CY_ISR_AckTimeoutISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void AckTimeoutISR_Start(void);
void AckTimeoutISR_StartEx(cyisraddress address);
void AckTimeoutISR_Stop(void);

CY_ISR_PROTO(AckTimeoutISR_Interrupt);

void AckTimeoutISR_SetVector(cyisraddress address);
cyisraddress AckTimeoutISR_GetVector(void);

void AckTimeoutISR_SetPriority(uint8 priority);
uint8 AckTimeoutISR_GetPriority(void);

void AckTimeoutISR_Enable(void);
uint8 AckTimeoutISR_GetState(void);
void AckTimeoutISR_Disable(void);

void AckTimeoutISR_SetPending(void);
void AckTimeoutISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the AckTimeoutISR ISR. */
#define AckTimeoutISR_INTC_VECTOR            ((reg32 *) AckTimeoutISR__INTC_VECT)

/* Address of the AckTimeoutISR ISR priority. */
#define AckTimeoutISR_INTC_PRIOR             ((reg32 *) AckTimeoutISR__INTC_PRIOR_REG)

/* Priority of the AckTimeoutISR interrupt. */
#define AckTimeoutISR_INTC_PRIOR_NUMBER      AckTimeoutISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable AckTimeoutISR interrupt. */
#define AckTimeoutISR_INTC_SET_EN            ((reg32 *) AckTimeoutISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the AckTimeoutISR interrupt. */
#define AckTimeoutISR_INTC_CLR_EN            ((reg32 *) AckTimeoutISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the AckTimeoutISR interrupt state to pending. */
#define AckTimeoutISR_INTC_SET_PD            ((reg32 *) AckTimeoutISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the AckTimeoutISR interrupt. */
#define AckTimeoutISR_INTC_CLR_PD            ((reg32 *) AckTimeoutISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_AckTimeoutISR_H */


/* [] END OF FILE */
