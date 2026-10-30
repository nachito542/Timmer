#include "Timmer.h"

uint32_t ms= 0;

void timer_init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2->CR1 &= ~TIM_CR1_CEN;// Lo fuerzo a 0
    TIM2->PSC = 7; 
    TIM2->ARR = 0xFFFF;
    TIM2->CNT = 0;
    TIM2->DIER |= TIM_DIER_UIE;
    TIM2->EGR |= TIM_EGR_UG;
    TIM2->SR = ~TIM_SR_UIF;
    NVIC_EnableIRQ(TIM2_IRQn);
    NVIC_SetPriority(TIM2_IRQn, 2);
    TIM2->CR1 |= TIM_CR1_CEN; // Lo fuerzo a 1
}

void TIM2_IRQHandler(void) {

    if (TIM2->SR & TIM_SR_UIF) {
        TIM2->SR = ~TIM_SR_UIF;
        ms += 65536;
    }
}

void delay_us(uint32_t us) {
    uint32_t start_us = TIM2->CNT;
    while ((TIM2->CNT - start_us) < us);
}

void delay_ms(uint32_t ms_val) {
    uint32_t start_ms = timer_millis();
    while ((timer_millis() - start_ms) < ms_val);
}

void delay_init(void) {
    timer_init();
}

uint32_t timer_millis(void) {
    uint32_t total_us = ms + TIM2->CNT;
    return total_us / 1000;
}