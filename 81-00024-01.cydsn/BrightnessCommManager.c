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

#define MAX_PAYLOAD_BYTE_COUNT  MAX_DRIVER_COUNT + 1
#define HEADER_BYTE_COUNT       2
#define EOP_BYTE_COUNT          2
#define MAX_PACKET_SIZE         HEADER_BYTE_COUNT + MAX_PAYLOAD_BYTE_COUNT + EOP_BYTE_COUNT

#define PACKET_TYPE_COUNT       6
#define HEADER_START_INDEX      0
#define PAYLOAD_START_INDEX     HEADER_BYTE_COUNT

#define TIMEOUT_LIMIT_IN_MILLISECONDS   10000
#define HEAD_BOARD_TIMEOUT   150
    
/**********DEFINED CONSTANTS**********/
enum PacketState
{
    HEADER_STATE,
    PAYLOAD_STATE,
    EOP_STATE
};

/**********DATA STRUCTURES**********/
typedef struct
{
    const uint8 HEADER_BYTE;
    const uint8 PACKET_TYPE;
    const uint8 PAYLOAD_SIZE;
    const uint8 EOP_CARRIAGE_RETURN;
    const uint8 EOP_LINE_FEED;
}Packet;

static Packet PacketList[PACKET_TYPE_COUNT] = 
{
    {'~', 'B', 8, '\r', '\n'},          //Definition: Brightness, Value Range: 0x00-0xFF, Module 0(Head)-7(Kaboose)
    {'~', 'C', 9, '\r', '\n'},          //Definition: Driver Count, Payload:
                                        //Byte 0: Number of Drivers, Value Range: 1-8
                                        //Byte1-Byte8: Driver ID, Value Range: 1-8
    {'~', 'M', 11, '\r', '\n'},
    {'~', 'S', 3, '\r', '\n'},           //Save brightness and motor position to EEPROM
    {'~', 'L', 1, '\r', '\n'},
    {'~', 'A', 1, '\r', '\n'} 
};    

/**********GLOBAL VARIABLES**********/
static uint8 bDriverCountReceived = FALSE;

volatile uint8 bCommunicationTimeOut = FALSE;
static uint8 stateOfLightBar = 0;
volatile uint16 timeOutCounter = 0;
volatile uint8 bIsCommunicationTrigger = FALSE;
/**********LOCAL FUNCTION PROTOTYPES**********/
static uint8 processLowPowerRequest(uint8* packet, uint8 length);
static void detectPacket(uint8 dataByte);
static uint8 processDriverCountPacket(uint8* packet, uint8 length);
static uint8 processBrightnessPacket(uint8* packet, uint8 length, uint8 bFlashPattern);
static uint8 processReinitlizationPacket(uint8* packet, uint8 length);
static void saveStateBar(uint8 * volatileMemoryArray, const uint8 * nonVolatileMemoryArray, uint8* packet);
static void putBarToSleep(void);
static void returnFromSleep(void);
static void processOutputSelectUart(void);
/**********DEFINED GLOBAL FUNCTIONS**********/
static uint16 regulatedBrightness = 0;
//static uint16 rampDownIterator = 0;
static uint16 bFirstTimeRampDown = 0;
static int16 previousBrightnessLocal = 0;
static uint8 ifPowerUp = FALSE;

RxPacket rxPacket;


RxPacket *pRxPacket;
////////////////////////////////////Time-Out and Low Power Functions///////////////////////////////////////////////////////

uint8 getStateOfBar(void)
{
    return stateOfLightBar;
}

uint8 getDegaultPosition(void)
{
    static const uint8 * localNonVolatileMemory = 0;
    localNonVolatileMemory = getNonVolatileBarStateMemory();
    
    return localNonVolatileMemory[1];
}

