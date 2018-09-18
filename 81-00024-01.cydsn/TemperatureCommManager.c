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
#include "TemperatureCommManager.h"
#include "DriverControl.h"

#define MAX_PAYLOAD_BYTE_COUNT  MAX_DRIVER_COUNT * 2 + 2
#define HEADER_BYTE_COUNT       2
#define EOP_BYTE_COUNT          2
#define MAX_PACKET_SIZE         HEADER_BYTE_COUNT + MAX_PAYLOAD_BYTE_COUNT + EOP_BYTE_COUNT

#define PACKET_TYPE_COUNT       6
#define HEADER_START_INDEX      0
#define PAYLOAD_START_INDEX     HEADER_BYTE_COUNT

#define TIMEOUT_LIMIT_IN_MILLISECONDS   30
    
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
    {'~', 'C', 9, '\r', '\n'},          //Definition: Driver Count
                                        //Payload:
                                        //Byte 0: Number of Drivers, Value Range:1-8
                                        //Byte1-Byte8:Driver ID, Value Range:1-8
    {'~', 'A', 9, '\r', '\n'},          //Definition: Acknowledgement Packet
                                        //Payload:
                                        //Byte 0: Number of Drivers, Value Range:1-8
                                        //Byte1-Byte8:Driver ID, Value Range:1-8
    {'~', 'T', 18, '\r', '\n'},         //T for LED Temp, Modules 0(head)-7(Kaboose), Value Range: 0x00-0xFF
    {'~', 'U', 18, '\r', '\n'},         //U for Switch Node Temp, Modules 0(head)-7(Kaboose), Value Range: 0x00-0xFF
    {'~', 'W', 18, '\r', '\n'},         //W for Micro Temp, Modules 0(head)-7(Kaboose), Value Range: 0x00-0xFF
    {'~', 'V', 18, '\r', '\n'}          //V for Ambient Temp, Modules 0(head)-7(Kaboose), Value Range: 0x00-0xFF
};   

static uint8 lastDriverPacket[MAX_PACKET_SIZE - 9];
static uint8 temperaturePayload[ADC_SAMPLE_COUNT - 1][MAX_PAYLOAD_BYTE_COUNT];

/**********GLOBAL VARIABLES**********/
static uint16 timerCount = 0;

static uint8 bLastDriverInChain = FALSE;

uint8 bReadyToSendNextBrightnessTimeoutPacket = FALSE;
uint8 readyToSendThresholdCounter = 0;


uint8 sendTempPacketBack = 0;
/**********LOCAL FUNCTION PROTOTYPES**********/
static void detectPacket(uint8 dataByte);
static uint8 processTemperaturePacket(uint8* packet, uint8 length);
static uint8 processFinalDriverCountPacket(uint8* packet, uint8 length);
static uint8 processAckPacket(uint8* packet, uint8 length);
static int16 getHighestTemperature(uint8* packet, uint8 length);

/**********DEFINED GLOBAL FUNCTIONS**********/

uint8 isReadyToSendNextBrightnessPacket(void)
{
   return bReadyToSendNextBrightnessTimeoutPacket;
}

void clearIsReadyToSendNextBrightnessPacket(void)
{
    bReadyToSendNextBrightnessTimeoutPacket = FALSE;
}

/*******************************************************************************
* Function Name: isLastDriver
********************************************************************************
*
* Summary:
*  Returns if the current module is last driver in packet based on a ACK timeout.
*  An ACK timeout is when there is no ACK packet sent from the next module within 
*  the timeout perioud.
* Parameters:
*  None.
*
* Return:
*  TRUE if the module is the last in the chain.
*
*******************************************************************************/
uint8 isLastDriver(void)
{
    return bLastDriverInChain;
}


/*******************************************************************************
* Function Name: processTemperatureByteReceivedHandler
********************************************************************************
*
* Summary:
*  Called in UART_In_ISR(), triggers when a byte is received from the end driver.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void processTemperatureByteReceivedHandler(void)
{
    //uint8 dataByte = 0;
    //uint32 interruptSource = 0;
    
    //do
    //{
    //    dataByte = (uint8)(UART_Temperature_UartGetByte() & 0xFF);
    //    detectPacket(dataByte);
    //}while(UART_Temperature_SpiUartGetRxBufferSize() > 0);
    
    //interruptSource = UART_Temperature_GetRxInterruptSourceMasked();
    //UART_Temperature_ClearRxInterruptSource(interruptSource);
}



/*******************************************************************************
* Function Name: setLastDriverPacket
********************************************************************************
*
* Summary:
*  Passes the Count packet from BrightnessCommManager to TemperatureCommManager.
*  This should only be called in the last driver of the chain.
*
* Parameters:
*  dataPacket: The reference to the packet being passed
*  length: The length of the packet in bytes
*
* Return:
*  SUCCESS for valid parameters, FAILURE otherwise
*
*******************************************************************************/
uint8 setLastDriverPacket(uint8* dataPacket, uint8 length)
{
    if((dataPacket == NULL) || (length != (MAX_PACKET_SIZE - 9)))
        return FAILURE;
    
    memcpy(lastDriverPacket, dataPacket, length);
    
    return SUCCESS;
}

