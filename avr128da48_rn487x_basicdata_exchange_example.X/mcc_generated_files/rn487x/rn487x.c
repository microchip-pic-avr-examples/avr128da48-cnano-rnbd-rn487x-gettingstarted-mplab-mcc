/**
 * RN487X Generated Driver Source File
 * 
 * @file rn487x.c
 * 
 * @ingroup rn487x
 * 
 * @brief This is the generated driver source file for RN487X driver using RN4870/1.
 *
 * @version RN487X Driver Version  2.0.0
*/
/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rn487x.h"
#include "rn487x_interface.h"

/* This value depends upon the System Clock Frequency, Baudrate value and Error percentage of Baudrate*/
#define RESPONSE_TIMEOUT 65 

/**
 * @def STATUS_MESSAGE_DELIMITER
 * This Variable provide a definition of the RN487X devices PRE/POST status message delimiter.
 */
char RN487X_STATUS_MESSAGE_DELIMITER = '%';

bool skip_Delimter = false;

uint8_t RN487X_cmdBuf[64];                                 /**< Command TX Buffer */

const char * const RN487X_driver_version = "2.0.0"; /**<  Current RN487X Driver Version */

static char *RN487X_asyncBuffer;                           /**< Async Message Buffer */
static uint8_t RN487X_asyncBufferSize;                     /**< Size of the Async Message Buffer */
static char *RN487X_pHead;                                 /**< Pointer to the Head of the Async Message Buffer */
static uint8_t RN487X_peek = 0;                            /**< Recieved Non-Status Message Data */
static bool RN487X_dataReady = false;                      /**< Flag which indicates whether Non-Status Message Data is ready */

uint8_t resp[100];

/**
 * @ingroup rn487x
 * @brief This function filters status messages from RN487X data.
 * @param void This function takes no params.
 * @retval true - data is ready
 * @retval false -data is not ready
 */
static bool RN487X_DataFilter(void);

bool RN487X_Init(void)
{
    //Enter reset
    RN487X.ResetModule(true);
    //Wait for Reset
    RN487X.DelayMs(RN487X_RESET_DELAY_TIME);
    //Exit reset
    RN487X.ResetModule(false);

    //Wait while RN487X is booting up
    RN487X.DelayMs(RN487X_STARTUP_DELAY);

    //Remove unread data sent by RN487x, if any
    while (RN487X.DataReady())
    {
        RN487X.Read();
    }

    return true;
}

void RN487X_SendCmd(const uint8_t *cmd, uint8_t cmdLen)
{
    uint8_t index = 0;
	
	do{
        if (RN487X.TransmitReady())
        {
            RN487X.Write(cmd[index]);
            index++; 
        }
    }
    while(index < cmdLen);
       
    while(!RN487X.TransmitReady());
}

uint8_t RN487X_GetCmd(const uint8_t *getCmd, uint8_t getCmdLen)
{
    uint8_t index = 0, ResponseTime=0;

    RN487X_SendCmd(getCmd, getCmdLen);
	
	//Wait for the response time
    while(!RN487X.DataReady() && ResponseTime<=RESPONSE_TIMEOUT)
    {
        RN487X.DelayMs(1);
        ResponseTime++;
    }

    do
    {
        //Read Ready data 
        if(RN487X.DataReady())
        {
            resp[index++]=RN487X.Read();
        }
    }
    while (resp[index - 1U] != '>');

    return index;
}

bool RN487X_ReadMsg(const uint8_t *expectedMsg, uint8_t msgLen)
{
    unsigned int ResponseRead=0,ResponseTime=0,ResponseCheck=0;
	
	//Wait for the response time
    while(!RN487X.DataReady() || ResponseTime<=RESPONSE_TIMEOUT)
    {
        RN487X.DelayMs(1);
        ResponseTime++;
    }
	
	//Read Ready data 
    while(RN487X.DataReady())
    {
        resp[ResponseRead]=RN487X.Read();
        ResponseRead++;
    }
	
	//Comparing length of response expected
    if (ResponseRead != msgLen)
    {
        return false;
    }
	
	//Comparing the Response with expected result
    for(ResponseCheck=0;ResponseCheck<ResponseRead;ResponseCheck++)
    {
        if (resp[ResponseCheck] != expectedMsg[ResponseCheck])
        {
            return false;
        }
    }

    return true;
}


