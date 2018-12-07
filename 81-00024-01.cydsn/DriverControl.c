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
#include "DriverControl.h"
#include "BrightnessCommManager.h"

#define MAX_ADC_CONVERSION_WAIT_LIMIT   5
#define SAMPLE_COUNT_PER_CYCLE          1
#define BRIGHTNESS_CHANGE_PER_SAMPLE    1

#define RAMP_DOWN_RATE                  1
#define STEADY_INCREASE_RATE            1
#define STEADY_DECREASE_RATE            1

#define MAX_SCALING_FACTOR              0xFF
#define SAFE_TEMPERATURE_TOLERANCE      0

#define VOLTAGE_SENSE_LOWER_BOUND       670
#define VOLTAGE_SENSE_UPPER_BOUND       870
    
/**********DEFINED CONSTANTS**********/
enum RegulationState
{
    STARTUP,
    STEADY_INCREASE,
    STEADY_DECREASE,
    NO_CHANGE
};

enum TemperatureStatus
{
    WITHIN_TOLERANCE,
    EXCEEDED_UPPER_BOUND,
    EXCEEDED_LOWER_BOUND,
    ERROR
};

typedef struct
{
    const int16 MAX_TEMPERATURE;
    const int16 SAFE_TEMPERATURE;
}ThermalLimit;

static ThermalLimit ThermalLimitArray[ADC_SAMPLE_COUNT] = 
{
    {200, 100}, //LED
    {200, 100}, //SwitchNode  
    {25,  5}, //Micros
    {500, 100}  //Ambient
};

/**********DATA STRUCTURES**********/
typedef struct
{
    uint8 ID_Number;
    uint8 driverCount;
    uint8 bLastDriverInChain;
}DriverProperties;

static DriverProperties PositionData = {0, 0, TRUE};

typedef struct
{
    uint8 requestedBrightness;
    uint8 regulatedBrightness;
    uint8 previousBrightness;
    enum RegulationState currentState;
    uint8 scalingFactor;
}RegulationProperties;

static RegulationProperties RegulationData = {0, 0, 0, STARTUP, 0xFF};
static RegulationProperties RegulationDataFast = {0, 0, 0, STARTUP, 0xFF};

typedef struct
{
    uint8 bEnable;
    uint8 scalingFactor;
}VoltageSenseProperties;

static VoltageSenseProperties VoltageSenseData = {TRUE, 0xFF};
uint8 regulateBrightnessFaster(int16* TemperatureData, uint8 length);
/**********GLOBAL VARIABLES**********/


/**********LOCAL FUNCTION PROTOTYPES**********/
static enum TemperatureStatus getTemperatureStatus(int16* TemperatureData,
    uint8 length, int16 tolerance);

/**********DEFINED GLOBAL FUNCTIONS**********/
uint8 getPreviousBrightness(void)
{
    return RegulationData.previousBrightness;
}

/*******************************************************************************
* Function Name: getDriverID
********************************************************************************
*
* Summary:
*  Returns the ID number of this driver.
*
* Parameters:
*  None.
*
* Return:
*  Value 1 for head module, 2 - 8 for trailer module
*
*******************************************************************************/
uint8 getDriverID(void)
{
    return PositionData.ID_Number;
}

/*******************************************************************************
* Function Name: setIdentityByComm
********************************************************************************
*
* Summary:
*  Sets the ID number for this driver based on UART communication. The number
*  assigned is the driver position away from the controller.
*
* Parameters:
*  positionNumber: The ID number based on position in the chain.
*
* Return:
*  SUCCESS for valid input, FAILURE otherwise
*
*******************************************************************************/
uint8 setIdentityByComm(uint8 positionNumber)
{
    if(positionNumber < HEAD_MODULE_ID || positionNumber > MAX_DRIVER_COUNT)
        return FAILURE;
    
    PositionData.ID_Number = positionNumber;
    
    return SUCCESS;
}

