#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#include "DS1307.h"
#include "I2C.h"


struct
{
   unsigned char s;
   unsigned char m;
   unsigned char h;
   unsigned char dy;
   unsigned char dt;
   unsigned char mt;
   unsigned char yr;
}time;


void DS1307_init(void)
{
	I2C_init();
	DS1307_write(control_reg, 0x00);
}


unsigned char DS1307_read(unsigned char address)
{
	unsigned char value = 0x00;

	I2C_start();
	I2C_write(DS1307_WR);
	I2C_write(address);

	I2C_start();
	I2C_write(DS1307_RD);
	value = I2C_read(I2C_NACK);
	I2C_stop();
	
	return value;
}


void DS1307_write(unsigned char address, unsigned char value)
{
	I2C_start();
	I2C_write(DS1307_WR);
	I2C_write(address);
	I2C_write(value);
	I2C_stop();
}


unsigned char bcd_to_decimal(unsigned char value)
{
	return ((value & 0x0F) + (((value & 0xF0) >> 0x04) * 0x0A));
}


unsigned char decimal_to_bcd(unsigned char value)
{
	return (((value / 0x0A) << 0x04) & 0xF0) | ((value % 0x0A) & 0x0F);
}


void get_time(void)
{
	time.s = DS1307_read(sec_reg);
	time.s = bcd_to_decimal(time.s);
	
	time.m = DS1307_read(min_reg);
	time.m = bcd_to_decimal(time.m);
	
	time.h = DS1307_read(hr_reg);
	time.h = bcd_to_decimal(time.h);
	
	time.dy = DS1307_read(day_reg);
	time.dy = bcd_to_decimal(time.dy);
	
	time.dt = DS1307_read(date_reg);
	time.dt = bcd_to_decimal(time.dt);
	
	time.mt = DS1307_read(month_reg);
	time.mt = bcd_to_decimal(time.mt);
	
	time.yr = DS1307_read(year_reg);
	time.yr = bcd_to_decimal(time.yr);
}


void set_time(void)
{
	time.s = decimal_to_bcd(time.s);
	DS1307_write(sec_reg, time.s);
	
	time.m = decimal_to_bcd(time.m);
	DS1307_write(min_reg, time.m);
	
	time.h = decimal_to_bcd(time.h);
	DS1307_write(hr_reg, time.h);
	
	time.dy = decimal_to_bcd(time.dy);
	DS1307_write(day_reg, time.dy);
	
	time.dt = decimal_to_bcd(time.dt);
	DS1307_write(date_reg, time.dt);
	
	time.mt = decimal_to_bcd(time.mt);
	DS1307_write(month_reg, time.mt);
	
	time.yr = decimal_to_bcd(time.yr);
	DS1307_write(year_reg, time.yr);
}