bool RN487X_ReadDefaultResponse(void)
{
    uint8_t DefaultResponse[30];
    bool status = false;

    unsigned int ResponseWait=0,DataReadcount=0;
    while(!RN487X.DataReady() || ResponseWait<=RESPONSE_TIMEOUT)
    {
        RN487X.DelayMs(1);
        ResponseWait++;
    }
    
    while(RN487X.DataReady())
    {
        DefaultResponse[DataReadcount]=RN487X.Read();
        DataReadcount++;
    }

    switch (DefaultResponse[0])
    {
        case 'A':
        {
            if ((DefaultResponse[1] == 'O') && (DefaultResponse[2] == 'K'))
                status = true;

            break;
        }
        case 'E':
        {
            if ((DefaultResponse[1] == 'r') && (DefaultResponse[2] == 'r'))
                status = false;

            break;
        }
        default:
        {
            return status;
        }
    }
  
    return status;
}

bool RN487X_SendCommand_ReceiveResponse(const uint8_t *cmdMsg, uint8_t cmdLen, const uint8_t *responsemsg, uint8_t responseLen)
{
    int ResponseRead=0,ResponseTime=0,ResponseCheck=0;
    
    //Flush out any read data
    while (RN487X.DataReady())
    {
        RN487X.Read();
    }
    
    //Sending Command to UART
    RN487X_SendCmd(cmdMsg, cmdLen);
    
    //Waiting for the response time
    while(!RN487X.DataReady() || ResponseTime<=RESPONSE_TIMEOUT)
    {
        RN487X.DelayMs(1);
        ResponseTime++;
    }
    
    //Read Ready data 
    while(RN487X.DataReady())
    {
        resp[ResponseRead]=RN487X.Read();
        ResponseRead++;
    }
	
	//Comparing length of response expected
	if (ResponseRead != responseLen)
    {
        return false;
    }
    
    //Comparing the Response with expected result
    for(ResponseCheck=0;ResponseCheck<ResponseRead;ResponseCheck++)
    {
        if (resp[ResponseCheck] != responsemsg[ResponseCheck])
        {
            return false;
        }
    }
	
    return true;
}


bool RN487X_EnterCmdMode(void)
{
    const uint8_t cmdModeResponse[] = {'C', 'M', 'D', '>', ' '};
	
	RN487X_cmdBuf[0] = '$';
    RN487X_cmdBuf[1] = '$';
    RN487X_cmdBuf[2] = '$';
        
    return RN487X_SendCommand_ReceiveResponse(RN487X_cmdBuf, 3U, cmdModeResponse, 5U);
}

bool RN487X_EnterDataMode(void)
{
    const uint8_t dataModeResponse[] = {'E', 'N', 'D', '\r', '\n'};
	
	RN487X_cmdBuf[0] = '-';
    RN487X_cmdBuf[1] = '-';
    RN487X_cmdBuf[2] = '-';
    RN487X_cmdBuf[3] = '\r';
    RN487X_cmdBuf[4] = '\n';

    return RN487X_SendCommand_ReceiveResponse(RN487X_cmdBuf, 5, dataModeResponse, 5U);
}

bool RN487X_SetName(const uint8_t *name, uint8_t nameLen)
{
    uint8_t index;
	const uint8_t cmdPrompt[] = {'A', 'O', 'K', '\r', '\n', 'C', 'M', 'D', '>', ' '};

    RN487X_cmdBuf[0] = 'S';
    RN487X_cmdBuf[1] = 'N';
    RN487X_cmdBuf[2] = ',';
	

    for (index = 0; index < nameLen; index++)
    {
        RN487X_cmdBuf[3 + index] = name[index];
    }
    index = index + 3;

    RN487X_cmdBuf[index++] = '\r';
    RN487X_cmdBuf[index++] = '\n';

    return RN487X_SendCommand_ReceiveResponse(RN487X_cmdBuf, nameLen + 5U, cmdPrompt, 10);
}

bool RN487X_SetBaudRate(uint8_t baudRate)
{
    uint8_t temp = (baudRate >> 4);
	const uint8_t cmdPrompt[] = {'A', 'O', 'K', '\r', '\n', 'C', 'M', 'D', '>', ' '};
	
    RN487X_cmdBuf[0] = 'S';
    RN487X_cmdBuf[1] = 'B';
    RN487X_cmdBuf[2] = ',';
    RN487X_cmdBuf[3] = NIBBLE2ASCII(temp);
	temp = (baudRate & 0x0F);
    RN487X_cmdBuf[4] = NIBBLE2ASCII(temp);
    RN487X_cmdBuf[5] = '\r';
    RN487X_cmdBuf[6] = '\n';

    return RN487X_SendCommand_ReceiveResponse(RN487X_cmdBuf, 7U, cmdPrompt, 10);
}


