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


#include "../usart1.h"
#define RECEIVE_ERROR_MASK 0x46


static void DefaultFramingErrorCallback(void);
static void DefaultOverrunErrorCallback(void);
static void DefaultParityErrorCallback(void);
void (*USART1_rx_isr_cb)(void) = &USART1_DefaultRxIsrCb;
void (*USART1_tx_isr_cb)(void) = &USART1_DefaultTxIsrCb;
void (*USART1_framing_err_cb)(void) = &DefaultFramingErrorCallback;
void (*USART1_overrun_err_cb)(void) = &DefaultOverrunErrorCallback;
void (*USART1_parity_err_cb)(void) = &DefaultParityErrorCallback;

const struct UART_INTERFACE USART1_Interface = {
  .Initialize = USART1_Initialize,
  .Write = USART1_Write,
  .Read = USART1_Read,
  .RxCompleteCallbackRegister = USART1_SetRXISRCb,
  .TxCompleteCallbackRegister = USART1_SetTXISRCb,
  .ErrorCallbackRegister = NULL,
  .FramingErrorCallbackRegister = USART1_FramingErrorCallbackRegister,
  .OverrunErrorCallbackRegister = USART1_OverrunErrorCallbackRegister,
  .ParityErrorCallbackRegister = USART1_ParityErrorCallbackRegister,
  .ChecksumErrorCallbackRegister = NULL,
  .IsRxReady = USART1_IsRxReady,
  .IsTxReady = USART1_IsTxReady,
  .IsTxDone = USART1_IsTxDone
};

/* Static Variables holding the ringbuffer used in IRQ mode */
static uint8_t          USART1_rxbuf[USART1_RX_BUFFER_SIZE];
static volatile uint8_t USART1_rx_head;
static volatile uint8_t USART1_rx_tail;
static volatile uint8_t USART1_rx_elements;
static uint8_t          USART1_txbuf[USART1_TX_BUFFER_SIZE];
static volatile uint8_t USART1_tx_head;
static volatile uint8_t USART1_tx_tail;
static volatile uint8_t USART1_tx_elements;

void USART1_ErrorCheck(void)
{
    uint8_t errorMask = USART1.RXDATAH;
    if(errorMask & RECEIVE_ERROR_MASK)
    {
        if(errorMask & USART_PERR_bm)
        {
            USART1_parity_err_cb();
        } 
        if(errorMask & USART_FERR_bm)
        {
            USART1_framing_err_cb();
        }
        if(errorMask & USART_BUFOVF_bm)
        {
            USART1_overrun_err_cb();
        }
    }
    
}

void USART1_DefaultRxIsrCb(void)
{
    uint8_t data;
    uint8_t tmphead;
    USART1_ErrorCheck();
    
    /* Read the received data */
    data = USART1.RXDATAL;
    /* Calculate buffer index */
    tmphead = (USART1_rx_head + 1) & USART1_RX_BUFFER_MASK;
        
    if (tmphead == USART1_rx_tail) {
            /* ERROR! Receive buffer overflow */
    }else {
    /*Store new index*/
    USART1_rx_head = tmphead;
    
    /* Store received data in buffer */
    USART1_rxbuf[tmphead] = data;
    USART1_rx_elements++;
    }
}

static void DefaultFramingErrorCallback(void)
{
    /* Add your interrupt code here or use USART1.FramingCallbackRegister function to use Custom ISR */
}

static void DefaultOverrunErrorCallback(void)
{
    /* Add your interrupt code here or use USART1.OverrunCallbackRegister function to use Custom ISR */
}

static void DefaultParityErrorCallback(void)
{
    /* Add your interrupt code here or use USART1.ParityCallbackRegister function to use Custom ISR */
}

void USART1_DefaultTxIsrCb(void)
{
    uint8_t tmptail;

    /* Check if all data is transmitted */
    if (USART1_tx_elements != 0) {
        /* Calculate buffer index */
        tmptail = (USART1_tx_tail + 1) & USART1_TX_BUFFER_MASK;
        /* Store new index */
        USART1_tx_tail = tmptail;
        /* Start transmission */
        USART1.TXDATAL = USART1_txbuf[tmptail];
        
        USART1_tx_elements--;
    }

    if (USART1_tx_elements == 0) {
            /* Disable Tx interrupt */
            USART1.CTRLA &= ~(1 << USART_DREIE_bp);
    }
}

void USART1_SetISRCb(usart_callback cb, usart1_cb_t type)
{
    switch (type) {
        case USART1_RX_CB:
                USART1_rx_isr_cb = cb;
                break;
        case USART1_TX_CB:
                USART1_tx_isr_cb = cb;
                break;
        default:
                // do nothing
                break;
    }
}

void USART1_SetRXISRCb(usart_callback cb)
{
    USART1_SetISRCb(cb,USART1_RX_CB);
}

