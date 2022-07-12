#include "func.h"
#include "timer.h"
#include "display.h"



volatile uint32_t ms = 0;
char seconds[20];

int main(void)
{
	uint8_t status=0;
	uint32_t ledstatus=0;
	uint32_t dauer = 0;
	uint32_t hintergrundbeleuchtung = 0;
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
		drawString(20, 220, fontcolor, hintergrundfarbe, seconds);
		
		
			if((GPIOA->IDR & 1) == 0){ // Wenn Taster nicht gedrückt--> Lampe leuchtet
				ledstatus = 0;					 // Ledstatus = 0	
				GPIOD->ODR |= (1<<12);	 // Lampe leuchtet
					if(status == 1){			 // Abfrage -> Wurde vorher Knopf gedrückt & losgelassen? Dann Timer bis Display aus.
						if(ms > hintergrundbeleuchtung+10000){
							TIM4->CCR2 -= 50;
							if(TIM4->CCR2 == 499){
								status = 0;
							}
						}
					}
			} else {
				if(status == 0){						// Wenn der Status vorher noch 0 war -->
					status = 1;  							// Statusvariable auf 1 setzen
					TIM4->CCR2 = 0x1387;					// Hintergrundbeleuchtung aktivieren
					
				}
				if(ledstatus == 0){					// Zeitinitialisierung für die Grüne LED
					ledstatus = ms;
				}
				if(ms<ledstatus+500){				// Wenn Zeit >500ms --> LED aus
					GPIOD->ODR &= ~(1<<12);
				}
				if(ms >= ledstatus+500 && ms<ledstatus+1000){	// Wenn Zeit <500ms && >1000ms --> LED an
					GPIOD->ODR |= (1<<12);
				}
				if(ledstatus+1000 < ms){		// Wenn Zeit >1000ms zurücksetzen des Status der LED und Wiederholung des Prozesses
					ledstatus = 0;
				}
				hintergrundbeleuchtung = ms;
			}
			
			while(ms < dauer+20){					// Warteschleife "busy-waiting", damit die Hauptschleife 50 mal/sek durchläuft (alle 20ms)
				wartevariable++;
			}
			dauer+=20;
		}
}
