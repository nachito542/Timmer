#include "stm32f103xb.h"
#include "Timmer.h"
#include "pwm.h"

void adc_init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN;
    GPIOA->CRL &= ~(0xF << (0 * 4));
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
    ADC1->SMPR2 |= (7 << (0 * 3)); 
    ADC1->SQR3 = (0 << 0);
    ADC1->CR2 |= ADC_CR2_ADON; 
    for(volatile int i = 0; i < 1000; i++);
    ADC1->CR2 |= ADC_CR2_RSTCAL; 
    while (ADC1->CR2 & ADC_CR2_RSTCAL); 
    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL); 
}
uint16_t adc_read(void) {
    ADC1->CR2 |= ADC_CR2_ADON | ADC_CR2_EXTSEL;
    while (!(ADC1->SR & ADC_SR_EOC));
    return ADC1->DR;
}

int main(void) {
    delay_init();
    adc_init();
    pwm_init(1, 1000);
    uint16_t valor_adc = 0;
    uint8_t duty_cycle = 0;
    while (1) {
        valor_adc = adc_read();
        duty_cycle = (uint8_t)((valor_adc * 100) / 4095);
        pwm(1, duty_cycle);
        delay_ms(50);
    }
}