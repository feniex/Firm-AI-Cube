/*******************************************************************************
* File Name: DIM_MINUS.h  
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

#if !defined(CY_PINS_DIM_MINUS_ALIASES_H) /* Pins DIM_MINUS_ALIASES_H */
#define CY_PINS_DIM_MINUS_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DIM_MINUS_0			(DIM_MINUS__0__PC)
#define DIM_MINUS_0_PS		(DIM_MINUS__0__PS)
#define DIM_MINUS_0_PC		(DIM_MINUS__0__PC)
#define DIM_MINUS_0_DR		(DIM_MINUS__0__DR)
#define DIM_MINUS_0_SHIFT	(DIM_MINUS__0__SHIFT)
#define DIM_MINUS_0_INTR	((uint16)((uint16)0x0003u << (DIM_MINUS__0__SHIFT*2u)))

#define DIM_MINUS_INTR_ALL	 ((uint16)(DIM_MINUS_0_INTR))


#endif /* End Pins DIM_MINUS_ALIASES_H */


/* [] END OF FILE */
