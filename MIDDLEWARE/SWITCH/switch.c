#include "switch.h"

void switch_init(switch_t *sw, port_t port, uint8_t pin)
{
    sw->port = port;
    sw->pin = pin;

    gpio_mode(sw->port, sw->pin, INPUT);

    /* enable internal pull-up */
    gpio_write(sw->port, sw->pin, HIGH);
}

uint8_t switch_read(switch_t *sw)
{
    if(gpio_read(sw->port, sw->pin) == LOW)
    {
        return SWITCH_PRESSED;
    }
    else
    {
        return SWITCH_RELEASED;
    }
}