/*******************************************************************************
* Function Name: setDriverCount
********************************************************************************
*
* Summary:
*  Sets the number of drivers in the chain.
*
* Parameters:
*  newDriverCount: The updated number of drivers in the chain.
*
* Return:
*  SUCCESS for valid input, FAILURE otherwise
*
*******************************************************************************/
uint8 setDriverCount(uint8 newDriverCount)
{
    if(newDriverCount < HEAD_MODULE_ID || newDriverCount > MAX_DRIVER_COUNT)
        return FAILURE;
    
    PositionData.driverCount = newDriverCount;
    
    return SUCCESS;
}

/*******************************************************************************
* Function Name: isLastDriverInChain
********************************************************************************
*
* Summary:
*  Determines if this driver is at the end of the chain.
*
* Parameters:
*  None.
*
* Return:
*  TRUE if last driver in the chain, FALSE if otherwise
*
*******************************************************************************/
uint8 isLastDriverInChain(void)
{
    return PositionData.bLastDriverInChain;
}

/*******************************************************************************
* Function Name: setAsNotLastDriverInChain
********************************************************************************
*
* Summary:
*  At the start of the program, this driver is assumed to the be the last driver
*  in the chain. If an ACK packet is received at startup, this function is called
*  to update the status for not being in the last driver.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void setAsNotLastDriverInChain(void)
{
    PositionData.bLastDriverInChain = FALSE;
}

/*******************************************************************************
* Function Name: checkForUnderVoltage
********************************************************************************
*
* Summary:
*  Takes in the voltage sense reading and updates the undervoltage status.
*
* Parameters:
*  ADC_Value: The voltage sense reading
*
* Return:
*  None.
*
*******************************************************************************/
void checkForUnderVoltage(uint16 ADC_Value)
{
    if((VoltageSenseData.bEnable == TRUE) && (ADC_Value < VOLTAGE_SENSE_LOWER_BOUND))
    {
        VoltageSenseData.bEnable = FALSE;
        LED_Timer_Stop();
        VoltageSenseData.scalingFactor = 0;
    }
    else if((VoltageSenseData.bEnable == FALSE) && (ADC_Value > (VOLTAGE_SENSE_UPPER_BOUND)))
    {
        VoltageSenseData.bEnable = TRUE;
        LED_Timer_Start();
    }
}

/*******************************************************************************
* Function Name: processSoftStart
********************************************************************************
*
* Summary:
*  Called in LED_ISR, increases the brightness from full on to full off in 1 second.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void processSoftStart(void)
{
    LED_Timer_ClearInterrupt(LED_Timer_INTR_MASK_TC);
    
    if(VoltageSenseData.scalingFactor < 0xFF)
        VoltageSenseData.scalingFactor++;
    else
        LED_Timer_Stop();
}

/*******************************************************************************
* Function Name: updateBrightnessLevel
********************************************************************************
*
* Summary:
*  Updates the brightness of the LED. Resulting brightness may not match the
*  requested brightness depending on temperature regulation state.
*
* Parameters:
*  brightnessLevel: The desired brightness level for the LED.
*
* Return:
*  The resulting brightness level of the LED
*
*******************************************************************************/
uint8 updateBrightnessLevel(uint8 brightnessLevel, uint8 bRegulated)
{
    static uint8 tempBrightness = 0;
    static uint8 tempPreviousRequestedBrightness = 0;
    
    if(bRegulated != TRUE && bRegulated != FALSE)
    return 0;
    
   // brightnessLevel = (uint8)((uint16)(VoltageSenseData.scalingFactor)*
   //                     (uint16)(brightnessLevel) / MAX_SCALING_FACTOR);
    
    if(brightnessLevel != RegulationData.requestedBrightness)
        RegulationData.requestedBrightness = brightnessLevel;
    
    if(bRegulated == FALSE)
    {   
       // if(RegulationData.requestedBrightness != RegulationData.previousBrightness)
       // {
            if(brightnessLevel > 0)
            {
                PWM_Enable_Write(TRUE);
                PWM_WriteCompare(brightnessLevel);
            }
            else
            {
                PWM_Enable_Write(FALSE);
            }
       // };
        
        //RegulationData.previousBrightness = RegulationData.requestedBrightness;
        return brightnessLevel;
    }
    
    if(RegulationData.regulatedBrightness != RegulationData.previousBrightness)
    {
        if((RegulationData.requestedBrightness>RegulationData.regulatedBrightness)) //&& (RegulationData.currentState!=STARTUP||RegulationData.currentState!=NO_CHANGE))
        {
            tempBrightness = RegulationData.regulatedBrightness;
        }
        else
        {
            tempBrightness = RegulationData.requestedBrightness;
        }
        if(tempBrightness > 0)
        {
            PWM_Enable_Write(TRUE);
            PWM_WriteCompare(tempBrightness);
        }
        else
            PWM_Enable_Write(FALSE);
    }
    
    tempPreviousRequestedBrightness = RegulationData.requestedBrightness;
    RegulationData.previousBrightness = tempBrightness;    
    return tempBrightness;
}

