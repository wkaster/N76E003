#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"

/* Needed for printf */
int putchar (int c) {
  while (!TI);
  TI = 0;
  SBUF = c;
  return c;
}


void WakeUp_Timer_ISR (void) __interrupt 17 			//ISR for self wake up timer
{
	printf("Wake up timer interrupt service routine called!\n");
	clr_WKTF; 											//WKT overflow flag: clear interrupt flag   
}


void main (void)
{
	InitialUART0_Timer3(115200);
   
	printf("Program start, configure Wake-up Timer\n");
	
//-----------------------------------------------------
//	WKT init	
//-----------------------------------------------------	
	WKCON = 0x04; 										// timer base 10kHz, Pre-scale = 1/256
	RWK = 0x00;											// WKT reload byte (aprox. 6.5s with this pre-scale)
	set_EWKT;											// enable WKT interrupt
	set_EA; 											// enable interrupts
	
	while(1) 
	{
		printf("Going to sleep now!\n");
		Timer0_Delay1ms(5);  // give some time to finish output the strig
		set_WKTR; 		// Wake-up timer run 
		set_PD;			// Set Power Down mode (the program will halt here until WKT ISR kicks in)
		clr_WKTR;		// Wake-up timer halt
		printf("Im awake for 3s!\n");
		Timer0_Delay1ms(3000);
	}
}