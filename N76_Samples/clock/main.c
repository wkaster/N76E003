#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"


void main (void) 
{
	Set_All_GPIO_Quasi_Mode;
	set_CLOEN;	// System Clock Output Enable -  P1.1 for measure
	
	while(1) {
		CKDIV = 0x00;	// System Clock 16Mhz
		Timer0_Delay1ms(6000);
		CKDIV = 0x01;	// System Clock 8Mhz (div. by 2)
		Timer0_Delay1ms(3000); // less clock more time will take: compensating.
		CKDIV = 0x02;	// System Clock 4Mhz (div. by 4)
		Timer0_Delay1ms(1500);
		
		CKDIV = 0x00;	// System Clock normal (div. by one)
		
		set_OSC1;	// switching system clock source to LIRC
		clr_OSC0;  
		
		while((CKEN&SET_BIT0)==1);  // Check clock switch fault flag OK (only works HIRC to LIRC)
		clr_HIRCEN;  // This will disable HIRC, probably power consumption will decresse (optional)
		Timer0_Delay1ms(10);
		
		set_HIRCEN;  // enable HIRC
		set_OSC0;	// switching system clock source to HIRC
		clr_OSC1;
	}
}
