/**
 * RN487X Generated Driver Interface Source File
 * 
 * @file rn487x_interface.c
 * 
 * @ingroup rn487x_interface
 * 
 * @brief This is the generated driver instance source file for the RN487X driver using RN4870/1
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

#include <string.h>
#include "rn487x_interface.h"
#include "rn487x.h"
#include "../timer/delay.h"
#include "../system/system.h"

static bool connected = false; //**< RN487X connection state */

/**
 * @ingroup rn487x_interface
 * @brief Initiate Hardware Reset of RN487X
 * @param value true - Reset State false - Normal State
 * @return none
 */
static void RN487X_Reset(bool value);

/**
 * @ingroup rn487x_interface
 * @brief Notify RN487X to expect incoming data
 * @param value true - RX Incoming false - No Data Incoming
 * @return none
 */
static void RN487X_RxIndicate(bool value);

/**
 * @ingroup rn487x_interface
 * @brief Set the RN487X System Configuration Mode
 * @param mode - APPLICATION_MODE - Normal Application Mode; TEST_MODE - Test Mode/Flash Update/EEPROM Configuration
 * @return none
 */
static void RN487X_SystemModeSet(RN487X_SYSTEM_MODES_t mode);

/**
 * @ingroup rn487x_interface
 * @brief Handle RN487X Status Message
 * @param message - Passed status message
 * @return none
 */
static void RN487X_MessageHandler(char* message);

/*****************************************************
*   *OPTIONAL* APPLICATION MESSAGE FORMATTING API(s)
******************************************************/  
/**
 * @ingroup rn487x_interface
 * @enum RN487X_MESSAGE_TYPE
 * @brief Enum of the MESSAGE TYPES supported in Driver Example(s)
 */
typedef enum 
{
    DISCONNECT_MSG  = 0,
    STREAM_OPEN_MSG = 1,
    GENERAL_MSG     = 2,
}RN487X_MESSAGE_TYPE;
/**
 * @ingroup rn487x_interface
 * @def GENERAL_PRINT_SIZE_LIMIT
 * This macro provide a definition used to process 
 */
#define GENERAL_PRINT_SIZE_LIMIT        (80)
/**
 * @ingroup rn487x_interface
 * @brief Prints the START Message "<<< " for UART_CDC
 * @param none
 * @return none
 */
static inline void RN487X_PrintMessageStart(void);
/**
 * @ingroup rn487x_interface
 * @brief Prints the END Message ">>>\r\n" for UART_CDC
 * @param none
 * @return none
 */
static inline void RN487X_PrintMessageEnd(void);
/**
 * @ingroup rn487x_interface
 * @brief Prints the Indicator [ or ] to UART_CDC
 *        [ - Disconnected | ] - Connected
 * @param none
 * @return none
 */
static inline void RN487X_PrintIndicatorCharacters(RN487X_MESSAGE_TYPE messageType);
/**
 * @ingroup rn487x_interface
 * @brief This API prints *Optional Application* Messages
 * @param none
 * @return none
 */
static inline void RN487X_PrintMessage(char* passedMessage);

/*****************************************************
*   Driver Instance Declaration(s) API(s)
******************************************************/  

const iRN487X_FunctionPtrs_t RN487X = {
    .Write = USART0_Write,
    .Read = USART0_Read,
    .DataReady = USART0_IsRxReady,
    .TransmitReady = USART0_IsTxReady,
    .RxIndicate = RN487X_RxIndicate,
    .ResetModule = RN487X_Reset,
    .SystemModeSet = RN487X_SystemModeSet,
    .DelayMs = DELAY_milliseconds,
    .AsyncHandler = RN487X_MessageHandler
};

/*****************************************************
*   Driver Public API
******************************************************/  

bool RN487X_IsConnected(void)
{
    return connected;
}

/*****************************************************
*   Driver Implementation Private API(s)
******************************************************/  

static void RN487X_Reset(bool value)
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

static void RN487X_RxIndicate(bool value)
{
    // Implement desired support code for RX Indicator
}

static void RN487X_SystemModeSet(RN487X_SYSTEM_MODES_t mode)
{
    // Implement desired support code for RX Indicator
}

/*****************************************************
*   *Optional* Message Formatting Private API(s)
******************************************************/  

static inline void RN487X_PrintMessageStart(void)
{
    USART1_Write('<');
    USART1_Write('<');
    USART1_Write('<');
    USART1_Write(' ');
}

static inline void RN487X_PrintMessageEnd(void)
{
    USART1_Write(' ');
    USART1_Write('>');
    USART1_Write('>');
    USART1_Write('>');
    USART1_Write(' ');
    USART1_Write('\r');
    USART1_Write('\n');
}

static inline void RN487X_PrintIndicatorCharacters(RN487X_MESSAGE_TYPE messageType)
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

static inline void RN487X_PrintMessage(char* passedMessage)
{
    char printCharacter [GENERAL_PRINT_SIZE_LIMIT];
	uint8_t messageIndex;
	
    strcpy(printCharacter, passedMessage);
    for (messageIndex = 0; messageIndex < strlen(passedMessage); messageIndex++)
    {
        USART1_Write(printCharacter[messageIndex]);  
    }
}

static void RN487X_MessageHandler(char* message)
{

    RN487X_MESSAGE_TYPE messageType;
    RN487X_PrintMessageStart();


    if (strstr(message, "DISCONNECT"))
    {
        messageType = DISCONNECT_MSG;
        connected = false;
    }
    else if (strstr(message, "STREAM_OPEN"))
    {
        messageType = STREAM_OPEN_MSG;
        connected = true;
    }
    else
    {
        messageType = GENERAL_MSG;
    }
    RN487X_PrintMessage(message);
    RN487X_PrintMessageEnd();
    RN487X_PrintIndicatorCharacters(messageType);
}
