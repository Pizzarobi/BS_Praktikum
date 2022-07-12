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
	NVIC_SetPriority(TIM7_IRQn, 7); // Erst Priorit�t setzen, dann einschalten! Bei falscher Priorit�t evtl. Probleme
	NVIC_EnableIRQ(TIM7_IRQn);
}

void TIM7_IRQHandler(){
	TIM7->SR &= ~(0x1);
	ms+=1; // Muss uint sein! Unsigned!
	sprintf(seconds, "%d.%2d", (ms/1000), (ms%1000));
}

void timer4_init(void){
	// Peripheral TIMER4 einschalten
	RCC->APB1ENR |= 1<<2;
	GPIOD->AFR[1] |= 0x200000;
	// Register konfigurieren
	TIM4->PSC = 0x53;
	TIM4->ARR = 0x1387;
	TIM4->CR1 |= 0x1;
	
	TIM4->CCMR1 |= 0x6000;
	TIM4->CCER |= 1<<4;
	TIM4->CCR2 = 0x1F3;
}
