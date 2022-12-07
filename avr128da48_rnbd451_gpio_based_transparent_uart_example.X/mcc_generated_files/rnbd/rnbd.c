/**
 * RNBD Generated Driver Source File
 * 
 * @file rnbd.c
 * 
 * @ingroup rnbd
 * 
 * @brief This is the generated driver source file for RNBD driver using RNBD.
 *
 * @version RNBD Driver Version  2.0.0
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
#include <stdlib.h>
#include "rnbd.h"
#include "rnbd_interface.h"

/**
 * @def STATUS_MESSAGE_DELIMITER
 * This macro provide a definition of the RNBD devices PRE/POST status message delimiter.
 */
#define RNBD_STATUS_MESSAGE_DELIMITER  	      ('%')

uint8_t RNBD_cmdBuf[64];                                 /**< Command TX Buffer */

const char * const RNBD_driver_version = "2.0.0"; /**<  Current RNBD Driver Version */

static char *RNBD_asyncBuffer;                           /**< Async Message Buffer */
static uint8_t RNBD_asyncBufferSize;                     /**< Size of the Async Message Buffer */
static char *RNBD_pHead;                                 /**< Pointer to the Head of the Async Message Buffer */
static uint8_t RNBD_peek = 0;                            /**< Recieved Non-Status Message Data */
static bool RNBD_dataReady = false;                      /**< Flag which indicates whether Non-Status Message Data is ready */

/**
 * @ingroup rnbd
 * @brief This function filters status messages from RNBD data.
 * @param void This function takes no params.
 * @retval true - data is ready
 * @retval false -data is not ready
 */
static bool RNBD_DataFilter(void);

bool RNBD_Initialize(void)
{
    //Enter reset
    RNBD.ResetModule(true);
    //Wait for Reset
    RNBD.DelayMs(RNBD_RESET_DELAY_TIME);
    //Exit reset
    RNBD.ResetModule(false);

    //Wait while RNBD is booting up
    RNBD.DelayMs(RNBD_STARTUP_DELAY);

    //Remove unread data sent by RN487x, if any
    while (RNBD.DataReady())
    {
        RNBD.Read();
    }

    return true;
}

void RNBD_CmdSend(const uint8_t *cmd, uint8_t cmdLen)
{
    uint8_t index = 0;

    while (index < cmdLen)
    {
        if (RNBD.TransmitReady())
        {
            RNBD.Write(cmd[index]);
            index++;
        }
    }
}

uint8_t RNBD_CmdGet(const char *getCmd, uint8_t getCmdLen, char *getCmdResp)
{
    uint8_t index = 0;

    RNBD_CmdSend((uint8_t *) getCmd, getCmdLen);

    do
    {
        getCmdResp[index++] = RNBD.Read();
    }
    while (getCmdResp[index - 1] != '\n');

    return index;
}

bool RNBD_MsgRead(const uint8_t *expectedMsg, uint8_t msgLen)
{
    uint8_t index;
    uint8_t resp;

    for (index = 0; index < msgLen; index++)
    {
        resp = RNBD.Read();
        if (resp != expectedMsg[index])
        {
            return false;
        }
    }

    return true;
}


bool RNBD_DefaultResponseRead(void)
{
    uint8_t resp[3];
    bool status = false;

    resp[0] = RNBD.Read();
    resp[1] = RNBD.Read();
    resp[2] = RNBD.Read();

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
    RNBD.Read();
    RNBD.Read();

    //Read CMD>
    RNBD.Read();
    RNBD.Read();
    RNBD.Read();
    RNBD.Read();
    RNBD.Read();
  
    return status;
}


