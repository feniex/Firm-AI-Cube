/*******************************************************************************
* File Name: TestPin.h  
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

#if !defined(CY_PINS_TestPin_H) /* Pins TestPin_H */
#define CY_PINS_TestPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "TestPin_aliases.h"


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
} TestPin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   TestPin_Read(void);
void    TestPin_Write(uint8 value);
uint8   TestPin_ReadDataReg(void);
#if defined(TestPin__PC) || (CY_PSOC4_4200L) 
    void    TestPin_SetDriveMode(uint8 mode);
#endif
void    TestPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   TestPin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void TestPin_Sleep(void); 
void TestPin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(TestPin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define TestPin_DRIVE_MODE_BITS        (3)
    #define TestPin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - TestPin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the TestPin_SetDriveMode() function.
         *  @{
         */
        #define TestPin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define TestPin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define TestPin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define TestPin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define TestPin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define TestPin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define TestPin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define TestPin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define TestPin_MASK               TestPin__MASK
#define TestPin_SHIFT              TestPin__SHIFT
#define TestPin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TestPin_SetInterruptMode() function.
     *  @{
     */
        #define TestPin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define TestPin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define TestPin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define TestPin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(TestPin__SIO)
    #define TestPin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(TestPin__PC) && (CY_PSOC4_4200L)
    #define TestPin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define TestPin_USBIO_DISABLE              ((uint32)(~TestPin_USBIO_ENABLE))
    #define TestPin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define TestPin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define TestPin_USBIO_ENTER_SLEEP          ((uint32)((1u << TestPin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << TestPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define TestPin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << TestPin_USBIO_SUSPEND_SHIFT)))
    #define TestPin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << TestPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define TestPin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(TestPin__PC)
    /* Port Configuration */
    #define TestPin_PC                 (* (reg32 *) TestPin__PC)
#endif
/* Pin State */
#define TestPin_PS                     (* (reg32 *) TestPin__PS)
/* Data Register */
#define TestPin_DR                     (* (reg32 *) TestPin__DR)
/* Input Buffer Disable Override */
#define TestPin_INP_DIS                (* (reg32 *) TestPin__PC2)

/* Interrupt configuration Registers */
#define TestPin_INTCFG                 (* (reg32 *) TestPin__INTCFG)
#define TestPin_INTSTAT                (* (reg32 *) TestPin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define TestPin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(TestPin__SIO)
    #define TestPin_SIO_REG            (* (reg32 *) TestPin__SIO)
#endif /* (TestPin__SIO_CFG) */

/* USBIO registers */
#if !defined(TestPin__PC) && (CY_PSOC4_4200L)
    #define TestPin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define TestPin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define TestPin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define TestPin_DRIVE_MODE_SHIFT       (0x00u)
#define TestPin_DRIVE_MODE_MASK        (0x07u << TestPin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins TestPin_H */


/* [] END OF FILE */
