#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#include "I2C.h"
#include "DS1307.h"
#include <stdlib.h>


extern struct
{
	unsigned char s;
	unsigned char m;
	unsigned char h;
	unsigned char dy;
	unsigned char dt;
	unsigned char mt;
	unsigned char yr;
}time;

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

char * 
gets (char *s)
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


void main(void)
{
	__code char weekday[7][4] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
	__code char month[12][4] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	
	
	unsigned char hour_0;
	unsigned char hour_1;
	unsigned char min_0;
	unsigned char min_1;
	unsigned char sec_0;
	unsigned char sec_1;
	unsigned char menukey;
	char in_time[3];
	

	InitialUART0_Timer3(115200);
	TI = 1;
	
	P15_PushPull_Mode;
	
	DS1307_init();
	

	while(1)
	{
		get_time();
		
		/* printf_small does not implement %02d formating */
		hour_0 = time.h / 10;
		hour_1 = time.h %10;
		min_0 = time.m / 10;
		min_1 = time.m % 10;
		sec_0 = time.s / 10;
		sec_1 = time.s % 10;
		
		printf_small("\n Time: %d%d:%d%d:%d%d send 't' key to adjust the time", hour_0, hour_1, min_0, min_1, sec_0, sec_1);
		printf_small("\n Date: %s, %s %d, 20%d send 'd' key to adjust the date", weekday[time.dy - 1], month[time.mt - 1], time.dt, time.yr);
		
		if(RI) {
			menukey = getchar();
			if(menukey == 0x74 || menukey == 0x54) {
				printf_small("\n Enter hour [0-23]: ");
				gets(in_time);
				time.h = atoi(in_time);
				getchar();
				printf_small("\n Enter minute [0-59]: ");
				gets(in_time);
				time.m = atoi(in_time);
				getchar();
				printf_small("\n Enter second [0-59]: ");
				gets(in_time);
				time.s = atoi(in_time);
				set_time();
			}
			if(menukey == 0x64 || menukey == 0x44) {
				printf_small("\n Enter week day [1-7]: ");
				gets(in_time);
				time.dy = atoi(in_time);
				getchar();
				printf_small("\n Enter date [1-31]: ");
				gets(in_time);
				time.dt = atoi(in_time);
				getchar();
				printf_small("\n Enter month [1-12]: ");
				gets(in_time);
				time.mt = atoi(in_time);
				getchar();
				printf_small("\n Enter year [0-99]: ");
				gets(in_time);
				time.yr = atoi(in_time);
				set_time();
			}
			RI = 0;
		}
		
		Timer0_Delay1ms(1000);
	};
}