void timeOutStateMachine(const uint8 * nonVolatileMemoryArray)
{           
    switch(stateOfLightBar)
    {
        case IS_TIME_OUT_TRUE:
            if(bCommunicationTimeOut == TRUE)
            {
                //LED_Output_Write(TRUE); 
                CyDelay(10);
               if(getDriverID() == HEAD_MODULE_ID)
               {
                    if(getDriverID() == HEAD_MODULE_ID)
                    {
                        stateOfLightBar = HIGH_TIMOUT;
                        //WakeupISR_Start();
                    }
               }
              // else
              // {
              //      previousBrightnessLocal = getPreviousBrightness();
              //      stateOfLightBar = LOW_TIMEOUT;
              //      //WakeupISR_Start();
              // }
            }
            break;
        case HIGH_TIMOUT:
            if(bCommunicationTimeOut == FALSE) //&& UART_Rx_Read() == 1) bIsCommunicationTrigger == TRUE &&
            {
                bIsCommunicationTrigger = FALSE;
                stateOfLightBar = IS_TIME_OUT_TRUE;
                //WakeupISR_Stop();
            }
            takeInputValues();
            if(isReadyToSendNextBrightnessPacket() == TRUE)
            {
                //timeoutDefaultBrightness(getNonVolatileBarStateMemory());
                clearIsReadyToSendNextBrightnessPacket();
            }
            break;
        case LOW_TIMEOUT:
            if(isReadyToSendNextBrightnessPacket() == TRUE)
            {
                putBarToSleep();
                CySysPmDeepSleep(); 

                if(bIsCommunicationTrigger == TRUE)
                {
                    bIsCommunicationTrigger = FALSE;
                    stateOfLightBar = IS_TIME_OUT_TRUE;
                    //WakeupISR_Stop();
                    bFirstTimeRampDown = FALSE;
                    CySoftwareReset(); 
                }
                    clearIsReadyToSendNextBrightnessPacket();
            }
            break;
        case 3:
            break;
        default:
            break;
    }   
}

