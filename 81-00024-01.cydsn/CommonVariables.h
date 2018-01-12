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
    
/**********DEFINED CONSTANTS**********/
    

/**********DATA STRUCTURES**********/
    

/**********GLOBAL VARIABLES**********/
    

/**********GLOBAL FUNCTION PROTOTYPES**********/
void clearInitializeAlreadyEEPROM(void);
const uint8 * getNonVolatileBarStateMemory(void);
uint8 * getVolatileBarStateMemory(void);
#endif

/* [] END OF FILE */
