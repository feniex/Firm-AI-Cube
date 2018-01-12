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

#ifndef BRIGHTNESS_COMM_MANAGER_H_
#define BRIGHTNESS_COMM_MANAGER_H_

/**********PREPROCESSOR DIRECTIVES**********/
#include <project.h>
    
/**********DEFINED CONSTANTS**********/
#define IS_TIME_OUT_TRUE            0    
#define HIGH_TIMOUT                 1
#define LOW_TIMEOUT                 2   

#define MAX_SIZE_OF_RX 13    
    
/**********DATA STRUCTURES**********/
    

/**********GLOBAL VARIABLES**********/
typedef union rxPacketPayload
{
    uint8 bytes[MAX_SIZE_OF_RX];
    
    struct rxData
    {
       uint8 startByte;
       uint8 header;
       uint16 endMotorPosition;
       uint8 desiredLightBrightness[8];
       uint8 calibration;
    }Payload;
}RxPacket;    

/**********GLOBAL FUNCTION PROTOTYPES**********/
uint8 isDriverCountReceived(void);    
void setDriverCountReceived(void);    
void assignDriverIDs(void);
void timeOutStateMachine(const uint8 * nonVolatileMemoryArray);
void isThereHighLowTransitionFromUART(void);
void processTimeoutTimerRoutine(void);
void processBrightnessByteReceivedHandler(void);
void timeoutDefaultBrightness(const uint8 * nonVolatileMemoryArray);
void processCalibrationPacket(void);
uint8 getStateOfBar(void);
uint8 getDegaultPosition(void);
 RxPacket * getRxPacket(void);

#endif
/* [] END OF FILE */
