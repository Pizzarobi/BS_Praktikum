#ifndef _FUNKTIONEN_H
#define _FUNKTIONEN_H

#include <inttypes.h>
#include <string.h>
#include "STM32F4xx.h"
#include "core_cm4.h"
#include "_mcpr_stm32f407.h"

// Funktionen
extern void LCD_Output16BitWord(uint16_t data);
extern void u_delay(double usec);
extern void delayForFunction(uint8_t sec);

#endif
