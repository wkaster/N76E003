/*---------------------------------------------------------------------------------------------------------*/
/* SDCC 30s prime number calculation benchmark for Nuvoton N76E003                                         */
/* Just connect any serial adapter on N76 ports P.06 and P.07 and view the result in PC serial monitor     */
/* P0.6 [TX] -> FTDI [RX]                                                                                  */
/* P0.7 [RX] <- FTDI [TX]                                                                                  */
/* Adapted from Nuvoton's UART0_Printf sample code                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include <math.h>
#include <float.h>
#include <stdbool.h>

unsigned int timerCount = 0;
long bigger      = 0;
long i           = 2; // Start at 2
long found       = 0; // Number of primtes we've found
bool timesup     = 0;

int is_prime(long num);
int sqrti(long num);

/* Needed for printf */
int putchar (int c) {
  while (!TI);
  TI = 0;
  SBUF = c;
  return c;
}

void main()
{
    int prime;
    InitialUART0_Timer3(115200);
	
	printf_small("Begining prime number test... \n"); 
 
    set_EA; // enable interrupt
    set_ET0; // enable timer0 interrupt
    TMOD |= 0x01; // mode 1

    // timer0, mode 1
    TL0 = LOBYTE(TIMER_DIV12_VALUE_40ms); 
    TH0 = HIBYTE(TIMER_DIV12_VALUE_40ms);
	
    set_TR0; // enable timer
	
    while (1)
    {
		prime = is_prime(i); // Check if the number we're on is prime

		if (prime == 1) {
			found++;
			bigger = i;
		}

		i++;
		
		if(timesup) {
			printf_small("\n Found: %ld in 30s", found);
			printf_small("\n Bigger prime is: %ld", bigger);
		  
			// reset
			bigger = 0;
			i = 2;
			found = 0;
			timesup = 0;
			timerCount = 0;
			set_TR0; // enable timer
		}

    }
}

int is_prime(long num) {
	// Only have to check for divisible for the sqrt(number)
	float root = sqrtf(__slong2fs(num));
	int upper = __fs2sint(root);
	
	/* int upper = sqrti(num);  // alternative function */
	

	// Check if the number is evenly divisible (start at 2 going up)
	for (int cnum = 2; cnum <= upper; cnum++) {
		int mod = num % cnum; // Remainder

		if (mod == 0) {
			return 0;
		} // If the remainer is 0 it's evenly divisible
	}

	return 1; // If you get this far it's prime
}

/* alternative faster int sqrt calc funcion - (cheating?) */
int sqrti(long num) {
    int res = 0;
    int bit = 1 << 14; // The second-to-top bit is set: 1 << 30 for 32 bits
 
    // "bit" starts at the highest power of four <= the argument.
    while (bit > num)
        bit >>= 2;
        
    while (bit != 0) {
        if (num >= res + bit) {
            num -= res + bit;
            res = (res >> 1) + bit;
        }
        else {
            res >>= 1;
		}
        bit >>= 2;
    }
    return res;
}

void T0_int(void) __interrupt 1
{
    TL0 = LOBYTE(TIMER_DIV12_VALUE_40ms); 
    TH0 = HIBYTE(TIMER_DIV12_VALUE_40ms);
    if (++timerCount == 750)
    {
		  timesup = 1;
		  clr_TR0;  // stop timer
    }
}
