/*******************************************************************************
* File Name: PCB_TempInput1.h  
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

#if !defined(CY_PINS_PCB_TempInput1_H) /* Pins PCB_TempInput1_H */
#define CY_PINS_PCB_TempInput1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PCB_TempInput1_aliases.h"


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
} PCB_TempInput1_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PCB_TempInput1_Read(void);
void    PCB_TempInput1_Write(uint8 value);
uint8   PCB_TempInput1_ReadDataReg(void);
#if defined(PCB_TempInput1__PC) || (CY_PSOC4_4200L) 
    void    PCB_TempInput1_SetDriveMode(uint8 mode);
#endif
void    PCB_TempInput1_SetInterruptMode(uint16 position, uint16 mode);
uint8   PCB_TempInput1_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PCB_TempInput1_Sleep(void); 
void PCB_TempInput1_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PCB_TempInput1__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PCB_TempInput1_DRIVE_MODE_BITS        (3)
    #define PCB_TempInput1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PCB_TempInput1_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PCB_TempInput1_SetDriveMode() function.
         *  @{
         */
        #define PCB_TempInput1_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PCB_TempInput1_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PCB_TempInput1_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PCB_TempInput1_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PCB_TempInput1_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PCB_TempInput1_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PCB_TempInput1_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PCB_TempInput1_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PCB_TempInput1_MASK               PCB_TempInput1__MASK
#define PCB_TempInput1_SHIFT              PCB_TempInput1__SHIFT
#define PCB_TempInput1_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PCB_TempInput1_SetInterruptMode() function.
     *  @{
     */
        #define PCB_TempInput1_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PCB_TempInput1_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PCB_TempInput1_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PCB_TempInput1_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PCB_TempInput1__SIO)
    #define PCB_TempInput1_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PCB_TempInput1__PC) && (CY_PSOC4_4200L)
    #define PCB_TempInput1_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PCB_TempInput1_USBIO_DISABLE              ((uint32)(~PCB_TempInput1_USBIO_ENABLE))
    #define PCB_TempInput1_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PCB_TempInput1_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PCB_TempInput1_USBIO_ENTER_SLEEP          ((uint32)((1u << PCB_TempInput1_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PCB_TempInput1_USBIO_SUSPEND_DEL_SHIFT)))
    #define PCB_TempInput1_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PCB_TempInput1_USBIO_SUSPEND_SHIFT)))
    #define PCB_TempInput1_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PCB_TempInput1_USBIO_SUSPEND_DEL_SHIFT)))
    #define PCB_TempInput1_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PCB_TempInput1__PC)
    /* Port Configuration */
    #define PCB_TempInput1_PC                 (* (reg32 *) PCB_TempInput1__PC)
#endif
/* Pin State */
#define PCB_TempInput1_PS                     (* (reg32 *) PCB_TempInput1__PS)
/* Data Register */
#define PCB_TempInput1_DR                     (* (reg32 *) PCB_TempInput1__DR)
/* Input Buffer Disable Override */
#define PCB_TempInput1_INP_DIS                (* (reg32 *) PCB_TempInput1__PC2)

/* Interrupt configuration Registers */
#define PCB_TempInput1_INTCFG                 (* (reg32 *) PCB_TempInput1__INTCFG)
#define PCB_TempInput1_INTSTAT                (* (reg32 *) PCB_TempInput1__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PCB_TempInput1_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PCB_TempInput1__SIO)
    #define PCB_TempInput1_SIO_REG            (* (reg32 *) PCB_TempInput1__SIO)
#endif /* (PCB_TempInput1__SIO_CFG) */

/* USBIO registers */
#if !defined(PCB_TempInput1__PC) && (CY_PSOC4_4200L)
    #define PCB_TempInput1_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PCB_TempInput1_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PCB_TempInput1_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PCB_TempInput1_DRIVE_MODE_SHIFT       (0x00u)
#define PCB_TempInput1_DRIVE_MODE_MASK        (0x07u << PCB_TempInput1_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PCB_TempInput1_H */


/* [] END OF FILE */
