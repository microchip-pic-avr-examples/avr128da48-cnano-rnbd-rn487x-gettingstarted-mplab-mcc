/**
  @Company
    Microchip Technology Inc.

  @Description
    This Source file provides APIs.
    Generation Information :
    Driver Version    :   1.0.0
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


#ifndef USART1_H
#define USART1_H

#include <stdbool.h>
#include <stdio.h>
#include "../system/utils/compiler.h"
#include "../system/utils/atomic.h"
#include "../system/clock.h"
#include "uart_interface.h"

/* Normal Mode, Baud register value */
#define USART1_BAUD_RATE(BAUD_RATE) (((float)10000000 * 64 / (16 * (float)BAUD_RATE)) + 0.5)

/* USART1 Ringbuffer */

#define USART1_RX_BUFFER_SIZE 64
#define USART1_TX_BUFFER_SIZE 64
#define USART1_RX_BUFFER_MASK (USART1_RX_BUFFER_SIZE - 1)
#define USART1_TX_BUFFER_MASK (USART1_TX_BUFFER_SIZE - 1)

typedef enum { USART1_RX_CB = 1, USART1_TX_CB } usart1_cb_t;
typedef void (*usart_callback)(void);
extern const struct UART_INTERFACE USART1_Interface;

/**
 * \brief Initialize USART interface
 * If module is configured to disabled state, the clock to the USART is disabled
 * if this is supported by the device's clock system.
 *
 * \return Initialization status.
 * \retval 0 the USART init was successful
 * \retval 1 the USART init was not successful
 */
void USART1_Initialize(void);

/**
 * \brief Enable RX and TX in USART1
 * 1. If supported by the clock system, enables the clock to the USART
 * 2. Enables the USART module by setting the RX and TX enable-bits in the USART control register
 *
 * \return Nothing
 */
void USART1_Enable(void);

/**
 * \brief Enable RX in USART1
 * 1. If supported by the clock system, enables the clock to the USART
 * 2. Enables the USART module by setting the RX enable-bit in the USART control register
 *
 * \return Nothing
 */
void USART1_EnableRx(void);

/**
 * \brief Enable TX in USART1
 * 1. If supported by the clock system, enables the clock to the USART
 * 2. Enables the USART module by setting the TX enable-bit in the USART control register
 *
 * \return Nothing
 */
void USART1_EnableTx(void);

/**
 * \brief Disable USART1
 * 1. Disables the USART module by clearing the enable-bit(s) in the USART control register
 * 2. If supported by the clock system, disables the clock to the USART
 *
 * \return Nothing
 */
void USART1_Disable(void);

/**
 * \brief Get recieved data from USART1
 *
 * \return Data register from USART1 module
 */
uint8_t USART1_GetData(void);

/**
 * \brief Check if the usart can accept data to be transmitted
 *
 * \return The status of USART TX data ready check
 * \retval false The USART can not receive data to be transmitted
 * \retval true The USART can receive data to be transmitted
 */
bool USART1_IsTxReady(void);

/**
 * \brief Check if the USART has received data
 *
 * \return The status of USART RX data ready check
 * \retval true The USART has received data
 * \retval false The USART has not received data
 */
bool USART1_IsRxReady(void);

/**
 * \brief Check if USART1 data is transmitted
 *
 * \return Receiver ready status
 * \retval true  Data is not completely shifted out of the shift register
 * \retval false Data completely shifted out if the USART shift register
 */
bool USART1_IsTxBusy(void);

bool USART1_IsTxDone(void);
/**
 * \brief Read one character from USART1
 *
 * Function will block if a character is not available.
 *
 * \return Data read from the USART1 module
 */
uint8_t USART1_Read(void);

/**
 * \brief Write one character to USART1
 *
 * Function will block until a character can be accepted.
 *
 * \param[in] data The character to write to the USART
 *
 * \return Nothing
 */
void USART1_Write(const uint8_t data);

/**
 * \brief ErrorCheck USART interface
 *
 * Checks the Recieve Error for Parity, Framing, OverRun
 *
 * No Return and Arguments associated
 */
void USART1_ErrorCheck(void);

/**
 * \brief Set call back function for USART1
 *
 * \param[in] cb The call back function to set
 *
 * \param[in] type The type of ISR to be set
 *
 * \return Nothing
 */
 
void USART1_DefaultRxIsrCb(void);

void USART1_DefaultTxIsrCb(void);

void USART1_SetISRCb(usart_callback cb, usart1_cb_t type);

void USART1_SetRXISRCb(usart_callback cb);

void USART1_SetTXISRCb(usart_callback cb);

void USART1_FramingErrorCallbackRegister(void* callbackHandler);

void USART1_OverrunErrorCallbackRegister(void* callbackHandler);

void USART1_ParityErrorCallbackRegister(void* callbackHandler);

#endif /* USART1_H */