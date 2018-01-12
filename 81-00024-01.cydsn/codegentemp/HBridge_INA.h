/*******************************************************************************
* File Name: HBridge_INA.h  
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

#if !defined(CY_PINS_HBridge_INA_H) /* Pins HBridge_INA_H */
#define CY_PINS_HBridge_INA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "HBridge_INA_aliases.h"


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
} HBridge_INA_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   HBridge_INA_Read(void);
void    HBridge_INA_Write(uint8 value);
uint8   HBridge_INA_ReadDataReg(void);
#if defined(HBridge_INA__PC) || (CY_PSOC4_4200L) 
    void    HBridge_INA_SetDriveMode(uint8 mode);
#endif
void    HBridge_INA_SetInterruptMode(uint16 position, uint16 mode);
uint8   HBridge_INA_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void HBridge_INA_Sleep(void); 
void HBridge_INA_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(HBridge_INA__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define HBridge_INA_DRIVE_MODE_BITS        (3)
    #define HBridge_INA_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - HBridge_INA_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the HBridge_INA_SetDriveMode() function.
         *  @{
         */
        #define HBridge_INA_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define HBridge_INA_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define HBridge_INA_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define HBridge_INA_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define HBridge_INA_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define HBridge_INA_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define HBridge_INA_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define HBridge_INA_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define HBridge_INA_MASK               HBridge_INA__MASK
#define HBridge_INA_SHIFT              HBridge_INA__SHIFT
#define HBridge_INA_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HBridge_INA_SetInterruptMode() function.
     *  @{
     */
        #define HBridge_INA_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define HBridge_INA_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define HBridge_INA_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define HBridge_INA_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(HBridge_INA__SIO)
    #define HBridge_INA_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(HBridge_INA__PC) && (CY_PSOC4_4200L)
    #define HBridge_INA_USBIO_ENABLE               ((uint32)0x80000000u)
    #define HBridge_INA_USBIO_DISABLE              ((uint32)(~HBridge_INA_USBIO_ENABLE))
    #define HBridge_INA_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define HBridge_INA_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define HBridge_INA_USBIO_ENTER_SLEEP          ((uint32)((1u << HBridge_INA_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << HBridge_INA_USBIO_SUSPEND_DEL_SHIFT)))
    #define HBridge_INA_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << HBridge_INA_USBIO_SUSPEND_SHIFT)))
    #define HBridge_INA_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << HBridge_INA_USBIO_SUSPEND_DEL_SHIFT)))
    #define HBridge_INA_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(HBridge_INA__PC)
    /* Port Configuration */
    #define HBridge_INA_PC                 (* (reg32 *) HBridge_INA__PC)
#endif
/* Pin State */
#define HBridge_INA_PS                     (* (reg32 *) HBridge_INA__PS)
/* Data Register */
#define HBridge_INA_DR                     (* (reg32 *) HBridge_INA__DR)
/* Input Buffer Disable Override */
#define HBridge_INA_INP_DIS                (* (reg32 *) HBridge_INA__PC2)

/* Interrupt configuration Registers */
#define HBridge_INA_INTCFG                 (* (reg32 *) HBridge_INA__INTCFG)
#define HBridge_INA_INTSTAT                (* (reg32 *) HBridge_INA__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define HBridge_INA_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(HBridge_INA__SIO)
    #define HBridge_INA_SIO_REG            (* (reg32 *) HBridge_INA__SIO)
#endif /* (HBridge_INA__SIO_CFG) */

/* USBIO registers */
#if !defined(HBridge_INA__PC) && (CY_PSOC4_4200L)
    #define HBridge_INA_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define HBridge_INA_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define HBridge_INA_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define HBridge_INA_DRIVE_MODE_SHIFT       (0x00u)
#define HBridge_INA_DRIVE_MODE_MASK        (0x07u << HBridge_INA_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins HBridge_INA_H */


/* [] END OF FILE */
