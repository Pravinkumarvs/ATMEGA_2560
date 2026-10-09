#include "adc.h"

void adc_init(void)
{
    ADMUX_REG = 0x40;
    ADCSRB_REG = 0x00;
    ADCSRA_REG = 0x87;
}

uint16_t adc_read(uint8_t channel)
{
    uint16_t value;

    if(channel > 15)
    {
        return 0;
    }

    ADMUX_REG = 0x40 | (channel & 0x07);

    if(channel >= 8)
    {
        ADCSRB_REG = 0x08;
    }
    else
    {
        ADCSRB_REG = 0x00;
    }

    ADCSRA_REG |= (1 << 6);

    while(ADCSRA_REG & (1 << 6))
    {
    }

    value = ADCL_REG;
    value |= ((uint16_t)ADCH_REG << 8);

    return value;
}