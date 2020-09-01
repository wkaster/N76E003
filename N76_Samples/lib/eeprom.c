#include "N76E003.h"
#include "Common.h"
#include "SFR_Macro.h"
#include "Function_define.h"

/* Erase 128 bytes page */
void Erase_APROM_Page(unsigned int u16EPAddr)
{
	//Erase APROM DATAFLASH page
	set_IAPEN; 							//enable IAP mode
	set_APUEN;							//enable APROM update
	IAPAL = u16EPAddr&0xff;
	IAPAH = (u16EPAddr>>8)&0xff;
	IAPFD = 0xFF;
    IAPCN = 0x22; 		
 	set_IAPGO; 
	
	clr_APUEN;
	clr_IAPEN;
}

/* Write 1 byte to APROM flash memory */
void Write_APROM_BYTE(unsigned int u16EPAddr,unsigned char u8EPData)
{
	//Save data to APROM DATAFLASH
	set_IAPEN; 
	set_APUEN;
	IAPAL = u16EPAddr&0xff;
    IAPAH = (u16EPAddr>>8)&0xff;
	IAPFD = u8EPData;
	IAPCN = 0x21;
	set_IAPGO;			
	
	clr_APUEN;
	clr_IAPEN;
}