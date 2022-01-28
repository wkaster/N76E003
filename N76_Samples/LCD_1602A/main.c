#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#include "lcd.h"


void main (void)
{
	int i=0;
	
	LCD_Init();

	while(1) {	
		LCD_SetCursor(4,0);
		LCD_ShowString("LCD DEMO\0" );
		LCD_SetCursor(3,1);
		LCD_ShowString("N76E003 uC\0" );

		Timer0_Delay1ms(6000);
		
		LCD_ClearScreen();

		LCD_ShowString("Number:\0" );
		for(i=0;i<20;i++) {
			LCD_SetCursor(8,0);
			LCD_ShowInteger(i);
			Timer0_Delay1ms(1000);
		}
		
		LCD_ClearScreen();
	}
}
