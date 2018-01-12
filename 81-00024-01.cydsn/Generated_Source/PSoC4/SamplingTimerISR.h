/*******************************************************************************
* File Name: SamplingTimerISR.h
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
#if !defined(CY_ISR_SamplingTimerISR_H)
#define CY_ISR_SamplingTimerISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void SamplingTimerISR_Start(void);
void SamplingTimerISR_StartEx(cyisraddress address);
void SamplingTimerISR_Stop(void);

CY_ISR_PROTO(SamplingTimerISR_Interrupt);

void SamplingTimerISR_SetVector(cyisraddress address);
cyisraddress SamplingTimerISR_GetVector(void);

void SamplingTimerISR_SetPriority(uint8 priority);
uint8 SamplingTimerISR_GetPriority(void);

void SamplingTimerISR_Enable(void);
uint8 SamplingTimerISR_GetState(void);
void SamplingTimerISR_Disable(void);

void SamplingTimerISR_SetPending(void);
void SamplingTimerISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the SamplingTimerISR ISR. */
#define SamplingTimerISR_INTC_VECTOR            ((reg32 *) SamplingTimerISR__INTC_VECT)

/* Address of the SamplingTimerISR ISR priority. */
#define SamplingTimerISR_INTC_PRIOR             ((reg32 *) SamplingTimerISR__INTC_PRIOR_REG)

/* Priority of the SamplingTimerISR interrupt. */
#define SamplingTimerISR_INTC_PRIOR_NUMBER      SamplingTimerISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable SamplingTimerISR interrupt. */
#define SamplingTimerISR_INTC_SET_EN            ((reg32 *) SamplingTimerISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the SamplingTimerISR interrupt. */
#define SamplingTimerISR_INTC_CLR_EN            ((reg32 *) SamplingTimerISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the SamplingTimerISR interrupt state to pending. */
#define SamplingTimerISR_INTC_SET_PD            ((reg32 *) SamplingTimerISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the SamplingTimerISR interrupt. */
#define SamplingTimerISR_INTC_CLR_PD            ((reg32 *) SamplingTimerISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_SamplingTimerISR_H */


/* [] END OF FILE */
