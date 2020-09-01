
#define sec_reg                          0x00
#define min_reg                          0x01
#define hr_reg                           0x02
#define day_reg                          0x03
#define date_reg                         0x04
#define month_reg                        0x05
#define year_reg                         0x06
#define control_reg                      0x07

#define DS1307_WR                        0xD0
#define DS1307_RD                        0xD1


void DS1307_init(void);
unsigned char DS1307_read(unsigned char address);
void DS1307_write(unsigned char address, unsigned char value);
unsigned char bcd_to_decimal(unsigned char value);
unsigned char decimal_to_bcd(unsigned char value);
void get_time(void);
void set_time(void);