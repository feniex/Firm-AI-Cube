/*******************************************************************************
* File Name: ZOOM_MINUS.h  
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

#if !defined(CY_PINS_ZOOM_MINUS_ALIASES_H) /* Pins ZOOM_MINUS_ALIASES_H */
#define CY_PINS_ZOOM_MINUS_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define ZOOM_MINUS_0			(ZOOM_MINUS__0__PC)
#define ZOOM_MINUS_0_PS		(ZOOM_MINUS__0__PS)
#define ZOOM_MINUS_0_PC		(ZOOM_MINUS__0__PC)
#define ZOOM_MINUS_0_DR		(ZOOM_MINUS__0__DR)
#define ZOOM_MINUS_0_SHIFT	(ZOOM_MINUS__0__SHIFT)
#define ZOOM_MINUS_0_INTR	((uint16)((uint16)0x0003u << (ZOOM_MINUS__0__SHIFT*2u)))

#define ZOOM_MINUS_INTR_ALL	 ((uint16)(ZOOM_MINUS_0_INTR))


#endif /* End Pins ZOOM_MINUS_ALIASES_H */


/* [] END OF FILE */
