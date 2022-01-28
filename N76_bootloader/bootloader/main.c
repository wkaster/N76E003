/*---------------------------------------------------------------------------------------------------------*/
/* SDCC simple serial ISR UART0 for Nuvoton N76E003                                                        */
/* Just connect any serial adapter on N76 ports P.06 and P.07 and view the result in PC serial monitor     */
/* P0.6 [TX] -> FTDI [RX]                                                                                  */
/* P0.7 [RX] <- FTDI [TX]                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/

#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#include <stdbool.h>


#define CMD_SOH			0x01    // [SOH] Start of Heading
#define CMD_STX			0x02	// [STX] Start of Text
#define CMD_ETX			0x03	// [ETX] End of Text
#define CMD_EOT         0x04    // [EOT] End of Transmission
#define CMD_ACK			0x06	// [ACK] Acknowledge
#define CMD_NACK		0x15	// [NAK] Negative Acknowledge
#define CMD_SUB         0x1A    // [SUB] Substitute
#define CMD_DEL         0x7F    // [DEL] Delete



unsigned char receivedBuf[20];
unsigned char idx = 0;
bool cmdmode = true;


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
	
    InitialUART0_Timer3(9600);
	
	set_ES; // ensable serial interrupt
	set_EA; // enable interrupt
	
	
	while(1)
	{
		// commands
		if(idx > 0 && cmdmode) {
			switch(receivedBuf[0])
			{
				case CMD_SOH:
					Send_Data_To_UART0(CMD_ACK);
					idx = 0;
					cmdmode = true;
					// here all begins
				break;
				case CMD_EOT:
					Send_Data_To_UART0(CMD_ACK);
					idx = 0;
					cmdmode = true;
				break;				
				case CMD_SUB:
				{
					if(idx == 2 && receivedBuf[1] == CMD_DEL) {
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
				crc8 = dallas_crc8(&receivedBuf[1], 16);
				if(crc8 == receivedBuf[17]) {
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