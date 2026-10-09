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

/* 30 ms at 0.5 us per timer count */
#define ULTRA_TIMEOUT_COUNT 60000U

/* Returned when no echo arrives (no object or sensor not connected) */
#define ULTRA_NO_ECHO 0

#ifdef __cplusplus
extern "C" {
#endif

void ultra_init(void);
uint16_t ultra_getDistance(void);

#ifdef __cplusplus
}
#endif

#endif