/*******************************************************************************
* Function Name: wakeupModule
********************************************************************************
*
* Summary:
*  Called in WakeupISR, sets the flag to indicate that an edge found on UART_Rx.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void isThereHighLowTransitionFromUART(void)
{
    //WakeupISR_ClearPending();
    //UART_Rx_ClearInterrupt();
    
    bIsCommunicationTrigger = TRUE;
}

/*******************************************************************************
* Function Name: processTimeoutTimerRoutine
********************************************************************************
*
* Summary:
*  Called in CommTimeoutISR(), counts up while waiting for the next brightness
*  packet. If the timer limit is reached, then the LED is shut off and timeout
*  flag is set to put the module to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void processTimeoutTimerRoutine(void)
{
    CommTimeoutISR_ClearPending();
    TimeoutTimer_ClearInterrupt(TimeoutTimer_INTR_MASK_TC);

    if(getDriverID() == HEAD_MODULE_ID)
    {
            if(timeOutCounter<HEAD_BOARD_TIMEOUT)
            {
                timeOutCounter++;
            }
            else
            {
                TimeoutTimer_Stop();
                timeOutCounter = 0;
                bCommunicationTimeOut = TRUE;
            }
    }
    else
    {
         if(timeOutCounter<TIMEOUT_LIMIT_IN_MILLISECONDS)
        {
            timeOutCounter++;
        }
        else
        {
            TimeoutTimer_Stop();
            timeOutCounter = 0;
            bCommunicationTimeOut = TRUE;
        }
    }

}

/*******************************************************************************
* Function Name: processBrightnessByteReceivedHandler
********************************************************************************
*
* Summary:
*  Called in UART_Out_ISR(), triggers when a byte is received from the controller.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void processBrightnessByteReceivedHandler(void)
{
    
    uint8 dataByte = 0;
    uint32 interruptSource = 0;
    //do
    //{
    //    dataByte = UART_LED_GetChar();
    //    detectPacket(dataByte);
        
    //}while(UART_LED_ReadRxStatus() & UART_LED_RX_STS_FIFO_NOTEMPTY);
    do
    {
        dataByte = (uint8)(UART_LED_UartGetByte() & 0xFF);
        detectPacket(dataByte);
    }while(UART_LED_SpiUartGetRxBufferSize() > 0);
    
    interruptSource = UART_LED_GetRxInterruptSourceMasked();
    UART_LED_ClearRxInterruptSource(interruptSource);
}

void timeoutDefaultBrightness(const uint8 * nonVolatileMemoryArray)
{
    uint8 currentRegulatedBrightness = 0;
    uint8 driver_ID = 0; 
    static uint16 loopIterator = 0;
    
    driver_ID = getDriverID();
    if(driver_ID == HEAD_MODULE_ID)
    {
        if(ifPowerUp == FALSE)
        {
            ifPowerUp = TRUE;
            CyDelay(250);
            //for(loopIterator = 0; loopIterator<nonVolatileMemoryArray[0]; loopIterator+=32)
            //{
            //    currentRegulatedBrightness = updateBrightnessLevel(loopIterator, TRUE);
            //    UART_LED_PutChar('~');
            //    UART_LED_PutChar('B');
            //    UART_LED_PutChar(currentRegulatedBrightness);
            //    UART_LED_PutChar(currentRegulatedBrightness);
            //    UART_LED_PutChar(currentRegulatedBrightness);
            //    UART_LED_PutChar(currentRegulatedBrightness);
            //    UART_LED_PutChar(currentRegulatedBrightness);
            //    UART_LED_PutChar(currentRegulatedBrightness);
            //    UART_LED_PutChar(currentRegulatedBrightness);
            //    UART_LED_PutChar(currentRegulatedBrightness);
            //    UART_LED_PutChar(0x0D);
            //    UART_LED_PutChar(0x0A);
            //    CyDelayUs(3000);
            //}
        }
        currentRegulatedBrightness = updateBrightnessLevel(nonVolatileMemoryArray[0], TRUE);
        //currentRegulatedBrightness = updateBrightnessLevel(0, TRUE);
       // UART_LED_PutChar('~');
       // UART_LED_PutChar('B');
       // UART_LED_PutChar(currentRegulatedBrightness);
       // UART_LED_PutChar(currentRegulatedBrightness);
       // UART_LED_PutChar(currentRegulatedBrightness);
       // UART_LED_PutChar(currentRegulatedBrightness);
       // UART_LED_PutChar(currentRegulatedBrightness);
       // UART_LED_PutChar(currentRegulatedBrightness);
       // UART_LED_PutChar(currentRegulatedBrightness);
       // UART_LED_PutChar(currentRegulatedBrightness);
       // UART_LED_PutChar(0x0D);
       // UART_LED_PutChar(0x0A);        
    }
}

////////////////////////////////////Driver Count Initialization Functions//////////////////////////////////////////////////
uint8 isDriverCountReceived(void)
{
    return bDriverCountReceived;
}

void setDriverCountReceived(void)
{
    bDriverCountReceived = TRUE;
}

/*******************************************************************************
* Function Name: assignDriverIDs
********************************************************************************
*
* Summary:
*  Sends out the driver count packet. Only the head module executes this.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void assignDriverIDs(void)
{
    uint8 driverCountPacket[MAX_PACKET_SIZE];
    
    if(getDriverID() != HEAD_MODULE_ID)
        return;
    
    memset(driverCountPacket, 0, MAX_PACKET_SIZE);
    driverCountPacket[HEADER_START_INDEX] = PacketList[1].HEADER_BYTE;
    driverCountPacket[HEADER_START_INDEX + 1] = PacketList[1].PACKET_TYPE;
    driverCountPacket[PAYLOAD_START_INDEX + PacketList[1].PAYLOAD_SIZE]
        = PacketList[1].EOP_CARRIAGE_RETURN;
    driverCountPacket[PAYLOAD_START_INDEX + PacketList[1].PAYLOAD_SIZE + 1]
        = PacketList[1].EOP_LINE_FEED;
    driverCountPacket[PAYLOAD_START_INDEX] = 1;
    driverCountPacket[PAYLOAD_START_INDEX + 1] = HEAD_MODULE_ID;
    
    //UART_LED_PutArray(driverCountPacket, MAX_PACKET_SIZE);
}

/**********DEFINED LOCAL FUNCTIONS**********/

////////////////////////////////////Recieve from controller or previous module functions//////////////////////////////////////

