#include "extint.h"

#define EIMSK_REG (*(volatile uint8_t*)0x3D)
#define EICRA_REG (*(volatile uint8_t*)0x69)
#define EICRB_REG (*(volatile uint8_t*)0x6A)

void extint_init(uint8_t interrupt, uint8_t mode)
{
    if(interrupt < 4)
    {
        EICRA_REG &= ~(0x03 << (interrupt * 2));
        EICRA_REG |= (mode << (interrupt * 2));
    }
    else
    {
        EICRB_REG &= ~(0x03 << ((interrupt - 4) * 2));
        EICRB_REG |= (mode << ((interrupt - 4) * 2));
    }
}

void extint_enable(uint8_t interrupt)
{
    EIMSK_REG |= (1 << interrupt);
}

void extint_disable(uint8_t interrupt)
{
    EIMSK_REG &= ~(1 << interrupt);
}