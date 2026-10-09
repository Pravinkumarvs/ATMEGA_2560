
#include "segment.h"
#include "gpio.h"
#include <stdint.h>

/* Common cathode: display digits 0-9 */
void c_segment(port_t port, uint8_t data)
{
    const uint8_t c[10] = {
        0x3F, 0x06, 0x5B, 0x4F, 0x66,
        0x6D, 0x7D, 0x07, 0x7F, 0x6F
    };

    if (data > 9)
        return;

    for (uint8_t pin = 0; pin < 8; pin++)
    {
        gpio_write(port, pin, (c[data] >> pin) & 1);
    }
}

/* Common anode: display digits 0-9 */
void a_segment(port_t port, uint8_t data)
{
    const uint8_t a[10] = {
        0xC0, 0xF9, 0xA4, 0xB0, 0x99,
        0x92, 0x82, 0xF8, 0x80, 0x90
    };

    if (data > 9)
        return;

    for (uint8_t pin = 0; pin < 8; pin++)
    {
        gpio_write(port, pin, (a[data] >> pin) & 1);
    }
}
