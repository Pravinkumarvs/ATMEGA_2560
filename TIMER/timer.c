#include "timer.h"

// Delay in seconds
void timer_delay_s(uint16_t s)
{
    for(uint16_t s_count = 0; s_count < s; s_count++){
        TIMER1_A = 0x00;
        TIMER1_CNT = 0;
        TIMER1_OCR = 62499;

        TIMER1_FLAG = (1 << 1);

        TIMER1_B = 0x0C;

        while(!(TIMER1_FLAG & (1 << 1)))
        {
        }

        TIMER1_B = 0x00;
    }
}

// Delay in milliseconds
void timer_delay_ms(uint16_t ms){
    for(uint16_t ms_count = 0; ms_count < ms; ms_count++){
        TIMER1_A = 0x00;
        TIMER1_CNT = 0;
        TIMER1_OCR = 249;

        TIMER1_FLAG = (1 << 1);

        TIMER1_B = 0x0B;

        while(!(TIMER1_FLAG & (1 << 1)))
        {
        }

        TIMER1_B = 0x00;
    }
}

// Delay in microseconds
void timer_delay_us(uint16_t us){
    if(us == 0)
    {
        return;
    }

    /* OCR is 16-bit: 0.5 us per count allows at most 32767 us */
    if(us > 32767)
    {
        timer_delay_us(us - 32767);
        us = 32767;
    }

    TIMER1_A = 0x00;
    TIMER1_CNT = 0;

    TIMER1_OCR = (us * 2) - 1;

    TIMER1_FLAG = (1 << 1);

    TIMER1_B = 0x0A;

    while(!(TIMER1_FLAG & (1 << 1)))
    {
    }

    TIMER1_B = 0x00;
}

// Start Timer1
void timer_start(void)
{
    TIMER1_A = 0x00;
    TIMER1_B = 0x02;
}

// Stop Timer1
void timer_stop(void)
{
    TIMER1_B = 0x00;
}

// Reset Timer1 count
void timer_reset(void)
{
    TIMER1_CNT = 0;
    TIMER1_FLAG = (1 << 0);
}

// Get Timer1 count
uint16_t timer_get_count(void)
{
    return TIMER1_CNT;
}