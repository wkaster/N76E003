/*---------------------------------------------------------------------------------------------------------*/
/* SDCC simple serial ISR UART0 for Nuvoton N76E003                                                        */
/* Just connect any serial adapter on N76 ports P.06 and P.07 and view the result in PC serial monitor     */
/* P0.6 [TX] -> FTDI [RX]                                                                                  */
/* P0.7 [RX] <- FTDI [TX]                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/

#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

unsigned char receivedChar='a';

void serial_isr() __interrupt 4
{ 
    if(RI == 1)
    {
		if(SBUF != '\n') {
			receivedChar = SBUF; 
		}
        RI = 0;              // Clear the Receive interrupt flag
    }
}

void serial_txString(char *ptr)
{
    while(*ptr)
        Send_Data_To_UART0(*ptr++);
}


void main()
{
    InitialUART0_Timer3(115200);
	
	set_ES; // ensable serial interrupt
	set_EA; // enable interrupt
	
	while(1)
	{
		serial_txString("\n Received: ");
		Send_Data_To_UART0(receivedChar);
		Timer0_Delay1ms(500);
	}
}