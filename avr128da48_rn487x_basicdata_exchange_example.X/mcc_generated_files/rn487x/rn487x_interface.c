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


static void RN487X_MessageHandler(char* message)
{



    if (strstr(message, "DISCONNECT"))
    {
        connected = false;
    }
    else if (strstr(message, "STREAM_OPEN"))
    {
        connected = true;
    }
    else
    {
        // Left Intentionally Blank: For General Messages
    }
}
