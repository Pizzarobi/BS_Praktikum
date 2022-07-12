#include "display.h"
#include "fonts.h"


void LCD_init(void){
	// Display-Reset
	GPIOD->ODR &= ~(0x8); // Low impuls auf PD3 --> Reset
	delayForFunction(1);
	GPIOD->ODR |= 0x8;
	
	// Initialisierungssequenzen senden
	LCD_WriteReg(0x0010, 0x0001); /* Enter sleep mode */
	LCD_WriteReg(0x001E, 0x00B2); /* Set initial power parameters. */
	LCD_WriteReg(0x0028, 0x0006); /* Set initial power parameters. */
	LCD_WriteReg(0x0000, 0x0001); /* Start the oscillator.*/
	LCD_WriteReg(0x0001, 0x72EF); /* Set pixel format and basic display orientation */
	LCD_WriteReg(0x0002, 0x0600);
	LCD_WriteReg(0x0010, 0x0000); /* Exit sleep mode.*/
	delayForFunction(1);// 30ms warten // weniger geht meist auch
	LCD_WriteReg(0x0011, 0x6870); /* Configure pixel color format and MCU interface parameters.*/
	LCD_WriteReg(0x0012, 0x0999); /* Set analog parameters */
	LCD_WriteReg(0x0026, 0x3800);
	LCD_WriteReg(0x0007, 0x0033); /* Enable the display */
	LCD_WriteReg(0x000C, 0x0005); /* Set VCIX2 voltage to 6.1V.*/
	LCD_WriteReg(0x000D, 0x000A); /* Configure Vlcd63 and VCOMl */
	LCD_WriteReg(0x000E, 0x2E00);
	LCD_WriteReg(0x0044, (240-1) << 8); /* Set the display size and ensure that the GRAM window
																				 is set to allow access to the full display buffer.*/
	LCD_WriteReg(0x0045, 0x0000);
	LCD_WriteReg(0x0046, 320-1);
	LCD_WriteReg(0x004E, 0x0000); /*Set cursor to 0,0 */
	LCD_WriteReg(0x004F, 0x0000);
}

void LCD_setCursor(uint16_t x, uint16_t y){
	LCD_WriteReg(0x004E,x);
	LCD_WriteReg(0x004F,y);
}


void LCD_drawPixel(uint16_t color){
	LCD_WriteReg(0x0022, color);
}


void clearDisplay(uint16_t color){
	int i;
	LCD_setCursor(0,0);
	for(i=0; i<320*260; i++){
		LCD_drawPixel(color);
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

void activateDisplay(void){
	//clearDisplay(hintergrundfarbe);
	// Hintergrundbeleuchtung aktivieren
	GPIOD->MODER |= 1<<26;
	GPIOD->ODR |= 1<<13;
}

void deactivateDisplay(void){
	// Hintergrundbeleuchtung aktivieren
	//clearDisplay(hintergrundfarbe);
	GPIOD->ODR &= ~(1<<13);
}