/*******************************************************************************
* Function Name: getMaxTemperature
********************************************************************************
*
* Summary:
*  Obtains the next temperature sample from ADC.
*
* Parameters:
*  None.
*
* Return:
*  The next temperature sample from ADC
*
*******************************************************************************/
int16 getMaxTemperature(enum TemperaturePoint channelNumber)
{
    if(channelNumber < LED || channelNumber > MICRO)
        return 0;
    
    return ThermalLimitArray[channelNumber].MAX_TEMPERATURE;
}

/*******************************************************************************
* Function Name: getTemperatureSample
********************************************************************************
*
* Summary:
*  Obtains the next temperature sample(s) from ADC. This function can return a
*  single sample or multiple samples in one call.
*
* Parameters:
*  bSingleSample: TRUE for single sample, FALSE for multiple samples
*  channelNumber: Channel selection for single sample: LED, SWITCH_NODE, AMBIENT, or MICRO
*  sampleArray: Reference to the array that contains 4 temperature samples
*  length: Size of the array in # of temperature points
*
* Return:
*  Single temperature value or Reference to array of 4 temperature samples
*
*******************************************************************************/
int16 getTemperatureSample(uint8 bSingleSample, enum TemperaturePoint channelNumber, 
    int16* sampleArray, uint8 length)
{  
    uint8 ADC_WaitCount = 0;
    int16 temperatureSample_16 = 0;
    float temperatureSample_float = 0;
    uint32 channelIndex = 0;    
    
    if((bSingleSample != TRUE) && (bSingleSample != FALSE))
        return 0;
    
    if(bSingleSample)
    {   //Input check for single sample
        if(channelNumber < LED || channelNumber > VOLTAGE_SENSE)
            return 0;
    }
    else
    {   //Input check for multiple samples
        if(sampleArray == NULL || length > ADC_SAMPLE_COUNT)
            return 0;
    }
    
    while(!ADC_SAR_Seq_IsEndConversion(ADC_SAR_Seq_RETURN_STATUS) 
        && (ADC_WaitCount < MAX_ADC_CONVERSION_WAIT_LIMIT))
    {   //Wait for ADC conversion to complete
        ADC_WaitCount++;
        CyDelayUs(8);
    }
    
    if(ADC_WaitCount > MAX_ADC_CONVERSION_WAIT_LIMIT)
        return 0;   //For case when conversion doesn't complete
    
    if(bSingleSample)
    {   //Get single sample
        if(channelNumber == MICRO)
        {
            //temperatureSample_float = (float)(ADC_SAR_Seq_GetResult16(VOLTAGE_SENSE));
            temperatureSample_float = temperatureSample_float * 5 / 1.024;
            temperatureSample_16 = (int16)(DieTemp_CountsTo_Celsius((int32)(temperatureSample_float)));            
        }
        else
        {
            if(channelNumber == VOLTAGE_SENSE)
                temperatureSample_16 = ADC_SAR_Seq_GetResult16((uint32)(MICRO));
            else
                temperatureSample_16 = ADC_SAR_Seq_GetResult16((uint32)(channelNumber));
        }
    }
    else
    {   //Get 4 temperature samples
        for(channelIndex = 0; channelIndex < (ADC_SAMPLE_COUNT - 2); channelIndex++)
        {
            temperatureSample_16 = ADC_SAR_Seq_GetResult16(channelIndex);
            sampleArray[channelIndex] = temperatureSample_16;
        }
            
        //temperatureSample_float = (float)(ADC_SAR_Seq_GetResult16(MICRO));
        //temperatureSample_float = temperatureSample_float * 5 / 1.024;
        //sampleArray[ADC_SAMPLE_COUNT - 2]
        //    = (int16)(DieTemp_CountsTo_Celsius((int32)(temperatureSample_float)));
            
        //temperatureSample_16 = ADC_SAR_Seq_GetResult16(MICRO);
        //    sampleArray[ADC_SAMPLE_COUNT - 1] = temperatureSample_16;
    }
    
    return temperatureSample_16;
}

