/**
 * RN487X Generated Driver API Header File
 * 
 * @file rn487x.h
 * 
 * @defgroup  rn487x RN487X
 * 
 * @brief This is the generated header file for the RN487X driver
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

#ifndef RN487X_H
#define	RN487X_H
#include <stdbool.h>
#include <stdint.h>   

/**
 * @ingroup rn487x
 * @def RN487X_RESET_DELAY_TIME
 * This macro defines the time needed to place RN487X device in reset.
 */
#define RN487X_RESET_DELAY_TIME         (1)

/**
 * @ingroup rn487x
 * @def RN487X_STARTUP_DELAY
 * This macro defines the RN487X boot time.
 */
#define RN487X_STARTUP_DELAY            (300)

/**
 * @ingroup rn487x
 * @def NIBBLE2ASCII
 * Converts nibble to ASCII
 */
#define NIBBLE2ASCII(nibble) (((nibble < 0x0A) ? (nibble + '0') : (nibble + 0x57)))


/**
  Section: Data Type Definitions
*/

/**
 * @ingroup rn487x
 * @enum RN487X_SET_IO_CAPABILITY_t
 * @brief Defines the different capability options for {nameUpperCase}
 */
typedef enum
{
    SET_IO_CAP_0,    /*!< No input no output with bonding */
    SET_IO_CAP_1,    /*!< Display YesNo */
    SET_IO_CAP_2,    /*!< No input no output */
    SET_IO_CAP_3,    /*!< Key board only */
    SET_IO_CAP_4,    /*!< Display only */
    SET_IO_CAP_5,    /*!< Keyboard display */
}RN487X_SET_IO_CAPABILITY_t;


/**
 * @ingroup rn487x
 * @enum RN487X_BAUDRATE_t
 * @brief Defines the different baudrates supported by the {nameUpperCase} driver
 */     
typedef enum
{
    BR_921600,
    BR_460800,
    BR_230400,
    BR_115200,
    BR_57600,
    BR_38400,
    BR_28800,
    BR_19200,
    BR_14400,
    BR_9600,
    BR_4800,
    BR_2400,
}RN487X_BAUDRATE_t;


/**
 * @ingroup rn487x
 * @enum RN487X_FEATURES_BITMAP_t
 * @brief Defines the different feature modes supported by the {nameUpperCase} driver
 */  
typedef enum
{
    RN487X_ENABLE_FLOW_CONTROL = 0x8000,
    RN487X_NO_PROMPT = 0x4000,
    RN487X_FAST_MODE = 0x2000,
    RN487X_NO_BEACON_SCAN = 0x1000,
    RN487X_NO_CONNECT_SCAN = 0x0800,
    RN487X_NO_DUPLICATE_SCAN_RESULT_FILTER = 0x0400,
    RN487X_PASSIVE_SCAN = 0x0200,
    RN487X_UART_TRANSPARENT_WITHOUT_ACK = 0x0100,
    RN487X_REBOOT_AFTER_DISCONNECTION = 0x0080,
    RN487X_RUNNING_SCRIPT_AFTER_POWER_ON = 0x0040,
    RN487X_SUPPORT_RN4020_MLDP_STREAMING_SERVICE = 0x0020,
    RN487X_DATA_LENGTH_EXTENSION = 0x0010,
    RN487X_COMMAND_MODE_GUARD = 0x0008,
}RN487X_FEATURES_BITMAP_t;


/**
 * @ingroup rn487x
 * @enum RN487X_FACTORY_RESET_MODE_t
 * @brief Defines the different factory reset options for the {nameUpperCase} driver
 */  
typedef enum
{
    SF_1 = 1,   //Reset to factory default
    SF_2 = 2,   //Reset to factory default including private services and script
}RN487X_FACTORY_RESET_MODE_t;


/**
 * @ingroup rn487x
 * @enum RN487X_DEFAULT_SERVICE_BITMAP_t
 * @brief Defines the default services options for the {nameUpperCase} driver
 */  
typedef enum
{
    SS_DEVICE_INFO = 0X80,
    SS_UART_TRANSPARENT = 0x40,
    SS_BEACON = 0x20,
    SS_RESERVED = 0x10,
}RN487X_DEFAULT_SERVICE_BITMAP_t;


/**
 * @ingroup rn487x
 * @union rn487x_gpio_ioBitMap_t
 * @brief Bits (pins) set as (1) are considered OUTPUTS
 */ 
