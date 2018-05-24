/*******************************************************************************
* File Name: modeChangeISR.h
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
#if !defined(CY_ISR_modeChangeISR_H)
#define CY_ISR_modeChangeISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void modeChangeISR_Start(void);
void modeChangeISR_StartEx(cyisraddress address);
void modeChangeISR_Stop(void);

CY_ISR_PROTO(modeChangeISR_Interrupt);

void modeChangeISR_SetVector(cyisraddress address);
cyisraddress modeChangeISR_GetVector(void);

void modeChangeISR_SetPriority(uint8 priority);
uint8 modeChangeISR_GetPriority(void);

void modeChangeISR_Enable(void);
uint8 modeChangeISR_GetState(void);
void modeChangeISR_Disable(void);

void modeChangeISR_SetPending(void);
void modeChangeISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the modeChangeISR ISR. */
#define modeChangeISR_INTC_VECTOR            ((reg32 *) modeChangeISR__INTC_VECT)

/* Address of the modeChangeISR ISR priority. */
#define modeChangeISR_INTC_PRIOR             ((reg32 *) modeChangeISR__INTC_PRIOR_REG)

/* Priority of the modeChangeISR interrupt. */
#define modeChangeISR_INTC_PRIOR_NUMBER      modeChangeISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable modeChangeISR interrupt. */
#define modeChangeISR_INTC_SET_EN            ((reg32 *) modeChangeISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the modeChangeISR interrupt. */
#define modeChangeISR_INTC_CLR_EN            ((reg32 *) modeChangeISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the modeChangeISR interrupt state to pending. */
#define modeChangeISR_INTC_SET_PD            ((reg32 *) modeChangeISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the modeChangeISR interrupt. */
#define modeChangeISR_INTC_CLR_PD            ((reg32 *) modeChangeISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_modeChangeISR_H */


/* [] END OF FILE */
