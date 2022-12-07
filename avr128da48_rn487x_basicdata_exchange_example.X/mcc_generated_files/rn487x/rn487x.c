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
© [2022] Microchip Technology Inc. and its subsidiaries.

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
#include "rn487x.h"
#include "rn487x_interface.h"

/**
 * @def STATUS_MESSAGE_DELIMITER
 * This macro provide a definition of the RN487X devices PRE/POST status message delimiter.
 */
#define RN487X_STATUS_MESSAGE_DELIMITER  	      ('%')

uint8_t RN487X_cmdBuf[64];                                 /**< Command TX Buffer */

const char * const RN487X_driver_version = "2.0.0"; /**<  Current RN487X Driver Version */

static char *RN487X_asyncBuffer;                           /**< Async Message Buffer */
static uint8_t RN487X_asyncBufferSize;                     /**< Size of the Async Message Buffer */
static char *RN487X_pHead;                                 /**< Pointer to the Head of the Async Message Buffer */
static uint8_t RN487X_peek = 0;                            /**< Recieved Non-Status Message Data */
static bool RN487X_dataReady = false;                      /**< Flag which indicates whether Non-Status Message Data is ready */

/**
 * @ingroup rn487x
 * @brief This function filters status messages from RN487X data.
 * @param void This function takes no params.
 * @retval true - data is ready
 * @retval false -data is not ready
 */
static bool RN487X_DataFilter(void);

bool RN487X_Initialize(void)
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

void RN487X_CmdSend(const uint8_t *cmd, uint8_t cmdLen)
{
    uint8_t index = 0;

    while (index < cmdLen)
    {
        if (RN487X.TransmitReady())
        {
            RN487X.Write(cmd[index]);
            index++;
        }
    }
}

uint8_t RN487X_CmdGet(const char *getCmd, uint8_t getCmdLen, char *getCmdResp)
{
    uint8_t index = 0;

    RN487X_CmdSend((uint8_t *) getCmd, getCmdLen);

    do
    {
        getCmdResp[index++] = RN487X.Read();
    }
    while (getCmdResp[index - 1] != '\n');

    return index;
}

bool RN487X_MsgRead(const uint8_t *expectedMsg, uint8_t msgLen)
{
    uint8_t index;
    uint8_t resp;

    for (index = 0; index < msgLen; index++)
    {
        resp = RN487X.Read();
        if (resp != expectedMsg[index])
        {
            return false;
        }
    }

    return true;
}


bool RN487X_DefaultResponseRead(void)
{
    uint8_t resp[3];
    bool status = false;

    resp[0] = RN487X.Read();
    resp[1] = RN487X.Read();
    resp[2] = RN487X.Read();

    switch (resp[0])
    {
        case 'A':
        {
            if ((resp[1] == 'O') && (resp[2] == 'K'))
                status = true;

            break;
        }
        case 'E':
        {
            if ((resp[1] == 'r') && (resp[2] == 'r'))
                status = false;

            break;
        }
        default:
        {
            return status;
        }
    }

    /* Read carriage return and line feed comes with response */
    RN487X.Read();
    RN487X.Read();

    //Read CMD>
    RN487X.Read();
    RN487X.Read();
    RN487X.Read();
    RN487X.Read();
    RN487X.Read();
  
    return status;
}


void RN487X_MsgWait(const char *expectedMsg, uint8_t msgLen)
{
    uint8_t index = 0;
    uint8_t resp;

    do
    {
        resp = RN487X.Read();

        if (resp == expectedMsg[index])
        {
            index++;
        }
        else
        {
            index = 0;
            if (resp == expectedMsg[index])
            {
                index++;
            }
        }
    }
    while (index < msgLen);
}


