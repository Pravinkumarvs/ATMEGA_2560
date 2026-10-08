#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <stdint.h>
#include "gpio.h"
#include "timer.h"

/* --------------------------
   Pin Configuration
   -------------------------- */

#define ULTRA_TRIG_PORT PORT_B
#define ULTRA_TRIG_PIN  7

#define ULTRA_ECHO_PORT PORT_B
#define ULTRA_ECHO_PIN  6

/* --------------------------
   Timeout
   -------------------------- */

/*
 * Timer1 runs at 2 MHz (0.5 us/count).
 * 60000 counts = 30 ms, ~517 cm: past the HC-SR04 range
 * and below the 16 bit overflow at 65535.
 */
#define ULTRA_TIMEOUT_COUNT 60000

/* returned when no echo arrives (no object / sensor unplugged) */
#define ULTRA_NO_ECHO       0xFFFF

/* --------------------------
   Function Prototypes
   -------------------------- */

void ultra_init(void);

uint16_t ultra_getDistance(void);

#endif