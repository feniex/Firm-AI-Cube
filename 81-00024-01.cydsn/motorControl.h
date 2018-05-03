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

#include "commonVariables.h"

#define MOTOR_OUTA_HIGH HBridge_INA_DR |= HBridge_INA_MASK  //Sets the motor out A pin high
#define MOTOR_OUTA_LOW HBridge_INA_DR &= ~HBridge_INA_MASK //Sets the motor out A pin low

#define MOTOR_OUTB_HIGH HBridge_INB_DR |= HBridge_INB_MASK  //Sets the motor out B pin high
#define MOTOR_OUTB_LOW HBridge_INB_DR &= ~HBridge_INB_MASK //Sets the motor out B pin low

typedef enum CalibrationStates
{
    START_CALIBRATING = 00,
    MOVE_FORWARD_STATE = 02,
    MOVE_BACKWARD_STATE = 03,
    DONE_CALIBRATING = 1
}CalibrationState;

typedef struct Motor
{
    uint16 currentCS;
    uint16 forwardLimitCS;
    uint16 backwardLimitCS;
    float calculatePercentageOfRange;
    uint8  bDoneMoving;
    
    uint8 hallEffectEdgeDetect;

    int16 forwardPotLimit; 
    int16 backwardPotLimit;
    int16 currentPot;
    
    float desiredPotFloat;
    int16 desiredPot;
    int16 errorPot;
    int16 previousErrorPot;
    
    float Proportional;
    float Integral;
    float Derivative;
    int16 MotorOutput;
    
    uint8 adjustedSpeed;
    uint8 direction;

    uint8 calibrated;
    
    uint16 motorCurrent[12];
    uint8 motorCurrentSamplesIterator;
    uint16 busVoltage;
    uint8 bOverCurrentStart;
    uint8 bOverCurrentEnd;
    uint16 overCurrentTimerOutCounter;
}MotorIO;

typedef enum MotorDirectionOFF_NOTHING
{
    FORWARD = 01,
    BACKWARDS = 10,
    BRAKE = 00,
    OFF_NOTHING = 3
}Direction;

typedef enum MotorSpeed
{
    FULL_SPEED = 0xFF,
    OFF = 00,
    MINIMUM_SPEED = 0x3F
}Speed;

typedef enum MotorConstants
{
    MANIP_VARIABLE_MAX = 0x00FF,
    MANIP_VARIABLE_MIN = 0x0005,
    HARDWARE_LIMIT_MAX = 0x00FF,
    HARDWARE_LIMIT_MIN = 0x0000,
    DESIRED_POSITION = 0
}MotorConstants;

#define Kp 0.75
#define Ki 0.001
#define Kd 4

#define OVER_CURRENT_VALUE 500
#define OVER_CURRENT_TIMER_THRESHOLD 500

#define CENTER_POT 0x080
#define MAX_CENTER_RANGE 0x0100
#define MIN_CENTER_RANGE 0x0008

#define POT_FEEDBACK 3u
#define HBridge_CS   2u
#define VDETECT      2u

#define MAX_CURRENT 10
#define MIN_VOLTAGE 1194

void initializeMotor(void);
void setMotorOutputs(Direction direction, Speed speed);
MotorIO * motorControlLoop(int16 manualDesiredPostion);
int16 calibrateMotor(void);
void loadLimitSwitchValue(void);
void setMotorPosition(uint8 localMotorPosition);

/* [] END OF FILE */
