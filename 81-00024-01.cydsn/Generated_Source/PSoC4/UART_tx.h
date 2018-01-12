/*******************************************************************************
* File Name: UART_Tx.h  
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

#if !defined(CY_PINS_UART_Tx_H) /* Pins UART_Tx_H */
#define CY_PINS_UART_Tx_H

#include "cytypes.h"
#include "cyfitter.h"
#include "UART_Tx_aliases.h"


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
} UART_Tx_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   UART_Tx_Read(void);
void    UART_Tx_Write(uint8 value);
uint8   UART_Tx_ReadDataReg(void);
#if defined(UART_Tx__PC) || (CY_PSOC4_4200L) 
    void    UART_Tx_SetDriveMode(uint8 mode);
#endif
void    UART_Tx_SetInterruptMode(uint16 position, uint16 mode);
uint8   UART_Tx_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void UART_Tx_Sleep(void); 
void UART_Tx_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(UART_Tx__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define UART_Tx_DRIVE_MODE_BITS        (3)
    #define UART_Tx_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - UART_Tx_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the UART_Tx_SetDriveMode() function.
         *  @{
         */
        #define UART_Tx_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define UART_Tx_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define UART_Tx_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define UART_Tx_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define UART_Tx_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define UART_Tx_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define UART_Tx_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define UART_Tx_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define UART_Tx_MASK               UART_Tx__MASK
#define UART_Tx_SHIFT              UART_Tx__SHIFT
#define UART_Tx_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in UART_Tx_SetInterruptMode() function.
     *  @{
     */
        #define UART_Tx_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define UART_Tx_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define UART_Tx_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define UART_Tx_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(UART_Tx__SIO)
    #define UART_Tx_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(UART_Tx__PC) && (CY_PSOC4_4200L)
    #define UART_Tx_USBIO_ENABLE               ((uint32)0x80000000u)
    #define UART_Tx_USBIO_DISABLE              ((uint32)(~UART_Tx_USBIO_ENABLE))
    #define UART_Tx_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define UART_Tx_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define UART_Tx_USBIO_ENTER_SLEEP          ((uint32)((1u << UART_Tx_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << UART_Tx_USBIO_SUSPEND_DEL_SHIFT)))
    #define UART_Tx_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << UART_Tx_USBIO_SUSPEND_SHIFT)))
    #define UART_Tx_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << UART_Tx_USBIO_SUSPEND_DEL_SHIFT)))
    #define UART_Tx_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(UART_Tx__PC)
    /* Port Configuration */
    #define UART_Tx_PC                 (* (reg32 *) UART_Tx__PC)
#endif
/* Pin State */
#define UART_Tx_PS                     (* (reg32 *) UART_Tx__PS)
/* Data Register */
#define UART_Tx_DR                     (* (reg32 *) UART_Tx__DR)
/* Input Buffer Disable Override */
#define UART_Tx_INP_DIS                (* (reg32 *) UART_Tx__PC2)

/* Interrupt configuration Registers */
#define UART_Tx_INTCFG                 (* (reg32 *) UART_Tx__INTCFG)
#define UART_Tx_INTSTAT                (* (reg32 *) UART_Tx__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define UART_Tx_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(UART_Tx__SIO)
    #define UART_Tx_SIO_REG            (* (reg32 *) UART_Tx__SIO)
#endif /* (UART_Tx__SIO_CFG) */

/* USBIO registers */
#if !defined(UART_Tx__PC) && (CY_PSOC4_4200L)
    #define UART_Tx_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define UART_Tx_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define UART_Tx_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define UART_Tx_DRIVE_MODE_SHIFT       (0x00u)
#define UART_Tx_DRIVE_MODE_MASK        (0x07u << UART_Tx_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins UART_Tx_H */


/* [] END OF FILE */
