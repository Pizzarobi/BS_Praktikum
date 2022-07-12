#include "func.h"


void LCD_Output16BitWord(uint16_t data) {
    // Bits 0 und 1 schreiben
    GPIOD->ODR |= ((data & 0x3) << 14);
    GPIOD->ODR &= (((data & 0x3) << 14) | 0x3FFF);

    // Bits 2 und 3 schreiben
    GPIOD->ODR |= ((data & 0xC) >> 2);
    GPIOD->ODR &= (((data & 0xC) >> 2) | 0xFFFC);

    // Bits 4 bis 12 schreiben
    GPIOE->ODR |= ((data & 0x1FF0) << 3);
    GPIOE->ODR &= (((data & 0x1FF0) << 3) | 0x7F);

    // Bits 13 bis 15 schreiben
    GPIOD->ODR |= ((data & 0xE000) >> 5);
    GPIOD->ODR &= (((data & 0xE000) >> 5) | 0xF8FF);

}


// Busywaiting Funktionen
void delayForFunction(uint8_t sec){
	int i=0;
	int fac= 10;
	while(i<fac*sec){
		i++;
	}
}

void u_delay(double usec){
	int i = 0;
	int fac = 10000;
	while (i < fac * usec){ 
		i++; 
	}
}
