#include "gpio.h"
#include "pwm.h"
#include <avr/io.h>

static uint8_t pwm_running;

static void pwm_connect(void)
{
    /*
     * Non-inverting PWM
     * COM4A1:0 = 10
     */
    TCCR4A &= ~((1 << COM4A1) |
                (1 << COM4A0));

    TCCR4A |= (1 << COM4A1);
}

static void pwm_disconnect(void)
{
    TCCR4A &= ~((1 << COM4A1) |
                (1 << COM4A0));

    /* Output LOW */
    gpio_write(PORT_H, 3, 0);
}

void pwm_init(void)
{
    /* OC4A = PH3 = Arduino Mega D6 */
    gpio_mode(PORT_H, 3, OUTPUT);

    /* Initially LOW */
    gpio_write(PORT_H, 3, 0);

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

    pwm_running = 0;
}


void pwm_set_duty(unsigned char duty)
{
    if (duty > 100)
        duty = 100;

    OCR4A = ((unsigned long)duty * ICR4) / 100;

    /*
     * OCR4A = 0 still gives a 1-tick spike every period,
     * so detach the pin for a true 0%
     */
    if (duty == 0)
        pwm_disconnect();
    else if (pwm_running)
        pwm_connect();
}


void pwm_on(void)
{
    pwm_running = 1;

    if (OCR4A != 0)
        pwm_connect();

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
    pwm_running = 0;

    /* Stop Timer4 */
    TCCR4B &= ~((1 << CS42) |
                (1 << CS41) |
                (1 << CS40));

    pwm_disconnect();
}