/*******************************************************************************
* Function Name: processAckTimeoutRoutine
********************************************************************************
*
* Summary:
*  Called in AckTimeoutISR(), counts up while waiting for an ACK from the next
*  driver in the chain. If the timer limit is reached, it is assumed that this
*  driver is the last driver of the chain.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void processAckTimeoutRoutine(void)
{
    AckTimer_ClearInterrupt(AckTimer_INTR_MASK_TC);
    
    if(timerCount < TIMEOUT_LIMIT_IN_MILLISECONDS)
    {
        
        //UART_LED_PutArray(lastDriverPacket, MAX_PACKET_SIZE - 9);
        timerCount++;
    }
    else
    {
        bLastDriverInChain = TRUE;
        //UART_LED_Control_Write(FALSE);
        AckTimer_Stop();
        timerCount = 0;
        setDriverCount(lastDriverPacket[PAYLOAD_START_INDEX]);
        //UART_Temperature_SpiUartPutArray(lastDriverPacket, MAX_PACKET_SIZE - 9);
        memset(lastDriverPacket, 0, MAX_PACKET_SIZE - 9);
    }
}

/*******************************************************************************
* Function Name: processSamplingTimerRoutine
********************************************************************************
*
* Summary:
*  Called in SamplingTimerISR(), samples temperatures at a periodic rate. This timer
*  should only run in the last driver of the chain, since the last board drives
*  the sampling rate throughout the chain.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void processSamplingTimerRoutine(void)
{
    static int16 ADC_Data[ADC_SAMPLE_COUNT] = {0, 0, 0, 0};
    static int16 HighestTemperatures[ADC_SAMPLE_COUNT - 1] = {0, 0, 0};
    static enum TemperaturePoint channelNumber = LED;
    static uint8 temporaryPacket[5] = {'~', 'B', 0, '\r', '\n'};
    
    uint8 packet[MAX_PACKET_SIZE];
    uint8 driverID = 0;
    uint16 temperatureSample = 0;
    
    SamplingTimer_ClearInterrupt(SamplingTimer_INTR_MASK_TC);   
    
    //readyToSendThresholdCounter++;
    
    //if(readyToSendThresholdCounter>=1)
    //{
    //    readyToSendThresholdCounter = 0;
    //    bReadyToSendNextBrightnessTimeoutPacket = TRUE;
    //}
    

    //Get next temperature sample to add to array
    getTemperatureSample(FALSE, 0, ADC_Data, ADC_SAMPLE_COUNT);
    temperatureSample = ADC_Data[channelNumber];    
    driverID = getDriverID();
    
    //Create packet for temperature data
    memset(packet, 0, MAX_PACKET_SIZE);
    packet[HEADER_START_INDEX] = PacketList[channelNumber + 2].HEADER_BYTE;
    packet[HEADER_START_INDEX + 1] = PacketList[channelNumber + 2].PACKET_TYPE;
    packet[PAYLOAD_START_INDEX + PacketList[channelNumber + 2].PAYLOAD_SIZE] 
        = PacketList[channelNumber + 2].EOP_CARRIAGE_RETURN;
    packet[PAYLOAD_START_INDEX + PacketList[channelNumber + 2].PAYLOAD_SIZE + 1]
        = PacketList[channelNumber + 2].EOP_LINE_FEED;
        
    memcpy(&packet[PAYLOAD_START_INDEX], temperaturePayload[channelNumber],
        MAX_PAYLOAD_BYTE_COUNT);
    packet[PAYLOAD_START_INDEX + driverID * 2] = (temperatureSample >> 8) & 0xFF;
    packet[PAYLOAD_START_INDEX + driverID * 2 + 1] = temperatureSample & 0xFF;
    
    if(driverID == HEAD_MODULE_ID)
    {   //Add max temperature to packet if this is the head module
        //checkForUnderVoltage(ADC_Data[VOLTAGE_SENSE]);
        temperatureSample = (uint16)(getMaxTemperature(channelNumber));
        packet[PAYLOAD_START_INDEX] = (temperatureSample >> 8) & 0xFF;
        packet[PAYLOAD_START_INDEX + 1] = temperatureSample & 0xFF;
    }
    
    //Send off temperature packet
    //packet[getDriverID()+2] = getDriverID();
    
    sendTempPacketBack++;
    if(sendTempPacketBack>2)
    {
        sendTempPacketBack = 0;
        //UART_Temperature_SpiUartPutArray(packet, MAX_PACKET_SIZE);
    }
    HighestTemperatures[channelNumber] =
        getHighestTemperature(&packet[PAYLOAD_START_INDEX + 2], MAX_PAYLOAD_BYTE_COUNT);
    
    if((driverID == HEAD_MODULE_ID) && (channelNumber == SWITCH_NODE))
    {   //Adjust brightness based on temp and send new brightness
        regulateBrightness(HighestTemperatures, ADC_SAMPLE_COUNT - 1);             
        temporaryPacket[PAYLOAD_START_INDEX] = getNewMaxBrightness();
        //UART_Temperature_SpiUartPutArray(temporaryPacket, 5);
    }
    
    //Enable injection before obtaining the micro temp in the next iteration
    if(channelNumber == (MICRO - 1))
        ADC_SAR_Seq_EnableInjection();
    
    channelNumber = (channelNumber + 1) % (ADC_SAMPLE_COUNT - 1);
    
}

/**********DEFINED LOCAL FUNCTIONS**********/
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
				
				if(dataTypeIndex == 0)
                    processFinalDriverCountPacket(packet, MAX_PACKET_SIZE - 9);                   
				else if(dataTypeIndex == 1)
                    processAckPacket(packet, MAX_PACKET_SIZE - 9);
                else
                    processTemperaturePacket(packet, MAX_PACKET_SIZE);
    	        
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
* Function Name: processTemperaturePacket
********************************************************************************
*
* Summary:
*  Obtains the temperature for this module, adds the temperature to this packet, and
*  sends the packet to the previous module.
*
* Parameters:
*  packet: The reference to the temperature packet to process.
*  length: The byte count for this packet.
*
* Return:
*  SUCCESS for valid inputs, FAILURE otherwise
*
*******************************************************************************/
static uint8 processTemperaturePacket(uint8* packet, uint8 length)
{
    uint8 driverID = 0;
    uint8 channelNumber;
    
    if(packet == NULL || length != MAX_PACKET_SIZE)
        return FAILURE;
    
    driverID = getDriverID();
    if((driverID < HEAD_MODULE_ID) || (driverID > MAX_DRIVER_COUNT))
        return FAILURE;
    
    for(channelNumber = 0; channelNumber < ADC_SAMPLE_COUNT; channelNumber++)
    {   //Determining ADC channel number based on packet type
        if(packet[HEADER_START_INDEX + 1] == PacketList[channelNumber + 2].PACKET_TYPE)
            break;
    }
    
    memcpy(temperaturePayload[channelNumber],
        &packet[PAYLOAD_START_INDEX], MAX_PAYLOAD_BYTE_COUNT);
    
    return SUCCESS; //Return here if this is a head module
}

