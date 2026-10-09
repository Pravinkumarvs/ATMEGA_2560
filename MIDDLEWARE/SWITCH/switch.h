
#ifndef SWITCH_H
#define SWITCH_H

#include <stdint.h>
#include "gpio.h"

#define SWITCH_RELEASED  0
#define SWITCH_PRESSED   1

#ifdef __cplusplus
extern "C" {
#endif

void switch_init(port_t port, uint8_t pin);
uint8_t switch_read(void);

#ifdef __cplusplus
}
#endif

#endif
