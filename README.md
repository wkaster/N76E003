# N76E003

This project aim to support the Nuvoton N76E003 microcontroller in Linux  
using SDCC.  

Problem with bitwise OR and SFRs  (Thanks to Skcks)
--------------------------------

**NOTE:** This issue occurs only in **sdcc versions 3.8 and below**.

When sdcc compiles the instruction "=|" (bitwise inclusive OR and assignment)  
it uses 3 instructions, and for some protected SFR's only 4 cycles could take  
place after the TA protection unlock is called.  

Example:  

Keil C51 code:  
\--------------  
```asm
mov	TA, #0xAA				; TA = 0xAA  
mov	TA, #0x55				; TA = 0x55 {'U'}  
orl	SFRS, #0x01		  	; SFRS |= 0x01  
```
SDCC non corrected code:  
\--------------------------  
```asm
mov	TA, #0xAA			   ; TA = 0xAA  
mov	TA, #0x55			   ; TA = 0x55 {'U'}  
mov	R6, SFRS				; R6 = SFRS  
orl	0x06, #0x01			 ; 0x06 |= 0x01  
mov	SFRS, R6				; SFRS = R6  
```

Solution 1  
----------
Use a peep.def file containing:  

replace {  
&nbsp;&nbsp;mov&nbsp;    %1,%2  
&nbsp;&nbsp;orl&nbsp;    a%1,%3  
&nbsp;&nbsp;mov&nbsp;    %2,%1  
} by {  
&nbsp;&nbsp;orl&nbsp;    %2,%3  
}  

Solution 2 (Thanks to Vladimir Shevtsov / MrFeek)  
----------
Make a modified SFR_Macro.h replacing all "|=" statments  

Example:  

Replace this:&nbsp; #define&nbsp; set_SMOD&nbsp;&nbsp;&nbsp;&nbsp;PCON    |= SET_BIT7;   // Original  
By this:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;#define&nbsp; set_SMOD   &nbsp;&nbsp;\__asm__ ("orl _PCON,#0x80");&nbsp;  // SDCC compatible  


Disable Power-On Reset (POR)  
----------------------------

Nuvoton (strongly) recommends disable POR at startup.  See section 24.1 of  
the datasheet for more information.  That could be done using the  
"_sdcc_external_startup" function as shown below.  

```c
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

```  
