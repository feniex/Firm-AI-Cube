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
static const uint8 CYCODE eepromBrightnessMotorPosition[6] = {0xFF, 0x00, 0x00, 0x00,0x00,0x00};   //Brightness Value, Motor Position Value, Current Board ID, Initialized Count Already 
static uint8 ramBrightnessMotorPosition[6] ={0x00,0x00,0x00,0x00,00,00};
static const uint8 bSetInitializedAlready = 1;
static uint8 beepromCountAlreadyReset = 0;
static const uint8 *peepromMemory;
extern MotorIO *pMotor;

volatile uint8 timerForInputs=0;
volatile uint16 timerForMotorInputs=0;
volatile uint8 timerForInputsMotor = 0; 
/**********LOCAL FUNCTION PROTOTYPES**********/
static void initializePeripherals(void);
void loadInitialMotorBrightnessValue(void);

static uint16 trackBrightness = 0;
static uint16 trackMotor = 0;

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
    modeChangeISR_Start();
    //ADC_SAR_Seq_1_Start();
    //ADC_SAR_Seq_1_GetResult16();
    //inputIncrease_Start();
    //inputTimerISR_Start();
    
    if(*(volatile uint8 *) &eepromBrightnessMotorPosition[3] == 0)
    {
        calibrateMotor();
        ramBrightnessMotorPosition[3] = 1;
        ramBrightnessMotorPosition[2] = 0;
        //ramBrightnessMotorPosition[1] = 0xFF;
        ramBrightnessMotorPosition[4] = pMotor->forwardLimitCS;
        ramBrightnessMotorPosition[5] = pMotor->backwardLimitCS;
        EmEEPROM_Write(&ramBrightnessMotorPosition[1],&eepromBrightnessMotorPosition[1],5);
    }
    else
    {
        loadLimitSwitchValue();
        loadInitialMotorBrightnessValue();
    }
    loadInitialMotorBrightnessValue();
    
    {
        setIdentityByComm(HEAD_MODULE_ID);
    }
    }    

    for(;;)
    {
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

void takeInputValues(void)
{
    volatile uint8 readInputValues = 0;
    volatile uint8 previousReadInputValues = 0;
    uint8 test = 0;
    
    
    if(timerForInputs == 1)
    {
        timerForInputs = 0;
        readInputValues = inputs_Read();
        timerForMotorInputs++;   
        
        if((readInputValues&DIM_PLUS) == DIM_PLUS)
        {
            if(trackBrightness>=254)
            {
                trackBrightness = 254;
            }
            trackBrightness+=1;
            setBrightness(trackBrightness);
            test = 2;
        }
        else if((readInputValues&DIM_MINUS) == DIM_MINUS)    //DIMMINUS
        {
            if(trackBrightness<=1)
            {
                trackBrightness = 1;
            }
            //trackBrightness = 100;
            trackBrightness-=1;
            setBrightness(trackBrightness);
            test = 3;
        }
        setBrightness(trackBrightness);
    }
    
    if(timerForInputsMotor==1) //|| previousReadInputValues!= readInputValues)
    {
        timerForInputsMotor=0;
        
        if((readInputValues&ZOOM_PLUS) == ZOOM_PLUS)
        {
        if(trackMotor>=254)
        {
            trackMotor = 254;
        }
        //trackMotor=254;
        trackMotor+=1;
        setMotorPosition(trackMotor);
        test = 0;
    }
        else if((readInputValues&ZOOM_MINUS) == ZOOM_MINUS)  //DIMPLUS
        {
        if(trackMotor<=1)
        {
            trackMotor = 1;
        }
        //trackMotor=1;
        trackMotor-=1;
        setMotorPosition(trackMotor);
        test = 1;
    }                  
    }
    previousReadInputValues = readInputValues;
    
}

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

void loadInitialMotorBrightnessValue(void)
{
    static const uint8 * pLocalNonVolatileMemory;
    pLocalNonVolatileMemory = getNonVolatileBarStateMemory();
    
    trackBrightness = pLocalNonVolatileMemory[0];
    trackMotor = pLocalNonVolatileMemory[1];
}

void setMotorPositionValue(uint8 localMotor)
{
    trackMotor = localMotor;
}

void setLightValue(uint8 localLED)
{
    trackBrightness = localLED;
}

/* [] END OF FILE */