/*******************************************************************************
* Function Name: processFinalDriverCountPacket
********************************************************************************
*
* Summary:
*  Sends the complete driver count packet to the previous module without modification.
*
* Parameters:
*  packet: The reference to the complete driver count packet.
*  length: The byte count for this packet.
*
* Return:
*  SUCCESS for valid inputs, FAILURE otherwise
*
*******************************************************************************/
static uint8 processFinalDriverCountPacket(uint8* packet, uint8 length)
{
    if(packet == NULL || (length != MAX_PACKET_SIZE - 9))
        return FAILURE;
    
    setDriverCount(packet[PAYLOAD_START_INDEX]);
    //UART_Temperature_SpiUartPutArray(packet, MAX_PACKET_SIZE - 9);
    
    
    if(getDriverID() == HEAD_MODULE_ID)
    {
        //UART_LED_Control_Write(TRUE); 
    }
    else
    {
        //UART_LED_Control_Write(FALSE);
    }
    return SUCCESS;
}

/*******************************************************************************
* Function Name: processAckPacket
********************************************************************************
*
* Summary:
*  Receiving the ack packet indicates that there is a module appended to this one.
*
* Parameters:
*  packet: The reference to the ack packet.
*  length: The byte count for this packet.
*
* Return:
*  SUCCESS for valid inputs, FAILURE otherwise
*
*******************************************************************************/
static uint8 processAckPacket(uint8* packet, uint8 length)
{
    if(packet == NULL || length != (MAX_PACKET_SIZE - 9))
        return FAILURE;
    
    AckTimer_Stop();
    timerCount = 0;
    setAsNotLastDriverInChain();
    return SUCCESS;
}

/*******************************************************************************
* Function Name: getHighestTemperature
********************************************************************************
*
* Summary:
*  Returns the highest temperature detected out of all modules.
*
* Parameters:
*  packet: The reference to the temperature packet to process.
*  length: The byte count for this packet.
*
* Return:
*  The highest temperature detected out of all modules, 0 if there is an input error
*
*******************************************************************************/
static int16 getHighestTemperature(uint8* packet, uint8 length)
{
    int16 highestTemperature = 0;
    int16 temperatureToCheck = 0;
    uint8 moduleIndex = 0;
    
    if(packet == NULL || length != MAX_PAYLOAD_BYTE_COUNT)
        return 0;
    
    for(moduleIndex = 0; moduleIndex < MAX_DRIVER_COUNT; moduleIndex++)
    {
        temperatureToCheck = 0;
        temperatureToCheck = (int16)(packet[moduleIndex * 2] << 8);
        temperatureToCheck |= (int16)(packet[moduleIndex * 2 + 1]);
        
        if(temperatureToCheck > highestTemperature)
            highestTemperature = temperatureToCheck;
    }
    
    return highestTemperature;
}

/* [] END OF FILE */
