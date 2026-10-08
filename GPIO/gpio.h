#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/* =========================
   PORT DEFINITIONS
   ========================= */

typedef enum
{
    PORT_A,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E,
    PORT_F,
    PORT_G,
    PORT_H,
    PORT_J,
    PORT_K,
    PORT_L
} port_t;


/* =========================
   GPIO DEFINITIONS
   ========================= */

#define INPUT   0
#define OUTPUT  1

#define LOW     0
#define HIGH    1


/* =========================
   FUNCTION DECLARATIONS
   ========================= */

void gpio_mode(port_t port, uint8_t pin, uint8_t mode);

void gpio_write(port_t port, uint8_t pin, uint8_t value);

uint8_t gpio_read(port_t port, uint8_t pin);

void mydelayh(long count);



#endif