/*******************************************************************************
* Function Name: getNewMaxBrightness
********************************************************************************
*
* Summary:
*  Returns the new max brightness that was adjusted during regulation.
*
* Parameters:
*  None
*
* Return:
*  Adjusted max brightness
*
*******************************************************************************/
uint8 getNewMaxBrightness(void)
{
    return RegulationData.scalingFactor;
}

/*******************************************************************************
* Function Name: regulateBrightness
********************************************************************************
*
* Summary:
*  Adjusts the brightness of the LED based on 4 temperature readings
*  and the current regulation state.
*
* Parameters:
*  TemperatureData: Reference to the 4 temperature points
*  length: Size of array in # of temperature points
*
* Return:
*  The updated brightness based on regulation
*
*******************************************************************************/
uint8 regulateBrightness(int16* TemperatureData, uint8 length)
{
    static uint8 timerCountLocal = 0;
    enum TemperatureStatus temperatureStatus = WITHIN_TOLERANCE;
    
    if(TemperatureData == NULL || length > ADC_SAMPLE_COUNT || PositionData.ID_Number != 1)
        return 0;
    
    switch(RegulationData.currentState)
    {
        case STARTUP:
            if((timerCountLocal % SAMPLE_COUNT_PER_CYCLE) == 0)
            {
                RegulationData.scalingFactor = MAX_SCALING_FACTOR;
                RegulationData.regulatedBrightness = RegulationData.requestedBrightness;
            }
            if((timerCountLocal % (SAMPLE_COUNT_PER_CYCLE * BRIGHTNESS_CHANGE_PER_SAMPLE)) == 0)
            {
                temperatureStatus = getTemperatureStatus(TemperatureData, length, 0);
                if(temperatureStatus == EXCEEDED_UPPER_BOUND)
                    RegulationData.currentState = STEADY_DECREASE;
            }
            break;            
        case STEADY_DECREASE:  
            if((timerCountLocal % SAMPLE_COUNT_PER_CYCLE) == 0)
            {
                if(RegulationData.scalingFactor > 0)
                    RegulationData.scalingFactor--;
            
                RegulationData.regulatedBrightness = (uint8)((uint16)(RegulationData.requestedBrightness) * 
                    (uint16)(RegulationData.scalingFactor) / MAX_SCALING_FACTOR);
            }
            if((timerCountLocal % (SAMPLE_COUNT_PER_CYCLE * BRIGHTNESS_CHANGE_PER_SAMPLE)) == 0)
            {
                            temperatureStatus = getTemperatureStatus(TemperatureData, length,
                    SAFE_TEMPERATURE_TOLERANCE);
                
                if(temperatureStatus == WITHIN_TOLERANCE)
                    RegulationData.currentState = NO_CHANGE;
                else if(temperatureStatus == EXCEEDED_LOWER_BOUND)
                    RegulationData.currentState = STEADY_INCREASE;
            }
            break;
        case STEADY_INCREASE:
            if((timerCountLocal % SAMPLE_COUNT_PER_CYCLE) == 0)
            {
                if(RegulationData.scalingFactor < MAX_SCALING_FACTOR)
                    RegulationData.scalingFactor++;
            
                RegulationData.regulatedBrightness = (uint8)((uint16)(RegulationData.requestedBrightness) * 
                    (uint16)(RegulationData.scalingFactor) / MAX_SCALING_FACTOR);
            }
            if((timerCountLocal % (SAMPLE_COUNT_PER_CYCLE * BRIGHTNESS_CHANGE_PER_SAMPLE)) == 0)
            {
                temperatureStatus = getTemperatureStatus(TemperatureData, length,
                    SAFE_TEMPERATURE_TOLERANCE);
                
                if(temperatureStatus == EXCEEDED_UPPER_BOUND)
                    RegulationData.currentState = STEADY_DECREASE;
                else if(temperatureStatus == WITHIN_TOLERANCE)
                    RegulationData.currentState = NO_CHANGE;
            }
            break;
        case NO_CHANGE:
            if((timerCountLocal % SAMPLE_COUNT_PER_CYCLE) == 0)
            {
                RegulationData.regulatedBrightness = (uint8)((uint16)(RegulationData.requestedBrightness) * 
                    (uint16)(RegulationData.scalingFactor) / MAX_SCALING_FACTOR);
            }
            if((timerCountLocal % (SAMPLE_COUNT_PER_CYCLE * BRIGHTNESS_CHANGE_PER_SAMPLE)) == 0)
            {
                temperatureStatus = getTemperatureStatus(TemperatureData, length,
                    SAFE_TEMPERATURE_TOLERANCE);
                
                if(temperatureStatus == EXCEEDED_UPPER_BOUND)
                    RegulationData.currentState = STEADY_DECREASE;
                else if(temperatureStatus == EXCEEDED_LOWER_BOUND)
                    RegulationData.currentState = STEADY_INCREASE;
            }
            break;
    }
    
    timerCountLocal = (timerCountLocal + 1) % (SAMPLE_COUNT_PER_CYCLE * BRIGHTNESS_CHANGE_PER_SAMPLE);   
    return RegulationData.regulatedBrightness;    
}

