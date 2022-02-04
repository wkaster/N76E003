/**
*  N76E003 and MS51x Bootloader by Wiliam Kaster
*  Visit https://github.com/wkaster/N76E003 for more info
*
*  This bootloader is NOT COMPATIBLE with Nuvoton's ISP software
*
*  Version 1.0: 2022-02-04
*       First working version
*/
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#include <stdbool.h>


#define APROM_SIZE      16*1024 // 16Kb (APROM) + 2Kb (LDROM) = 18Kb TOTAL  (adjust for MS51x)
#define BLOCK_SIZE      16		// bytes in data block
#define CMD_SOH			0x01    // [SOH] Start of Heading
#define CMD_STX			0x02	// [STX] Start of Text
#define CMD_ETX			0x03	// [ETX] End of Text
#define CMD_EOT         0x04    // [EOT] End of Transmission
#define CMD_ACK			0x06	// [ACK] Acknowledge
#define CMD_NACK		0x15	// [NAK] Negative Acknowledge
#define CMD_SUB         0x1A    // [SUB] Substitute
#define CMD_DEL         0x7F    // [DEL] Delete


unsigned char timerCount = 0;
unsigned char receivedBuf[20];
unsigned char idx = 0;


void timer0_isr(void) __interrupt 1
{
    TL0 = LOBYTE(TIMER_DIV12_VALUE_40ms); 
    TH0 = HIBYTE(TIMER_DIV12_VALUE_40ms);
    if (++timerCount == 15)
    {
		clr_TR0;  // stop timer
		idx = 1;
		receivedBuf[0] = CMD_EOT;	// reset from aprom		
    }
}

void serial_isr() __interrupt 4
{ 
    if(RI == 1)
    {
		receivedBuf[idx] = SBUF;
		idx++;
		if(idx > 19) {
			receivedBuf[0] = 0x00;
			idx = 0;
		}
        RI = 0;              // Clear the Receive interrupt flag
    }
}


unsigned char dallas_crc8(unsigned char* data, unsigned char size)
{
    unsigned char crc = 0;
    for ( unsigned char i = 0; i < size; ++i )
    {
        unsigned char inbyte = data[i];
        for ( unsigned char j = 0; j < 8; ++j )
        {
            unsigned char mix = (crc ^ inbyte) & 0x01;
            crc >>= 1;
            if ( mix ) crc ^= 0x8C;
            inbyte >>= 1;
        }
    }
    return crc;
}


void main()
{
	unsigned char crc8 = 0;
	unsigned char i;
	unsigned int u16ApromAddr = 0x0000;
	bool cmdmode = true;
	
	/* maximum speed 19200 without change clock frequency to 16.6MHz. */
    InitialUART0_Timer3(19200);
	
	TMOD |= 0x01; // mode 1
	
    TL0 = TIMER_DIV12_VALUE_40ms&&0xff;
    TH0 = (TIMER_DIV12_VALUE_40ms>>8)&0xff;
	
	set_ET0; 	// enable timer0 interrupt
	set_ES; 	// ensable serial interrupt
	set_EA; 	// enable interrupts
	
	set_TR0; 	// run timer
	
	while(1)
	{
		// commands
		if(idx > 0 && cmdmode) {
			switch(receivedBuf[0])
			{
				case CMD_SOH:
					Send_Data_To_UART0(CMD_ACK);
					clr_TR0;						// stop timer
					idx = 0;
					cmdmode = true;
				break;
				case CMD_EOT:
					Send_Data_To_UART0(CMD_ACK);
					clr_SWRF;						// clear software reset flag
					clr_EA;							// disable interrupts
					TA=0xAA;
					TA=0x55;
					CHPCON&=~SET_BIT1;				// boot from APROM
					TA=0xAA;
					TA=0x55;
					CHPCON|=SET_BIT7;				//  reset
				break;				
				case CMD_SUB:
				{
					if(idx == 2 && receivedBuf[1] == CMD_DEL) {
						// Erase APROM (128 bytes per page)
						clr_EA;								// disable interrupts
						set_IAPEN; 							//enable IAP mode
						set_APUEN;							//enable APROM update
						
						for(u16ApromAddr=0x0000 ; u16ApromAddr < APROM_SIZE ; u16ApromAddr = u16ApromAddr+128)
						{
							IAPAL = u16ApromAddr&0xff;
							IAPAH = (u16ApromAddr>>8)&0xff;
							IAPFD = 0xFF;						// this mode must be 0xFF
							IAPCN = 0x22;						// APROM page erase - see datasheet IAP modes and command codes		
							set_IAPGO; 
						}
						
						clr_APUEN;
						clr_IAPEN;
						u16ApromAddr = 0x0000;				// reset Aprom Address
						set_EA;								// enable interrupts						
						Send_Data_To_UART0(CMD_ACK);
						idx = 0;
					}
					if(idx >= 2  && receivedBuf[1] != CMD_DEL) {
 						Send_Data_To_UART0(CMD_NACK);
						idx = 0;
					}
					break;
				}
				case CMD_STX:
					cmdmode = false;
				break;
				default:
					Send_Data_To_UART0(CMD_NACK);
					idx = 0;
				break;
			}
		}
		// data
		if(idx > 17 && !cmdmode) {
			if(receivedBuf[18] == CMD_ETX) {
				crc8 = dallas_crc8(&receivedBuf[1], BLOCK_SIZE);
				if(crc8 == receivedBuf[BLOCK_SIZE + 1]) {
					//Save data to APROM DATAFLASH
					clr_EA;								// disable interrupts
					set_IAPEN; 
					set_APUEN;
					for(i = 1; i <= BLOCK_SIZE ; i++) {
						IAPAL = u16ApromAddr&0xff;			// low byte
						IAPAH = (u16ApromAddr>>8)&0xff;		// high byte
						IAPFD = receivedBuf[i];				// byte to save
						IAPCN = 0x21;						// APROM byte program - see datasheet IAP modes and command codes
						set_IAPGO;							// do it!
						u16ApromAddr++;						// next APROM byte addr
					}
					clr_APUEN;
					clr_IAPEN;
					set_EA;								// enable interrupts
					Send_Data_To_UART0(CMD_ACK);
				}
				else {
					Send_Data_To_UART0(CMD_NACK);
				}
				idx = 0;
				cmdmode = true;
			}
		}
	}
}