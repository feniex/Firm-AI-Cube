/*******************************************************************************
* File Name: limitSwitch.h  
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

#if !defined(CY_PINS_limitSwitch_ALIASES_H) /* Pins limitSwitch_ALIASES_H */
#define CY_PINS_limitSwitch_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define limitSwitch_0			(limitSwitch__0__PC)
#define limitSwitch_0_PS		(limitSwitch__0__PS)
#define limitSwitch_0_PC		(limitSwitch__0__PC)
#define limitSwitch_0_DR		(limitSwitch__0__DR)
#define limitSwitch_0_SHIFT	(limitSwitch__0__SHIFT)
#define limitSwitch_0_INTR	((uint16)((uint16)0x0003u << (limitSwitch__0__SHIFT*2u)))

#define limitSwitch_INTR_ALL	 ((uint16)(limitSwitch_0_INTR))


#endif /* End Pins limitSwitch_ALIASES_H */


/* [] END OF FILE */
