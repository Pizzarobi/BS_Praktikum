#include "STM32F4xx.h"
#include "_mcpr_stm32f407.h"
#include <inttypes.h>
#include "func.h"



int main(void)
{
	uint32_t time = 1050;
	mcpr_SetSystemCoreClock();

	// Peripheral GPIOD einschalten
	RCC->AHB1ENR |= 1<<3|1;

	// Orange LED konfigurieren
	GPIOD->MODER |= 1<<24;
	GPIOD->ODR |= 1<<12;
	
	
	while( 1 ) {
		if( (GPIOA->IDR & 1) == 0) { 
			GPIOD->ODR |= ~(1<<12); 
		} else { 
			GPIOD->ODR |= 1<<12;
			u_delay(time);
			GPIOD->ODR &= ~(1<<12);
			u_delay(time);
		}
		
	}
		
}

void u_delay(uint32_t usec){
	int i = 0;
	int fac = 10000;
	while (i < fac * usec){ 
		i++; 
	}
}

