#ifndef SEGMENT_H
#define SEGMENT_H

#include <stdint.h>
#include "gpio.h"

// 7-segment display control function
void c_segment(port_t port, uint8_t data);//common cathode
void a_segment(port_t port, uint8_t data);//common anode

#endif