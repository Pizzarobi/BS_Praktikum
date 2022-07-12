#ifndef _FUNKTIONEN_H
#define _FUNKTIONEN_H

#include <inttypes.h>

// Funktionen
extern void LCD_Output16BitWord(uint16_t data);
extern void u_delay(double usec);
extern void LCD_command(uint16_t commando);
extern void LCD_data(uint16_t data);
extern void LCD_WriteReg(uint16_t commando, uint16_t data);
extern void drawLetter(uint16_t x, uint16_t y, uint8_t c, uint16_t color, uint16_t backgroundcolor);
extern void delayForFunction(uint8_t sec);
extern void drawString(uint16_t x, uint16_t y, uint16_t color, uint16_t backgroundcolor, char* string);

#endif