typedef union
{
    uint8_t gpioBitMap;
    struct
    {
        unsigned p2_2 : 1;          // 01
        unsigned p2_4 : 1;          // 02
        unsigned p3_5 : 1;          // 04
        unsigned p1_2 : 1;          // 08
        unsigned p1_3 : 1;          // 10
        unsigned reserved : 3;
    };
}rn487x_gpio_ioBitMap_t;


/**
 * @ingroup rn487x
 * @union rn487x_gpio_stateBitMap_t
 * @brief  Bits (states) set as (1) are considered HIGH
 */ 
typedef union
{
    uint8_t gpioStateBitMap;
    struct
    {
        unsigned p2_2_state : 1;
        unsigned p2_4_state : 1;
        unsigned p3_5_state : 1;
        unsigned p1_2_state : 1;
        unsigned p1_3_state : 1;
        unsigned reserved : 3;
    };
}rn487x_gpio_stateBitMap_t;


/**
 * @ingroup rn487x
 * @union rn487x_gpio_bitmap_t
 * @brief  Bits used for I/O (|) related commands
 */ 
typedef union 
{
    uint16_t gpioMap;
    struct
    {
        rn487x_gpio_ioBitMap_t ioBitMap;
        rn487x_gpio_stateBitMap_t ioStateBitMap;
    };
}rn487x_gpio_bitmap_t;


 /**
  *  @ingroup rn487x
  *  @brief Initializes RN487X Device
  *  @retval true - Initialization Success
  *  @retval false - Initialization Failure
  */
bool RN487X_Initialize(void);

 /**
  * @ingroup rn487x
  * @brief Sends out command to RN487X.
  * @param cmd - RN487X command
  * @param cmdLen - RN487X command length
  * @return none
  */
void RN487X_CmdSend(const uint8_t *cmd, uint8_t cmdLen);

/**
 * @ingroup rn487x
 * @brief Gets config value from RN487X by sending get command
 * @param getCmd - Get command to send
 * @param getCmdLen - Get command length
 * @param getCmdResp Buffer to store get command response
 * @return index - tracked command response length.
 */
uint8_t RN487X_CmdGet(const char *getCmd, uint8_t getCmdLen, char *getCmdResp);


 /**
  * @ingroup rn487x
  * @brief Reads specific message from RN487X.
  * @param expectedMsg - Expected response/status message from RN487X
  * @param msgLen - Expected response/status message length.
  * @retval true - Expected Message Received
  * @retval false - Expected Message NOT Received
  */
bool RN487X_MsgRead(const uint8_t *expectedMsg, uint8_t msgLen);

 /**
  * @ingroup rn487x
  * @brief Reads default response from RN487X.
  * @retval true - Default Response Received
  * @retval false - Default Response NOT Received
  */
bool RN487X_DefaultResponseRead(void);


 /**
  * @ingroup rn487x
  * @brief Waits for specific message from RN487X.
  * @param expectedMsg - Expected response/status message from RN487X
  * @param msgLen - Expected response/status message length
  * @return none
  */
void RN487X_MsgWait(const char *expectedMsg, uint8_t msgLen);


 /**
  *  @ingroup rn487x
  *  @brief Puts the RN487X in command mode.
  *  @retval true - Command Mode Status = Success
  *  @retval false - Command Mode Status = Failure
  */
bool RN487X_CmdModeEnter(void);

 /**
  *  @ingroup rn487x
  *  @brief Puts the RN487X in data mode.
  *  @retval true - Data Mode Status = Success
  *  @retval false -Data Mode Status = Failure
  */
bool RN487X_DataModeEnter(void);


 /**
  * @ingroup rn487x
  * @brief Sets device name.
  * @param name - Device name [20 alphanumeric characters max]
  * @param nameLen - Device name length
  * @retval true - Sets device name
  * @retval false - Failure
  */
bool RN487X_NameSet(const char *name, uint8_t nameLen);


 /**
  * @ingroup rn487x
  * @brief Sets Modules communication Baud Rate.
  * @param name - (2) character hex value coordinate to Command options 2.4.5
  * @retval true - Sets device name
  * @retval false - Failure
  */
