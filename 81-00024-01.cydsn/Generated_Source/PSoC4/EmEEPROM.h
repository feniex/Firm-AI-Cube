/*******************************************************************************
* File Name: EmEEPROM.h
* Version 1.20
*
* Description:
*  This file provides constants and parameter values for the Emulated EEPROM
*  Component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#ifndef CY_EM_EEPROM_EmEEPROM_H
#define CY_EM_EEPROM_EmEEPROM_H

#include "cytypes.h"
#include "CyFlash.h"

#if !defined(CYDEV_FLASH_BASE)
    #define CYDEV_FLASH_BASE                    (CYDEV_FLS_BASE)
#endif  /* !defined(CYDEV_FLS_BASE) */

#define EmEEPROM_FLASH_BASE_ADDR        (CYDEV_FLASH_BASE)
#define EmEEPROM_FLASH_SIZE             (CYDEV_FLASH_SIZE)
#define EmEEPROM_FLASH_END_ADDR         (EmEEPROM_FLASH_BASE_ADDR + EmEEPROM_FLASH_SIZE)

#if (CY_PSOC3)
    #define EmEEPROM_CODE_ADDR_OFFSET   (0xff0000u)
    #define EmEEPROM_CODE_ADDR_END      (EmEEPROM_CODE_ADDR_OFFSET + (EmEEPROM_FLASH_SIZE - 1u))
    #define EmEEPROM_CODE_ADDR_MASK     (0xffffu)
#endif /* (CY_PSOC3) */

#define EmEEPROM_ROWS_IN_ARRAY          (CY_FLASH_SIZEOF_ARRAY/CY_FLASH_SIZEOF_ROW)


/***************************************
*        Function Prototypes
***************************************/
void EmEEPROM_Start(void) ;
void EmEEPROM_Stop(void) ;
#if (CY_PSOC3)
    cystatus EmEEPROM_Write(const uint8 srcBuf[], const uint8 eepromPtr[],
                                                uint16 byteCount) ;
#else
    cystatus EmEEPROM_Write(const uint8 srcBuf[], const uint8 eepromPtr[], uint32 byteCount);
#endif /* (CY_PSOC3) */

#endif /* CY_EM_EEPROM_EmEEPROM_H */


/* [] END OF FILE */
