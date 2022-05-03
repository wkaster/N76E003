/**
Read VDD (supply) voltage
based on Nuvoton's ADC Bandgap VDD average sample
*/
#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"

float Bandgap_Voltage;

/* Needed for printf */
int putchar (int c) {
  while (!TI);
  TI = 0;
  SBUF = c;
  return c;
}


// Read bandgap (vref) 
void READ_BANDGAP()
{
	UINT8 BandgapHigh,BandgapLow,BandgapMark;
	float Bandgap_Value,Bandgap_Voltage_Temp;
	
	set_IAPEN;
	IAPCN = READ_UID;
	IAPAL = 0x0d;
    IAPAH = 0x00;
    set_IAPGO;
	BandgapLow = IAPFD;
	BandgapMark = BandgapLow&0xF0;
		
	if (BandgapMark==0x80)
	{
		BandgapLow = BandgapLow&0x0F;
		IAPAL = 0x0C;
		IAPAH = 0x00;
		set_IAPGO;
		BandgapHigh = IAPFD;
		Bandgap_Value = (BandgapHigh<<4)+BandgapLow;
		Bandgap_Voltage_Temp = Bandgap_Value*3/4;
		Bandgap_Voltage = Bandgap_Voltage_Temp - 33;			//the actually banggap voltage value is similar this value.
	}
	if (BandgapMark==0x00)
	{
		BandgapLow = BandgapLow&0x0F;
		IAPAL = 0x0C;
		IAPAH = 0x00;
		set_IAPGO;
		BandgapHigh = IAPFD;
		Bandgap_Value = (BandgapHigh<<4)+BandgapLow;
		Bandgap_Voltage= Bandgap_Value*3/4;
	}
	if (BandgapMark==0x90)
	{
		IAPAL = 0x0E;
		IAPAH = 0x00;
		set_IAPGO;
		BandgapHigh = IAPFD;
		IAPAL = 0x0F;
		IAPAH = 0x00;
		set_IAPGO;
		BandgapLow = IAPFD;
		BandgapLow = BandgapLow&0x0F;
		Bandgap_Value = (BandgapHigh<<4)+BandgapLow;
		Bandgap_Voltage= Bandgap_Value*3/4;
	}
	clr_IAPEN;
}


void main (void)
{
	float bgvalue;
	float VDD_Voltage;
	unsigned  char __xdata ADCdataH[5], ADCdataL[5];
	int ADCsumH=0, ADCsumL=0;
	int i;
	unsigned char ADCavgH,ADCavgL;

	InitialUART0_Timer1(115200);

	//float Bandgap_Voltage = 1200;   /* usually just fine... or use the function */
	READ_BANDGAP();
	
	printf_fast_f("\n Bandgap voltage = %.2f mV", Bandgap_Voltage);

	while (1)
	{
		Enable_ADC_BandGap;												
		CKDIV = 0x02;															// IMPORTANT!! Modify system clock to 4MHz ,then add the ADC sampling clock base to add the sampling timing.
		for(i=0;i<5;i++)													// All following ADC detect timing is 200uS run under 4MHz.
		{
			clr_ADCF;
			set_ADCS;																
			while(ADCF == 0);
			ADCdataH[i] = ADCRH;
			ADCdataL[i] = ADCRL;
		}		
		CKDIV = 0x00;															// After ADC sampling, modify system clock back to 16MHz to run next code.
		Disable_ADC;
		for(i=2;i<5;i++)													// use the last 3 times data to make average 
		{
			ADCsumH = ADCsumH + ADCdataH[i];
			ADCsumL = ADCsumL + ADCdataL[i];
		}				
		ADCavgH = ADCsumH/3;
		ADCavgL = ADCsumL/3;
		bgvalue = (ADCavgH<<4) + ADCavgL;
		VDD_Voltage = (0x1000/bgvalue)*Bandgap_Voltage;
		printf_fast_f("\n VDD voltage = %.2f mV", VDD_Voltage); 
		Timer0_Delay1ms(500);
		ADCsumH = 0;
		ADCsumL = 0;
	}
}