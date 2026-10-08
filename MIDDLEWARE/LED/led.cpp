#include "led.h"

static port_t led_port;
static uint8_t led_pin;
static uint8_t led_state;

void led_init(port_t port, uint8_t pin)
{
    led_port = port;
    led_pin = pin;
    led_state = LOW;

    gpio_mode(led_port, led_pin, OUTPUT);
    gpio_write(led_port, led_pin, LOW);
}

void led_on(void)
{
    gpio_write(led_port, led_pin, HIGH);
    led_state = HIGH;
}

void led_off(void)
{
    gpio_write(led_port, led_pin, LOW);
    led_state = LOW;
}

void led_toggle(void)
{
    if(led_state == LOW)
    {
        led_on();
    }
    else
    {
        led_off();
    }
}