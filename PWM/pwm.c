
#include <stdint.h>
#include "gpio.h"
#include "pwm.h"

/* =========================
   TIMER3 REGISTER ADDRESSES
   ATmega2560
   ========================= */

#define TCCR3A_REG  (*(volatile uint8_t *)0x90)
#define TCCR3B_REG  (*(volatile uint8_t *)0x91)
#define ICR3_REG    (*(volatile uint16_t *)0x96)
#define OCR3A_REG   (*(volatile uint16_t *)0x98)

/* =========================
   TIMER3 BIT DEFINITIONS
   ========================= */

#define COM3A1  7
#define COM3A0  6

#define WGM31   1
#define WGM33   4
#define WGM32   3

#define CS32    2
#define CS31    1
#define CS30    0

/* =========================
   PWM INITIALIZATION
   ========================= */

void pwm_init(void)
{
    /* PE3 = OC3A = Arduino Mega pin 5 */
    gpio_mode(PORT_E, 3, OUTPUT);
    gpio_write(PORT_E, 3, LOW);

    /* Stop Timer3 during configuration */
    TCCR3A_REG = 0x00;
    TCCR3B_REG = 0x00;

    /* Fast PWM Mode 14: TOP = ICR3 */
    TCCR3A_REG |= (1 << WGM31);

    TCCR3B_REG |= (1 << WGM33) |
                  (1 << WGM32);

    /* Set PWM frequency to approximately 2 kHz */
    ICR3_REG = 999;

    /* Initial duty cycle = 0% */
    OCR3A_REG = 0;
}

/* =========================
   SET PWM DUTY CYCLE
   duty = 0 to 100
   ========================= */

void pwm_set_duty(uint8_t duty)
{
    if (duty > 100)
    {
        duty = 100;
    }

    OCR3A_REG =
        ((uint32_t)duty * ICR3_REG) / 100;
}

/* =========================
   START PWM
   ========================= */

void pwm_on(void)
{
    /* Enable non-inverting PWM on OC3A */
    TCCR3A_REG &= ~((1 << COM3A1) |
                    (1 << COM3A0));

    TCCR3A_REG |= (1 << COM3A1);

    /* Select prescaler = 8 */
    TCCR3B_REG &= ~((1 << CS32) |
                    (1 << CS31) |
                    (1 << CS30));

    TCCR3B_REG |= (1 << CS31);
}

/* =========================
   STOP PWM
   ========================= */

void pwm_off(void)
{
    /* Disconnect Timer3 output */
    TCCR3A_REG &= ~((1 << COM3A1) |
                    (1 << COM3A0));

    /* Stop Timer3 clock */
    TCCR3B_REG &= ~((1 << CS32) |
                    (1 << CS31) |
                    (1 << CS30));

    /* Set output LOW */
    gpio_write(PORT_E, 3, LOW);
}