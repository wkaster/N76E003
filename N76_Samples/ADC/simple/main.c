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


unsigned int ADC_read(void)
{
	register unsigned int value = 0x0000;
	  
	clr_ADCF;
	set_ADCS;									
	while(ADCF == 0);
	  
	value = ADCRH;
	value <<= 4;
	value |= ADCRL;
	  
	return value;
}


void main (void) 
{
	unsigned int ADCValue;
	float fVoltage;
	InitialUART0_Timer3(115200);
	TI = 1;
	
	/* Enable AIN0 pin for ADC read */
	Enable_ADC_AIN0;
		
	while(1)
	{
		ADCValue = ADC_read();

		/* warning: considering 5v VDD and no calibration */
		fVoltage = ((float) ADCValue * 5) / 4095;
	
		printf_fast_f("\n Voltage: %.3f", fVoltage);
		
		Timer0_Delay1ms(500);
	}
}
