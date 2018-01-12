/*******************************************************************************
* File Name: PotFeedBack.h  
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

#if !defined(CY_PINS_PotFeedBack_ALIASES_H) /* Pins PotFeedBack_ALIASES_H */
#define CY_PINS_PotFeedBack_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PotFeedBack_0			(PotFeedBack__0__PC)
#define PotFeedBack_0_PS		(PotFeedBack__0__PS)
#define PotFeedBack_0_PC		(PotFeedBack__0__PC)
#define PotFeedBack_0_DR		(PotFeedBack__0__DR)
#define PotFeedBack_0_SHIFT	(PotFeedBack__0__SHIFT)
#define PotFeedBack_0_INTR	((uint16)((uint16)0x0003u << (PotFeedBack__0__SHIFT*2u)))

#define PotFeedBack_INTR_ALL	 ((uint16)(PotFeedBack_0_INTR))


#endif /* End Pins PotFeedBack_ALIASES_H */


/* [] END OF FILE */
