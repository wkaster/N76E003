#define RS_HIGH                        set_P00
#define RS_LOW                         clr_P00

#define EN_HIGH                        set_P01
#define EN_LOW                         clr_P01

#define DB4_HIGH                       set_P10
#define DB4_LOW                        clr_P10

#define DB5_HIGH                       set_P11
#define DB5_LOW                        clr_P11

#define DB6_HIGH                       set_P12
#define DB6_LOW                        clr_P12

#define DB7_HIGH                       set_P13
#define DB7_LOW                        clr_P13


#define DAT							1
#define CMD							0

void pulse_enable(void);
void LCD_Init(void);
void LCD_Write(unsigned char ch, unsigned char mode);
void LCD_ShowString(char *msg);
void LCD_SetCursor(unsigned char x_pos, unsigned char y_pos);
void LCD_ClearScreen(void);
void LCD_ShowInteger(int value);