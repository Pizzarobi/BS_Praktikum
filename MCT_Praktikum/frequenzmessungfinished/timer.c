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
	//TIM4->CCR2 = 0x1F3;
	TIM4->CCR2 = 0x1387;
}

void timer12_init(void){
	// Peripheral Register B einschalten
	RCC->AHB1ENR |= 1<<1;
	// Pin PB14 konfigurieren
	GPIOB->MODER |= 1<<29;
	GPIOB->MODER &= ~(1<<28);
	GPIOB->AFR[1] |= 9<<24;
	// Peripheral TIMER12 einschalten
	RCC->APB1ENR |= 1<<6;
	// Register konfigurieren
	TIM12->PSC = 0;
	TIM12->ARR = 0xFFFF;		// Reloadregister auf Maximum
	TIM12->CCMR1 |= 0x1;		// 
	TIM12->CCER |= 0x1;			// Enable Capture-/Compareregister
	TIM12->DIER |= 0x3;
	NVIC_SetPriority(TIM8_BRK_TIM12_IRQn, 10);
	NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn);
	TIM12->CR1 |= 0x1;
}
										
void TIM8_BRK_TIM12_IRQHandler(){
	if(TIM12->SR & 1){
		TIM12->SR &= ~(0x1);
		overflow += 1;	// Overflow
	}
	if(TIM12->SR & 2){
		TIM12->SR &= ~(0x2);
		capture2 = capture1;
		capture1 = TIM12->CCR1;	// Capture
		captureticks = capture1 - capture2;
		captureticks += overflow*0x10000;
		overflow = 0;
	}
}
