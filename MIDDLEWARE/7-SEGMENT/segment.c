#include "segment.h"
#include "gpio.h"

/* Segments a-g (+dp) on pins 0-7 of the selected port */
static void segment_write(uint8_t ports, uint8_t pattern)
{
  for(uint8_t i = 0; i < 8; i++)
  {
    gpio_mode((port_t)ports, i, OUTPUT);
    gpio_write((port_t)ports, i, (pattern >> i) & 1);
  }
}

//for 0-9 in 7 segment in common cathode
void c_segment(uint8_t ports, uint8_t data)
{
  static const uint8_t c[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

  if(data > 9)
    return;

  segment_write(ports, c[data]);
}

//for 0-9 in 7 segment in common anode
void a_segment(uint8_t ports, uint8_t data)
{
  static const uint8_t a[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

  if(data > 9)
    return;

  segment_write(ports, a[data]);
}
