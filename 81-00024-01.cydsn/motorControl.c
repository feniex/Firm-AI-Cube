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

#include "motorControl.h"
#include "BrightnessCommManager.h"

MotorIO *pMotor;
RxPacket * rxPacketLocal;
MotorIO motorStatus = 
{0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
MotorIO *pMotor;

uint8 bDoneMovingCalibrate = FALSE;
static uint32 timeOutCalibrate = 0;
uint16 checkMotorCurrent(void);

/*******************************************************************************
* ISR Name: HALL_EFFECT_EDGE_DETECT_INTERRUPT
********************************************************************************
*
* Summary:
*  Executes whenever an edge is detected from the hall effect sensor.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(HALL_EFFECT_EDGE_DETECT_INTERRUPT)
{    
    //static uint16 testPotValue = 0;
    pMotor->hallEffectEdgeDetect = TRUE;
    setMotorOutputs(BRAKE,0xFF);
    CyDelay(10);
    pMotor->forwardLimitCS = ADC_SAR_Seq_GetResult16(POT_FEEDBACK);
    pMotor->forwardLimitCS = pMotor->forwardLimitCS>>3;
    if(pMotor->forwardLimitCS<60)
    {
        pMotor->backwardLimitCS=pMotor->forwardLimitCS-pMotor->forwardLimitCS;
    }
    else
    {
        pMotor->backwardLimitCS=pMotor->forwardLimitCS-60;
    }
    pMotor->calibrated = DONE_CALIBRATING;
    limitSwitch_ClearInterrupt();
}

CY_ISR(OVER_CURRENT_ISR)
{
    if(ADC_SAR_Seq_IsEndConversion(ADC_SAR_Seq_RETURN_STATUS) !=0)
    {
        pMotor->motorCurrent[pMotor->motorCurrentSamplesIterator] = checkMotorCurrent();
        pMotor->motorCurrentSamplesIterator++;
    }
    

    if(pMotor->motorCurrent[0]>= OVER_CURRENT_VALUE && pMotor->motorCurrent[1]>= OVER_CURRENT_VALUE && pMotor->motorCurrent[2] >= OVER_CURRENT_VALUE && pMotor->motorCurrent[3] >= OVER_CURRENT_VALUE && pMotor->motorCurrent[4] >= OVER_CURRENT_VALUE && pMotor->motorCurrent[5] >= OVER_CURRENT_VALUE && pMotor->motorCurrent[6] >= OVER_CURRENT_VALUE && pMotor->motorCurrent[7] >= OVER_CURRENT_VALUE && pMotor->motorCurrent[8] >= OVER_CURRENT_VALUE && pMotor->motorCurrent[9] >= OVER_CURRENT_VALUE && pMotor->motorCurrent[10] >= OVER_CURRENT_VALUE && pMotor->motorCurrent[11] >= OVER_CURRENT_VALUE)// && pMotor->motorCurrent[12] >= OVER_CURRENT_VALUE && pMotor->motorCurrent[13] >= OVER_CURRENT_VALUE && pMotor->motorCurrent[14] >= OVER_CURRENT_VALUE && pMotor->motorCurrent[15] >= OVER_CURRENT_VALUE && pMotor->motorCurrent[16] >= OVER_CURRENT_VALUE && pMotor->motorCurrent[17] >= OVER_CURRENT_VALUE && pMotor->motorCurrent[18] >= OVER_CURRENT_VALUE && pMotor->motorCurrent[19] >= OVER_CURRENT_VALUE && pMotor->motorCurrent[20] >= OVER_CURRENT_VALUE && pMotor->motorCurrent[21] >= OVER_CURRENT_VALUE && pMotor->motorCurrent[22] >= OVER_CURRENT_VALUE && pMotor->motorCurrent[23] >= OVER_CURRENT_VALUE && pMotor->motorCurrent[24] >= OVER_CURRENT_VALUE)
    {
            setMotorOutputs(BRAKE,0xFF);
            for(pMotor->motorCurrentSamplesIterator = 0; pMotor->motorCurrentSamplesIterator<12; pMotor->motorCurrentSamplesIterator++)
            {
                pMotor->motorCurrent[pMotor->motorCurrentSamplesIterator] = 0;
            }
            pMotor->motorCurrentSamplesIterator = 0;
            pMotor->bOverCurrentStart = TRUE;
    }
    if( pMotor->bOverCurrentStart == TRUE)
    {
        pMotor->overCurrentTimerOutCounter++;
        if(pMotor->overCurrentTimerOutCounter>=OVER_CURRENT_TIMER_THRESHOLD)
        {
            pMotor->overCurrentTimerOutCounter=0;
            pMotor->bOverCurrentStart = FALSE;
        }
    }
    if(pMotor->motorCurrentSamplesIterator>=12)
    {
        pMotor->motorCurrentSamplesIterator = 0;
    }
    
    timerForInputs = 1;
    
    overCurrentTimerISR_ClearPending();
    overCurrentTimer_ReadStatusRegister();
    //overCurrentTimer_ClearInterrupt(overCurrentTimer_INTR_MASK_TC);
}

/*******************************************************************************
* Function Name: initializeMotor
********************************************************************************
*
* Summary:
*  Inititates the motor PWM module
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void initializeMotor(void)
{  
    static const uint8 * pNonVolatileMotorPosition = 0;
    pwmClock_Enable();
    motorControlPWM_Start();
    motorControlPWM_SetCompareMode(motorControlPWM__B_PWM__LESS_THAN);
    motorControlPWM_WriteCompare(0x00);
    pMotor = &motorStatus;
    rxPacketLocal = getRxPacket();
    pNonVolatileMotorPosition = getNonVolatileBarStateMemory();
    rxPacketLocal->Payload.endMotorPosition = pNonVolatileMotorPosition[1];
    pMotor->forwardLimitCS = 255;
    setMotorOutputs(BRAKE,0xFF);
    overCurrentTimerISR_StartEx(OVER_CURRENT_ISR);
    overCurrentTimer_Start();
    //aMux_Start();
}

/*******************************************************************************
* Function Name: setMotorOutputs
********************************************************************************
*
* Summary:
*  Inititates the calibration sequence for the motor
*
* Parameters:  
*   Direction: 00 BRAKE
*              01 Forward
*              10 Reverse
*   Speed:     0-255 Steps of control
*
* Return:
*   None
*
*******************************************************************************/


/*******************************************************************************
* Function Name: calibrateMotor
********************************************************************************
*
* Summary:
*  Inititates the calibration sequence for the motor
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/

int16 calibrateMotor(void)
{
    pMotor->calibrated = START_CALIBRATING;
    
    while(pMotor->calibrated!=1)
    {
       //while(bDoneMovingCalibrate == FALSE)
       //{
            //motorControlLoop(1);
       //}
       hallEffectISR_StartEx(HALL_EFFECT_EDGE_DETECT_INTERRUPT);
       CyDelay(5000);
       bDoneMovingCalibrate = FALSE;
       while(bDoneMovingCalibrate == FALSE)
       {
            if(pMotor->calibrated == 1)
            {
                timeOutCalibrate = 0;
                CyDelay(1);
                setMotorOutputs(BRAKE,0xFF);
                break;
            }
     
            motorControlLoop(252);
       };
       // CyDelay(5000);
       //bDoneMovingCalibrate = FALSE;
       timeOutCalibrate++;
       if(timeOutCalibrate >= 6)
       {
            timeOutCalibrate = 0;
            break;
       }
    }
    setMotorOutputs(BRAKE,0xFF);
    hallEffectISR_Stop();
    CyDelay(10);
    return pMotor->forwardLimitCS;
}

void loadLimitSwitchValue(void)
{
    static const uint8 * pLocalNonVolatileMemory;
    pLocalNonVolatileMemory = getNonVolatileBarStateMemory();
    pMotor->forwardLimitCS = pLocalNonVolatileMemory[4];
    pMotor->backwardLimitCS = pLocalNonVolatileMemory[5];
}

void setMotorOutputs(Direction direction, Speed speed)
{
    if(direction == FORWARD)
    {
        MOTOR_OUTB_LOW;
        MOTOR_OUTA_HIGH;
    }
    else if(direction == BACKWARDS)
    {
        MOTOR_OUTB_HIGH;
        MOTOR_OUTA_LOW;
    }
    else if(direction == BRAKE)
    {
        MOTOR_OUTB_LOW;
        MOTOR_OUTA_LOW;
    }
    else if(direction == OFF_NOTHING)
    {
        MOTOR_OUTB_HIGH;
        MOTOR_OUTA_HIGH;
    }
    
    motorControlPWM_WriteCompare(speed);
}

MotorIO * motorControlLoop(int16 manualDesiredPostion)
{   
    if(pMotor->bOverCurrentStart == FALSE)
    {
    //pMotor->motorCurrent = checkMotorCurrent();
    //pMotor->busVoltage = checkBusVoltage();   
    //setMotorOutputs(BACKWARDS,0xFF);
    //if(checkMotorCurrent()< MAX_CURRENT || checkBusVoltage() > MIN_VOLTAGE)
    {
        if(manualDesiredPostion!=0)
        {
            pMotor->desiredPot = manualDesiredPostion;
        }
        else
        {
            //if(getStateOfBar() == 1)
            //{
            //    pMotor->desiredPot = (int16)getDegaultPosition();
            //}
            if(pMotor->desiredPot != rxPacketLocal->Payload.endMotorPosition) //&& getStateOfBar() == 0)
            {
                pMotor->desiredPot = rxPacketLocal->Payload.endMotorPosition;
                pMotor->calculatePercentageOfRange = pMotor->forwardLimitCS;
                pMotor->calculatePercentageOfRange = pMotor->calculatePercentageOfRange/255;
                pMotor->desiredPotFloat = pMotor->desiredPot;
                pMotor->desiredPot = (int16)pMotor->desiredPotFloat*(pMotor->calculatePercentageOfRange);
            }
        }

            //Account for endian change from PSOC 5 to PSOC 3 architectures
        //pMotor->desiredPot = pMotor->desiredPot*2;
        //pMotor->desiredPot = 0xFF;


        if(pMotor->desiredPot>=pMotor->forwardLimitCS)//if(pMotor->desiredPot>=255)
        {
            pMotor->desiredPot = pMotor->forwardLimitCS;

        }
        
        if(pMotor->desiredPot<=pMotor->backwardLimitCS)//if(pMotor->desiredPot>=255)
        {
            pMotor->desiredPot = pMotor->backwardLimitCS;

        }
        
        if(pMotor->desiredPot>=HARDWARE_LIMIT_MAX)//if(pMotor->desiredPot>=255)
        {
            pMotor->desiredPot = HARDWARE_LIMIT_MAX;
            //pMotor->calculatePercentageOfRange = pMotor->forwardLimitCS/255;
            //pMotor->desiredPot = pMotor->desiredPot*(pMotor->calculatePercentageOfRange);
            //pMotor->desiredPot = 255;
        }
        
        if(pMotor->desiredPot<=HARDWARE_LIMIT_MIN)
        {
            pMotor->desiredPot = HARDWARE_LIMIT_MIN;
        }
       
        //previous_error = error or 0 if undefined
        //error = setpoint - actual_position
        //P = Kp * error
        //I = I + Ki * error * dt
        //D = Kd * (error - previous_error) / dt
        //output = P + I + D
        //wait(dt) 
        //aMux_Select(0x01);
        
        pMotor->currentPot = ADC_SAR_Seq_GetResult16(POT_FEEDBACK);
        pMotor->currentPot = pMotor->currentPot>>3;
        
        pMotor->errorPot = pMotor->desiredPot - pMotor->currentPot;
        pMotor->Proportional = Kp * pMotor->errorPot;
        pMotor->Integral =Ki * pMotor->Integral + pMotor->errorPot;
        pMotor->Derivative = Kd*pMotor->errorPot - pMotor->previousErrorPot;
        pMotor->MotorOutput = pMotor->Proportional + pMotor->Integral + pMotor->Derivative;
        
        
        
        if(pMotor->MotorOutput>=255)
        {
            pMotor->MotorOutput=255;
        }
        else if(pMotor->MotorOutput<=-255)
        {
            pMotor->MotorOutput=-255;
        }
        
        //pMotor->currentCS = getCurrentSense();
        
        
        if(pMotor->MotorOutput >= DESIRED_POSITION-TOLERANCE && pMotor->MotorOutput<= DESIRED_POSITION+TOLERANCE)
        {
            setMotorOutputs(BRAKE,0xFF);
            CyDelay(5);
            bDoneMovingCalibrate = TRUE;
        }
        else if(pMotor->MotorOutput>DESIRED_POSITION+TOLERANCE)
        {
                bDoneMovingCalibrate = FALSE;
                setMotorOutputs(FORWARD,pMotor->MotorOutput);
                if(manualDesiredPostion!=0)
                {
                    setMotorOutputs(FORWARD,0xFF);
                }
                else
                {
                    setMotorOutputs(FORWARD,pMotor->MotorOutput);
                }
        }
        else if(pMotor->MotorOutput<DESIRED_POSITION-TOLERANCE)
        {
            bDoneMovingCalibrate = FALSE;
            if(manualDesiredPostion!=0)
            {
                setMotorOutputs(BACKWARDS,0xFF);
            }
            else
            {
                setMotorOutputs(BACKWARDS,-1*pMotor->MotorOutput);
            }
        }
        
        pMotor->previousErrorPot = pMotor->errorPot;
    }
    }
    else
    {
        setMotorOutputs(BRAKE,0xFF);
        //CyDelay(50);
        //setMotorOutputs(OFF_NOTHING,0x00);
    }
    
    return pMotor;
}

void setMotorPosition(uint8 localMotorPosition)
{
    rxPacketLocal->Payload.endMotorPosition = localMotorPosition;
}

uint16 checkMotorCurrent(void)
{
    uint16 motorCurrentValue = 0;
    motorCurrentValue = ADC_SAR_Seq_GetResult16(HBridge_CS);
    return motorCurrentValue;
}