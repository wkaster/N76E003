# N76E003

This project aim to support the Nuvoton N76E003 microcontroller in Linux
using SDCC.

Problem with bitwise OR and SFRs  (Thanks to Skcks)
--------------------------------

When sdcc compiles the instruction "=|" (bitwise inclusive OR and assignment)
it uses 3 instructions, and for some protected SFR's only 4 cycles could take 
place after the TA protection unlock is called.

Example:

Keil C51 code:
------------------------------------------------------------------
mov	TA, #0xAA				; TA = 0xAA
mov	TA, #0x55				; TA = 0x55 {'U'}
orl	SFRS, #0x01				; SFRS |= 0x01

SDCC non corrected code:
------------------------------------------------------------------
mov	TA, #0xAA				; TA = 0xAA
mov	TA, #0x55				; TA = 0x55 {'U'}
mov	R6, SFRS				; R6 = SFRS
orl	0x06, #0x01				; 0x06 |= 0x01
mov	SFRS, R6				; SFRS = R6


Solution 1 
----------
Use a peep.def file containing:

replace { 
    mov    %1,%2
    orl    a%1,%3
    mov    %2,%1
} by { 
    orl    %2,%3
}

Solution 2 (Thanks to Vladimir Shevtsov / MrFeek)
----------
Make a modified SFR_Macro.h

Replace this: #define set_SMOD    PCON    |= SET_BIT7   // Original
By this:      #define set_SMOD   __asm__ ("orl _PCON,#0x80")  // SDCC compatible



Disable Power-On Reset (POR)
----------------------------

Nuvoton (strongly) recommends disable POR at startup.  See section 24.1 of 
the datasheet for more information.  That could be done using the 
"_sdcc_external_startup" function as shown below.

unsigned char _sdcc_external_startup (void)
{
    __asm
    	mov	0xC7, #0xAA
	mov	0xC7, #0x55
	mov	0xFD, #0x5A
	mov	0xC7, #0xAA
	mov	0xC7, #0x55
	mov	0xFD, #0xA5
    __endasm;
    return 0;
}

