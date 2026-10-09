#ifndef PWM_H
#define PWM_H

#ifdef __cplusplus
extern "C" {
#endif

void pwm_init(void);
void pwm_set_duty(unsigned char duty);
void pwm_on(void);
void pwm_off(void);

#ifdef __cplusplus
}
#endif

#endif
