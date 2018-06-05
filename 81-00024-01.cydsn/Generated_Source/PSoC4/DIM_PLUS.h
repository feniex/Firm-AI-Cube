/*******************************************************************************
* File Name: DIM_PLUS.h  
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

#if !defined(CY_PINS_DIM_PLUS_H) /* Pins DIM_PLUS_H */
#define CY_PINS_DIM_PLUS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DIM_PLUS_aliases.h"


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
} DIM_PLUS_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DIM_PLUS_Read(void);
void    DIM_PLUS_Write(uint8 value);
uint8   DIM_PLUS_ReadDataReg(void);
#if defined(DIM_PLUS__PC) || (CY_PSOC4_4200L) 
    void    DIM_PLUS_SetDriveMode(uint8 mode);
#endif
void    DIM_PLUS_SetInterruptMode(uint16 position, uint16 mode);
uint8   DIM_PLUS_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DIM_PLUS_Sleep(void); 
void DIM_PLUS_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DIM_PLUS__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DIM_PLUS_DRIVE_MODE_BITS        (3)
    #define DIM_PLUS_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DIM_PLUS_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DIM_PLUS_SetDriveMode() function.
         *  @{
         */
        #define DIM_PLUS_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DIM_PLUS_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DIM_PLUS_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DIM_PLUS_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DIM_PLUS_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DIM_PLUS_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DIM_PLUS_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DIM_PLUS_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DIM_PLUS_MASK               DIM_PLUS__MASK
#define DIM_PLUS_SHIFT              DIM_PLUS__SHIFT
#define DIM_PLUS_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DIM_PLUS_SetInterruptMode() function.
     *  @{
     */
        #define DIM_PLUS_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DIM_PLUS_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DIM_PLUS_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DIM_PLUS_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DIM_PLUS__SIO)
    #define DIM_PLUS_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DIM_PLUS__PC) && (CY_PSOC4_4200L)
    #define DIM_PLUS_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DIM_PLUS_USBIO_DISABLE              ((uint32)(~DIM_PLUS_USBIO_ENABLE))
    #define DIM_PLUS_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DIM_PLUS_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DIM_PLUS_USBIO_ENTER_SLEEP          ((uint32)((1u << DIM_PLUS_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DIM_PLUS_USBIO_SUSPEND_DEL_SHIFT)))
    #define DIM_PLUS_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DIM_PLUS_USBIO_SUSPEND_SHIFT)))
    #define DIM_PLUS_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DIM_PLUS_USBIO_SUSPEND_DEL_SHIFT)))
    #define DIM_PLUS_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DIM_PLUS__PC)
    /* Port Configuration */
    #define DIM_PLUS_PC                 (* (reg32 *) DIM_PLUS__PC)
#endif
/* Pin State */
#define DIM_PLUS_PS                     (* (reg32 *) DIM_PLUS__PS)
/* Data Register */
#define DIM_PLUS_DR                     (* (reg32 *) DIM_PLUS__DR)
/* Input Buffer Disable Override */
#define DIM_PLUS_INP_DIS                (* (reg32 *) DIM_PLUS__PC2)

/* Interrupt configuration Registers */
#define DIM_PLUS_INTCFG                 (* (reg32 *) DIM_PLUS__INTCFG)
#define DIM_PLUS_INTSTAT                (* (reg32 *) DIM_PLUS__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DIM_PLUS_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DIM_PLUS__SIO)
    #define DIM_PLUS_SIO_REG            (* (reg32 *) DIM_PLUS__SIO)
#endif /* (DIM_PLUS__SIO_CFG) */

/* USBIO registers */
#if !defined(DIM_PLUS__PC) && (CY_PSOC4_4200L)
    #define DIM_PLUS_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DIM_PLUS_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DIM_PLUS_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DIM_PLUS_DRIVE_MODE_SHIFT       (0x00u)
#define DIM_PLUS_DRIVE_MODE_MASK        (0x07u << DIM_PLUS_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DIM_PLUS_H */


/* [] END OF FILE */
