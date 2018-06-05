/*******************************************************************************
* File Name: ZOOM_MINUS.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_ZOOM_MINUS_H) /* Pins ZOOM_MINUS_H */
#define CY_PINS_ZOOM_MINUS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ZOOM_MINUS_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} ZOOM_MINUS_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   ZOOM_MINUS_Read(void);
void    ZOOM_MINUS_Write(uint8 value);
uint8   ZOOM_MINUS_ReadDataReg(void);
#if defined(ZOOM_MINUS__PC) || (CY_PSOC4_4200L) 
    void    ZOOM_MINUS_SetDriveMode(uint8 mode);
#endif
void    ZOOM_MINUS_SetInterruptMode(uint16 position, uint16 mode);
uint8   ZOOM_MINUS_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void ZOOM_MINUS_Sleep(void); 
void ZOOM_MINUS_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(ZOOM_MINUS__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define ZOOM_MINUS_DRIVE_MODE_BITS        (3)
    #define ZOOM_MINUS_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ZOOM_MINUS_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the ZOOM_MINUS_SetDriveMode() function.
         *  @{
         */
        #define ZOOM_MINUS_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define ZOOM_MINUS_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define ZOOM_MINUS_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define ZOOM_MINUS_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define ZOOM_MINUS_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define ZOOM_MINUS_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define ZOOM_MINUS_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define ZOOM_MINUS_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define ZOOM_MINUS_MASK               ZOOM_MINUS__MASK
#define ZOOM_MINUS_SHIFT              ZOOM_MINUS__SHIFT
#define ZOOM_MINUS_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ZOOM_MINUS_SetInterruptMode() function.
     *  @{
     */
        #define ZOOM_MINUS_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define ZOOM_MINUS_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define ZOOM_MINUS_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define ZOOM_MINUS_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(ZOOM_MINUS__SIO)
    #define ZOOM_MINUS_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(ZOOM_MINUS__PC) && (CY_PSOC4_4200L)
    #define ZOOM_MINUS_USBIO_ENABLE               ((uint32)0x80000000u)
    #define ZOOM_MINUS_USBIO_DISABLE              ((uint32)(~ZOOM_MINUS_USBIO_ENABLE))
    #define ZOOM_MINUS_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define ZOOM_MINUS_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define ZOOM_MINUS_USBIO_ENTER_SLEEP          ((uint32)((1u << ZOOM_MINUS_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << ZOOM_MINUS_USBIO_SUSPEND_DEL_SHIFT)))
    #define ZOOM_MINUS_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << ZOOM_MINUS_USBIO_SUSPEND_SHIFT)))
    #define ZOOM_MINUS_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << ZOOM_MINUS_USBIO_SUSPEND_DEL_SHIFT)))
    #define ZOOM_MINUS_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(ZOOM_MINUS__PC)
    /* Port Configuration */
    #define ZOOM_MINUS_PC                 (* (reg32 *) ZOOM_MINUS__PC)
#endif
/* Pin State */
#define ZOOM_MINUS_PS                     (* (reg32 *) ZOOM_MINUS__PS)
/* Data Register */
#define ZOOM_MINUS_DR                     (* (reg32 *) ZOOM_MINUS__DR)
/* Input Buffer Disable Override */
#define ZOOM_MINUS_INP_DIS                (* (reg32 *) ZOOM_MINUS__PC2)

/* Interrupt configuration Registers */
#define ZOOM_MINUS_INTCFG                 (* (reg32 *) ZOOM_MINUS__INTCFG)
#define ZOOM_MINUS_INTSTAT                (* (reg32 *) ZOOM_MINUS__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define ZOOM_MINUS_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(ZOOM_MINUS__SIO)
    #define ZOOM_MINUS_SIO_REG            (* (reg32 *) ZOOM_MINUS__SIO)
#endif /* (ZOOM_MINUS__SIO_CFG) */

/* USBIO registers */
#if !defined(ZOOM_MINUS__PC) && (CY_PSOC4_4200L)
    #define ZOOM_MINUS_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define ZOOM_MINUS_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define ZOOM_MINUS_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define ZOOM_MINUS_DRIVE_MODE_SHIFT       (0x00u)
#define ZOOM_MINUS_DRIVE_MODE_MASK        (0x07u << ZOOM_MINUS_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins ZOOM_MINUS_H */


/* [] END OF FILE */
