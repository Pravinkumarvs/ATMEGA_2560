
#ifndef SEGMENT_H
#define SEGMENT_H

#include <stdint.h>
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

void c_segment(port_t port, uint8_t data);
void a_segment(port_t port, uint8_t data);

#ifdef __cplusplus
}
#endif

#endif
