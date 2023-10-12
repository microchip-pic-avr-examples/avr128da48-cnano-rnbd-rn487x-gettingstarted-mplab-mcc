/**
 * \file rnbd_example.c
 * \brief This file contains the APIs required to communicate with the RNBD driver library to 
 *        create, and open a basic Transparent EUSART demonstration.
 */  
/*
    (c) 2022 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include <stdbool.h>
#include "rnbd_example.h"
#include "../../mcc_generated_files/uart/usart1.h"
#include "../rnbd/rnbd_interface.h"
#include "../rnbd/rnbd.h"
#include <util/delay.h>

/** MACRO used to configure the application used buffer sizes.
 *  This is used by the application for communication buffers.
 */
#define MAX_BUFFER_SIZE                 (80)

bool returnval = false;

/**< Status Buffer instance passed to RNBD drive used for Asynchronous Message Handling (see *RNBD_AsyncMessageHandlerSet in rnbd.c) */
static char statusBuffer[MAX_BUFFER_SIZE];    

/**
 * \ingroup RNBD_Example
 * \brief Example Implmentation of Transparent UART
 *        This can be connected to a Smart BLE 'Terminal' 
 *        application for simple data exchange demostration.
 *
 * For more details, refer RNBD user guide.
 * \return Connected Status
 * \retval true - Connected.
 * \retval false - Not Connected
 */  
static bool RNBD_Example_TransparentUart(void);
/**
 * \ingroup RNBD_Example_Run
 * \brief This 'Runs' the example applications While(1) loop
 *
 * For more details, refer  RNBD user guide.
 * \param none
 * \return void
 */  
static void RNBD_Example_Run(void);

bool RNBD_Example_Initialized(void)
{
    bool exampleIsInitialized = false;
    
    exampleIsInitialized = RNBD_AsyncMessageHandlerSet(statusBuffer, sizeof(statusBuffer));

    RNBD_Init();

    _delay_ms(300);


    uint16_t GR_HexByte=0;
    returnval = RNBD_EnterCmdMode();
    _delay_ms(50);
    
	if(returnval == true)
	{
		GR_HexByte=RNBD_GetGRCommand();
		if((GR_HexByte & 0x1000) == 0x0000)
		{
			GR_HexByte|= 0x1000;
			RNBD_SetFeaturesBitmap(GR_HexByte);
			_delay_ms(50);

			RNBD_RebootCmd();
			_delay_ms(300);
		}
		else
		{
			RNBD_EnterDataMode();
			_delay_ms(50);
		}
		
		if (exampleIsInitialized == true)
		{
			RNBD_Example_Run();
		}
	}
    else
    {
        return false;
    } 

}

static void RNBD_Example_Run(void)
{
    while(1)
    {
        if (true == RNBD_Example_TransparentUart())
        {
            // Connected
        }
        else
        {
            // Not Connected
        }
    }
}

static bool RNBD_Example_TransparentUart(void)
{
   bool isConnected,isOTAComplete;
   isConnected = RNBD_IsConnected();
   isOTAComplete = RNBD_IsOTAComplete();

   if (true == isConnected && false == isOTAComplete)
   {
       while (RNBD_isDataReady())
       {
           USART1_Write(RNBD_Read());
       }
       while (USART1_IsRxReady())
       {
           RNBD.Write(USART1_Read());
       }
   }
   else
    {
        while(RNBD_isDataReady())
        {
            USART1_Write(RNBD_Read());
        }
        while (USART1_IsRxReady())
        {
            RNBD.Write(USART1_Read());
        }
    }

    return isConnected;
}
