
#ifndef TWO_SEGMENT_H
#define TWO_SEGMENT_H

#include <stdint.h>
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Initialize 2-digit 7-segment display */
void two_segment_init(port_t seg_port,
                      port_t digit_port,
                      uint8_t digit1_pin,
                      uint8_t digit2_pin);

/* Display a number from 0 to 99 */
void two_segment_display(uint8_t number);

/* Refresh the multiplexed display */
void two_segment_refresh(void);

#ifdef __cplusplus
}
#endif

#endif
