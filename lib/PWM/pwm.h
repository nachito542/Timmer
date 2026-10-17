#ifndef PWM_H
#define PWM_H

#include "stm32f103xb.h"
#include <stdint.h>

void pwm_init(uint8_t canal, uint32_t frec);
void pwm(uint8_t canal, uint8_t duty);

#endif