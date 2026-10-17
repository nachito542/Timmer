#include "pwm.h"

void pwm_init(uint8_t canal, uint32_t frec) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;
    uint32_t timer_clock = 72000000;
    uint32_t psc_val = 71; 
    uint32_t arr_val = (1000000 / frec) - 1;
    TIM3->PSC = psc_val;
    TIM3->ARR = arr_val;
     if (canal == 1) {
        GPIOA->CRL &= ~(0xF << (6 * 4));
        GPIOA->CRL |=  (0xB << (6 * 4)); TIM3->CCMR1 &= ~TIM_CCMR1_OC1M;
        TIM3->CCMR1 |=  (6 << TIM_CCMR1_OC1M_Pos) | TIM_CCMR1_OC1PE;
        TIM3->CCER  |=  TIM_CCER_CC1E;
    } 
    else if (canal == 2) {
        GPIOA->CRL &= ~(0xF << (7 * 4));
        GPIOA->CRL |=  (0xB << (7 * 4));

        TIM3->CCMR1 &= ~TIM_CCMR1_OC2M;
        TIM3->CCMR1 |=  (6 << TIM_CCMR1_OC2M_Pos) | TIM_CCMR1_OC2PE;
        TIM3->CCER  |=  TIM_CCER_CC2E;
    } 
    else if (canal == 3) {
        GPIOB->CRL &= ~(0xF << (0 * 4));
        GPIOB->CRL |=  (0xB << (0 * 4));

        TIM3->CCMR2 &= ~TIM_CCMR2_OC3M;
        TIM3->CCMR2 |=  (6 << TIM_CCMR2_OC3M_Pos) | TIM_CCMR2_OC3PE;
        TIM3->CCER  |=  TIM_CCER_CC3E;
    } 
    else if (canal == 4) {
        GPIOB->CRL &= ~(0xF << (1 * 4));
        GPIOB->CRL |=  (0xB << (1 * 4));

        TIM3->CCMR2 &= ~TIM_CCMR2_OC4M;
        TIM3->CCMR2 |=  (6 << TIM_CCMR2_OC4M_Pos) | TIM_CCMR2_OC4PE;
        TIM3->CCER  |=  TIM_CCER_CC4E;
    }
     TIM3->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
    TIM3->EGR |= TIM_EGR_UG;
}

void pwm(uint8_t canal, uint8_t duty) {
    if (duty > 100) duty = 100;
     uint32_t ccr_val = ((TIM3->ARR + 1) * duty) / 100;

    switch (canal) {
        case 1: TIM3->CCR1 = ccr_val; break;
        case 2: TIM3->CCR2 = ccr_val; break;
        case 3: TIM3->CCR3 = ccr_val; break;
        case 4: TIM3->CCR4 = ccr_val; break;
        default: break;
    }
}