/**
 * RNBD Generated Driver Interface Source File
 * 
 * @file rnbd_interface.c
 * 
 * @ingroup rnbd_interface
 * 
 * @brief This is the generated driver instance source file for the RNBD driver using RNBD
 *
 * @version RNBD Driver Version  2.0.0
*/
/*
© [2023] Microchip Technology Inc. and its subsidiaries.

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

#include <string.h>
#include "rnbd_interface.h"
#include "rnbd.h"
#include "../timer/delay.h"
#include "../system/system.h"

static bool connected = false,OTAComplete = false; //**< RNBD connection state */

/**
 * @ingroup rnbd_interface
 * @brief Initiate Hardware Reset of RNBD
 * @param value true - Reset State false - Normal State
 * @return none
 */
static void RNBD_Reset(bool value);

/**
 * @ingroup rnbd_interface
 * @brief Notify RNBD to expect incoming data
 * @param value true - RX Incoming false - No Data Incoming
 * @return none
 */
static void RNBD_RxIndicate(bool value);

/**
 * @ingroup rnbd_interface
 * @brief Set the RNBD System Configuration Mode
 * @param mode - APPLICATION_MODE - Normal Application Mode; TEST_MODE - Test Mode/Flash Update/EEPROM Configuration
 * @return none
 */
static void RNBD_SystemModeSet(RNBD_SYSTEM_MODES_t mode);

/**
 * @ingroup rnbd_interface
 * @brief Handle RNBD Status Message
 * @param message - Passed status message
 * @return none
 */
static void RNBD_MessageHandler(char* message);

/*****************************************************
*   *OPTIONAL* APPLICATION MESSAGE FORMATTING API(s)
******************************************************/  
/**
 * @ingroup rnbd_interface
 * @enum RNBD_MESSAGE_TYPE
 * @brief Enum of the MESSAGE TYPES supported in Driver Example(s)
 */
typedef enum 
{
    DISCONNECT_MSG  = 0,
    STREAM_OPEN_MSG = 1,
    GENERAL_MSG     = 2,
}RNBD_MESSAGE_TYPE;
/**
 * @ingroup rnbd_interface
 * @def GENERAL_PRINT_SIZE_LIMIT
 * This macro provide a definition used to process 
 */
#define GENERAL_PRINT_SIZE_LIMIT        (80)
/**
 * @ingroup rnbd_interface
 * @brief Prints the START Message "<<< " for UART_CDC
 * @param none
 * @return none
 */
static inline void RNBD_PrintMessageStart(void);
/**
 * @ingroup rnbd_interface
 * @brief Prints the END Message ">>>\r\n" for UART_CDC
 * @param none
 * @return none
 */
static inline void RNBD_PrintMessageEnd(void);
/**
 * @ingroup rnbd_interface
 * @brief Prints the Indicator [ or ] to UART_CDC
 *        [ - Disconnected | ] - Connected
 * @param none
 * @return none
 */
static inline void RNBD_PrintIndicatorCharacters(RNBD_MESSAGE_TYPE messageType);
/**
 * @ingroup rnbd_interface
 * @brief This API prints *Optional Application* Messages
 * @param none
 * @return none
 */
static inline void RNBD_PrintMessage(char* passedMessage);

/*****************************************************
*   Driver Instance Declaration(s) API(s)
******************************************************/  

const iRNBD_FunctionPtrs_t RNBD = {
    .Write = USART0_Write,
    .Read = USART0_Read,
    .DataReady = USART0_IsRxReady,
    .TransmitReady = USART0_IsTxReady,
    .RxIndicate = RNBD_RxIndicate,
    .ResetModule = RNBD_Reset,
    .SystemModeSet = RNBD_SystemModeSet,
    .DelayMs = DELAY_milliseconds,
    .AsyncHandler = RNBD_MessageHandler
};

/*****************************************************
*   Driver Public API
******************************************************/  

bool RNBD_IsConnected(void)
{
    return connected;
}

bool RNBD_IsOTAComplete(void)
{
    return OTAComplete;
}

/*****************************************************
*   Driver Implementation Private API(s)
******************************************************/  

static void RNBD_Reset(bool value)
{
    if (true == value)
    {
        BT_RST_SetLow();
    }
    else
    {
        BT_RST_SetHigh();
    }
}

static void RNBD_RxIndicate(bool value)
{
    // Implement desired support code for RX Indicator
}

static void RNBD_SystemModeSet(RNBD_SYSTEM_MODES_t mode)
{
    // Implement desired support code for RX Indicator
}

/*****************************************************
*   *Optional* Message Formatting Private API(s)
******************************************************/  

static inline void RNBD_PrintMessageStart(void)
{
    USART1_Write('<');
    USART1_Write('<');
    USART1_Write('<');
    USART1_Write(' ');
}

static inline void RNBD_PrintMessageEnd(void)
{
    USART1_Write(' ');
    USART1_Write('>');
    USART1_Write('>');
    USART1_Write('>');
    USART1_Write(' ');
    USART1_Write('\r');
    USART1_Write('\n');
}

static inline void RNBD_PrintIndicatorCharacters(RNBD_MESSAGE_TYPE messageType)
{
    if (DISCONNECT_MSG == messageType)
    {
        USART1_Write('[');
    }
    else if (STREAM_OPEN_MSG == messageType)
    {
        USART1_Write(']');
    }
    else
    {

    }
}

static inline void RNBD_PrintMessage(char* passedMessage)
{
    char printCharacter [GENERAL_PRINT_SIZE_LIMIT];
	uint8_t messageIndex;
	
    strcpy(printCharacter, passedMessage);
    for (messageIndex = 0; messageIndex < strlen(passedMessage); messageIndex++)
    {
        USART1_Write(printCharacter[messageIndex]);  
    }
}

static void RNBD_MessageHandler(char* message)
{

    RNBD_MESSAGE_TYPE messageType;
    RNBD_PrintMessageStart();

    int BT_Status_Ind1 = BT_STATUS_IND_1_GetValue();
    int BT_Status_Ind2 = BT_STATUS_IND_2_GetValue(); 


    if((!BT_Status_Ind1 && !BT_Status_Ind2) || (BT_Status_Ind1 && !BT_Status_Ind2))
    {
        messageType = DISCONNECT_MSG;   
        connected = false;
        OTAComplete = false;
    }
    else if(BT_Status_Ind1 && BT_Status_Ind2) 
    {

        messageType = STREAM_OPEN_MSG;
        connected = true;
    }
    else
    {
        messageType = GENERAL_MSG;
    }

    if (strstr(message, "OTA_REQ"))
    {
        OTAComplete = true;
        RNBD.Write('\r');
        RNBD.Write('\n');
//        
         
        RNBD.Write('O');
        RNBD.Write('T');
        RNBD.Write('A');
        RNBD.Write('A');
        RNBD.Write(',');
        RNBD.Write('0');
        RNBD.Write('1');
        RNBD.Write('\r');
        RNBD.Write('\n');
    }


    RNBD_PrintMessage(message);
    RNBD_PrintMessageEnd();
    RNBD_PrintIndicatorCharacters(messageType);
}
