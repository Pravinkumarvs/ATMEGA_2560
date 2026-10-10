
#include "two_segment.h"
#include "gpio.h"

/* Shared segment port and digit selection pins */
static port_t segment_port;
static port_t select_port;

static uint8_t dig1_pin;
static uint8_t dig2_pin;

static uint8_t tens;
static uint8_t units;
static uint8_t current_digit;

/* Common-cathode digit patterns: a,b,c,d,e,f,g,dp */
static const uint8_t digit_code[10] =
{
    0x3F, 0x06, 0x5B, 0x4F, 0x66,
    0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

/* Custom segment patterns for special display */
#define HH_PATTERN 0x73

static void write_segments(uint8_t value)
{
    uint8_t pattern;

    if (value == 10)
    {
        pattern = 0x73;  // Your HH segment pattern
    }
    else
    {
        pattern = digit_code[value];
    }

    for (uint8_t pin = 0; pin < 8; pin++)
    {
        gpio_write(segment_port, pin,
                   (pattern >> pin) & 1);
    }
}

void two_segment_init(port_t seg_port,
                      port_t digit_port,
                      uint8_t digit1_pin,
                      uint8_t digit2_pin)
{
    segment_port = seg_port;
    select_port = digit_port;

    dig1_pin = digit1_pin;
    dig2_pin = digit2_pin;

    for (uint8_t pin = 0; pin < 8; pin++)
        gpio_mode(segment_port, pin, OUTPUT);

    gpio_mode(select_port, dig1_pin, OUTPUT);
    gpio_mode(select_port, dig2_pin, OUTPUT);

    /* Both digits OFF */
    gpio_write(select_port, dig1_pin, HIGH);
    gpio_write(select_port, dig2_pin, HIGH);

    tens = 0;
    units = 0;
    current_digit = 0;
}



void two_segment_display(uint8_t number)
{
    if (number == 100)
    {
        tens = 10;   // Special HH marker
        units = 10;  // Special HH marker
    }
    else
    {
        if (number > 99)
            number = 99;

        tens = number / 10;
        units = number % 10;
    }
}