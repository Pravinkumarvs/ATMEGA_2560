
#include "gpio.h"
#include "pwm.h"
#include <Arduino.h>
#include <avr/io.h>

void pwm_init(void)
{
    gpio_mode(PORT_E, 3, OUTPUT);

    TCCR3A = 0;
    TCCR3B = 0;

    /* Fast PWM Mode 14 */
    TCCR3A |= (1 << WGM31);
    TCCR3B |= (1 << WGM33) | (1 << WGM32);

    ICR3 = 999;
    OCR3A = 0;
}

void pwm_set_duty(unsigned char duty)
{
    if (duty > 100)
        duty = 100;

    OCR3A = ((unsigned long)duty * ICR3) / 100;
}

void pwm_on(void)
{
    TCCR3A &= ~((1 << COM3A1) | (1 << COM3A0));
    TCCR3A |= (1 << COM3A1);

    TCCR3B &= ~((1 << CS32) |
                (1 << CS31) |
                (1 << CS30));

    TCCR3B |= (1 << CS31);
}

void pwm_off(void)
{
    TCCR3A &= ~((1 << COM3A1) | (1 << COM3A0));

    TCCR3B &= ~((1 << CS32) |
                (1 << CS31) |
                (1 << CS30));

    gpio_write(PORT_E, 3, LOW);
}
