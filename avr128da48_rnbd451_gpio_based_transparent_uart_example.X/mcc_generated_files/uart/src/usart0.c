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


#include "../usart0.h"
#define RECEIVE_ERROR_MASK 0x46


static void DefaultFramingErrorCallback(void);
static void DefaultOverrunErrorCallback(void);
static void DefaultParityErrorCallback(void);
void (*USART0_rx_isr_cb)(void) = &USART0_DefaultRxIsrCb;
void (*USART0_tx_isr_cb)(void) = &USART0_DefaultTxIsrCb;
void (*USART0_framing_err_cb)(void) = &DefaultFramingErrorCallback;
void (*USART0_overrun_err_cb)(void) = &DefaultOverrunErrorCallback;
void (*USART0_parity_err_cb)(void) = &DefaultParityErrorCallback;

const struct UART_INTERFACE USART0_Interface = {
  .Initialize = USART0_Initialize,
  .Write = USART0_Write,
  .Read = USART0_Read,
  .RxCompleteCallbackRegister = USART0_SetRXISRCb,
  .TxCompleteCallbackRegister = USART0_SetTXISRCb,
  .ErrorCallbackRegister = NULL,
  .FramingErrorCallbackRegister = USART0_FramingErrorCallbackRegister,
  .OverrunErrorCallbackRegister = USART0_OverrunErrorCallbackRegister,
  .ParityErrorCallbackRegister = USART0_ParityErrorCallbackRegister,
  .ChecksumErrorCallbackRegister = NULL,
  .IsRxReady = USART0_IsRxReady,
  .IsTxReady = USART0_IsTxReady,
  .IsTxDone = USART0_IsTxDone
};

/* Static Variables holding the ringbuffer used in IRQ mode */
static uint8_t          USART0_rxbuf[USART0_RX_BUFFER_SIZE];
static volatile uint8_t USART0_rx_head;
static volatile uint8_t USART0_rx_tail;
static volatile uint8_t USART0_rx_elements;
static uint8_t          USART0_txbuf[USART0_TX_BUFFER_SIZE];
static volatile uint8_t USART0_tx_head;
static volatile uint8_t USART0_tx_tail;
static volatile uint8_t USART0_tx_elements;

void USART0_ErrorCheck(void)
{
    uint8_t errorMask = USART0.RXDATAH;
    if(errorMask & RECEIVE_ERROR_MASK)
    {
        if(errorMask & USART_PERR_bm)
        {
            USART0_parity_err_cb();
        } 
        if(errorMask & USART_FERR_bm)
        {
            USART0_framing_err_cb();
        }
        if(errorMask & USART_BUFOVF_bm)
        {
            USART0_overrun_err_cb();
        }
    }
    
}

void USART0_DefaultRxIsrCb(void)
{
    uint8_t data;
    uint8_t tmphead;
    USART0_ErrorCheck();
    
    /* Read the received data */
    data = USART0.RXDATAL;
    /* Calculate buffer index */
    tmphead = (USART0_rx_head + 1) & USART0_RX_BUFFER_MASK;
        
    if (tmphead == USART0_rx_tail) {
            /* ERROR! Receive buffer overflow */
    }else {
    /*Store new index*/
    USART0_rx_head = tmphead;
    
    /* Store received data in buffer */
    USART0_rxbuf[tmphead] = data;
    USART0_rx_elements++;
    }
}

static void DefaultFramingErrorCallback(void)
{
    /* Add your interrupt code here or use USART0.FramingCallbackRegister function to use Custom ISR */
}

static void DefaultOverrunErrorCallback(void)
{
    /* Add your interrupt code here or use USART0.OverrunCallbackRegister function to use Custom ISR */
}

static void DefaultParityErrorCallback(void)
{
    /* Add your interrupt code here or use USART0.ParityCallbackRegister function to use Custom ISR */
}

void USART0_DefaultTxIsrCb(void)
{
    uint8_t tmptail;

    /* Check if all data is transmitted */
    if (USART0_tx_elements != 0) {
        /* Calculate buffer index */
        tmptail = (USART0_tx_tail + 1) & USART0_TX_BUFFER_MASK;
        /* Store new index */
        USART0_tx_tail = tmptail;
        /* Start transmission */
        USART0.TXDATAL = USART0_txbuf[tmptail];
        
        USART0_tx_elements--;
    }

    if (USART0_tx_elements == 0) {
            /* Disable Tx interrupt */
            USART0.CTRLA &= ~(1 << USART_DREIE_bp);
    }
}

void USART0_SetISRCb(usart_callback cb, usart0_cb_t type)
{
    switch (type) {
        case USART0_RX_CB:
                USART0_rx_isr_cb = cb;
                break;
        case USART0_TX_CB:
                USART0_tx_isr_cb = cb;
                break;
        default:
                // do nothing
                break;
    }
}

