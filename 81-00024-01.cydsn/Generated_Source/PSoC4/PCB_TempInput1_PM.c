/*******************************************************************************
* File Name: PCB_TempInput1.c  
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
#include "PCB_TempInput1.h"

static PCB_TempInput1_BACKUP_STRUCT  PCB_TempInput1_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: PCB_TempInput1_Sleep
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
*  \snippet PCB_TempInput1_SUT.c usage_PCB_TempInput1_Sleep_Wakeup
*******************************************************************************/
void PCB_TempInput1_Sleep(void)
{
    #if defined(PCB_TempInput1__PC)
        PCB_TempInput1_backup.pcState = PCB_TempInput1_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            PCB_TempInput1_backup.usbState = PCB_TempInput1_CR1_REG;
            PCB_TempInput1_USB_POWER_REG |= PCB_TempInput1_USBIO_ENTER_SLEEP;
            PCB_TempInput1_CR1_REG &= PCB_TempInput1_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PCB_TempInput1__SIO)
        PCB_TempInput1_backup.sioState = PCB_TempInput1_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        PCB_TempInput1_SIO_REG &= (uint32)(~PCB_TempInput1_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: PCB_TempInput1_Wakeup
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
*  Refer to PCB_TempInput1_Sleep() for an example usage.
*******************************************************************************/
void PCB_TempInput1_Wakeup(void)
{
    #if defined(PCB_TempInput1__PC)
        PCB_TempInput1_PC = PCB_TempInput1_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            PCB_TempInput1_USB_POWER_REG &= PCB_TempInput1_USBIO_EXIT_SLEEP_PH1;
            PCB_TempInput1_CR1_REG = PCB_TempInput1_backup.usbState;
            PCB_TempInput1_USB_POWER_REG &= PCB_TempInput1_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PCB_TempInput1__SIO)
        PCB_TempInput1_SIO_REG = PCB_TempInput1_backup.sioState;
    #endif
}


/* [] END OF FILE */
