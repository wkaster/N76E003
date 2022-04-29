/**
Simple example using SPI
Sparkfun's Graphic LCD 84x48-Nokia 5110 Library ported to N76E003 by wkaster

N76E003								5110 LCD
-------								--------
P0.0 (MOSI)		<-------------->	DIN
P1.0 (SPCLK) 	<-------------->	CLK
P1.1 			<-------------->	DC
P1.2 			<-------------->	RST
P1.5 (SS)		<-------------->	CE
*/

#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#include "PCD8544.h"

void main(){
	SPI_Initial();
	lcdBegin();
	updateDisplay(); // with displayMap untouched, SFE logo
	setContrast(40); // Good values range from 40-60
	Timer0_Delay1ms(3000);
	
	while(1) {
		clearDisplay(0);
		gotoXY(0,0);
		setLine(1, 1, 40, 40, 1);
		setLine(4, 4, 33, 42, 1);
		updateDisplay();
		Timer0_Delay1ms(3000);
		
		clearDisplay(0);
		gotoXY(0,0);
		setRect(3, 3, 80, 40, 0, 1);
		setStr("N76E003",10,10,1);
		updateDisplay();
		Timer0_Delay1ms(3000);
		
		clearDisplay(0);
		gotoXY(0,0);
		setRect(3, 3, 80, 40, 1, 1);
		setStr("N76E003",10,10,0);
		updateDisplay();
		Timer0_Delay1ms(3000);		
		
		
		clearDisplay(0);
		setStr("Hello",20,14,1);
		setStr("Friend!",15,26,1);
		updateDisplay();
		Timer0_Delay1ms(3000);
		
		clearDisplay(0);
		setCircle(30, 20, 18, 1, 1);
		updateDisplay();
		Timer0_Delay1ms(3000);
		
		clearDisplay(0);
		setCircle(42, 24, 23, 1, 1);
		setLine(42, 3, 38, 24, 1);
		setLine(42, 3, 46, 24, 1);
		setLine(38, 25, 46, 25, 1);
		setLine(49, 21, 64, 24, 1);
		setLine(49, 27, 64, 24, 1);
		setLine(48, 21, 48, 27, 1);
		updateDisplay();
		Timer0_Delay1ms(3000);
				
	}

}
