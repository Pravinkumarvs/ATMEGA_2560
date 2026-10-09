
#ifndef SEGMENT_H
#define SEGMENT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// 7-segment display control function
void c_segment(uint8_t ports, uint8_t data); // common cathode
void a_segment(uint8_t ports, uint8_t data); // common anode

#ifdef __cplusplus
}
#endif

#endif