void USART0_SetRXISRCb(usart_callback cb)
{
    USART0_SetISRCb(cb,USART0_RX_CB);
}

void USART0_SetTXISRCb(usart_callback cb)
{
    USART0_SetISRCb(cb,USART0_TX_CB);
}

void USART0_FramingErrorCallbackRegister(void* callbackHandler)
{
    USART0_framing_err_cb=callbackHandler;
}

void USART0_OverrunErrorCallbackRegister(void* callbackHandler)
{
    USART0_overrun_err_cb=callbackHandler;
}

void USART0_ParityErrorCallbackRegister(void* callbackHandler)
{
    USART0_parity_err_cb=callbackHandler;
}

/* Interrupt service routine for RX complete */
ISR(USART0_RXC_vect)
{
    if (USART0_rx_isr_cb != NULL)
    {
        (*USART0_rx_isr_cb)();
    }
}

/* Interrupt service routine for Data Register Empty */
ISR(USART0_DRE_vect)
{
    if (USART0_tx_isr_cb != NULL)
    {
        (*USART0_tx_isr_cb)();
    }
}

ISR(USART0_TXC_vect)
{
    USART0.STATUS |= USART_TXCIF_bm;
}

bool USART0_IsTxReady(void)
{
    return (USART0_tx_elements != USART0_TX_BUFFER_SIZE);
}

bool USART0_IsRxReady(void)
{
    return (USART0_rx_elements != 0);
}

bool USART0_IsTxBusy(void)
{
    return (!(USART0.STATUS & USART_TXCIF_bm));
}

bool USART0_IsTxDone(void)
{       
    return (USART0.STATUS & USART_TXCIF_bm);
}

uint8_t USART0_Read(void)
{
    uint8_t tmptail;

    /* Wait for incoming data */
    while (USART0_rx_elements == 0)
            ;
    /* Calculate buffer index */
    tmptail = (USART0_rx_tail + 1) & USART0_RX_BUFFER_MASK;
    /* Store new index */
    USART0_rx_tail = tmptail;
    ENTER_CRITICAL(R);
    USART0_rx_elements--;
    EXIT_CRITICAL(R);

    /* Return data */
    return USART0_rxbuf[tmptail];
}

void USART0_Write(const uint8_t data)
{
    uint8_t tmphead;

    /* Calculate buffer index */
    tmphead = (USART0_tx_head + 1) & USART0_TX_BUFFER_MASK;
    /* Wait for free space in buffer */
    while (USART0_tx_elements == USART0_TX_BUFFER_SIZE)
            ;
    /* Store data in buffer */
    USART0_txbuf[tmphead] = data;
    /* Store new index */
    USART0_tx_head = tmphead;
    ENTER_CRITICAL(W);
    USART0_tx_elements++;
    EXIT_CRITICAL(W);
    /* Enable Tx interrupt */
    USART0.CTRLA |= (1 << USART_DREIE_bp);
}

void USART0_Initialize(void)
{
    //set baud rate register
    USART0.BAUD = (uint16_t)USART0_BAUD_RATE(115200);
	
    // ABEIE disabled; DREIE disabled; LBME disabled; RS485 DISABLE; RXCIE enabled; RXSIE enabled; TXCIE enabled; 
    USART0.CTRLA = 0xD0;
	
    // MPCM disabled; ODME disabled; RXEN enabled; RXMODE NORMAL; SFDEN disabled; TXEN enabled; 
    USART0.CTRLB = 0xC0;
	
    // CMODE Asynchronous Mode; UCPHA enabled; UDORD disabled; CHSIZE Character size: 8 bit; PMODE No Parity; SBMODE 1 stop bit; 
    USART0.CTRLC = 0x3;
	
    //DBGCTRL_DBGRUN
    USART0.DBGCTRL = 0x0;
	
    //EVCTRL_IREI
    USART0.EVCTRL = 0x0;
	
    //RXPLCTRL_RXPL
    USART0.RXPLCTRL = 0x0;
	
    //TXPLCTRL_TXPL
    USART0.TXPLCTRL = 0x0;
	

    uint8_t x;

    /* Initialize ringbuffers */
    x = 0;

    USART0_rx_tail     = x;
    USART0_rx_head     = x;
    USART0_rx_elements = x;
    USART0_tx_tail     = x;
    USART0_tx_head     = x;
    USART0_tx_elements = x;

}

void USART0_Enable(void)
{
    USART0.CTRLB |= USART_RXEN_bm | USART_TXEN_bm;
}

void USART0_EnableRx(void)
{
    USART0.CTRLB |= USART_RXEN_bm;
}

void USART0_EnableTx(void)
{
    USART0.CTRLB |= USART_TXEN_bm;
}

void USART0_Disable(void)
{
    USART0.CTRLB &= ~(USART_RXEN_bm | USART_TXEN_bm);
}

uint8_t USART0_GetData(void)
{
    return USART0.RXDATAL;
}