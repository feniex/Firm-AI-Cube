/*******************************************************************************
* File Name: DIM_PLUS.h  
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

#if !defined(CY_PINS_DIM_PLUS_ALIASES_H) /* Pins DIM_PLUS_ALIASES_H */
#define CY_PINS_DIM_PLUS_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DIM_PLUS_0			(DIM_PLUS__0__PC)
#define DIM_PLUS_0_PS		(DIM_PLUS__0__PS)
#define DIM_PLUS_0_PC		(DIM_PLUS__0__PC)
#define DIM_PLUS_0_DR		(DIM_PLUS__0__DR)
#define DIM_PLUS_0_SHIFT	(DIM_PLUS__0__SHIFT)
#define DIM_PLUS_0_INTR	((uint16)((uint16)0x0003u << (DIM_PLUS__0__SHIFT*2u)))

#define DIM_PLUS_INTR_ALL	 ((uint16)(DIM_PLUS_0_INTR))


#endif /* End Pins DIM_PLUS_ALIASES_H */


/* [] END OF FILE */
