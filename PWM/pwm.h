#ifndef PWM_H
#define PWM_H

void pwm_init(void);
void pwm_set_duty(unsigned char duty);
void pwm_on(void);
void pwm_off(void);

#endif