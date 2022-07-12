#include "STM32F4xx.h"
#include "_mcpr_stm32f407.h"
#include <inttypes.h>
#include "display.h"
#include <string.h>


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
