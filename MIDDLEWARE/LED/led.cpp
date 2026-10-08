#include "led.h"

void led_init(led_t *led, port_t port, uint8_t pin)
{
    led->port = port;
    led->pin = pin;
    led->state = LOW;

    gpio_mode(led->port, led->pin, OUTPUT);
    gpio_write(led->port, led->pin, LOW);
}

void led_on(led_t *led)
{
    gpio_write(led->port, led->pin, HIGH);
    led->state = HIGH;
}

void led_off(led_t *led)
{
    gpio_write(led->port, led->pin, LOW);
    led->state = LOW;
}

void led_toggle(led_t *led)
{
    if(led->state == LOW)
    {
        led_on(led);
    }
    else
    {
        led_off(led);
    }
}
