
#ifndef TIMMER_H
#define TIMMER_H

#include "stm32f103xb.h"
#include <stdint.h>

void delay_init(void);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
void timer_init(void);
uint32_t timer_millis(void);

#endif