bool RN487X_SetServiceBitmap(uint8_t serviceBitmap)
{
    const uint8_t cmdPrompt[] = {'A', 'O', 'K', '\r', '\n', 'C', 'M', 'D', '>', ' '};
    uint8_t temp = (serviceBitmap >> 4);

    RN487X_cmdBuf[0] = 'S';
    RN487X_cmdBuf[1] = 'S';
    RN487X_cmdBuf[2] = ',';
    RN487X_cmdBuf[3] = NIBBLE2ASCII(temp);
    temp = (serviceBitmap & 0x0F);
    RN487X_cmdBuf[4] = NIBBLE2ASCII(temp);
    RN487X_cmdBuf[5] = '\r';
    RN487X_cmdBuf[6] = '\n';

    return RN487X_SendCommand_ReceiveResponse(RN487X_cmdBuf, 7U, cmdPrompt, 10);
}


bool RN487X_SetFeaturesBitmap(uint16_t featuresBitmap)
{
    const uint8_t cmdPrompt[] = {'A', 'O', 'K', '\r', '\n', 'C', 'M', 'D', '>', ' '};
    uint8_t temp = (uint8_t) (featuresBitmap >> 12);

    RN487X_cmdBuf[0] = 'S';
    RN487X_cmdBuf[1] = 'R';
    RN487X_cmdBuf[2] = ',';
    temp = temp & 0x0F;
    RN487X_cmdBuf[3] = NIBBLE2ASCII(temp);
    temp = (uint8_t) (featuresBitmap >> 8);
    temp = temp & 0x0F;
    RN487X_cmdBuf[4] = NIBBLE2ASCII(temp);
    temp = (uint8_t) (featuresBitmap >> 4);
    temp = temp & 0x0F;
    RN487X_cmdBuf[5] = NIBBLE2ASCII(temp);
    temp = (uint8_t) featuresBitmap;
    temp = temp & 0x0F;
    RN487X_cmdBuf[6] = NIBBLE2ASCII(temp);
    RN487X_cmdBuf[7] = '\r';
    RN487X_cmdBuf[8] = '\n';

    return RN487X_SendCommand_ReceiveResponse(RN487X_cmdBuf, 9U, cmdPrompt, 10);
}


bool RN487X_SetIOCapability(uint8_t ioCapability)
{
    const uint8_t cmdPrompt[] = {'A', 'O', 'K', '\r', '\n', 'C', 'M', 'D', '>', ' '};
    RN487X_cmdBuf[0] = 'S';
    RN487X_cmdBuf[1] = 'A';
    RN487X_cmdBuf[2] = ',';
    RN487X_cmdBuf[3] = NIBBLE2ASCII(ioCapability);
    RN487X_cmdBuf[4] = '\r';
    RN487X_cmdBuf[5] = '\n';

    return RN487X_SendCommand_ReceiveResponse(RN487X_cmdBuf, 6U, cmdPrompt, 10);
}


bool RN487X_SetPinCode(const uint8_t *pinCode, uint8_t pinCodeLen)
{
    uint8_t index;
	const uint8_t cmdPrompt[] = {'A', 'O', 'K', '\r', '\n', 'C', 'M', 'D', '>', ' '};

    RN487X_cmdBuf[0] = 'S';
    RN487X_cmdBuf[1] = 'P';
    RN487X_cmdBuf[2] = ',';

    for (index = 0; index < pinCodeLen; index++)
    {
        RN487X_cmdBuf[3 + index] = pinCode[index];
    }
    index = index + 3;
    RN487X_cmdBuf[index++] = '\r';
    RN487X_cmdBuf[index++] = '\n';

    return RN487X_SendCommand_ReceiveResponse(RN487X_cmdBuf, index, cmdPrompt, 10);
}

bool RN487X_SetStatusMsgDelimiter(char preDelimiter, char postDelimiter)
{
    const uint8_t cmdPrompt[] = {'A', 'O', 'K', '\r', '\n', 'C', 'M', 'D', '>', ' '};
	
    RN487X_cmdBuf[0] = 'S';
    RN487X_cmdBuf[1] = '%';
    RN487X_cmdBuf[2] = ',';
    RN487X_cmdBuf[3] = preDelimiter;
    RN487X_cmdBuf[4] = ',';
    RN487X_cmdBuf[5] = postDelimiter;
    RN487X_cmdBuf[6] = '\r';
    RN487X_cmdBuf[7] = '\n';

    return RN487X_SendCommand_ReceiveResponse(RN487X_cmdBuf, 8, cmdPrompt, 10);
}