bool RN487X_CmdModeEnter(void)
{
    const uint8_t cmdPrompt[] = {'C', 'M', 'D', '>', ' '};

    RN487X_cmdBuf[0] = '$';
    RN487X_cmdBuf[1] = '$';
    RN487X_cmdBuf[2] = '$';

    RN487X_CmdSend(RN487X_cmdBuf, 3);

    return RN487X_MsgRead(cmdPrompt, sizeof (cmdPrompt));
}

bool RN487X_DataModeEnter(void)
{
    const uint8_t cmdPrompt[] = {'E', 'N', 'D', '\r', '\n'};

    RN487X_cmdBuf[0] = '-';
    RN487X_cmdBuf[1] = '-';
    RN487X_cmdBuf[2] = '-';
    RN487X_cmdBuf[3] = '\r';
    RN487X_cmdBuf[4] = '\n';

    RN487X_CmdSend(RN487X_cmdBuf, 5);

    return RN487X_MsgRead(cmdPrompt, sizeof (cmdPrompt));
}

bool RN487X_NameSet(const char *name, uint8_t nameLen)
{
    uint8_t index;

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

    RN487X_CmdSend(RN487X_cmdBuf, nameLen + 5);

    return RN487X_DefaultResponseRead();
}

bool RN487X_BaudRateSet(uint8_t baudRate)
{
    RN487X_cmdBuf[0] = 'S';
    RN487X_cmdBuf[1] = 'B';
    RN487X_cmdBuf[2] = ',';
    RN487X_cmdBuf[3] = ((uint8_t)(baudRate >> 4)) & 0x0F;
    RN487X_cmdBuf[4] = (baudRate & 0x0F);
    RN487X_cmdBuf[5] = '\r';
    RN487X_cmdBuf[6] = '\n';

    RN487X_CmdSend(RN487X_cmdBuf, 7);

    return RN487X_DefaultResponseRead();
}


bool RN487X_ServiceBitmapSet(uint8_t serviceBitmap)
{
    uint8_t temp = (serviceBitmap >> 4);

    RN487X_cmdBuf[0] = 'S';
    RN487X_cmdBuf[1] = 'S';
    RN487X_cmdBuf[2] = ',';
    RN487X_cmdBuf[3] = NIBBLE2ASCII(temp);
    temp = (serviceBitmap & 0x0F);
    RN487X_cmdBuf[4] = NIBBLE2ASCII(temp);
    RN487X_cmdBuf[5] = '\r';
    RN487X_cmdBuf[6] = '\n';

    RN487X_CmdSend(RN487X_cmdBuf, 7);

    return RN487X_DefaultResponseRead();
}


bool RN487X_FeaturesBitmapSet(uint16_t featuresBitmap)
{
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

    RN487X_CmdSend(RN487X_cmdBuf, 9);

    return RN487X_DefaultResponseRead();
}


bool RN487X_IOCapabilitySet(uint8_t ioCapability)
{
    RN487X_cmdBuf[0] = 'S';
    RN487X_cmdBuf[1] = 'A';
    RN487X_cmdBuf[2] = ',';
    RN487X_cmdBuf[3] = NIBBLE2ASCII(ioCapability);
    RN487X_cmdBuf[4] = '\r';
    RN487X_cmdBuf[5] = '\n';

    RN487X_CmdSend(RN487X_cmdBuf, 6);

    return RN487X_DefaultResponseRead();
}


bool RN487X_PinCodeSet(const char *pinCode, uint8_t pinCodeLen)
{
    uint8_t index;

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

    RN487X_CmdSend(RN487X_cmdBuf, index);

    return RN487X_DefaultResponseRead();
}

bool RN487X_StatusMsgDelimiterSet(char preDelimiter, char postDelimiter)
{
    RN487X_cmdBuf[0] = 'S';
    RN487X_cmdBuf[1] = '%';
    RN487X_cmdBuf[2] = ',';
    RN487X_cmdBuf[3] = preDelimiter;
    RN487X_cmdBuf[4] = ',';
    RN487X_cmdBuf[5] = postDelimiter;
    RN487X_cmdBuf[6] = '\r';
    RN487X_cmdBuf[7] = '\n';

    RN487X_CmdSend(RN487X_cmdBuf, 8);

    if (RN487X_DefaultResponseRead())
    {
        return true;
    }

    return false;
}


