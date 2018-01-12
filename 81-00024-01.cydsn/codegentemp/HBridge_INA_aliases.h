/*******************************************************************************
* File Name: HBridge_INA.h  
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

#if !defined(CY_PINS_HBridge_INA_ALIASES_H) /* Pins HBridge_INA_ALIASES_H */
#define CY_PINS_HBridge_INA_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define HBridge_INA_0			(HBridge_INA__0__PC)
#define HBridge_INA_0_PS		(HBridge_INA__0__PS)
#define HBridge_INA_0_PC		(HBridge_INA__0__PC)
#define HBridge_INA_0_DR		(HBridge_INA__0__DR)
#define HBridge_INA_0_SHIFT	(HBridge_INA__0__SHIFT)
#define HBridge_INA_0_INTR	((uint16)((uint16)0x0003u << (HBridge_INA__0__SHIFT*2u)))

#define HBridge_INA_INTR_ALL	 ((uint16)(HBridge_INA_0_INTR))


#endif /* End Pins HBridge_INA_ALIASES_H */


/* [] END OF FILE */
