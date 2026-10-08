#include "gpio.h"
#include "pwm.h"
#include <avr/io.h>

void pwm_init(void)
{
    /* OC4A = PE3 = Arduino Mega D5 */
    gpio_mode(PORT_E, 3, OUTPUT);

    /* Initially LOW */
    gpio_write(PORT_E, 3, 0);

    /* Stop Timer4 */
    TCCR4A = 0;
    TCCR4B = 0;

    /*
     * Fast PWM Mode 14
     * TOP = ICR4
     */
    TCCR4A |= (1 << WGM41);

    TCCR4B |= (1 << WGM43) |
              (1 << WGM42);

    /*
     * 16 MHz / (8 × (999 + 1))
     * = 2 kHz
     */
    ICR4 = 999;

    /* 0% duty initially */
    OCR4A = 0;
}


void pwm_set_duty(unsigned char duty)
{
    if (duty > 100)
        duty = 100;

    OCR4A = ((unsigned long)duty * ICR4) / 100;
}


void pwm_on(void)
{
    /*
     * Non-inverting PWM
     * COM4A1:0 = 10
     */
    TCCR4A &= ~((1 << COM4A1) |
                (1 << COM4A0));

    TCCR4A |= (1 << COM4A1);

    /*
     * Prescaler = 8
     * CS42:0 = 010
     */
    TCCR4B &= ~((1 << CS42) |
                (1 << CS41) |
                (1 << CS40));

    TCCR4B |= (1 << CS41);
}


void pwm_off(void)
{
    /* Disconnect PWM */
    TCCR4A &= ~((1 << COM4A1) |
                (1 << COM4A0));

    /* Stop Timer4 */
    TCCR4B &= ~((1 << CS42) |
                (1 << CS41) |
                (1 << CS40));

    /* Output LOW */
    gpio_write(PORT_E, 3, 0);
}