#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdint.h>
#include "gpio.h"

void keypad_init(void);
char keypad_get_key(void);

#endif