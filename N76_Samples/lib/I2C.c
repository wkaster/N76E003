#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#include "I2C.h"


void I2C_GPIO_Init(int mode)
{
	if(mode != 0) {
		/* alternative I2C GPIOS */
		P02_OpenDrain_Mode;
		P16_OpenDrain_Mode;
		set_I2CPX;		
	} else {
		/* regular I2C GPIOS */
		P13_OpenDrain_Mode;
		P14_OpenDrain_Mode;
		clr_I2CPX;
	}
}

void I2C_init(void)
{
	I2C_GPIO_Init(regular_I2C_pins);
	I2CLK = I2C_CLOCK; 
	set_I2CEN; 
}


void I2C_start(void)
{
	signed int t = timeout_count;
	
	set_STA;                                
  clr_SI;
  while((SI == 0) && (t > 0))
	{
		t--;
	};     
}

void I2C_stop(void)
{
	signed int t = timeout_count;
	
	clr_SI;
  set_STO;
	while((STO == 1) && (t > 0))
	{
		t--;
	};     
}


unsigned char I2C_read(unsigned char ack_mode)
{
	signed int t = timeout_count;
	unsigned char value = 0x00;

	set_AA;                             
  clr_SI;
  while((SI == 0) && (t > 0))
	{
		t--;
	};   	
	
	value = I2DAT;

	if(ack_mode == I2C_NACK)
	{
		t = timeout_count;
		clr_AA;   
		clr_SI;
		while((SI == 0) && (t > 0))
		{
			t--;
		};   		
	}
	
	return value;
}


void I2C_write(unsigned char value)
{
	signed int t = timeout_count;
	
	I2DAT = value; 
	clr_STA;           
	clr_SI;
	while((SI == 0) && (t > 0))
	{
		t--;
	};  
}