/*******************************************************************************
* File Name: ID_Status.h  
* Version 1.90
*
* Description:
*  This file containts Status Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_STATUS_REG_ID_Status_H) /* CY_STATUS_REG_ID_Status_H */
#define CY_STATUS_REG_ID_Status_H

#include "cytypes.h"
#include "CyLib.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 statusState;

} ID_Status_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8 ID_Status_Read(void) ;
void ID_Status_InterruptEnable(void) ;
void ID_Status_InterruptDisable(void) ;
void ID_Status_WriteMask(uint8 mask) ;
uint8 ID_Status_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define ID_Status_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define ID_Status_INPUTS              8


/***************************************
*             Registers
***************************************/

/* Status Register */
#define ID_Status_Status             (* (reg8 *) ID_Status_sts_sts_reg__STATUS_REG )
#define ID_Status_Status_PTR         (  (reg8 *) ID_Status_sts_sts_reg__STATUS_REG )
#define ID_Status_Status_Mask        (* (reg8 *) ID_Status_sts_sts_reg__MASK_REG )
#define ID_Status_Status_Aux_Ctrl    (* (reg8 *) ID_Status_sts_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_ID_Status_H */


/* [] END OF FILE */
