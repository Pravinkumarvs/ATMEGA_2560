#ifndef SWITCH_H
#define SWITCH_H

#include <stdint.h>
#include "gpio.h"

#define SWITCH_RELEASED  0
#define SWITCH_PRESSED   1

/*
 * Wiring: switch between the pin and GND.
 * The internal pull-up is enabled, so the pin reads LOW when pressed.
 */
typedef struct
{
    port_t  port;
    uint8_t pin;
} switch_t;

void switch_init(switch_t *sw, port_t port, uint8_t pin);
uint8_t switch_read(switch_t *sw);

#endif
