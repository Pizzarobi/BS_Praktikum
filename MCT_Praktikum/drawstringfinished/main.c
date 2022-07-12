#include "STM32F4xx.h"
#include "_mcpr_stm32f407.h"
#include <inttypes.h>
#include "func.h"
#include "fonts.h"
#include "display.h"
#include <string.h>

#define hintergrundfarbe 0x2EA5
#define fontcolor 0xFFFF

char satz[] = "Fuer Fortnite-Gang!!";
char satz1[] = "Rennauto-Staubwolke! #187";
char satz2[] = "Amberg ist die Hood.";
char satz3[] = "#924Haramberg";
char satz4[] = "Schwurbler raus!";
char satz5[] = "Mama, ich hab dich lieb!";

void DisplayMessung(void)
{
uint16_t colorbg = 0xF800; // Rot
uint16_t colorfg;
while(1) {
GPIOD->ODR ^= 0x1000; // toggle Pin PD12 (grüne LED)
clearDisplay(colorbg); // lösche das Display
// gib einen Text aus
drawString( 20, 220, colorfg, colorbg, "Hallo Welt!" );
// Wechsle Farbe
colorfg = colorbg;
colorbg = ~colorbg;
}
}


int main(void)
{
	
	mcpr_SetSystemCoreClock();

	// Peripheral GPIOD einschalten
	RCC->AHB1ENR |= 1<<3|1;
	// Peripheral GPIOE einschalten
	RCC->AHB1ENR |= 1<<4|1;
	
	// Orange LED konfigurieren
	GPIOD->MODER |= 1<<24;
	
	// Orange LED (Port D12) auf Ausgang schalten
	GPIOD->ODR |= 1<<12;
	
	//Read auf 1
	GPIOD->MODER 	|= 1<<8;
	GPIOD->ODR		|= 1<<4;
	
	// GPIOs f�r Display
	GPIOE->MODER |= 0x55554040;
	GPIOD->MODER |= 0x55154545;
	
	// Hintergrundbeleuchtung
	GPIOD->MODER |= 1<<26;
	GPIOD->ODR |= 1<<13;
	
	// Display Initialisierung
	LCD_init();
	// Display Farbe einstellen
	clearDisplay(hintergrundfarbe);
	
	// Stringausgabe
	
	//DisplayMessung();
	
	//drawLetter(120,40,'A',0xFFFF);
	drawString(5, 150, fontcolor, hintergrundfarbe, satz2);
	drawString(5, 166, fontcolor, hintergrundfarbe, satz3);
	drawString(5, 220, fontcolor, hintergrundfarbe, satz4);
	
	while( 1 ) {
		if( (GPIOA->IDR & 1) == 0) { 
			drawString(5,5, fontcolor, hintergrundfarbe, satz1); 
		} else { 
			drawString(5,5, fontcolor, hintergrundfarbe, satz);
		}
		
		
		
	}
	
	
	
	/*while( 1 ) {
		if( (GPIOA->IDR & 1) == 0) { 
			GPIOD->ODR |= ~(1<<12); 
		} else { 
			GPIOD->ODR |= 1<<12;
			u_delay(1045);
			GPIOD->ODR &= ~(1<<12);
			u_delay(1045);
		}
		
		
		
	}*/
		
}


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

void LCD_command(uint16_t commando){
		GPIOD->ODR &= ~(0x80); 			// CS = 0
		GPIOE->ODR &= ~(0x8);				// D/C = 0 setzen (Kommando)
		LCD_Output16BitWord(commando);
		GPIOD->ODR &= ~(0x20);			// Pushimpuls auf WR
		GPIOD->ODR |= 0x80;					// CS = 1
		GPIOD->ODR |= 0x20;					// WR wieder auf 1
}

void LCD_data(uint16_t data){
		GPIOD->ODR &= ~(0x80); 			// CS = 0
		GPIOE->ODR |= 0x8;					// D/C = 1 setzen (Data)
		LCD_Output16BitWord(data);
		GPIOD->ODR &= ~(0x20);			// Pushimpuls auf WR
		GPIOD->ODR |= 0x80;					// CS = 1
		GPIOD->ODR |= 0x20;					// WR wieder auf 1
}

void LCD_WriteReg(uint16_t commando, uint16_t data){
	LCD_command(commando); 	// Schicke das Kommando
	LCD_data(data);					// Schicke die Daten
}





void drawLetter(uint16_t x, uint16_t y, uint8_t c, uint16_t color, uint16_t backgroundc){
    int letter = c;
    uint16_t x_pos = x;
		uint16_t y_pos = y;
		int a;
		int i;
		int j;
	  int z;

    for(a=0; a<32; a = a+2){
        int cnt = 0;
        char binary1[13] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', '\0',};
        for(i=7; i>=0; i--){
            if((console_font_12x16[(letter*32)+a]&(1<<i)) != 0){
                binary1[cnt] = '*';
            }
            cnt++;
        }
        for(j=7; j>3; j--){
            if((console_font_12x16[(letter*32)+(a+1)]&(1<<j)) != 0){
                binary1[cnt] = '*';
            }
            cnt++;
        }
				
				LCD_setCursor(x_pos,y_pos);
				y_pos++;
				//Ausgabe des Strings
				for(z=0; z<12; z++){
					if(binary1[z]=='*'){
						LCD_drawPixel(color);
					} else {
						LCD_drawPixel(backgroundc);
					}
				}
    }
}

// Drawstring mit automatischem Zeilenumbruch

void drawString(uint16_t x, uint16_t y, uint16_t color, uint16_t backgroundc, char* string){
	int i;
	int x_pos;
	int y_pos = y;
	int gleichi = 0;
	uint8_t character;
	for(i=0; i<strlen(string); i++){
		character = string[i];
		if((x+(gleichi*12))>=300){
			gleichi = 0;
			y_pos +=16;
		}
		x_pos = x+gleichi*12;
		drawLetter(x_pos, y_pos, character, color, backgroundc);
		gleichi++;
	}
}




