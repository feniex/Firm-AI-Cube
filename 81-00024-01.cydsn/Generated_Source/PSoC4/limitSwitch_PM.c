/*******************************************************************************
* File Name: limitSwitch.c  
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
#include "limitSwitch.h"

static limitSwitch_BACKUP_STRUCT  limitSwitch_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: limitSwitch_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
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
*  \snippet limitSwitch_SUT.c usage_limitSwitch_Sleep_Wakeup
*******************************************************************************/
void limitSwitch_Sleep(void)
{
    #if defined(limitSwitch__PC)
        limitSwitch_backup.pcState = limitSwitch_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            limitSwitch_backup.usbState = limitSwitch_CR1_REG;
            limitSwitch_USB_POWER_REG |= limitSwitch_USBIO_ENTER_SLEEP;
            limitSwitch_CR1_REG &= limitSwitch_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(limitSwitch__SIO)
        limitSwitch_backup.sioState = limitSwitch_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        limitSwitch_SIO_REG &= (uint32)(~limitSwitch_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: limitSwitch_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to limitSwitch_Sleep() for an example usage.
*******************************************************************************/
void limitSwitch_Wakeup(void)
{
    #if defined(limitSwitch__PC)
        limitSwitch_PC = limitSwitch_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            limitSwitch_USB_POWER_REG &= limitSwitch_USBIO_EXIT_SLEEP_PH1;
            limitSwitch_CR1_REG = limitSwitch_backup.usbState;
            limitSwitch_USB_POWER_REG &= limitSwitch_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(limitSwitch__SIO)
        limitSwitch_SIO_REG = limitSwitch_backup.sioState;
    #endif
}


/* [] END OF FILE */
