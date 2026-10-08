#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

/* TIMER1 CONTROL REGISTERS */
#define TIMER1_A     (*(volatile uint8_t*)0x80)   // Timer1 Control Register A
#define TIMER1_B     (*(volatile uint8_t*)0x81)   // Timer1 Control Register B

/* TIMER1 COUNTER AND COMPARE REGISTER */
#define TIMER1_CNT   (*(volatile uint16_t*)0x84)   // Timer1 Counter
#define TIMER1_OCR   (*(volatile uint16_t*)0x88)   // Timer1 Output Compare

/* TIMER1 INTERRUPT AND FLAG REGISTERS */
#define TIMER1_INT   (*(volatile uint8_t*)0x6F)   // Timer1 Interrupt Control
#define TIMER1_FLAG  (*(volatile uint8_t*)0x36)   // Timer1 Interrupt Flag

#ifdef __cplusplus
extern "C" {
#endif

void timer_delay_s(uint16_t s);
void timer_delay_ms(uint16_t ms);
void timer_delay_us(uint16_t us);

void timer_start(void);
void timer_stop(void);
void timer_reset(void);
uint16_t timer_get_count(void);

#ifdef __cplusplus
}
#endif

#endif