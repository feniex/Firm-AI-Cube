/*******************************************************************************
* File Name: HBridge_INA.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "HBridge_INA.h"

static HBridge_INA_BACKUP_STRUCT  HBridge_INA_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: HBridge_INA_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet HBridge_INA_SUT.c usage_HBridge_INA_Sleep_Wakeup
*******************************************************************************/
void HBridge_INA_Sleep(void)
{
    #if defined(HBridge_INA__PC)
        HBridge_INA_backup.pcState = HBridge_INA_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            HBridge_INA_backup.usbState = HBridge_INA_CR1_REG;
            HBridge_INA_USB_POWER_REG |= HBridge_INA_USBIO_ENTER_SLEEP;
            HBridge_INA_CR1_REG &= HBridge_INA_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(HBridge_INA__SIO)
        HBridge_INA_backup.sioState = HBridge_INA_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        HBridge_INA_SIO_REG &= (uint32)(~HBridge_INA_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: HBridge_INA_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to HBridge_INA_Sleep() for an example usage.
*******************************************************************************/
void HBridge_INA_Wakeup(void)
{
    #if defined(HBridge_INA__PC)
        HBridge_INA_PC = HBridge_INA_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            HBridge_INA_USB_POWER_REG &= HBridge_INA_USBIO_EXIT_SLEEP_PH1;
            HBridge_INA_CR1_REG = HBridge_INA_backup.usbState;
            HBridge_INA_USB_POWER_REG &= HBridge_INA_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(HBridge_INA__SIO)
        HBridge_INA_SIO_REG = HBridge_INA_backup.sioState;
    #endif
}


/* [] END OF FILE */