void RNBD_MsgWait(const char *expectedMsg, uint8_t msgLen)
{
    uint8_t index = 0;
    uint8_t resp;

    do
    {
        resp = RNBD.Read();

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


bool RNBD_CmdModeEnter(void)
{
    const uint8_t cmdPrompt[] = {'C', 'M', 'D', '>', ' '};

    RNBD_cmdBuf[0] = '$';
    RNBD_cmdBuf[1] = '$';
    RNBD_cmdBuf[2] = '$';

    RNBD_CmdSend(RNBD_cmdBuf, 3);

    return RNBD_MsgRead(cmdPrompt, sizeof (cmdPrompt));
}

bool RNBD_DataModeEnter(void)
{
    const uint8_t cmdPrompt[] = {'E', 'N', 'D', '\r', '\n'};

    RNBD_cmdBuf[0] = '-';
    RNBD_cmdBuf[1] = '-';
    RNBD_cmdBuf[2] = '-';
    RNBD_cmdBuf[3] = '\r';
    RNBD_cmdBuf[4] = '\n';

    RNBD_CmdSend(RNBD_cmdBuf, 5);

    return RNBD_MsgRead(cmdPrompt, sizeof (cmdPrompt));
}

uint16_t RNBD_GetGRCommand(void)
{
    static char response[4];
    uint16_t GR_Bitmap_Value=0;

    RNBD_cmdBuf[0] = 'g';
    RNBD_cmdBuf[1] = 'r';
    RNBD_cmdBuf[2] = '\r';
    RNBD_cmdBuf[3] = '\n';

    RNBD_CmdSend(RNBD_cmdBuf, 4);
    response[0] = RNBD.Read();
    response[1] = RNBD.Read();
    response[2] = RNBD.Read();
    response[3] = RNBD.Read();

    // Read carriage return and line feed
    RNBD.Read();
    RNBD.Read();

    // Read CMD>
    RNBD.Read();
    RNBD.Read();
    RNBD.Read();
    RNBD.Read();
    RNBD.Read();
    GR_Bitmap_Value = (int)strtol(response, NULL, 16);
    

    return GR_Bitmap_Value;
}


bool RNBD_NameSet(const char *name, uint8_t nameLen)
{
    uint8_t index;

    RNBD_cmdBuf[0] = 'S';
    RNBD_cmdBuf[1] = 'N';
    RNBD_cmdBuf[2] = ',';
	

    for (index = 0; index < nameLen; index++)
    {
        RNBD_cmdBuf[3 + index] = name[index];
    }
    index = index + 3;

    RNBD_cmdBuf[index++] = '\r';
    RNBD_cmdBuf[index++] = '\n';

    RNBD_CmdSend(RNBD_cmdBuf, nameLen + 5);

    return RNBD_DefaultResponseRead();
}

bool RNBD_BaudRateSet(uint8_t baudRate)
{
    RNBD_cmdBuf[0] = 'S';
    RNBD_cmdBuf[1] = 'B';
    RNBD_cmdBuf[2] = ',';
    RNBD_cmdBuf[3] = ((uint8_t)(baudRate >> 4)) & 0x0F;
    RNBD_cmdBuf[4] = (baudRate & 0x0F);
    RNBD_cmdBuf[5] = '\r';
    RNBD_cmdBuf[6] = '\n';

    RNBD_CmdSend(RNBD_cmdBuf, 7);

    return RNBD_DefaultResponseRead();
}


bool RNBD_ServiceBitmapSet(uint8_t serviceBitmap)
{
    uint8_t temp = (serviceBitmap >> 4);

    RNBD_cmdBuf[0] = 'S';
    RNBD_cmdBuf[1] = 'S';
    RNBD_cmdBuf[2] = ',';
    RNBD_cmdBuf[3] = NIBBLE2ASCII(temp);
    temp = (serviceBitmap & 0x0F);
    RNBD_cmdBuf[4] = NIBBLE2ASCII(temp);
    RNBD_cmdBuf[5] = '\r';
    RNBD_cmdBuf[6] = '\n';

    RNBD_CmdSend(RNBD_cmdBuf, 7);

    return RNBD_DefaultResponseRead();
}


bool RNBD_FeaturesBitmapSet(uint16_t featuresBitmap)
{
    uint8_t temp = (uint8_t) (featuresBitmap >> 12);

    RNBD_cmdBuf[0] = 'S';
    RNBD_cmdBuf[1] = 'R';
    RNBD_cmdBuf[2] = ',';
    temp = temp & 0x0F;
    RNBD_cmdBuf[3] = NIBBLE2ASCII(temp);
    temp = (uint8_t) (featuresBitmap >> 8);
    temp = temp & 0x0F;
    RNBD_cmdBuf[4] = NIBBLE2ASCII(temp);
    temp = (uint8_t) (featuresBitmap >> 4);
    temp = temp & 0x0F;
    RNBD_cmdBuf[5] = NIBBLE2ASCII(temp);
    temp = (uint8_t) featuresBitmap;
    temp = temp & 0x0F;
    RNBD_cmdBuf[6] = NIBBLE2ASCII(temp);
    RNBD_cmdBuf[7] = '\r';
    RNBD_cmdBuf[8] = '\n';

    RNBD_CmdSend(RNBD_cmdBuf, 9);

    return RNBD_DefaultResponseRead();
}


bool RNBD_IOCapabilitySet(uint8_t ioCapability)
{
    RNBD_cmdBuf[0] = 'S';
    RNBD_cmdBuf[1] = 'A';
    RNBD_cmdBuf[2] = ',';
    RNBD_cmdBuf[3] = NIBBLE2ASCII(ioCapability);
    RNBD_cmdBuf[4] = '\r';
    RNBD_cmdBuf[5] = '\n';

    RNBD_CmdSend(RNBD_cmdBuf, 6);

    return RNBD_DefaultResponseRead();
}


bool RNBD_PinCodeSet(const char *pinCode, uint8_t pinCodeLen)
{
    uint8_t index;

    RNBD_cmdBuf[0] = 'S';
    RNBD_cmdBuf[1] = 'P';
    RNBD_cmdBuf[2] = ',';

    for (index = 0; index < pinCodeLen; index++)
    {
        RNBD_cmdBuf[3 + index] = pinCode[index];
    }
    index = index + 3;
    RNBD_cmdBuf[index++] = '\r';
    RNBD_cmdBuf[index++] = '\n';

    RNBD_CmdSend(RNBD_cmdBuf, index);

    return RNBD_DefaultResponseRead();
}

bool RNBD_StatusMsgDelimiterSet(char preDelimiter, char postDelimiter)
{
    RNBD_cmdBuf[0] = 'S';
    RNBD_cmdBuf[1] = '%';
    RNBD_cmdBuf[2] = ',';
    RNBD_cmdBuf[3] = preDelimiter;
    RNBD_cmdBuf[4] = ',';
    RNBD_cmdBuf[5] = postDelimiter;
    RNBD_cmdBuf[6] = '\r';
    RNBD_cmdBuf[7] = '\n';

    RNBD_CmdSend(RNBD_cmdBuf, 8);

    if (RNBD_DefaultResponseRead())
    {
        return true;
    }

    return false;
}


bool RNBD_OutputsSet(rnbd_gpio_bitmap_t bitMap)
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

    RNBD_cmdBuf[0] = '|';    // I/O
    RNBD_cmdBuf[1] = 'O';    // Output
    RNBD_cmdBuf[2] = ',';
    RNBD_cmdBuf[3] = ioHighNibble;       // - | - | - | P1_3
    RNBD_cmdBuf[4] = ioLowNibble;        // P1_2 | P3_5 | P2_4 | P2_2
    RNBD_cmdBuf[5] = ',';
    RNBD_cmdBuf[6] = stateHighNibble;    // - | - | - | P1_3
    RNBD_cmdBuf[7] = stateLowNibble;     // P1_2 | P3_5 | P2_4 | P2_2
    RNBD_cmdBuf[8] = '\r';
    RNBD_cmdBuf[9] = '\n';

    RNBD_CmdSend(RNBD_cmdBuf, 10);
    return RNBD_DefaultResponseRead();
}


rnbd_gpio_stateBitMap_t RNBD_InputsValuesGet(rnbd_gpio_ioBitMap_t getGPIOs)
{
    char ioHighNibble = '0';
    char ioLowNibble = '0';
    uint8_t ioValue[] = {'0', '0'};
    rnbd_gpio_stateBitMap_t ioBitMapValue;
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

    RNBD_cmdBuf[0] = '|';    // I/O
    RNBD_cmdBuf[1] = 'I';    // Output
    RNBD_cmdBuf[2] = ',';
    RNBD_cmdBuf[3] = ioHighNibble;       // - | - | - | P1_3
    RNBD_cmdBuf[4] = ioLowNibble;        // P1_2 | P3_5 | P2_4 | P2_2
    RNBD_cmdBuf[5] = '\r';
    RNBD_cmdBuf[6] = '\n';

    RNBD_CmdSend(RNBD_cmdBuf, 7);
    RNBD_MsgRead(ioValue, sizeof (ioValue));    
    ioBitMapValue.gpioStateBitMap = ( (((ioValue[0] - '0') & 0x0F) << 4) | ((ioValue[1] - '0') & 0x0F) );
    return ioBitMapValue;
}


uint8_t * RNBD_RSSIValueGet(void)
{
    static uint8_t resp[3];

    RNBD_cmdBuf[0] = 'M';
    RNBD_cmdBuf[1] = '\r';
    RNBD_cmdBuf[2] = '\n';

    RNBD_CmdSend(RNBD_cmdBuf, 3);

    resp[0] = RNBD.Read();
    resp[1] = RNBD.Read();
    resp[2] = RNBD.Read();

    // Read carriage return and line feed
    RNBD.Read();
    RNBD.Read();

    // Read CMD>
    RNBD.Read();
    RNBD.Read();
    RNBD.Read();
    RNBD.Read();
    RNBD.Read();

    return resp;
}


bool RNBD_CmdReboot(void)
{
    const uint8_t reboot[] = {'R', 'e', 'b', 'o', 'o', 't', 'i', 'n', 'g', '\r', '\n'};

    RNBD_cmdBuf[0] = 'R';
    RNBD_cmdBuf[1] = ',';
    RNBD_cmdBuf[2] = '1';
    RNBD_cmdBuf[4] = '\r';
    RNBD_cmdBuf[5] = '\n';

    RNBD_CmdSend(RNBD_cmdBuf, 5);

    return RNBD_MsgRead(reboot, sizeof (reboot));
}


bool RNBD_FactoryReset(RNBD_FACTORY_RESET_MODE_t resetMode)
{
    const uint8_t reboot[] = {'R', 'e', 'b', 'o', 'o', 't', ' ', 'a', 'f', 't', 'e', 'r', ' ', 'F', 'a', 'c', 't', 'o', 'r', 'y', ' ', 'R', 'e', 's', 'e', 't', '\r', '\n'};
    RNBD_cmdBuf[0] = 'S';
    RNBD_cmdBuf[1] = 'F';
    RNBD_cmdBuf[2] = ',';
    RNBD_cmdBuf[4] = resetMode;
    RNBD_cmdBuf[5] = '\r';
    RNBD_cmdBuf[5] = '\n';

    RNBD_CmdSend(RNBD_cmdBuf, 6);

    return RNBD_MsgRead(reboot, sizeof (reboot));
}


bool RNBD_Disconnect(void)
{
    RNBD_cmdBuf[0] = 'K';
    RNBD_cmdBuf[1] = ',';
    RNBD_cmdBuf[2] = '1';
    RNBD_cmdBuf[3] = '\r';
    RNBD_cmdBuf[4] = '\n';

    RNBD_CmdSend(RNBD_cmdBuf, 5);

    return RNBD_DefaultResponseRead();
}


bool RNBD_AsyncMessageHandlerSet(char* pBuffer, uint8_t len)
{
    if ((pBuffer != NULL) && (len > 1))
    {
      RNBD_asyncBuffer = pBuffer;
      RNBD_asyncBufferSize = len - 1;
      return true;
    }
    else
    {
        return false;
    }
}

bool RNBD_isDataReady(void)
{
    if (RNBD_dataReady)
    {
        return true;
    }
    
    if (RNBD.DataReady())
    {
        return RNBD_DataFilter();
    }
    return false;
}

uint8_t RNBD_Read(void)
{
    while(RNBD_isDataReady() == false); // Wait
    RNBD_dataReady = false;
    return RNBD_peek;
}

static bool RNBD_DataFilter(void)
{
    static bool asyncBuffering = false;
    
    uint8_t readChar = RNBD.Read();
    
    if(asyncBuffering == true)
    {
        if(readChar == RNBD_STATUS_MESSAGE_DELIMITER)
        {
            asyncBuffering = false;
            *RNBD_pHead = '\0';
            RNBD.AsyncHandler(RNBD_asyncBuffer);
        }
        else if (RNBD_pHead < RNBD_asyncBuffer + RNBD_asyncBufferSize)
        {
            *RNBD_pHead++ = readChar;
        }
    }
    else
    {
        if (readChar == RNBD_STATUS_MESSAGE_DELIMITER)
        {
            asyncBuffering = true;
            RNBD_pHead = RNBD_asyncBuffer;
        }
        else 
        {
            RNBD_dataReady = true;
            RNBD_peek = readChar;
        }
    }
    return RNBD_dataReady;
}
