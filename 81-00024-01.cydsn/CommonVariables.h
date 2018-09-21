/* ========================================
 *
 * Copyright FENIEX INDUSTRIES, 2016
 * 4200 CONTROLLER
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
/**********CHANGE LOG**********/

#ifndef COMMON_VARIABLES_H_
#define COMMON_VARIABLES_H_

/**********PREPROCESSOR DIRECTIVES**********/
#include <project.h>
    
#define SUCCESS 0
#define FAILURE 1

#define TRUE    1
#define FALSE   0
    
#define HEAD_BOARD          FALSE
#define HEAD_MODULE_ID      1
#define MAX_DRIVER_COUNT    8
    
#define ZOOM_PLUS   0x04
#define ZOOM_MINUS  0x01
#define DIM_PLUS    0x02
#define DIM_MINUS   0x08
    
/**********DEFINED CONSTANTS**********/
extern volatile uint8 timerForInputs; 
extern volatile uint8 timerForInputsMotor; 
    

/**********DATA STRUCTURES**********/
    

/**********GLOBAL VARIABLES**********/
    

/**********GLOBAL FUNCTION PROTOTYPES**********/
void clearInitializeAlreadyEEPROM(void);
const uint8 * getNonVolatileBarStateMemory(void);
uint8 * getVolatileBarStateMemory(void);
void takeInputValues(void);
#endif

/* [] END OF FILE */
