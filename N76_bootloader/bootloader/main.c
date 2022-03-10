/**
*  N76E003 and MS51x Bootloader by Wiliam Kaster and Konstantin Kim
*  Visit https://github.com/wkaster/N76E003 for more info
*
*  This bootloader is NOT COMPATIBLE with Nuvoton's ISP software
*
*  Version 1.0: 2022-02-04
*       First working version
*  Version 1.1: 2022-03-10
*		Code performance and adjusts
*		Footprint shrink
*/
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include <stdbool.h>


#define APROM_SIZE      17*1024 // 17Kb (APROM) + 1Kb (LDROM) = 18Kb TOTAL  (adjust for MS51x)
#define BLOCK_SIZE      16		// bytes in data block
#define CMD_SOH			0x01    // [SOH] Start of Heading
#define CMD_STX			0x02	// [STX] Start of Text
#define CMD_ETX			0x03	// [ETX] End of Text
#define CMD_EOT         0x04    // [EOT] End of Transmission
#define CMD_ACK			0x06	// [ACK] Acknowledge
#define CMD_NACK		0x15	// [NAK] Negative Acknowledge
#define CMD_SUB         0x1A    // [SUB] Substitute
#define CMD_DEL         0x7F    // [DEL] Delete

uint8_t idx;
uint8_t timerCount;
uint8_t buff[BLOCK_SIZE +3];

uint16_t __at (0xA6) IAPA16 ;
volatile uint16_t __at (0xC5) RLH3;

inline void uart_init(uint32_t u32Baudrate) //use timer3 as Baudrate generator
{
	P06_PushPull_Mode;	//tx
	P07_Input_Mode;		//rx

	RLH3   = 65535 - FOSC/(16*u32Baudrate);

	SCON   = 0x52;     //UART0 Mode1,REN=1,TI=1
	PCON  |= (1<<7);	//set_SMOD;        //PCON: UART0 Double Rate Enable
	T3CON  = 0x20;	//T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1), BRCK=1 (UART0 baud rate clock source = Timer3)
	T3CON |= (1<<3);	//	TR3=1 - Enable Timer3
}

inline void tx_sync(){
	while(!TI);
}

static void tx(char c) {
	tx_sync();
	TI = 0;
	SBUF = c;
	idx = 0;
}

inline void ta() {	//timed access protection
	TA=0xAA;
	TA=0x55;
}

static void iap_on() {	//warning:  interrupts have to be disabled
	ta();	CHPCON |= SET_BIT0;	//set_IAPEN; 		//enable IAP mode
	ta();	IAPUEN |= SET_BIT0;	//set_APUEN;		//enable APROM update
}

static void iap_go() {
	ta();	IAPTRG |= SET_BIT0;	//set_IAPGO;
}

static void iap_off() {
	ta();	IAPUEN &=~ SET_BIT0;	//	clr_APUEN;
	ta();	CHPCON &=~ SET_BIT0;	//	clr_IAPEN;
}

void timer0_isr(void) __interrupt 1
{
	TL0 = LOBYTE(TIMER_DIV12_VALUE_40ms);
	TH0 = HIBYTE(TIMER_DIV12_VALUE_40ms);
	if (!(++timerCount&0x0f))
	{
		clr_TR0;  // stop timer
		idx = 1;
		buff[0] = CMD_EOT;	// reset from aprom
	}
}

void serial_isr() __interrupt 4
{
	if (RI)	{
		if (idx >= sizeof(buff)) {	//overflow
			idx = 0;
		}
		buff[idx] = SBUF;
		idx++;
		RI = 0;              // Clear the Receive interrupt flag
	}
}


inline uint8_t dallas_crc8(const __idata uint8_t* data, uint8_t size)
{
	uint8_t crc = 0;
	do {
		uint8_t inbyte = *data++;
		uint8_t j=8;
		do {
			uint8_t mix = (crc ^ inbyte) & 0x01;
			crc >>= 1;
			if ( mix ) crc ^= 0x8C;
			inbyte >>= 1;
		} while (--j);
	} while (--size);
	return crc;
}

#define u16ApromAddr IAPA16
//uint16_t u16ApromAddr;

void main()
{
//	uint16_t u16ApromAddr = 0x0000;
	u16ApromAddr = 0x0000;
	bool cmdmode = true;
	idx = 0;
	timerCount = 0;

	uart_init(19200);	//	maximum speed 19200 without change clock frequency to 16.6MHz.

	TMOD |= 0x01; // mode 1

	TL0 = TIMER_DIV12_VALUE_40ms&&0xff;
	TH0 = (TIMER_DIV12_VALUE_40ms>>8)&0xff;

	set_ET0; 	// enable timer0 interrupt
	set_ES; 	// enable serial interrupt
	set_EA; 	// enable interrupts

	set_TR0; 	// run timer

	for(;;)	{
		// commands
		if(idx > 0 && cmdmode) {
			switch(buff[0])
			{
				case CMD_SOH:
					tx(CMD_ACK);
					clr_TR0;						// stop timer
					cmdmode = true;
					break;
				case CMD_EOT:
					tx(CMD_ACK);
					tx_sync();
					clr_SWRF;						// clear software reset flag
					clr_EA;							// disable interrupts
					ta();	CHPCON&=~SET_BIT1;		// clr_BS		boot from APROM
					ta();	CHPCON|= SET_BIT7;		// set_SWRST	reset
					break;
				case CMD_STX:
					cmdmode = false;
					break;
				case CMD_SUB:
				{
					if(idx == 2 && buff[1] == CMD_DEL) {	// Erase APROM (128 bytes per page)
						clr_EA;								// disable interrupts
						iap_on();
							IAPCN = 0x22;						// APROM page erase - see datasheet IAP modes and command codes
							IAPFD = 0xFF;						// this mode must be 0xFF
							IAPAH = APROM_SIZE/256;
							do {
								IAPAH--;
								IAPAL = 0x80;	iap_go();
								IAPAL = 0x00;	iap_go();
							} while (IAPAH);
						iap_off();
						u16ApromAddr = 0x0000;				// reset Aprom Address
						set_EA;								// enable interrupts
						tx(CMD_ACK);
					}
					if(idx >= 2  && buff[1] != CMD_DEL) {	//KK: still this part not so clear for me...
 						tx(CMD_NACK);
					}
					break;
				}
				default:
					tx(CMD_NACK);
					break;
			}
		}
		// data
		if( (idx >= BLOCK_SIZE+2) && !cmdmode) {
			if(buff[BLOCK_SIZE +2] == CMD_ETX) {
				uint8_t crc = dallas_crc8(&buff[1], BLOCK_SIZE);
				if(buff[BLOCK_SIZE + 1] == crc) {
					uint8_t i;
					const __idata uint8_t*	src = buff;
					//Save data to APROM DATAFLASH
					clr_EA;								// disable interrupts
					iap_on();
						IAPCN = 0x21;						// APROM byte program - see datasheet IAP modes and command codes
						for(i = BLOCK_SIZE; i; --i) {
							IAPFD = *++src;						// byte to save
							iap_go();							// do it!
							u16ApromAddr++;
						}
					iap_off();
					set_EA;								// enable interrupts
					tx(CMD_ACK);
				}
				else {
					tx(CMD_NACK);
				}
				cmdmode = true;
			}
		}
	}
}