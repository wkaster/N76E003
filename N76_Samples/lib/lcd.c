#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#include "lcd.h"


void pulse_enable(void)
{
	EN_HIGH;
	Timer0_Delay1ms(4);
	EN_LOW;
	Timer0_Delay1ms(4);
}

void LCD_Init(void)
{
	Timer0_Delay1ms(10);
	
	/* Initializing P1 ports */
	P00_PushPull_Mode;  // RS
	P01_PushPull_Mode;  // EN

	P10_PushPull_Mode;  // DB4
	P11_PushPull_Mode;  // DB5
	P12_PushPull_Mode;  // DB6
	P13_PushPull_Mode;  // DB7

	Timer0_Delay1ms(100);
	
	// this sequence is repeated 3x
	RS_LOW;
	DB7_LOW;
	DB6_LOW;
	DB5_HIGH;
	DB4_HIGH;
	
	pulse_enable();

	Timer0_Delay1ms(100);		// repeat sequence
	
	pulse_enable();
	
	Timer0_Delay1ms(100);		// repeat sequence
	
	pulse_enable();
	
	RS_LOW;
	DB7_LOW;
	DB6_LOW;
	DB5_HIGH;
	DB4_LOW;

	pulse_enable();
	
	/* 4bit set, now other parameters */
	
	LCD_Write(0x28, CMD); // Function set 4bit, 2 lines, 5x7 dots
	
	LCD_Write(0x0C, CMD); // display on
	
	LCD_Write(0x01, CMD); // clear display
	
	LCD_Write(0x06, CMD); // Entry mode set

	LCD_Write(0x02, CMD); // Set position 0,0

	/* End of LCD init */	
}

void LCD_Write(unsigned char ch, unsigned char mode)
{
	if(mode) RS_HIGH; else RS_LOW;

    // upper 4bits
	if(ch & 0x10) DB4_HIGH; else DB4_LOW;
	if(ch & 0x20) DB5_HIGH; else DB5_LOW;
	if(ch & 0x40) DB6_HIGH; else DB6_LOW;
	if(ch & 0x80) DB7_HIGH; else DB7_LOW;  

	pulse_enable();

	// lower 4 bits
	if(ch & 0x01) DB4_HIGH; else DB4_LOW;
	if(ch & 0x02) DB5_HIGH; else DB5_LOW;
	if(ch & 0x04) DB6_HIGH; else DB6_LOW;
	if(ch & 0x08) DB7_HIGH; else DB7_LOW;

	pulse_enable();
}

void LCD_ShowString(char *msg)
{
	int idx =0;
	if (msg==0)
		return;
	while (msg[idx] !=0)
	{
		LCD_Write(msg[idx++], DAT);
	}
} 

void LCD_SetCursor(unsigned char x_pos, unsigned char y_pos)
{
	if(y_pos == 0)
	{
		LCD_Write((0x80 | x_pos), CMD);
	}
	else
	{
		LCD_Write((0xC0 | x_pos), CMD);
	}
}

void LCD_ClearScreen(void)
{
	LCD_Write(0x01, CMD);
	LCD_Write(0x02, CMD);
}

void LCD_ShowInteger(int value)
{
    char buf[6] ;
    
    sprintf(buf,"%u", value);
    LCD_ShowString(buf);  
}
