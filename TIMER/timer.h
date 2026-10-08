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

/*
 * NOTE: every function below uses Timer1. Do not call a delay while a
 * timer_start()/timer_stop() measurement is running (e.g. ultra_getDistance),
 * and do not use them from an ISR while main code is using them.
 */

/* TIMER DELAY FUNCTIONS */
void timer_delay_s(uint16_t s);       // Delay in seconds
void timer_delay_ms(uint16_t ms);     // Delay in milliseconds
void timer_delay_us(uint16_t us);     // Delay in microseconds

// Timer control functions
void timer_start(void);
void timer_stop(void);
void timer_reset(void);
uint16_t timer_get_count(void);

#endif