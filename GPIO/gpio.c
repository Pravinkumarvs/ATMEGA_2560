#include "gpio.h"

/* =========================
   DDR REGISTER ADDRESSES
   ========================= */

volatile uint8_t* ddr[11] =
{
    (uint8_t*)0x21,    /* DDRA */
    (uint8_t*)0x24,    /* DDRB */
    (uint8_t*)0x27,    /* DDRC */
    (uint8_t*)0x2A,    /* DDRD */
    (uint8_t*)0x2D,    /* DDRE */
    (uint8_t*)0x30,    /* DDRF */
    (uint8_t*)0x33,    /* DDRG */
    (uint8_t*)0x101,   /* DDRH */
    (uint8_t*)0x104,   /* DDRJ */
    (uint8_t*)0x107,   /* DDRK */
    (uint8_t*)0x10A    /* DDRL */
};


/* =========================
   PORT REGISTER ADDRESSES
   ========================= */

volatile uint8_t* port_reg[11] =
{
    (uint8_t*)0x22,    /* PORTA */
    (uint8_t*)0x25,    /* PORTB */
    (uint8_t*)0x28,    /* PORTC */
    (uint8_t*)0x2B,    /* PORTD */
    (uint8_t*)0x2E,    /* PORTE */
    (uint8_t*)0x31,    /* PORTF */
    (uint8_t*)0x34,    /* PORTG */
    (uint8_t*)0x102,   /* PORTH */
    (uint8_t*)0x105,   /* PORTJ */
    (uint8_t*)0x108,   /* PORTK */
    (uint8_t*)0x10B    /* PORTL */
};


/* =========================
   PIN REGISTER ADDRESSES
   ========================= */

volatile uint8_t* pin_reg[11] =
{
    (uint8_t*)0x20,    /* PINA */
    (uint8_t*)0x23,    /* PINB */
    (uint8_t*)0x26,    /* PINC */
    (uint8_t*)0x29,    /* PIND */
    (uint8_t*)0x2C,    /* PINE */
    (uint8_t*)0x2F,    /* PINF */
    (uint8_t*)0x32,    /* PING */
    (uint8_t*)0x100,   /* PINH */
    (uint8_t*)0x103,   /* PINJ */
    (uint8_t*)0x106,   /* PINK */
    (uint8_t*)0x109    /* PINL */
};


/* =========================
   GPIO MODE
   ========================= */

void gpio_mode(port_t port, uint8_t pin, uint8_t mode)
{
    if (mode == OUTPUT)
    {
        *ddr[port] |= (uint8_t)(1 << pin);
    }
    else
    {
        *ddr[port] &= (uint8_t)~(1 << pin);
    }
}


/* =========================
   GPIO WRITE
   ========================= */

void gpio_write(port_t port, uint8_t pin, uint8_t value)
{
    if (value == HIGH)
    {
        *port_reg[port] |= (uint8_t)(1 << pin);
    }
    else
    {
        *port_reg[port] &= (uint8_t)~(1 << pin);
    }
}


/* =========================
   GPIO READ
   ========================= */

uint8_t gpio_read(port_t port, uint8_t pin)
{
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

