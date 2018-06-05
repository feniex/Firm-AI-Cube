/*******************************************************************************
* File Name: ZOOM_PLUS.h  
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

#if !defined(CY_PINS_ZOOM_PLUS_ALIASES_H) /* Pins ZOOM_PLUS_ALIASES_H */
#define CY_PINS_ZOOM_PLUS_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define ZOOM_PLUS_0			(ZOOM_PLUS__0__PC)
#define ZOOM_PLUS_0_PS		(ZOOM_PLUS__0__PS)
#define ZOOM_PLUS_0_PC		(ZOOM_PLUS__0__PC)
#define ZOOM_PLUS_0_DR		(ZOOM_PLUS__0__DR)
#define ZOOM_PLUS_0_SHIFT	(ZOOM_PLUS__0__SHIFT)
#define ZOOM_PLUS_0_INTR	((uint16)((uint16)0x0003u << (ZOOM_PLUS__0__SHIFT*2u)))

#define ZOOM_PLUS_INTR_ALL	 ((uint16)(ZOOM_PLUS_0_INTR))


#endif /* End Pins ZOOM_PLUS_ALIASES_H */


/* [] END OF FILE */