bool RN487X_SetOutputs(rn487x_gpio_bitmap_t bitMap)
{
    const uint8_t cmdPrompt[] = {'A', 'O', 'K', '\r', '\n', 'C', 'M', 'D', '>', ' '};
	
    char ioHighNibble = '0';
    char ioLowNibble = '0';
    char stateHighNibble = '0';
    char stateLowNibble = '0';
    
    // Output pins configurations
    if (bitMap.ioBitMap.p1_3)
    {
        ioHighNibble = '1';
    }
    else
    {
        ioHighNibble = '0';
    }
    ioLowNibble = ( (0x0F & bitMap.ioBitMap.gpioBitMap) + '0');
    
    // High/Low Output settings
    if (bitMap.ioStateBitMap.p1_3_state)
    {
        stateHighNibble = '1';
    }
    else
    {
        stateHighNibble = '0';
    }
    stateLowNibble = ( (0x0F & bitMap.ioStateBitMap.gpioStateBitMap) + '0');

    RN487X_cmdBuf[0] = '|';    // I/O
    RN487X_cmdBuf[1] = 'O';    // Output
    RN487X_cmdBuf[2] = ',';
    RN487X_cmdBuf[3] = ioHighNibble;       // - | - | - | P1_3
    RN487X_cmdBuf[4] = ioLowNibble;        // P1_2 | P3_5 | P2_4 | P2_2
    RN487X_cmdBuf[5] = ',';
    RN487X_cmdBuf[6] = stateHighNibble;    // - | - | - | P1_3
    RN487X_cmdBuf[7] = stateLowNibble;     // P1_2 | P3_5 | P2_4 | P2_2
    RN487X_cmdBuf[8] = '\r';
    RN487X_cmdBuf[9] = '\n';

    return RN487X_SendCommand_ReceiveResponse(RN487X_cmdBuf, 10U, cmdPrompt, 10U);
}


rn487x_gpio_stateBitMap_t RN487X_GetInputsValues(rn487x_gpio_ioBitMap_t getGPIOs)
{
    char ioHighNibble = '0';
    char ioLowNibble = '0';
    uint8_t ioValue[] = {'0', '0'};
    rn487x_gpio_stateBitMap_t ioBitMapValue;
    ioBitMapValue.gpioStateBitMap = 0x00;
    
    // Output pins configurations
    if (getGPIOs.p1_3)
    {
        ioHighNibble = '1';
    }
    else
    {
        ioHighNibble = '0';
    }
    ioLowNibble = ( (0x0F & getGPIOs.gpioBitMap) + '0');

    RN487X_cmdBuf[0] = '|';    // I/O
    RN487X_cmdBuf[1] = 'I';    // Output
    RN487X_cmdBuf[2] = ',';
    RN487X_cmdBuf[3] = ioHighNibble;       // - | - | - | P1_3
    RN487X_cmdBuf[4] = ioLowNibble;        // P1_2 | P3_5 | P2_4 | P2_2
    RN487X_cmdBuf[5] = '\r';
    RN487X_cmdBuf[6] = '\n';

    RN487X_SendCommand_ReceiveResponse(RN487X_cmdBuf, 7, ioValue, sizeof (ioValue));
    
    ioBitMapValue.gpioStateBitMap = ( (((ioValue[0] - '0') & 0x0F) << 4) | ((ioValue[1] - '0') & 0x0F) );
    return ioBitMapValue;
}


uint8_t * RN487X_GetRSSIValue(void)
{
    static uint8_t rssiResp[20];
    unsigned int ResponseRead=0,ResponseTime=0;

    RN487X_cmdBuf[0] = 'M';
    RN487X_cmdBuf[1] = '\r';
    RN487X_cmdBuf[2] = '\n';
	
	RN487X_SendCmd(RN487X_cmdBuf, 3);
	
	//Wait for the response time
    while(!RN487X.DataReady() || ResponseTime<=RESPONSE_TIMEOUT)
    {
        RN487X.DelayMs(1);
        ResponseTime++;
    }
	
	//Read Ready data 
    while(RN487X.DataReady())
    {
        resp[ResponseRead]=RN487X.Read();
        ResponseRead++;
    }
	
	rssiResp[0]=resp[0];
	rssiResp[1]=resp[1];
	rssiResp[2]=resp[2];
		
	return rssiResp;
}


