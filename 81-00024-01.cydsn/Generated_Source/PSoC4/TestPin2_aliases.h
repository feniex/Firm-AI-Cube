/*******************************************************************************
* File Name: TestPin2.h  
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

#if !defined(CY_PINS_TestPin2_ALIASES_H) /* Pins TestPin2_ALIASES_H */
#define CY_PINS_TestPin2_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define TestPin2_0			(TestPin2__0__PC)
#define TestPin2_0_PS		(TestPin2__0__PS)
#define TestPin2_0_PC		(TestPin2__0__PC)
#define TestPin2_0_DR		(TestPin2__0__DR)
#define TestPin2_0_SHIFT	(TestPin2__0__SHIFT)
#define TestPin2_0_INTR	((uint16)((uint16)0x0003u << (TestPin2__0__SHIFT*2u)))

#define TestPin2_INTR_ALL	 ((uint16)(TestPin2_0_INTR))


#endif /* End Pins TestPin2_ALIASES_H */


/* [] END OF FILE */