bool RN487X_OutputsSet(rn487x_gpio_bitmap_t bitMap)
{
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

    RN487X_CmdSend(RN487X_cmdBuf, 10);
    return RN487X_DefaultResponseRead();
}


rn487x_gpio_stateBitMap_t RN487X_InputsValuesGet(rn487x_gpio_ioBitMap_t getGPIOs)
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

    RN487X_CmdSend(RN487X_cmdBuf, 7);
    RN487X_MsgRead(ioValue, sizeof (ioValue));    
    ioBitMapValue.gpioStateBitMap = ( (((ioValue[0] - '0') & 0x0F) << 4) | ((ioValue[1] - '0') & 0x0F) );
    return ioBitMapValue;
}


uint8_t * RN487X_RSSIValueGet(void)
{
    static uint8_t resp[3];

    RN487X_cmdBuf[0] = 'M';
    RN487X_cmdBuf[1] = '\r';
    RN487X_cmdBuf[2] = '\n';

    RN487X_CmdSend(RN487X_cmdBuf, 3);

    resp[0] = RN487X.Read();
    resp[1] = RN487X.Read();
    resp[2] = RN487X.Read();

    // Read carriage return and line feed
    RN487X.Read();
    RN487X.Read();

    // Read CMD>
    RN487X.Read();
    RN487X.Read();
    RN487X.Read();
    RN487X.Read();
    RN487X.Read();

    return resp;
}


bool RN487X_CmdReboot(void)
{
    const uint8_t reboot[] = {'R', 'e', 'b', 'o', 'o', 't', 'i', 'n', 'g', '\r', '\n'};

    RN487X_cmdBuf[0] = 'R';
    RN487X_cmdBuf[1] = ',';
    RN487X_cmdBuf[2] = '1';
    RN487X_cmdBuf[4] = '\r';
    RN487X_cmdBuf[5] = '\n';

    RN487X_CmdSend(RN487X_cmdBuf, 5);

    return RN487X_MsgRead(reboot, sizeof (reboot));
}


bool RN487X_FactoryReset(RN487X_FACTORY_RESET_MODE_t resetMode)
{
    const uint8_t reboot[] = {'R', 'e', 'b', 'o', 'o', 't', ' ', 'a', 'f', 't', 'e', 'r', ' ', 'F', 'a', 'c', 't', 'o', 'r', 'y', ' ', 'R', 'e', 's', 'e', 't', '\r', '\n'};
    RN487X_cmdBuf[0] = 'S';
    RN487X_cmdBuf[1] = 'F';
    RN487X_cmdBuf[2] = ',';
    RN487X_cmdBuf[4] = resetMode;
    RN487X_cmdBuf[5] = '\r';
    RN487X_cmdBuf[5] = '\n';

    RN487X_CmdSend(RN487X_cmdBuf, 6);

    return RN487X_MsgRead(reboot, sizeof (reboot));
}


bool RN487X_Disconnect(void)
{
    RN487X_cmdBuf[0] = 'K';
    RN487X_cmdBuf[1] = ',';
    RN487X_cmdBuf[2] = '1';
    RN487X_cmdBuf[3] = '\r';
    RN487X_cmdBuf[4] = '\n';

    RN487X_CmdSend(RN487X_cmdBuf, 5);

    return RN487X_DefaultResponseRead();
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
    }
    else
    {
        if (readChar == RN487X_STATUS_MESSAGE_DELIMITER)
        {
            asyncBuffering = true;
            RN487X_pHead = RN487X_asyncBuffer;
        }
        else 
        {
            RN487X_dataReady = true;
            RN487X_peek = readChar;
        }
    }
    return RN487X_dataReady;
}
