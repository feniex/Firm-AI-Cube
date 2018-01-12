/*******************************************************************************
* File Name: HBridge_PWM.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_HBridge_PWM_ALIASES_H) /* Pins HBridge_PWM_ALIASES_H */
#define CY_PINS_HBridge_PWM_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define HBridge_PWM_0			(HBridge_PWM__0__PC)
#define HBridge_PWM_0_PS		(HBridge_PWM__0__PS)
#define HBridge_PWM_0_PC		(HBridge_PWM__0__PC)
#define HBridge_PWM_0_DR		(HBridge_PWM__0__DR)
#define HBridge_PWM_0_SHIFT	(HBridge_PWM__0__SHIFT)
#define HBridge_PWM_0_INTR	((uint16)((uint16)0x0003u << (HBridge_PWM__0__SHIFT*2u)))

#define HBridge_PWM_INTR_ALL	 ((uint16)(HBridge_PWM_0_INTR))


#endif /* End Pins HBridge_PWM_ALIASES_H */


/* [] END OF FILE */