bool RN487X_BaudRateSet(uint8_t baudRate);


 /**
  * @ingroup rn487x
  * @brief Sets the default supported services in RN487X.
  * @pre RN487X should be in command mode.
  * @param serviceBitmap - Supported services bitmap in RN487X 
  * @retval true - Sets service bitmap
  * @retval false - Failure
  */
bool RN487X_ServiceBitmapSet(uint8_t serviceBitmap);


 /**
  * @ingroup rn487x
  * @brief Sets the supported features of RN487X.
  * @0pre RN487X should be in command mode.
  * @param featuresBitmap - Supported features bitmap in RN487X 
  * @retval true - Sets features bitmap
  * @retval false - Failure
  */
bool RN487X_FeaturesBitmapSet(uint16_t featuresBitmap);


 /**
  * @ingroup rn487x
  * @brief Sets the IO capability of RN487X and the system.
  * @pre RN487X should be in command mode.
  * @param ioCapability - IO capability of RN487X 
  * @retval true - Sets IO capability
  * @retval false - Failure
  */
bool RN487X_IOCapabilitySet(uint8_t ioCapability);


 /**
  * @ingroup rn487x
  * @brief Sets the security pin code on RN487X.
  * @preconditions RN487X should be in command mode.
  * @param pinCode - Security pin code
  * @param pinCodeLen - Security pin code length (4 or 6) 
  * @retval true - Sets security pin code
  * @retval false - Failure
  */
bool RN487X_PinCodeSet(const char *pinCode, uint8_t pinCodeLen);


 /**
  * @ingroup rn487x
  * @brief Sets status message delimiter on RN487X.
  * @preconditions RN487X should be in command mode.
  * @param preDelimiter - Character to be use for Pre-delimiter
  * @param postDelimiter - Character to be use for Post-delimiter
  * @retval true - Delimiters are Set to new characters
  * @retval false - Failure
  */
bool RN487X_StatusMsgDelimiterSet(char preDelimiter, char postDelimiter);


 /**
  * @ingroup rn487x
  * @brief Configures RN487X GPIO pins as output, and sets state
  * @param bitMap RN487X GPIO Output I/O & Low/High State
  * @retval true - Set State Success
  * @retval false - Set State Failure
  */
bool RN487X_OutputsSet(rn487x_gpio_bitmap_t bitMap);


 /**
  * @ingroup rn487x
  * @brief Get RN487X GPIO pins input state status (high/low)
  * @param getGPIOs RN487X pins to read state status from
  * @return RN487X_gpio_stateBitMap_t - 8bit value coordinated to possible pin options
  */
rn487x_gpio_stateBitMap_t RN487X_InputsValuesGet(rn487x_gpio_ioBitMap_t getGPIOs);


 /**
  * @ingroup rn487x
  * @brief Gets Latest RSSI value.
  * @retval <RSSI>
  * @retval ERR - Not Connected to RN487X
  */
uint8_t * RN487X_RSSIValueGet(void);


 /**
  * @ingroup rn487x
  * @brief Resets RN487X.
  * @retval true - Reboot Success
  * @retval false - Reboot Failure
  */
bool RN487X_CmdReboot(void);


 /**
  * @ingroup rn487x
  * @brief Restores Factory Settings of RN487X module.
  * @retval true - Reset Success
  * @retval false - Reset Failure
  */
bool RN487X_FactoryReset(RN487X_FACTORY_RESET_MODE_t resetMode);


 /**
  * @ingroup rn487x
  * @brief Disconnects the BLE link between RN487X and remote device.
  * @retval true - Disconnect Success
  * @retval false - Disconnect Failure
  */
bool RN487X_Disconnect(void);

 /**
  * @ingroup rn487x
  * @brief Sets up the Buffer and Buffer Size for Aysnc Message Handler
  * @param pBuffer - Passed buffer
  * @param len - Size of passed buffer 
  * @retval true - Set Success
  * @retval false - Set Failure
  */
bool RN487X_AsyncMessageHandlerSet(char* pBuffer, uint8_t len);

 /**
  * @ingroup rn487x
  * @brief Checks to see if there is Data Ready using Async Message Handling
  * @param none
  * @retval true - Data is ready
  * @retval false - Data is not ready
  */
bool RN487X_isDataReady(void);

 /**
  * @ingroup rn487x
  * @brief Read incoming Data using Async Message Handling
  * @param none
  * @return Data Read
  */
uint8_t RN487X_Read(void);

#endif	/* RN487X_H */