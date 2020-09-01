#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#include "eeprom.h"
#include <string.h>

#define BASE_ADDRESS  			0x3700
__code __at (BASE_ADDRESS) char eeprom[128] = "abc";

/* Needed for printf */
int putchar (int c) {
	while (!TI);
	TI = 0;
	SBUF = c;
	return c;
}

/* Needed for gets */
int getchar (void) {
	char c;
	while (!RI);
	c = SBUF;
	RI = 0;
	return c;
}

char * gets (char *s)
{
	char c;
	unsigned int count = 0;

	while (1)
	{
		c = getchar ();
		switch(c)
		{
			case '\b': /* backspace */
				if (count)
				{
					putchar ('\b');
					putchar (' ');
					putchar ('\b');
					--s;
					--count;
				}
			break;
			case '\n':
			case '\r': /* CR or LF */
				putchar ('\r');
				putchar ('\n');
				*s = 0;
				return s;
			default:
				*s++ = c;
				++count;
				putchar (c);
			break;
		}
	}
}


void main (void) 
{
	unsigned char menukey;
	__xdata unsigned char cTemp[128];
	int iSize, i;
	
	InitialUART0_Timer3(115200);
	TI = 1;
	
	while(1)
	{
		printf_small("\n Send 'r' to read, and 'w' to write eeprom data.");
		if(RI) {
			menukey = getchar();
			if(menukey == 0x72 || menukey == 0x52) {
				printf_small("\n Data: %s", eeprom);
			}
			if(menukey == 0x77 || menukey == 0x57) {
				printf_small("\n Enter eeprom data [0-127 bytes]: ");
				gets(cTemp);
				iSize = strlen(cTemp);
		
				Erase_APROM_Page(BASE_ADDRESS);
				
				for(i=0;i<iSize;i++) {
					Write_APROM_BYTE(BASE_ADDRESS+i,cTemp[i]);
				}
				Write_APROM_BYTE(BASE_ADDRESS+iSize,'\0' );
			}
			RI = 0;
		}

		Timer0_Delay1ms(1000);
	}
}
