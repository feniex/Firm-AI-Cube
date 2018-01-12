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

#ifndef TEMPERATURE_COMM_MANAGER_H_
#define TEMPERATURE_COMM_MANAGER_H_

/**********PREPROCESSOR DIRECTIVES**********/
#include <project.h>
    
/**********DEFINED CONSTANTS**********/
    

/**********DATA STRUCTURES**********/
    

/**********GLOBAL VARIABLES**********/
    

/**********GLOBAL FUNCTION PROTOTYPES**********/
void processTemperatureByteReceivedHandler(void);   

uint8 setLastDriverPacket(uint8* dataPacket, uint8 length);
void processAckTimeoutRoutine(void);
void processSamplingTimerRoutine(void);
uint8 isLastDriver(void);
uint8 isReadyToSendNextBrightnessPacket(void);
void clearIsReadyToSendNextBrightnessPacket(void);

#endif
/* [] END OF FILE */
