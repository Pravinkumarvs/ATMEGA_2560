
#ifndef PWM_H
#define PWM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void pwm_init(void);
void pwm_set_duty(uint8_t duty);
void pwm_on(void);
void pwm_off(void);

#ifdef __cplusplus
}
#endif

#endif