/*******************************************************************************
* Function Name: detectPacket
********************************************************************************
*
* Summary:
*  Determines if the incoming byte belongs to a valid packet. If the packet is
*  valid, then the payload is processed.
*
* Parameters:
*  dataByte: The next byte to check in the packet
*
* Return:
*  None.
*
*******************************************************************************/
static void detectPacket(uint8 dataByte)
{
    static uint8 packet[MAX_PACKET_SIZE];   
    static enum PacketState currentState = HEADER_STATE;
    static uint8 currentPacketIndex = HEADER_START_INDEX;
    static uint8 dataTypeIndex = 0;
    uint8 loopIndex = 0;
    
    switch(currentState)
    {
        case HEADER_STATE:
            if((currentPacketIndex == HEADER_START_INDEX) &&
                (dataByte == PacketList[dataTypeIndex].HEADER_BYTE))
            {
                packet[currentPacketIndex] = dataByte;
                currentPacketIndex++;
            }
            else if(currentPacketIndex == (HEADER_START_INDEX + 1))
            {
                for(loopIndex = 0; loopIndex < PACKET_TYPE_COUNT; loopIndex++)
                {
                    if(dataByte == PacketList[loopIndex].PACKET_TYPE)
                    {
                        dataTypeIndex = loopIndex;                        
                        packet[currentPacketIndex] = dataByte;
                        currentPacketIndex++;
                        currentState = PAYLOAD_STATE;
                        break;
                    }
                }
                
                if(loopIndex >= PACKET_TYPE_COUNT)
                {
                    currentPacketIndex = HEADER_START_INDEX;
                    dataTypeIndex = 0;
                }
            }
            else
            {
                currentPacketIndex = HEADER_START_INDEX;
                dataTypeIndex = 0;
            }
            break;
        case PAYLOAD_STATE:
            packet[currentPacketIndex] = dataByte;
            currentPacketIndex++;
            
            if(currentPacketIndex >= (PAYLOAD_START_INDEX + PacketList[dataTypeIndex].PAYLOAD_SIZE))
                currentState = EOP_STATE;
            break;
        case EOP_STATE:
            if((currentPacketIndex == (PAYLOAD_START_INDEX + PacketList[dataTypeIndex].PAYLOAD_SIZE)) &&
                (dataByte == PacketList[dataTypeIndex].EOP_CARRIAGE_RETURN))
            {
                packet[currentPacketIndex] = dataByte;
                currentPacketIndex++;
            }
            else if((currentPacketIndex == (PAYLOAD_START_INDEX + PacketList[dataTypeIndex].PAYLOAD_SIZE + 1))
                    && (dataByte == PacketList[dataTypeIndex].EOP_LINE_FEED))
            {
                packet[currentPacketIndex] = dataByte;
                
                TimeoutTimer_Stop();
                timeOutCounter = 0;
                bCommunicationTimeOut = FALSE;
                TimeoutTimer_Start();
                
				if(dataTypeIndex == 0)
                {
                    processOutputSelectUart();
                    processBrightnessPacket(packet, MAX_PACKET_SIZE - 1, FALSE);
                }
				else if(dataTypeIndex == 1)
                {
                    processOutputSelectUart();
                    processDriverCountPacket(packet, MAX_PACKET_SIZE);
                }
                else if (dataTypeIndex == 2)
                {
                    memcpy(rxPacket.bytes, packet, 13);
                }
                else if(dataTypeIndex == 3)
                {
                    processOutputSelectUart();
                    saveStateBar(getVolatileBarStateMemory(), getNonVolatileBarStateMemory(), packet);
                    //
                }
                else if(dataTypeIndex == 4)
                {                   
                    processLowPowerRequest(packet, MAX_PACKET_SIZE-8);
                }
                else if(dataTypeIndex == 5)
                {
                    processOutputSelectUart();
                    processReinitlizationPacket(packet, MAX_PACKET_SIZE-6);
                    processCalibrationPacket();
                }
                else
                {
                    processOutputSelectUart();
                    processBrightnessPacket(packet, MAX_PACKET_SIZE - 1, TRUE);
                }
                
                currentPacketIndex = HEADER_START_INDEX;
                currentState = HEADER_STATE;
                dataTypeIndex = 0;
            }
            else
            {
                currentPacketIndex = HEADER_START_INDEX;
                currentState = HEADER_STATE;
                dataTypeIndex = 0;
            }
            break;
    }
}

