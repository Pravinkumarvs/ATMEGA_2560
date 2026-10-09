#include "gpio.h"
#include "pwm.h"
#include <avr/io.h>

void pwm_init(void)
{
    /* OC3A = PE3 = Arduino Mega D5 (OC4A is PH3/D6, so Timer3 is used) */
    gpio_mode(PORT_E, 3, OUTPUT);

    /* Initially LOW */
    gpio_write(PORT_E, 3, 0);

    /* Stop Timer3 */
    TCCR3A = 0;
    TCCR3B = 0;

    /*
     * Fast PWM Mode 14
     * TOP = ICR3
     */
    TCCR3A |= (1 << WGM31);

    TCCR3B |= (1 << WGM33) |
              (1 << WGM32);

    /*
     * 16 MHz / (8 × (999 + 1))
     * = 2 kHz
     */
    ICR3 = 999;

    /* 0% duty initially */
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
    /*
     * Non-inverting PWM
     * COM3A1:0 = 10
     */
    TCCR3A &= ~((1 << COM3A1) |
                (1 << COM3A0));

    TCCR3A |= (1 << COM3A1);

    /*
     * Prescaler = 8
     * CS32:0 = 010
     */
    TCCR3B &= ~((1 << CS32) |
                (1 << CS31) |
                (1 << CS30));

    TCCR3B |= (1 << CS31);
}


void pwm_off(void)
{
    /* Disconnect PWM */
    TCCR3A &= ~((1 << COM3A1) |
                (1 << COM3A0));

    /* Stop Timer3 */
    TCCR3B &= ~((1 << CS32) |
                (1 << CS31) |
                (1 << CS30));

    /* Output LOW */
    gpio_write(PORT_E, 3, 0);
}