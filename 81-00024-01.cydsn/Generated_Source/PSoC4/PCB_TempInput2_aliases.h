/*******************************************************************************
* File Name: PCB_TempInput2.h  
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

#if !defined(CY_PINS_PCB_TempInput2_ALIASES_H) /* Pins PCB_TempInput2_ALIASES_H */
#define CY_PINS_PCB_TempInput2_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PCB_TempInput2_0			(PCB_TempInput2__0__PC)
#define PCB_TempInput2_0_PS		(PCB_TempInput2__0__PS)
#define PCB_TempInput2_0_PC		(PCB_TempInput2__0__PC)
#define PCB_TempInput2_0_DR		(PCB_TempInput2__0__DR)
#define PCB_TempInput2_0_SHIFT	(PCB_TempInput2__0__SHIFT)
#define PCB_TempInput2_0_INTR	((uint16)((uint16)0x0003u << (PCB_TempInput2__0__SHIFT*2u)))

#define PCB_TempInput2_INTR_ALL	 ((uint16)(PCB_TempInput2_0_INTR))


#endif /* End Pins PCB_TempInput2_ALIASES_H */


/* [] END OF FILE */