/*******************************************************************************
* Function Name: processDriverCountPacket
********************************************************************************
*
* Summary:
*  Uses packet to send an ack to the previous module, set the ID for this driver, 
*  send the packet to the next module, and start the timer to wait for an ack from
*  the next module.
*
* Parameters:
*  packet: The reference to the driver count packet to process.
*  length: The byte count for this packet.
*
* Return:
*  SUCCESS for valid inputs, FAILURE otherwise
*
*******************************************************************************/
static uint8 processLowPowerRequest(uint8* packet, uint8 length)
{
    static uint8 driver_ID = 0;
    //uint8 currentDriverCount = 0;
    
    if(packet == NULL || length != MAX_PACKET_SIZE-8)
        return FAILURE;
    
    driver_ID = getDriverID();

    if(driver_ID == HEAD_MODULE_ID)
    {
        //UART_LED_PutChar('~');
        //UART_LED_PutChar('L');
        //UART_LED_PutChar(01);
        //UART_LED_PutChar(0x0D);
        //UART_LED_PutChar(0x0A);
        //UART_LED_Control_Write(2);
    }    
    
    return TRUE;
}

/*******************************************************************************
* Function Name: processDriverCountPacket
********************************************************************************
*
* Summary:
*  Uses packet to send an ack to the previous module, set the ID for this driver, 
*  send the packet to the next module, and start the timer to wait for an ack from
*  the next module.
*
* Parameters:
*  packet: The reference to the driver count packet to process.
*  length: The byte count for this packet.
*
* Return:
*  SUCCESS for valid inputs, FAILURE otherwise
*
*******************************************************************************/
static uint8 processDriverCountPacket(uint8* packet, uint8 length)
{
    static uint8 bReceivedCountPacket = FALSE;
    uint8 currentDriverCount = 0;
    uint8 ackPacket[MAX_PACKET_SIZE];
    uint8 countIndex = 0;
    
    if(packet == NULL || length != MAX_PACKET_SIZE)
        return FAILURE;
    
    if(bReceivedCountPacket)
        return SUCCESS;
    
    bReceivedCountPacket = TRUE;
    memcpy(ackPacket, packet, length);
    ackPacket[HEADER_START_INDEX + 1] = 'A';
    
    for(countIndex = 0; countIndex < 5; countIndex++)
    {
        //UART_Temperature_SpiUartPutArray(ackPacket, length);
    }
        
    
    currentDriverCount = packet[PAYLOAD_START_INDEX] + 1;
    setIdentityByComm(currentDriverCount);
    bDriverCountReceived = TRUE;
    packet[currentDriverCount + PAYLOAD_START_INDEX] = currentDriverCount;
    packet[PAYLOAD_START_INDEX] = currentDriverCount;
    setLastDriverPacket(packet, length);
    //UART_LED_PutArray(packet, length);
    AckTimer_Start();
    
    return SUCCESS;
}

/*******************************************************************************
* Function Name: processDriverCountPacket
********************************************************************************
*
* Summary:
*  Uses packet to send an ack to the previous module, set the ID for this driver, 
*  send the packet to the next module, and start the timer to wait for an ack from
*  the next module.
*
* Parameters:
*  packet: The reference to the driver count packet to process.
*  length: The byte count for this packet.
*
* Return:
*  SUCCESS for valid inputs, FAILURE otherwise
*
*******************************************************************************/
static uint8 processReinitlizationPacket(uint8* packet, uint8 length)
{
    
    //if(length != MAX_PACKET_SIZE-6)
    //    return FAILURE;
    
    clearInitializeAlreadyEEPROM();
    //UART_LED_PutArray(packet, length);
    return SUCCESS;
}

