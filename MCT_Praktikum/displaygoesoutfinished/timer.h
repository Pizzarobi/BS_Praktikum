#ifndef _MYTIMER_H
#define _MYTIMER_H

#include "STM32F4xx.h"
#include "core_cm4.h"
#include "_mcpr_stm32f407.h"

extern volatile uint32_t ms;
extern char seconds[20];


void timer7_init(void);
void TIM7_IRQHandler(void);


#endif
