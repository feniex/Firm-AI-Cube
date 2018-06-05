/*******************************************************************************
* File Name: ZOOM_MINUS.c  
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
#include "ZOOM_MINUS.h"

static ZOOM_MINUS_BACKUP_STRUCT  ZOOM_MINUS_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: ZOOM_MINUS_Sleep
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
*  \snippet ZOOM_MINUS_SUT.c usage_ZOOM_MINUS_Sleep_Wakeup
*******************************************************************************/
void ZOOM_MINUS_Sleep(void)
{
    #if defined(ZOOM_MINUS__PC)
        ZOOM_MINUS_backup.pcState = ZOOM_MINUS_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            ZOOM_MINUS_backup.usbState = ZOOM_MINUS_CR1_REG;
            ZOOM_MINUS_USB_POWER_REG |= ZOOM_MINUS_USBIO_ENTER_SLEEP;
            ZOOM_MINUS_CR1_REG &= ZOOM_MINUS_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(ZOOM_MINUS__SIO)
        ZOOM_MINUS_backup.sioState = ZOOM_MINUS_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        ZOOM_MINUS_SIO_REG &= (uint32)(~ZOOM_MINUS_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: ZOOM_MINUS_Wakeup
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
*  Refer to ZOOM_MINUS_Sleep() for an example usage.
*******************************************************************************/
void ZOOM_MINUS_Wakeup(void)
{
    #if defined(ZOOM_MINUS__PC)
        ZOOM_MINUS_PC = ZOOM_MINUS_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            ZOOM_MINUS_USB_POWER_REG &= ZOOM_MINUS_USBIO_EXIT_SLEEP_PH1;
            ZOOM_MINUS_CR1_REG = ZOOM_MINUS_backup.usbState;
            ZOOM_MINUS_USB_POWER_REG &= ZOOM_MINUS_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(ZOOM_MINUS__SIO)
        ZOOM_MINUS_SIO_REG = ZOOM_MINUS_backup.sioState;
    #endif
}


/* [] END OF FILE */
