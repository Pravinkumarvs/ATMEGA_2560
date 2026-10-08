#ifndef ULTRA_H
#define ULTRA_H

#include <stdint.h>
#include "gpio.h"
#include "timer.h"

/* ==========================
   ULTRASONIC PIN CONFIGURATION
   ========================== */

#define ULTRA_TRIG_PORT PORT_B
#define ULTRA_TRIG_PIN  7

#define ULTRA_ECHO_PORT PORT_B
#define ULTRA_ECHO_PIN  6

#ifdef __cplusplus
extern "C" {
#endif

void ultra_init(void);
uint16_t ultra_getDistance(void);

#ifdef __cplusplus
}
#endif

#endif