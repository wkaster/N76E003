#include <stdbool.h>

__sbit __at (0x91) dcPin; 		// P1^1 DC - Data/Command, pin 5 on LCD.
__sbit __at (0x92) rstPin;		// P1^2 RST - Reset, pin 4 on LCD.


/* PCD8544-specific defines: */
#define LCD_COMMAND  0
#define LCD_DATA     1

/* 84x48 LCD Defines: */
#define LCD_WIDTH   84 // Note: x-coordinates go wide
#define LCD_HEIGHT  48 // Note: y-coordinates go high
#define WHITE       0  // For drawing pixels. A 0 draws white.
#define BLACK       1  // A 1 draws black.

void LCDWrite(bool data_or_command, unsigned char data);
void setPixel(int x, int y, bool bw);
void setLine(int x0, int y0, int x1, int y1, bool bw);
void setRect(int x0, int y0, int x1, int y1, bool fill, bool bw);
void setCircle(int x0, int y0, int radius, bool bw, int lineThickness);
void setChar(char character, int x, int y, bool bw);
void setStr(char * dString, int x, int y, bool bw);
void clearDisplay(bool bw);
void gotoXY(int x, int y);
void updateDisplay();
void setContrast(unsigned char contrast);
void invertDisplay();
void lcdBegin(void);
void SPI_Initial(void);