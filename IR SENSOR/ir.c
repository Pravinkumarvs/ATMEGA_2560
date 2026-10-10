#include "ir.h"

static uint8_t ir_channel;

void ir_init(uint8_t channel)
{
    ir_channel = channel;

    adc_init();
}

uint16_t ir_get_value(void)
{
    return adc_read(ir_channel);
}

uint8_t ir_read(void)
{
    uint16_t value;

    value = adc_read(ir_channel);

    if(value < IR_THRESHOLD)
    {
        return SLOT_OCCUPIED;
    }
    else
    {
        return SLOT_AVAILABLE;
    }
}

/* ========== IR SENSOR DEBOUNCE ========== */
