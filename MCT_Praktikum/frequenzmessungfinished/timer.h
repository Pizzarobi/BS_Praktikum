#ifndef _MYTIMER_H
#define _MYTIMER_H

#include "STM32F4xx.h"
#include "core_cm4.h"
#include "_mcpr_stm32f407.h"

extern volatile uint32_t ms;
extern volatile uint32_t overflow;
extern volatile uint32_t capture1;
extern volatile uint32_t capture2;
extern volatile uint32_t captureticks;


void timer7_init(void);
void timer4_init(void);
void timer12_init(void);
void TIM7_IRQHandler(void);
void TIM12_IRQHandler(void);


#endif
