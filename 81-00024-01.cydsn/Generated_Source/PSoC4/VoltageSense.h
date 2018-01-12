/*******************************************************************************
* File Name: VoltageSense.h  
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

#if !defined(CY_PINS_VoltageSense_H) /* Pins VoltageSense_H */
#define CY_PINS_VoltageSense_H

#include "cytypes.h"
#include "cyfitter.h"
#include "VoltageSense_aliases.h"


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
} VoltageSense_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   VoltageSense_Read(void);
void    VoltageSense_Write(uint8 value);
uint8   VoltageSense_ReadDataReg(void);
#if defined(VoltageSense__PC) || (CY_PSOC4_4200L) 
    void    VoltageSense_SetDriveMode(uint8 mode);
#endif
void    VoltageSense_SetInterruptMode(uint16 position, uint16 mode);
uint8   VoltageSense_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void VoltageSense_Sleep(void); 
void VoltageSense_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(VoltageSense__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define VoltageSense_DRIVE_MODE_BITS        (3)
    #define VoltageSense_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - VoltageSense_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the VoltageSense_SetDriveMode() function.
         *  @{
         */
        #define VoltageSense_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define VoltageSense_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define VoltageSense_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define VoltageSense_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define VoltageSense_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define VoltageSense_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define VoltageSense_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define VoltageSense_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define VoltageSense_MASK               VoltageSense__MASK
#define VoltageSense_SHIFT              VoltageSense__SHIFT
#define VoltageSense_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VoltageSense_SetInterruptMode() function.
     *  @{
     */
        #define VoltageSense_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define VoltageSense_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define VoltageSense_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define VoltageSense_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(VoltageSense__SIO)
    #define VoltageSense_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(VoltageSense__PC) && (CY_PSOC4_4200L)
    #define VoltageSense_USBIO_ENABLE               ((uint32)0x80000000u)
    #define VoltageSense_USBIO_DISABLE              ((uint32)(~VoltageSense_USBIO_ENABLE))
    #define VoltageSense_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define VoltageSense_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define VoltageSense_USBIO_ENTER_SLEEP          ((uint32)((1u << VoltageSense_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << VoltageSense_USBIO_SUSPEND_DEL_SHIFT)))
    #define VoltageSense_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << VoltageSense_USBIO_SUSPEND_SHIFT)))
    #define VoltageSense_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << VoltageSense_USBIO_SUSPEND_DEL_SHIFT)))
    #define VoltageSense_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(VoltageSense__PC)
    /* Port Configuration */
    #define VoltageSense_PC                 (* (reg32 *) VoltageSense__PC)
#endif
/* Pin State */
#define VoltageSense_PS                     (* (reg32 *) VoltageSense__PS)
/* Data Register */
#define VoltageSense_DR                     (* (reg32 *) VoltageSense__DR)
/* Input Buffer Disable Override */
#define VoltageSense_INP_DIS                (* (reg32 *) VoltageSense__PC2)

/* Interrupt configuration Registers */
#define VoltageSense_INTCFG                 (* (reg32 *) VoltageSense__INTCFG)
#define VoltageSense_INTSTAT                (* (reg32 *) VoltageSense__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define VoltageSense_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(VoltageSense__SIO)
    #define VoltageSense_SIO_REG            (* (reg32 *) VoltageSense__SIO)
#endif /* (VoltageSense__SIO_CFG) */

/* USBIO registers */
#if !defined(VoltageSense__PC) && (CY_PSOC4_4200L)
    #define VoltageSense_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define VoltageSense_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define VoltageSense_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define VoltageSense_DRIVE_MODE_SHIFT       (0x00u)
#define VoltageSense_DRIVE_MODE_MASK        (0x07u << VoltageSense_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins VoltageSense_H */


/* [] END OF FILE */
