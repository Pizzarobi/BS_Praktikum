#include "func.h"
#include "timer.h"
#include "display.h"
#include "stdio.h"



volatile uint32_t ms = 0;
volatile uint32_t overflow = 0;
volatile uint32_t capture1 = 0;
volatile uint32_t capture2 = 0;
volatile uint32_t captureticks = 0;
uint32_t frequenz;
char seconds[30];
char ticks[50];
char frequenzarray[30];

int main(void)
{
	uint32_t dauer = 0;
	
	// Anschalten
	mcpr_SetSystemCoreClock();
	
	// -------------------------------------------
	// Peripherals einschalten
	// -------------------------------------------

	RCC->AHB1ENR |= 1<<3|1;				// Peripheral GPIOD einschalten
	
	RCC->AHB1ENR |= 1<<4|1;				// Peripheral GPIOE einschalten
	
	// -------------------------------------------
	// Display Konfiguration
	// -------------------------------------------
	
	// GPIOs f�r Display
	GPIOE->MODER |= 0x55554040;
	GPIOD->MODER |= 0x55154545;
	
	//Read auf 1
	GPIOD->MODER 	|= 1<<8;
	GPIOD->ODR		|= 1<<4;
	
	
	// -------------------------------------------
	// LED Konfiguration
	// -------------------------------------------
	
	// GPIOs für grüne LED konfigurieren
	GPIOD->MODER |= 1<<24;
	GPIOD->ODR |= 1<<12;
	
	// GPIOs für die Disyplay-Dimmung konfigurieren
	// Umstellen des Port 13 auf Alternate Function
	GPIOD->MODER |= 1<<27;
	GPIOD->MODER &= ~(1<<26);
	
	// -------------------------------------------
	// Initialisierungen
	// -------------------------------------------
	
	LCD_init(); 					// Initialisierung des Displays
	
	timer7_init();				// Initialisierung des Timers
	
	timer4_init();
	
	timer12_init();
	
	// -------------------------------------------
	// Funktionen
	// -------------------------------------------
	
	//clearDisplay(hintergrundfarbe); 	// Display Farbe einstellen
	
	//drawString(5,5, fontcolor, hintergrundfarbe, satz); // Stringausgabe
	
		
	// Grüne LED mit Frequenz 1Hz blinken lassen & Displayreset nach 10sek
	dauer = ms;
	clearDisplay(hintergrundfarbe);
	while(1){
		uint16_t wartevariable=0;
		dauer = ms;
		sprintf(seconds, "Laufzeit: %5d.%1d sek", (ms/1000), (ms%10));
		drawString(20, 20, fontcolor, hintergrundfarbe, seconds);
		// Frequenz berechnen
		frequenz = 84000000/captureticks;
		sprintf(frequenzarray, "Frequenz: %7d Hz", frequenz);
		drawString(20, 40, fontcolor, hintergrundfarbe, frequenzarray);
		
		sprintf(ticks, "Tickzahl: %7d Ticks", captureticks);
		drawString(20, 60, fontcolor, hintergrundfarbe, ticks);

			while(ms < dauer+20){					// Warteschleife "busy-waiting", damit die Hauptschleife 50 mal/sek durchläuft (alle 20ms)
				wartevariable++;
			}
			dauer+=20;
			
		}
}