void USART1_SetTXISRCb(usart_callback cb)
{
    USART1_SetISRCb(cb,USART1_TX_CB);
}

void USART1_FramingErrorCallbackRegister(void* callbackHandler)
{
    USART1_framing_err_cb=callbackHandler;
}

void USART1_OverrunErrorCallbackRegister(void* callbackHandler)
{
    USART1_overrun_err_cb=callbackHandler;
}

void USART1_ParityErrorCallbackRegister(void* callbackHandler)
{
    USART1_parity_err_cb=callbackHandler;
}

/* Interrupt service routine for RX complete */
ISR(USART1_RXC_vect)
{
    if (USART1_rx_isr_cb != NULL)
    {
        (*USART1_rx_isr_cb)();
    }
}

/* Interrupt service routine for Data Register Empty */
ISR(USART1_DRE_vect)
{
    if (USART1_tx_isr_cb != NULL)
    {
        (*USART1_tx_isr_cb)();
    }
}

ISR(USART1_TXC_vect)
{
    USART1.STATUS |= USART_TXCIF_bm;
}

bool USART1_IsTxReady(void)
{
    return (USART1_tx_elements != USART1_TX_BUFFER_SIZE);
}

bool USART1_IsRxReady(void)
{
    return (USART1_rx_elements != 0);
}

bool USART1_IsTxBusy(void)
{
    return (!(USART1.STATUS & USART_TXCIF_bm));
}

bool USART1_IsTxDone(void)
{       
    return (USART1.STATUS & USART_TXCIF_bm);
}

uint8_t USART1_Read(void)
{
    uint8_t tmptail;

    /* Wait for incoming data */
    while (USART1_rx_elements == 0)
            ;
    /* Calculate buffer index */
    tmptail = (USART1_rx_tail + 1) & USART1_RX_BUFFER_MASK;
    /* Store new index */
    USART1_rx_tail = tmptail;
    ENTER_CRITICAL(R);
    USART1_rx_elements--;
    EXIT_CRITICAL(R);

    /* Return data */
    return USART1_rxbuf[tmptail];
}

void USART1_Write(const uint8_t data)
{
    uint8_t tmphead;

    /* Calculate buffer index */
    tmphead = (USART1_tx_head + 1) & USART1_TX_BUFFER_MASK;
    /* Wait for free space in buffer */
    while (USART1_tx_elements == USART1_TX_BUFFER_SIZE)
            ;
    /* Store data in buffer */
    USART1_txbuf[tmphead] = data;
    /* Store new index */
    USART1_tx_head = tmphead;
    ENTER_CRITICAL(W);
    USART1_tx_elements++;
    EXIT_CRITICAL(W);
    /* Enable Tx interrupt */
    USART1.CTRLA |= (1 << USART_DREIE_bp);
}

void USART1_Initialize(void)
{
    //set baud rate register
    USART1.BAUD = (uint16_t)USART1_BAUD_RATE(115200);
	
    // ABEIE disabled; DREIE disabled; LBME disabled; RS485 DISABLE; RXCIE enabled; RXSIE enabled; TXCIE enabled; 
    USART1.CTRLA = 0xD0;
	
    // MPCM disabled; ODME disabled; RXEN enabled; RXMODE NORMAL; SFDEN disabled; TXEN enabled; 
    USART1.CTRLB = 0xC0;
	
    // CMODE Asynchronous Mode; UCPHA enabled; UDORD disabled; CHSIZE Character size: 8 bit; PMODE No Parity; SBMODE 1 stop bit; 
    USART1.CTRLC = 0x3;
	
    //DBGCTRL_DBGRUN
    USART1.DBGCTRL = 0x0;
	
    //EVCTRL_IREI
    USART1.EVCTRL = 0x0;
	
    //RXPLCTRL_RXPL
    USART1.RXPLCTRL = 0x0;
	
    //TXPLCTRL_TXPL
    USART1.TXPLCTRL = 0x0;
	

    uint8_t x;

    /* Initialize ringbuffers */
    x = 0;

    USART1_rx_tail     = x;
    USART1_rx_head     = x;
    USART1_rx_elements = x;
    USART1_tx_tail     = x;
    USART1_tx_head     = x;
    USART1_tx_elements = x;

}

void USART1_Enable(void)
{
    USART1.CTRLB |= USART_RXEN_bm | USART_TXEN_bm;
}

void USART1_EnableRx(void)
{
    USART1.CTRLB |= USART_RXEN_bm;
}

void USART1_EnableTx(void)
{
    USART1.CTRLB |= USART_TXEN_bm;
}

void USART1_Disable(void)
{
    USART1.CTRLB &= ~(USART_RXEN_bm | USART_TXEN_bm);
}

uint8_t USART1_GetData(void)
{
    return USART1.RXDATAL;
}