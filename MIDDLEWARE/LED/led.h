#ifndef LED_H
#define LED_H

#include <stdint.h>
#include "gpio.h"

typedef struct
{
    port_t  port;
    uint8_t pin;
    uint8_t state;
} led_t;

void led_init(led_t *led, port_t port, uint8_t pin);
void led_on(led_t *led);
void led_off(led_t *led);
void led_toggle(led_t *led);

#endif
