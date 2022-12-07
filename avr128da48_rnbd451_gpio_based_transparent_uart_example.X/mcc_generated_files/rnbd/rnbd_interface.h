/**
 * RNBD Generated Driver Instance Header File
 * 
 * @file rnbd_interface.h
 * 
 * @defgroup rnbd_interface RNBD_INTERFACE
 * 
 * @brief This is the generated driver instance header file for the RNBD driver using RNBD
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

#ifndef RNBD_INTERFACE_H
#define	RNBD_INTERFACE_H

#include <stdbool.h>
#include <stdint.h>


/**
 * @ingroup rnbd_interface
 * @enum RNBD_SYSTEM_MODES_t
 * @brief Enum of the RNBD System Configuration Modes
 */
typedef enum
{
    TEST_MODE           = 0x00,
    APPLICATION_MODE    = 0x01 
}RNBD_SYSTEM_MODES_t;

/**
 * @ingroup rnbd_interface
 * @struct iRNBD_FunctionPtrs_t
 * @brief Struct of RNBD Interface Function Pointer Prototypes
 */
typedef struct
{
    // RNBD UART interface control
    void (*Write)(uint8_t);
    uint8_t (*Read)(void);
    bool (*TransmitReady)(void);
    bool (*DataReady)(void);
    // RNBD RX_IND pin control
    void (*RxIndicate)(bool);
    // RNBD Reset pin control
    void (*ResetModule)(bool);
    // RNBD Mode pin set
    void (*SystemModeSet)(RNBD_SYSTEM_MODES_t);
    // Delay API
    void (*DelayMs)(uint16_t);
    // Status Message Handler
    void (*AsyncHandler)(char*);
}iRNBD_FunctionPtrs_t;

extern const iRNBD_FunctionPtrs_t RNBD;

/**
 * @ingroup rnbd_interface
 * @brief Checks Connected State of RNBD
 * @retval true - Connected
 * @retval false - Not Connected
 */
bool RNBD_IsConnected(void);

/**
 * @ingroup rnbd_interface
 * @brief Checks OTA Connected State of RNBD
 * @retval true - Connected
 * @retval false - Not Connected
 */
bool RNBD_IsOTAComplete(void);

#endif	/* RNBD_INTERFACE_H */