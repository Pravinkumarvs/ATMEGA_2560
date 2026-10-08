#ifndef ADC_H
#define ADC_H

#include <stdint.h>

#define ADC0   0
#define ADC1   1
#define ADC2   2
#define ADC3   3
#define ADC4   4
#define ADC5   5
#define ADC6   6
#define ADC7   7
#define ADC8   8
#define ADC9   9
#define ADC10  10
#define ADC11  11
#define ADC12  12
#define ADC13  13
#define ADC14  14
#define ADC15  15

void adc_init(void);
uint16_t adc_read(uint8_t channel);

#endif