/*******************************************************************************
* Function Name: processBrightnessPacket
********************************************************************************
*
* Summary:
*  Uses the packet to determine the next brightness level for all modules, send the
*  packet to the next module, and start the temperature sampling timer if this module
*  is the last module in the chain.
*
* Parameters:
*  packet: The reference to the brightness packet to process.
*  length: The byte count for this packet.
*
* Return:
*  SUCCESS for valid inputs, FAILURE otherwise
*
*******************************************************************************/
static uint8 processBrightnessPacket(uint8* packet, uint8 length, uint8 bFlashPattern)
{
    static uint8 bFirstBrightnessPacket = TRUE;
    uint8 currentBrightness = 0;
    uint8 driver_ID = 0;
    
    if(packet == NULL || length != (MAX_PACKET_SIZE - 1))
        return FAILURE;
    
    if(bFlashPattern != TRUE && bFlashPattern != FALSE)
        return FAILURE;
    
    driver_ID = getDriverID();
    if((driver_ID < HEAD_MODULE_ID) || (driver_ID > MAX_DRIVER_COUNT))
        return FAILURE;
    
    //TimeoutTimer_Stop();
    
    if(bFirstBrightnessPacket)
    {
        bFirstBrightnessPacket = FALSE;           
        //SamplingTimer_Start();
    }
    
    if(isReadyToSendNextBrightnessPacket() == TRUE)
    {
        if(driver_ID == 1)
        {
            if(bFlashPattern)
                updateBrightnessLevel(packet[driver_ID + PAYLOAD_START_INDEX - 1], FALSE);
            else
            {
                currentBrightness =
                    updateBrightnessLevel(packet[driver_ID + PAYLOAD_START_INDEX - 1], TRUE);
                memset(&packet[PAYLOAD_START_INDEX], currentBrightness, MAX_DRIVER_COUNT);
            }
            //UART_LED_PutArray(packet, length);
        }
        else
        {
            updateBrightnessLevel(packet[driver_ID + PAYLOAD_START_INDEX - 1], FALSE);
        }
    }
    //TimeoutTimer_Start();
    
    return SUCCESS;
}

static void saveStateBar(uint8 * volatileMemoryArray, const uint8 * nonVolatileMemoryArray, uint8* packet)
{
    static uint8 driver_ID = 0;
    
    driver_ID = getDriverID();
    if(driver_ID == HEAD_BOARD)
    {        
        //UART_LED_PutArray(packet, 7);
    }
    volatileMemoryArray[0] = packet[driver_ID + PAYLOAD_START_INDEX - 1];
    EmEEPROM_Write(volatileMemoryArray,nonVolatileMemoryArray,1);
    
    volatileMemoryArray[1] = packet[3];
    EmEEPROM_Write(&volatileMemoryArray[1],&nonVolatileMemoryArray[1],1);
}

static void putBarToSleep(void)
{
    PWM_Stop();
    PWM_WriteCompare(0);

    CommTimeoutISR_Stop();
    AckTimeoutISR_Stop();
    
    SamplingTimerISR_Stop();
    ADC_SAR_Seq_Stop();
    ADC_SAR_Seq_StopConvert();
    
    UART_LED_ISR_Stop();
    UART_LED_Stop();
    
    //UART_LED_ISR_Stop();
    
    //UART_LED_Stop();
    //WakeupISR_Start();
    
    LED_ISR_Stop(); 
    
    SamplingTimer_Stop();
    TimeoutTimer_Stop();
}

static void returnFromSleep(void)
{
    static const uint8 * nonVolatileMemoryArray;
    
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
    CyDelay(250);
    //LED_Output_Write(FALSE);
    UART_LED_Control_Write(FALSE);
    
    nonVolatileMemoryArray = getNonVolatileBarStateMemory();
    setIdentityByComm(nonVolatileMemoryArray[2]);
    if(getDriverID()==HEAD_MODULE_ID)
    {
        UART_LED_Control_Write(TRUE);
    }
    else
    {
        UART_LED_Control_Write(FALSE);
    }
}

static void processOutputSelectUart(void)
{
    if(getDriverID() == HEAD_MODULE_ID)
    {
        //UART_LED_Control_Write(1);
    }
    else
    {
        //UART_LED_Control_Write(0);
    }
}

void processCalibrationPacket(void)
{
    static const uint8 * localNonVolatileMemory = 0;
    localNonVolatileMemory = getNonVolatileBarStateMemory();
    
    EmEEPROM_Write(0,&localNonVolatileMemory[3],1);
}

 RxPacket * getRxPacket(void)
{
    pRxPacket = &rxPacket;
    
    return pRxPacket;
}
/* [] END OF FILE */
