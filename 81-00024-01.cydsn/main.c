/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
/**********CHANGE LOG**********/


/**********PREPROCESSOR DIRECTIVES**********/
#include "CommonVariables.h"
#include "BrightnessCommManager.h"
#include "TemperatureCommManager.h"
#include "DriverControl.h"
#include "motorControl.h"
    
/**********DEFINED CONSTANTS**********/
    

/**********DATA STRUCTURES**********/


/**********GLOBAL VARIABLES**********/
static const uint8 CYCODE eepromBrightnessMotorPosition[5] = {0xFF, 0x00, 0x00, 0x00,0x00};   //Brightness Value, Motor Position Value, Current Board ID, Initialized Count Already 
static uint8 ramBrightnessMotorPosition[5] ={0x00,0x00,0x00,0x00,00};
static const uint8 bSetInitializedAlready = 1;
static uint8 beepromCountAlreadyReset = 0;
static const uint8 *peepromMemory;
extern MotorIO *pMotor;
/**********LOCAL FUNCTION PROTOTYPES**********/
static void initializePeripherals(void);
/**********DEFINED GLOBAL FUNCTIONS**********/

/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Start of program
*
* Parameters:
*  None.
*
* Return:
*  Never returns.
*
*******************************************************************************/
int main()
{   
    {
    CyGlobalIntEnable;
    initializePeripherals();
    
     if(*(volatile uint8 *) &eepromBrightnessMotorPosition[3] == 0)
    {
        calibrateMotor();
        ramBrightnessMotorPosition[3] = 1;
        ramBrightnessMotorPosition[2] = 0;
        ramBrightnessMotorPosition[1] = 0xFF;
        ramBrightnessMotorPosition[4] = pMotor->forwardLimitCS;
        EmEEPROM_Write(&ramBrightnessMotorPosition[1],&eepromBrightnessMotorPosition[1],4);
    }
    else
    {
        loadLimitSwitchValue();
    }
    
    //#if(HEAD_BOARD)
    //        CyDelay(200);
    //    #else
    //        CyDelay(50);  
    //#endif
    /*
    if(*(volatile uint8 *) &eepromBrightnessMotorPosition[3] == 0)
    {
        
        UART_LED_Control_Write(TRUE);
        
        #if(HEAD_BOARD)
            CyDelay(2000);
        #else
            CyDelay(50);  
        #endif

        #if(HEAD_BOARD)
            setIdentityByComm(HEAD_MODULE_ID);
            assignDriverIDs();
            setDriverCountReceived();
        #endif
        
        while(!isDriverCountReceived())
        {
        } 
        
        ramBrightnessMotorPosition[3] = 1;
        ramBrightnessMotorPosition[2] = getDriverID();
        EmEEPROM_Write(&ramBrightnessMotorPosition[2],&eepromBrightnessMotorPosition[2],2);
    }
    */
    //else
    {
        //peepromMemory = &eepromBrightnessMotorPosition[2];
        setIdentityByComm(HEAD_MODULE_ID);
        if(getDriverID()==HEAD_MODULE_ID)
        {
            //UART_LED_Control_Write(TRUE);
        }
        else
        {
            //UART_LED_Control_Write(FALSE);
        }
    }
    }    

    for(;;)
    {
       //PWM_Enable_Write(TRUE);
       //PWM_WriteCompare(0xFF);
        
        //setMotorOutputs(FORWARD,0xFF);
        //CyDelay(5000);
        //setMotorOutputs(BACKWARDS,0xFF);
        //CyDelay(5000);
        timeOutStateMachine(&eepromBrightnessMotorPosition[0]);
        motorControlLoop(0);
    }
}

/**********DEFINED GLOBAL FUNCTIONS**********/

/*******************************************************************************
* Function Name: initializePeripherals
********************************************************************************
*
* Summary:
*  Sets up all peripherals needed for the project.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/

void clearInitializeAlreadyEEPROM(void)
{
    static const uint8 detectedAlready = 0;
    //if(beepromCountAlreadyReset == 0)
    //{
        beepromCountAlreadyReset =1;
        EmEEPROM_Write(&detectedAlready,&eepromBrightnessMotorPosition[3],1);
    //}
}

const uint8 * getNonVolatileBarStateMemory(void)
{
    return &eepromBrightnessMotorPosition[0];
}

uint8 * getVolatileBarStateMemory(void)
{
    return &ramBrightnessMotorPosition[0];
}

/**********DEFINED LOCAL FUNCTIONS**********/

static void initializePeripherals(void)
{
    //UART_LED_Control_Write(TRUE);
    PWM_Enable_Write(FALSE);
    
    PWM_Start();
    PWM_WriteCompare(0);

    CommTimeoutISR_Start();
    AckTimeoutISR_Start();
    
    SamplingTimerISR_Start();
    ADC_SAR_Seq_Start();
    ADC_SAR_Seq_StartConvert();
    
    UART_LED_ISR_Start();
    UART_LED_Start();
    
    //UART_LED_ISR_Start();
    
    //UART_LED_Start();
    //WakeupISR_Start();
    
    LED_ISR_Start(); 
    
    SamplingTimer_Start();
    TimeoutTimer_Start();
    
    EmEEPROM_Start();
    
    initializeMotor();
    //CyDelay(250);
    //LED_Output_Write(FALSE);
    //UART_LED_Control_Write(FALSE);
}


/* [] END OF FILE */
