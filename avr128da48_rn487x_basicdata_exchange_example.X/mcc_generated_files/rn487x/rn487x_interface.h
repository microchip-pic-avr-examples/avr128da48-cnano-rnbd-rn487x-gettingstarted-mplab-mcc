/**
 * RN487X Generated Driver Instance Header File
 * 
 * @file rn487x_interface.h
 * 
 * @defgroup rn487x_interface RN487X_INTERFACE
 * 
 * @brief This is the generated driver instance header file for the RN487X driver using RN4870/1
 *
 * @version RN487X Driver Version  2.0.0
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

#ifndef RN487X_INTERFACE_H
#define	RN487X_INTERFACE_H

#include <stdbool.h>
#include <stdint.h>


/**
 * @ingroup rn487x_interface
 * @enum RN487X_SYSTEM_MODES_t
 * @brief Enum of the RN487X System Configuration Modes
 */
typedef enum
{
    TEST_MODE           = 0x00,
    APPLICATION_MODE    = 0x01 
}RN487X_SYSTEM_MODES_t;

/**
 * @ingroup rn487x_interface
 * @struct iRN487X_FunctionPtrs_t
 * @brief Struct of RN487X Interface Function Pointer Prototypes
 */
typedef struct
{
    // RN487x UART interface control
    void (*Write)(uint8_t);
    uint8_t (*Read)(void);
    bool (*TransmitReady)(void);
    bool (*DataReady)(void);
    // RN487x RX_IND pin control
    void (*RxIndicate)(bool);
    // RN487x Reset pin control
    void (*ResetModule)(bool);
    // RN487x Mode pin set
    void (*SystemModeSet)(RN487X_SYSTEM_MODES_t);
    // Delay API
    void (*DelayMs)(uint16_t);
    // Status Message Handler
    void (*AsyncHandler)(char*);
}iRN487X_FunctionPtrs_t;

extern const iRN487X_FunctionPtrs_t RN487X;

/**
 * @ingroup rn487x_interface
 * @brief Checks Connected State of RN487X
 * @retval true - Connected
 * @retval false - Not Connected
 */
bool RN487X_IsConnected(void);

#endif	/* RN487X_INTERFACE_H */