bool RN487X_RebootCmd(void)
{
    bool RebootStatus = false;
    const uint8_t rebootResponse[] = {'R', 'e', 'b', 'o', 'o', 't', 'i', 'n', 'g', '\r', '\n'};
	RN487X_cmdBuf[0] = 'R';
    RN487X_cmdBuf[1] = ',';
    RN487X_cmdBuf[2] = '1';
    RN487X_cmdBuf[4] = '\r';
    RN487X_cmdBuf[5] = '\n';

    RebootStatus = RN487X_SendCommand_ReceiveResponse(RN487X_cmdBuf, 5U, rebootResponse, 11U);
	
	RN487X.DelayMs(350);
	
	return RebootStatus;
}


bool RN487X_FactoryReset(RN487X_FACTORY_RESET_MODE_t resetMode)
{
    bool FactoryResetStatus = false;
    const uint8_t reboot[] = {'R', 'e', 'b', 'o', 'o', 't', ' ', 'a', 'f', 't', 'e', 'r', ' ', 'F', 'a', 'c', 't', 'o', 'r', 'y', ' ', 'R', 'e', 's', 'e', 't', '\r', '\n'};
    RN487X_cmdBuf[0] = 'S';
    RN487X_cmdBuf[1] = 'F';
    RN487X_cmdBuf[2] = ',';
    RN487X_cmdBuf[4] = (char)resetMode;
    RN487X_cmdBuf[5] = '\r';
    RN487X_cmdBuf[6] = '\n';

    FactoryResetStatus = RN487X_SendCommand_ReceiveResponse(RN487X_cmdBuf, 6U, reboot, 28U);
	
	RN487X.DelayMs(350);
	
	return FactoryResetStatus;
}


bool RN487X_Disconnect(void)
{
    RN487X_cmdBuf[0] = 'K';
    RN487X_cmdBuf[1] = ',';
    RN487X_cmdBuf[2] = '1';
    RN487X_cmdBuf[3] = '\r';
    RN487X_cmdBuf[4] = '\n';

    RN487X_SendCmd(RN487X_cmdBuf, 5U);

    return RN487X_ReadDefaultResponse();
}

void RN487X_set_StatusDelimter(char Delimter_Character)
{
	RN487X_STATUS_MESSAGE_DELIMITER = Delimter_Character;
}

char RN487X_get_StatusDelimter()
{
	return RN487X_STATUS_MESSAGE_DELIMITER;
}

void RN487X_set_NoDelimter(bool value)
{
    skip_Delimter=value;
}

bool RN487X_get_NoDelimter()
{
    return skip_Delimter;
}


bool RN487X_AsyncMessageHandlerSet(char* pBuffer, uint8_t len)
{
    if ((pBuffer != NULL) && (len > 1))
    {
      RN487X_asyncBuffer = pBuffer;
      RN487X_asyncBufferSize = len - 1;
      return true;
    }
    else
    {
        return false;
    }
}

bool RN487X_isDataReady(void)
{
    if (RN487X_dataReady)
    {
        return true;
    }
    
    if (RN487X.DataReady())
    {
        return RN487X_DataFilter();
    }
    return false;
}

uint8_t RN487X_Read(void)
{
    while(RN487X_isDataReady() == false); // Wait
    RN487X_dataReady = false;
    return RN487X_peek;
}

static bool RN487X_DataFilter(void)
{
    static bool asyncBuffering = false;
    
    uint8_t readChar = RN487X.Read();
    
    if(asyncBuffering == true)
    {
        if(readChar == RN487X_STATUS_MESSAGE_DELIMITER)
        {
            asyncBuffering = false;
            *RN487X_pHead = '\0';
            RN487X.AsyncHandler(RN487X_asyncBuffer);
        }
        else if (RN487X_pHead < RN487X_asyncBuffer + RN487X_asyncBufferSize)
        {
            *RN487X_pHead++ = readChar;
        }
		else
        {
            //do nothing
        }
    }
    else
    {
        if (readChar == RN487X_STATUS_MESSAGE_DELIMITER && (skip_Delimter == false))
        {
            asyncBuffering = true;
            RN487X_pHead = RN487X_asyncBuffer;
        }
        else 
        {
			skip_Delimter = true;
            RN487X_dataReady = true;
            RN487X_peek = readChar;
        }
    }
    return RN487X_dataReady;
}
