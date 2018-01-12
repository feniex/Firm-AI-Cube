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

#ifndef IO_CONTROL_H_
#define IO_CONTROL_H_

/**********PREPROCESSOR DIRECTIVES**********/
#include <project.h>
    
#define ADC_SAMPLE_COUNT    4
    
/**********DEFINED CONSTANTS**********/
enum TemperaturePoint
{
    LED = 0,
    SWITCH_NODE = 1,
    VOLTAGE_SENSE = 2,
    SPACE_HOLDER = 3,
    MICRO = 4
};    

/**********DATA STRUCTURES**********/


/**********GLOBAL VARIABLES**********/
    

/**********GLOBAL FUNCTION PROTOTYPES**********/
uint8 getDriverID(void);
uint8 setIdentityByComm(uint8 positionNumber);
uint8 setDriverCount(uint8 newDriverCount);
uint8 isLastDriverInChain(void);
void setAsNotLastDriverInChain(void);
void processSoftStart(void);
void checkForUnderVoltage(uint16 ADC_Value);
uint8 updateBrightnessLevel(uint8 brightnessLevel, uint8 bRegulated);
int16 getMaxTemperature(enum TemperaturePoint channelNumber);
int16 getTemperatureSample(uint8 bSingleSample, enum TemperaturePoint channelNumber, 
int16* sampleArray, uint8 length);
uint8 getNewMaxBrightness(void);
uint8 regulateBrightness(int16* TemperatureData, uint8 length);
uint8 getPreviousBrightness(void);
#endif
/* [] END OF FILE */
