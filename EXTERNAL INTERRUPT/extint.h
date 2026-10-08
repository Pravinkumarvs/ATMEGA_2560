#ifndef EXTINT_H
#define EXTINT_H

#include <stdint.h>

#define INT_LOW_LEVEL       0
#define INT_CHANGE          1
#define INT_FALLING         2
#define INT_RISING          3

void extint_init(uint8_t interrupt, uint8_t mode);
void extint_enable(uint8_t interrupt);
void extint_disable(uint8_t interrupt);

#endif