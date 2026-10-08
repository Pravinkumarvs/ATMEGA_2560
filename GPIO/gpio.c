#include "gpio.h"

#define SREG_REG (*(volatile uint8_t*)0x5F)

#define GPIO_VALID(port, pin) ((uint8_t)(port) <= PORT_L && (pin) < 8)

/* =========================
   DDR REGISTER ADDRESSES
   ========================= */

static volatile uint8_t* const ddr[11] =
{
    (volatile uint8_t*)0x21,    /* DDRA */
    (volatile uint8_t*)0x24,    /* DDRB */
    (volatile uint8_t*)0x27,    /* DDRC */
    (volatile uint8_t*)0x2A,    /* DDRD */
    (volatile uint8_t*)0x2D,    /* DDRE */
    (volatile uint8_t*)0x30,    /* DDRF */
    (volatile uint8_t*)0x33,    /* DDRG */
    (volatile uint8_t*)0x101,   /* DDRH */
    (volatile uint8_t*)0x104,   /* DDRJ */
    (volatile uint8_t*)0x107,   /* DDRK */
    (volatile uint8_t*)0x10A    /* DDRL */
};


/* =========================
   PORT REGISTER ADDRESSES
   ========================= */

static volatile uint8_t* const port_reg[11] =
{
    (volatile uint8_t*)0x22,    /* PORTA */
    (volatile uint8_t*)0x25,    /* PORTB */
    (volatile uint8_t*)0x28,    /* PORTC */
    (volatile uint8_t*)0x2B,    /* PORTD */
    (volatile uint8_t*)0x2E,    /* PORTE */
    (volatile uint8_t*)0x31,    /* PORTF */
    (volatile uint8_t*)0x34,    /* PORTG */
    (volatile uint8_t*)0x102,   /* PORTH */
    (volatile uint8_t*)0x105,   /* PORTJ */
    (volatile uint8_t*)0x108,   /* PORTK */
    (volatile uint8_t*)0x10B    /* PORTL */
};


/* =========================
   PIN REGISTER ADDRESSES
   ========================= */

static volatile uint8_t* const pin_reg[11] =
{
    (volatile uint8_t*)0x20,    /* PINA */
    (volatile uint8_t*)0x23,    /* PINB */
    (volatile uint8_t*)0x26,    /* PINC */
    (volatile uint8_t*)0x29,    /* PIND */
    (volatile uint8_t*)0x2C,    /* PINE */
    (volatile uint8_t*)0x2F,    /* PINF */
    (volatile uint8_t*)0x32,    /* PING */
    (volatile uint8_t*)0x100,   /* PINH */
    (volatile uint8_t*)0x103,   /* PINJ */
    (volatile uint8_t*)0x106,   /* PINK */
    (volatile uint8_t*)0x109    /* PINL */
};


/* =========================
   GPIO MODE
   ========================= */

void gpio_mode(port_t port, uint8_t pin, uint8_t mode)
{
    if (!GPIO_VALID(port, pin))
        return;

    /* read-modify-write must not be interrupted by an ISR on the same port */
    uint8_t sreg = SREG_REG;
    __asm__ __volatile__ ("cli" ::: "memory");

    if (mode == OUTPUT)
    {
        *ddr[port] |= (uint8_t)(1 << pin);
    }
    else
    {
        *ddr[port] &= (uint8_t)~(1 << pin);
    }

    SREG_REG = sreg;
}


/* =========================
   GPIO WRITE
   ========================= */

void gpio_write(port_t port, uint8_t pin, uint8_t value)
{
    if (!GPIO_VALID(port, pin))
        return;

    uint8_t sreg = SREG_REG;
    __asm__ __volatile__ ("cli" ::: "memory");

    if (value == HIGH)
    {
        *port_reg[port] |= (uint8_t)(1 << pin);
    }
    else
    {
        *port_reg[port] &= (uint8_t)~(1 << pin);
    }

    SREG_REG = sreg;
}


/* =========================
   GPIO READ
   ========================= */

uint8_t gpio_read(port_t port, uint8_t pin)
{
    if (!GPIO_VALID(port, pin))
        return LOW;

    return ((*pin_reg[port] & (uint8_t)(1 << pin)) != 0);
}


/* =========================
   DELAY
   ========================= */

void mydelayh(long count)
{
    volatile long i;

    for (i = 0; i < count; i++)
    {
        /* Delay */
    }
}

