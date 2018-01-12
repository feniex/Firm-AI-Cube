/*******************************************************************************
* File Name: SwitchNodeTempInput.h  
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

#if !defined(CY_PINS_SwitchNodeTempInput_ALIASES_H) /* Pins SwitchNodeTempInput_ALIASES_H */
#define CY_PINS_SwitchNodeTempInput_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SwitchNodeTempInput_0			(SwitchNodeTempInput__0__PC)
#define SwitchNodeTempInput_0_PS		(SwitchNodeTempInput__0__PS)
#define SwitchNodeTempInput_0_PC		(SwitchNodeTempInput__0__PC)
#define SwitchNodeTempInput_0_DR		(SwitchNodeTempInput__0__DR)
#define SwitchNodeTempInput_0_SHIFT	(SwitchNodeTempInput__0__SHIFT)
#define SwitchNodeTempInput_0_INTR	((uint16)((uint16)0x0003u << (SwitchNodeTempInput__0__SHIFT*2u)))

#define SwitchNodeTempInput_INTR_ALL	 ((uint16)(SwitchNodeTempInput_0_INTR))


#endif /* End Pins SwitchNodeTempInput_ALIASES_H */


/* [] END OF FILE */
