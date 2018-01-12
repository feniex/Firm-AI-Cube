/*******************************************************************************
* File Name: AmbientTempInput.c  
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
#include "AmbientTempInput.h"

static AmbientTempInput_BACKUP_STRUCT  AmbientTempInput_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: AmbientTempInput_Sleep
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
*  \snippet AmbientTempInput_SUT.c usage_AmbientTempInput_Sleep_Wakeup
*******************************************************************************/
void AmbientTempInput_Sleep(void)
{
    #if defined(AmbientTempInput__PC)
        AmbientTempInput_backup.pcState = AmbientTempInput_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            AmbientTempInput_backup.usbState = AmbientTempInput_CR1_REG;
            AmbientTempInput_USB_POWER_REG |= AmbientTempInput_USBIO_ENTER_SLEEP;
            AmbientTempInput_CR1_REG &= AmbientTempInput_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(AmbientTempInput__SIO)
        AmbientTempInput_backup.sioState = AmbientTempInput_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        AmbientTempInput_SIO_REG &= (uint32)(~AmbientTempInput_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: AmbientTempInput_Wakeup
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
*  Refer to AmbientTempInput_Sleep() for an example usage.
*******************************************************************************/
void AmbientTempInput_Wakeup(void)
{
    #if defined(AmbientTempInput__PC)
        AmbientTempInput_PC = AmbientTempInput_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            AmbientTempInput_USB_POWER_REG &= AmbientTempInput_USBIO_EXIT_SLEEP_PH1;
            AmbientTempInput_CR1_REG = AmbientTempInput_backup.usbState;
            AmbientTempInput_USB_POWER_REG &= AmbientTempInput_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(AmbientTempInput__SIO)
        AmbientTempInput_SIO_REG = AmbientTempInput_backup.sioState;
    #endif
}


/* [] END OF FILE */
