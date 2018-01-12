/*******************************************************************************
* File Name: AmbientTempInput.h  
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

#if !defined(CY_PINS_AmbientTempInput_ALIASES_H) /* Pins AmbientTempInput_ALIASES_H */
#define CY_PINS_AmbientTempInput_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define AmbientTempInput_0			(AmbientTempInput__0__PC)
#define AmbientTempInput_0_PS		(AmbientTempInput__0__PS)
#define AmbientTempInput_0_PC		(AmbientTempInput__0__PC)
#define AmbientTempInput_0_DR		(AmbientTempInput__0__DR)
#define AmbientTempInput_0_SHIFT	(AmbientTempInput__0__SHIFT)
#define AmbientTempInput_0_INTR	((uint16)((uint16)0x0003u << (AmbientTempInput__0__SHIFT*2u)))

#define AmbientTempInput_INTR_ALL	 ((uint16)(AmbientTempInput_0_INTR))


#endif /* End Pins AmbientTempInput_ALIASES_H */


/* [] END OF FILE */
