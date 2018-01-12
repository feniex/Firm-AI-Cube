/*******************************************************************************
* File Name: PotFeedBack.h  
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

#if !defined(CY_PINS_PotFeedBack_H) /* Pins PotFeedBack_H */
#define CY_PINS_PotFeedBack_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PotFeedBack_aliases.h"


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
} PotFeedBack_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PotFeedBack_Read(void);
void    PotFeedBack_Write(uint8 value);
uint8   PotFeedBack_ReadDataReg(void);
#if defined(PotFeedBack__PC) || (CY_PSOC4_4200L) 
    void    PotFeedBack_SetDriveMode(uint8 mode);
#endif
void    PotFeedBack_SetInterruptMode(uint16 position, uint16 mode);
uint8   PotFeedBack_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PotFeedBack_Sleep(void); 
void PotFeedBack_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PotFeedBack__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PotFeedBack_DRIVE_MODE_BITS        (3)
    #define PotFeedBack_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PotFeedBack_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PotFeedBack_SetDriveMode() function.
         *  @{
         */
        #define PotFeedBack_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PotFeedBack_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PotFeedBack_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PotFeedBack_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PotFeedBack_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PotFeedBack_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PotFeedBack_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PotFeedBack_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PotFeedBack_MASK               PotFeedBack__MASK
#define PotFeedBack_SHIFT              PotFeedBack__SHIFT
#define PotFeedBack_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PotFeedBack_SetInterruptMode() function.
     *  @{
     */
        #define PotFeedBack_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PotFeedBack_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PotFeedBack_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PotFeedBack_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PotFeedBack__SIO)
    #define PotFeedBack_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PotFeedBack__PC) && (CY_PSOC4_4200L)
    #define PotFeedBack_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PotFeedBack_USBIO_DISABLE              ((uint32)(~PotFeedBack_USBIO_ENABLE))
    #define PotFeedBack_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PotFeedBack_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PotFeedBack_USBIO_ENTER_SLEEP          ((uint32)((1u << PotFeedBack_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PotFeedBack_USBIO_SUSPEND_DEL_SHIFT)))
    #define PotFeedBack_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PotFeedBack_USBIO_SUSPEND_SHIFT)))
    #define PotFeedBack_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PotFeedBack_USBIO_SUSPEND_DEL_SHIFT)))
    #define PotFeedBack_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PotFeedBack__PC)
    /* Port Configuration */
    #define PotFeedBack_PC                 (* (reg32 *) PotFeedBack__PC)
#endif
/* Pin State */
#define PotFeedBack_PS                     (* (reg32 *) PotFeedBack__PS)
/* Data Register */
#define PotFeedBack_DR                     (* (reg32 *) PotFeedBack__DR)
/* Input Buffer Disable Override */
#define PotFeedBack_INP_DIS                (* (reg32 *) PotFeedBack__PC2)

/* Interrupt configuration Registers */
#define PotFeedBack_INTCFG                 (* (reg32 *) PotFeedBack__INTCFG)
#define PotFeedBack_INTSTAT                (* (reg32 *) PotFeedBack__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PotFeedBack_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PotFeedBack__SIO)
    #define PotFeedBack_SIO_REG            (* (reg32 *) PotFeedBack__SIO)
#endif /* (PotFeedBack__SIO_CFG) */

/* USBIO registers */
#if !defined(PotFeedBack__PC) && (CY_PSOC4_4200L)
    #define PotFeedBack_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PotFeedBack_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PotFeedBack_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PotFeedBack_DRIVE_MODE_SHIFT       (0x00u)
#define PotFeedBack_DRIVE_MODE_MASK        (0x07u << PotFeedBack_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PotFeedBack_H */


/* [] END OF FILE */
