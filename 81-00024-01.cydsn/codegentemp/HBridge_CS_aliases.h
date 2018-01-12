/*******************************************************************************
* File Name: HBridge_CS.h  
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

#if !defined(CY_PINS_HBridge_CS_ALIASES_H) /* Pins HBridge_CS_ALIASES_H */
#define CY_PINS_HBridge_CS_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define HBridge_CS_0			(HBridge_CS__0__PC)
#define HBridge_CS_0_PS		(HBridge_CS__0__PS)
#define HBridge_CS_0_PC		(HBridge_CS__0__PC)
#define HBridge_CS_0_DR		(HBridge_CS__0__DR)
#define HBridge_CS_0_SHIFT	(HBridge_CS__0__SHIFT)
#define HBridge_CS_0_INTR	((uint16)((uint16)0x0003u << (HBridge_CS__0__SHIFT*2u)))

#define HBridge_CS_INTR_ALL	 ((uint16)(HBridge_CS_0_INTR))


#endif /* End Pins HBridge_CS_ALIASES_H */


/* [] END OF FILE */
