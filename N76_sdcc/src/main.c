/*---------------------------------------------------------------------------------------------------------*/
/* SDCC simple "Hello World" UART0 for Nuvoton N76E003                                                     */
/* Just connect any serial adapter on N76 ports P.06 and P.07 and view the result in PC serial monitor     */
/* P0.6 [TX] -> FTDI [RX]                                                                                  */
/* P0.7 [RX] <- FTDI [TX]                                                                                  */
/* Adapted from Nuvoton's UART0_Printf sample code                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

/* Needed for printf */
int putchar (int c) {
  while (!TI);
  TI = 0;
  SBUF = c;
  return c;
}


/*==========================================================================*/
void main (void) 
{
	  InitialUART0_Timer3(115200);
	  TI = 1;															// Important, use prinft function must set TI=1;
	
		while(1)
		{
			printf_small("\n Hello world");
			Timer0_Delay1ms(300);
		}
}
