#include "switch.h"

static port_t switch_port;
static uint8_t switch_pin;

void switch_init(port_t port, uint8_t pin)
{
    switch_port = port;
    switch_pin = pin;

    gpio_mode(switch_port, switch_pin, INPUT);
}

uint8_t switch_read(void)
{
    if(gpio_read(switch_port, switch_pin) == HIGH)
    {
        return SWITCH_PRESSED;
    }
    else
    {
        return SWITCH_RELEASED;
    }
}