uint8 regulateBrightnessFaster(int16* TemperatureData, uint8 length)
{
    static uint8 timerCountLocalFaster = 0;
    enum TemperatureStatus temperatureStatusFaster = WITHIN_TOLERANCE;
    
    if(TemperatureData == NULL || length > ADC_SAMPLE_COUNT || PositionData.ID_Number != 1)
        return 0;
    
    switch(RegulationDataFast.currentState)
    {
        case STARTUP:
            if((timerCountLocalFaster % SAMPLE_COUNT_PER_CYCLE) == 0)
            {
                RegulationDataFast.scalingFactor = MAX_SCALING_FACTOR;
                RegulationDataFast.regulatedBrightness = RegulationDataFast.requestedBrightness;
            }
            if((timerCountLocalFaster % (SAMPLE_COUNT_PER_CYCLE * BRIGHTNESS_CHANGE_PER_SAMPLE)) == 0)
            {
                temperatureStatusFaster = getTemperatureStatus(TemperatureData, length, 0);
                if(temperatureStatusFaster == EXCEEDED_UPPER_BOUND)
                    RegulationDataFast.currentState = STEADY_DECREASE;
            }
            break;            
        case STEADY_DECREASE:  
            if((timerCountLocalFaster % SAMPLE_COUNT_PER_CYCLE) == 0)
            {
                if(RegulationDataFast.scalingFactor > 0)
                    RegulationDataFast.scalingFactor--;
            
                RegulationDataFast.regulatedBrightness = (uint8)((uint16)(RegulationDataFast.requestedBrightness) * 
                    (uint16)(RegulationDataFast.scalingFactor) / MAX_SCALING_FACTOR);
            }
            if((timerCountLocalFaster % (SAMPLE_COUNT_PER_CYCLE * BRIGHTNESS_CHANGE_PER_SAMPLE)) == 0)
            {
                            temperatureStatusFaster = getTemperatureStatus(TemperatureData, length,
                    SAFE_TEMPERATURE_TOLERANCE);
                
                if(temperatureStatusFaster == WITHIN_TOLERANCE)
                    RegulationDataFast.currentState = NO_CHANGE;
                else if(temperatureStatusFaster == EXCEEDED_LOWER_BOUND)
                    RegulationDataFast.currentState = STEADY_INCREASE;
            }
            break;
        case STEADY_INCREASE:
            if((timerCountLocalFaster % SAMPLE_COUNT_PER_CYCLE) == 0)
            {
                if(RegulationDataFast.scalingFactor < MAX_SCALING_FACTOR)
                    RegulationDataFast.scalingFactor++;
            
                RegulationDataFast.regulatedBrightness = (uint8)((uint16)(RegulationDataFast.requestedBrightness) * 
                    (uint16)(RegulationDataFast.scalingFactor) / MAX_SCALING_FACTOR);
            }
            if((timerCountLocalFaster % (SAMPLE_COUNT_PER_CYCLE * BRIGHTNESS_CHANGE_PER_SAMPLE)) == 0)
            {
                temperatureStatusFaster = getTemperatureStatus(TemperatureData, length,
                    SAFE_TEMPERATURE_TOLERANCE);
                
                if(temperatureStatusFaster == EXCEEDED_UPPER_BOUND)
                    RegulationDataFast.currentState = STEADY_DECREASE;
                else if(temperatureStatusFaster == WITHIN_TOLERANCE)
                    RegulationDataFast.currentState = NO_CHANGE;
            }
            break;
        case NO_CHANGE:
            if((timerCountLocalFaster % SAMPLE_COUNT_PER_CYCLE) == 0)
            {
                RegulationDataFast.regulatedBrightness = (uint8)((uint16)(RegulationDataFast.requestedBrightness) * 
                    (uint16)(RegulationDataFast.scalingFactor) / MAX_SCALING_FACTOR);
            }
            if((timerCountLocalFaster % (SAMPLE_COUNT_PER_CYCLE * BRIGHTNESS_CHANGE_PER_SAMPLE)) == 0)
            {
                temperatureStatusFaster = getTemperatureStatus(TemperatureData, length,
                    SAFE_TEMPERATURE_TOLERANCE);
                
                if(temperatureStatusFaster == EXCEEDED_UPPER_BOUND)
                    RegulationDataFast.currentState = STEADY_DECREASE;
                else if(temperatureStatusFaster == EXCEEDED_LOWER_BOUND)
                    RegulationDataFast.currentState = STEADY_INCREASE;
            }
            break;
    }
    
    timerCountLocalFaster = (timerCountLocalFaster + 1) % (SAMPLE_COUNT_PER_CYCLE * BRIGHTNESS_CHANGE_PER_SAMPLE);   
    return RegulationDataFast.regulatedBrightness;    
}

