#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <inttypes.h>
#include "func.h"

extern void LCD_init(void);
extern void LCD_setCursor(uint16_t x, uint16_t y);
extern void LCD_drawPixel(uint16_t color);
extern void clearDisplay(uint16_t color);

#endif
