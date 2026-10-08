#ifndef IR_H
#define IR_H

#include <stdint.h>
#include "adc.h"

#define SLOT_AVAILABLE  0
#define SLOT_OCCUPIED   1

#define IR_THRESHOLD    512

void ir_init(uint8_t channel);
uint16_t ir_get_value(void);
uint8_t ir_read(void);

#endif