/**********DEFINED LOCAL FUNCTIONS**********/
/*******************************************************************************
* Function Name: getTemperatureStatus
********************************************************************************
*
* Summary:
*  Returns temperature status based on 4 temperature points
*
* Parameters:
*  TemperatureData: Reference to the 4 temperature samples to check
*  length: Size of int16 array
*  tolerance: Tolerance amount for regulation (Range: temperature +/- tolerance)
*
* Return:
*  EXCEEDED_UPPER_BOUND, EXCEEDED_LOWER_BOUND, or WITHIN_TOLERANCE as valid inputs,
*  ERROR otherwise
*
*******************************************************************************/
static enum TemperatureStatus getTemperatureStatus(int16* TemperatureData,
    uint8 length, int16 tolerance)
{
    enum TemperaturePoint dataIndex = LED;
    
    if(TemperatureData == NULL)
        return ERROR;
    
    if(length > ADC_SAMPLE_COUNT)
        return ERROR;
    
    for(dataIndex = LED; dataIndex < length; dataIndex++)
    {
        if(TemperatureData[dataIndex] > 
            (ThermalLimitArray[dataIndex].MAX_TEMPERATURE + tolerance))
            return EXCEEDED_UPPER_BOUND;
    }
    
    for(dataIndex = LED; dataIndex < length; dataIndex++)
    {
        if(TemperatureData[dataIndex] < 
            (ThermalLimitArray[dataIndex].MAX_TEMPERATURE - tolerance))
            return EXCEEDED_LOWER_BOUND;
    }
    
    return WITHIN_TOLERANCE;
}

void setBrightness(unsigned char localBrightness)
{
    static uint8 previousBrightnessLocal = 0;
    
    RegulationData.requestedBrightness = localBrightness;
    
    if(localBrightness!=previousBrightnessLocal)
    {
        updateBrightnessLevel(localBrightness, FALSE);
    }
    else
    {
        if(previousBrightnessLocal != RegulationData.requestedBrightness)
        {
            updateBrightnessLevel(RegulationData.requestedBrightness, FALSE);
        }
        else
        {
            updateBrightnessLevel(RegulationData.requestedBrightness, TRUE);
        }
    }
    
    previousBrightnessLocal = localBrightness;
}

/* [] END OF FILE */
