/*******************************************************************************
* File Name: TestPin2.c  
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
#include "TestPin2.h"

static TestPin2_BACKUP_STRUCT  TestPin2_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: TestPin2_Sleep
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
*  \snippet TestPin2_SUT.c usage_TestPin2_Sleep_Wakeup
*******************************************************************************/
void TestPin2_Sleep(void)
{
    #if defined(TestPin2__PC)
        TestPin2_backup.pcState = TestPin2_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            TestPin2_backup.usbState = TestPin2_CR1_REG;
            TestPin2_USB_POWER_REG |= TestPin2_USBIO_ENTER_SLEEP;
            TestPin2_CR1_REG &= TestPin2_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(TestPin2__SIO)
        TestPin2_backup.sioState = TestPin2_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        TestPin2_SIO_REG &= (uint32)(~TestPin2_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: TestPin2_Wakeup
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
*  Refer to TestPin2_Sleep() for an example usage.
*******************************************************************************/
void TestPin2_Wakeup(void)
{
    #if defined(TestPin2__PC)
        TestPin2_PC = TestPin2_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            TestPin2_USB_POWER_REG &= TestPin2_USBIO_EXIT_SLEEP_PH1;
            TestPin2_CR1_REG = TestPin2_backup.usbState;
            TestPin2_USB_POWER_REG &= TestPin2_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(TestPin2__SIO)
        TestPin2_SIO_REG = TestPin2_backup.sioState;
    #endif
}


/* [] END OF FILE */
