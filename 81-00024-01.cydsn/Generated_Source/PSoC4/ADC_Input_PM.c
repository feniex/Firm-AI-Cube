/*******************************************************************************
* File Name: ADC_Input.c  
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
#include "ADC_Input.h"

static ADC_Input_BACKUP_STRUCT  ADC_Input_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: ADC_Input_Sleep
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
*  \snippet ADC_Input_SUT.c usage_ADC_Input_Sleep_Wakeup
*******************************************************************************/
void ADC_Input_Sleep(void)
{
    #if defined(ADC_Input__PC)
        ADC_Input_backup.pcState = ADC_Input_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            ADC_Input_backup.usbState = ADC_Input_CR1_REG;
            ADC_Input_USB_POWER_REG |= ADC_Input_USBIO_ENTER_SLEEP;
            ADC_Input_CR1_REG &= ADC_Input_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(ADC_Input__SIO)
        ADC_Input_backup.sioState = ADC_Input_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        ADC_Input_SIO_REG &= (uint32)(~ADC_Input_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: ADC_Input_Wakeup
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
*  Refer to ADC_Input_Sleep() for an example usage.
*******************************************************************************/
void ADC_Input_Wakeup(void)
{
    #if defined(ADC_Input__PC)
        ADC_Input_PC = ADC_Input_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            ADC_Input_USB_POWER_REG &= ADC_Input_USBIO_EXIT_SLEEP_PH1;
            ADC_Input_CR1_REG = ADC_Input_backup.usbState;
            ADC_Input_USB_POWER_REG &= ADC_Input_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(ADC_Input__SIO)
        ADC_Input_SIO_REG = ADC_Input_backup.sioState;
    #endif
}


/* [] END OF FILE */
