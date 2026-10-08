#ifndef LED_H
#define LED_H

#include <stdint.h>
#include "gpio.h"

void led_init(port_t port, uint8_t pin);
void led_on(void);
void led_off(void);
void led_toggle(void);

#endif