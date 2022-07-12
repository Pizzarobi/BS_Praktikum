#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "STM32F4xx.h"
#include "_mcpr_stm32f407.h"
#include <inttypes.h>
#include <string.h>
#include "func.h"

#define hintergrundfarbe 0xFFFF
#define fontcolor 0x0000

/*char satz[] = "Fuer Fortnite-Gang!!";
char satz1[] = "Rennauto-Staubwolke! #187";
char satz2[] = "Amberg ist die Hood.";
char satz3[] = "#924Haramberg";
char satz4[] = "Schwurbler raus!";
char satz5[] = "Mama, ich hab dich lieb!";*/

extern void LCD_init(void);
extern void LCD_setCursor(uint16_t x, uint16_t y);
extern void LCD_drawPixel(uint16_t color);
extern void clearDisplay(uint16_t color);
extern void LCD_command(uint16_t commando);
extern void LCD_data(uint16_t data);
extern void LCD_WriteReg(uint16_t commando, uint16_t data);
extern void drawLetter(uint16_t x, uint16_t y, uint8_t c, uint16_t color, uint16_t backgroundcolor);
extern void drawString(uint16_t x, uint16_t y, uint16_t color, uint16_t backgroundc, char* string);
extern void activateDisplay(void);
extern void deactivateDisplay(void);

#endif
