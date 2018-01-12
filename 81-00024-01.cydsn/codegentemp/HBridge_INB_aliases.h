/*******************************************************************************
* File Name: HBridge_INB.h  
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

#if !defined(CY_PINS_HBridge_INB_ALIASES_H) /* Pins HBridge_INB_ALIASES_H */
#define CY_PINS_HBridge_INB_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define HBridge_INB_0			(HBridge_INB__0__PC)
#define HBridge_INB_0_PS		(HBridge_INB__0__PS)
#define HBridge_INB_0_PC		(HBridge_INB__0__PC)
#define HBridge_INB_0_DR		(HBridge_INB__0__DR)
#define HBridge_INB_0_SHIFT	(HBridge_INB__0__SHIFT)
#define HBridge_INB_0_INTR	((uint16)((uint16)0x0003u << (HBridge_INB__0__SHIFT*2u)))

#define HBridge_INB_INTR_ALL	 ((uint16)(HBridge_INB_0_INTR))


#endif /* End Pins HBridge_INB_ALIASES_H */


/* [] END OF FILE */
