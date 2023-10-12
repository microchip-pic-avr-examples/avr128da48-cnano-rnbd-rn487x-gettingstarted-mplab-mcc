/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 1.1.0
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

#include "../pins.h"

static void (*IO_PA1_InterruptHandler)(void);
static void (*IO_PA0_InterruptHandler)(void);
static void (*IO_PC1_InterruptHandler)(void);
static void (*IO_PC0_InterruptHandler)(void);
static void (*BT_RST_InterruptHandler)(void);

void PIN_MANAGER_Initialize()
{
  /* DIR Registers Initialization */
    PORTA.DIR = 0x1;
    PORTB.DIR = 0x0;
    PORTC.DIR = 0x1;
    PORTD.DIR = 0x80;
    PORTE.DIR = 0x0;
    PORTF.DIR = 0x0;

  /* OUT Registers Initialization */
    PORTA.OUT = 0x0;
    PORTB.OUT = 0x0;
    PORTC.OUT = 0x0;
    PORTD.OUT = 0x80;
    PORTE.OUT = 0x0;
    PORTF.OUT = 0x0;

  /* PINxCTRL registers Initialization */
    PORTA.PIN0CTRL = 0x1;
    PORTA.PIN1CTRL = 0x1;
    PORTA.PIN2CTRL = 0x0;
    PORTA.PIN3CTRL = 0x0;
    PORTA.PIN4CTRL = 0x0;
    PORTA.PIN5CTRL = 0x0;
    PORTA.PIN6CTRL = 0x0;
    PORTA.PIN7CTRL = 0x0;
    PORTB.PIN0CTRL = 0x0;
    PORTB.PIN1CTRL = 0x0;
    PORTB.PIN2CTRL = 0x0;
    PORTB.PIN3CTRL = 0x0;
    PORTB.PIN4CTRL = 0x0;
    PORTB.PIN5CTRL = 0x0;
    PORTB.PIN6CTRL = 0x0;
    PORTB.PIN7CTRL = 0x0;
    PORTC.PIN0CTRL = 0x1;
    PORTC.PIN1CTRL = 0x1;
    PORTC.PIN2CTRL = 0x0;
    PORTC.PIN3CTRL = 0x0;
    PORTC.PIN4CTRL = 0x0;
    PORTC.PIN5CTRL = 0x0;
    PORTC.PIN6CTRL = 0x0;
    PORTC.PIN7CTRL = 0x0;
    PORTD.PIN0CTRL = 0x0;
    PORTD.PIN1CTRL = 0x0;
    PORTD.PIN2CTRL = 0x0;
    PORTD.PIN3CTRL = 0x0;
    PORTD.PIN4CTRL = 0x0;
    PORTD.PIN5CTRL = 0x0;
    PORTD.PIN6CTRL = 0x0;
    PORTD.PIN7CTRL = 0x9;
    PORTE.PIN0CTRL = 0x0;
    PORTE.PIN1CTRL = 0x0;
    PORTE.PIN2CTRL = 0x0;
    PORTE.PIN3CTRL = 0x0;
    PORTE.PIN4CTRL = 0x0;
    PORTE.PIN5CTRL = 0x0;
    PORTE.PIN6CTRL = 0x0;
    PORTE.PIN7CTRL = 0x0;
    PORTF.PIN0CTRL = 0x0;
    PORTF.PIN1CTRL = 0x0;
    PORTF.PIN2CTRL = 0x0;
    PORTF.PIN3CTRL = 0x0;
    PORTF.PIN4CTRL = 0x0;
    PORTF.PIN5CTRL = 0x0;
    PORTF.PIN6CTRL = 0x0;
    PORTF.PIN7CTRL = 0x0;

  /* EVGENCTRL registers Initialization */

  /* PORTMUX Initialization */
    PORTMUX.ACROUTEA = 0x0;
    PORTMUX.CCLROUTEA = 0x0;
    PORTMUX.EVSYSROUTEA = 0x0;
    PORTMUX.SPIROUTEA = 0x0;
    PORTMUX.TCAROUTEA = 0x0;
    PORTMUX.TCBROUTEA = 0x0;
    PORTMUX.TCDROUTEA = 0x0;
    PORTMUX.TWIROUTEA = 0x0;
    PORTMUX.USARTROUTEA = 0x0;
    PORTMUX.USARTROUTEB = 0x0;
    PORTMUX.ZCDROUTEA = 0x0;

  // register default ISC callback functions at runtime; use these methods to register a custom function
    IO_PA1_SetInterruptHandler(IO_PA1_DefaultInterruptHandler);
    IO_PA0_SetInterruptHandler(IO_PA0_DefaultInterruptHandler);
    IO_PC1_SetInterruptHandler(IO_PC1_DefaultInterruptHandler);
    IO_PC0_SetInterruptHandler(IO_PC0_DefaultInterruptHandler);
    BT_RST_SetInterruptHandler(BT_RST_DefaultInterruptHandler);
}

/**
  Allows selecting an interrupt handler for IO_PA1 at application runtime
*/
void IO_PA1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PA1_InterruptHandler = interruptHandler;
}

void IO_PA1_DefaultInterruptHandler(void)
{
    // add your IO_PA1 interrupt custom code
    // or set custom function using IO_PA1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PA0 at application runtime
*/
void IO_PA0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PA0_InterruptHandler = interruptHandler;
}

void IO_PA0_DefaultInterruptHandler(void)
{
    // add your IO_PA0 interrupt custom code
    // or set custom function using IO_PA0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PC1 at application runtime
*/
void IO_PC1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PC1_InterruptHandler = interruptHandler;
}

void IO_PC1_DefaultInterruptHandler(void)
{
    // add your IO_PC1 interrupt custom code
    // or set custom function using IO_PC1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PC0 at application runtime
*/
void IO_PC0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PC0_InterruptHandler = interruptHandler;
}

void IO_PC0_DefaultInterruptHandler(void)
{
    // add your IO_PC0 interrupt custom code
    // or set custom function using IO_PC0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for BT_RST at application runtime
*/
void BT_RST_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    BT_RST_InterruptHandler = interruptHandler;
}

void BT_RST_DefaultInterruptHandler(void)
{
    // add your BT_RST interrupt custom code
    // or set custom function using BT_RST_SetInterruptHandler()
}
ISR(PORTA_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTA.INTFLAGS & PORT_INT1_bm)
    {
       IO_PA1_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT0_bm)
    {
       IO_PA0_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTA.INTFLAGS = 0xff;
}

ISR(PORTB_PORT_vect)
{ 
    /* Clear interrupt flags */
    VPORTB.INTFLAGS = 0xff;
}

ISR(PORTC_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTC.INTFLAGS & PORT_INT1_bm)
    {
       IO_PC1_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT0_bm)
    {
       IO_PC0_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTC.INTFLAGS = 0xff;
}

ISR(PORTD_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTD.INTFLAGS & PORT_INT7_bm)
    {
       BT_RST_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTD.INTFLAGS = 0xff;
}

ISR(PORTE_PORT_vect)
{ 
    /* Clear interrupt flags */
    VPORTE.INTFLAGS = 0xff;
}

ISR(PORTF_PORT_vect)
{ 
    /* Clear interrupt flags */
    VPORTF.INTFLAGS = 0xff;
}

/**
 End of File
*/