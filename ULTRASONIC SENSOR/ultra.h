#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <stdint.h>
#include "gpio.h"
#include "timer.h"

/* --------------------------
   Pin Configuration
   -------------------------- */

#define TRIG_PORT PORT_B
#define TRIG_PIN  7

#define ECHO_PORT PORT_B
#define ECHO_PIN  6

/* --------------------------
   Function Prototypes
   -------------------------- */

void ultrasonic_init(void);

uint16_t ultrasonic_getDistance(void);

#endif