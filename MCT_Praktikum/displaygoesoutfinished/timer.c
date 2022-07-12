#include "timer.h"
#include <stdio.h>


// -----------------------------------------------
// Timer
// -----------------------------------------------


void timer7_init(void){
	// Peripheral TIMER7 einschalten
	RCC->APB1ENR |= 1<<5;
	// Register konfigurieren
	TIM7->DIER |= 0x1;
	TIM7->PSC = 0x53;
	TIM7->ARR = 0x3E7;
	TIM7->CR1 |= 0x1;
	NVIC_SetPriority(TIM7_IRQn, 7); // Erst Priorität setzen, dann einschalten! Bei falscher Priorität evtl. Probleme
	NVIC_EnableIRQ(TIM7_IRQn);
}

void TIM7_IRQHandler(){
	TIM7->SR &= ~(0x1);
	ms+=1; // Muss uint sein! Unsigned!
	sprintf(seconds, "%d.%2d", (ms/1000), (ms%1000));
}