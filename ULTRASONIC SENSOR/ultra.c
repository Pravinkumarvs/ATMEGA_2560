#include "ultra.h"
#include "timer.h"

/* ==========================
   INITIALIZATION
   ========================== */

void ultra_init(void)
{
    /* TRIG = OUTPUT */
    gpio_mode(
        ULTRA_TRIG_PORT,
        ULTRA_TRIG_PIN,
        OUTPUT
    );

    /* ECHO = INPUT */
    gpio_mode(
        ULTRA_ECHO_PORT,
        ULTRA_ECHO_PIN,
        INPUT
    );

    /* TRIG LOW */
    gpio_write(
        ULTRA_TRIG_PORT,
        ULTRA_TRIG_PIN,
        LOW
    );
}

/* ==========================
   DISTANCE MEASUREMENT
   ========================== */

uint16_t ultra_getDistance(void)
{
    uint16_t timer_count;
    uint32_t time_us;
    uint16_t distance;

    /* ------------------
       Trigger Pulse
       ------------------ */

    gpio_write(
        ULTRA_TRIG_PORT,
        ULTRA_TRIG_PIN,
        LOW
    );

    timer_delay_us(2);

    gpio_write(
        ULTRA_TRIG_PORT,
        ULTRA_TRIG_PIN,
        HIGH
    );

    timer_delay_us(10);

    gpio_write(
        ULTRA_TRIG_PORT,
        ULTRA_TRIG_PIN,
        LOW
    );

    /* ------------------
       Wait for Echo HIGH
       (30 ms timeout so a missing sensor cannot hang the program)
       ------------------ */

    timer_reset();
    timer_start();

    while (
        gpio_read(
            ULTRA_ECHO_PORT,
            ULTRA_ECHO_PIN
        ) == LOW
    )
    {
        if (timer_get_count() >= ULTRA_TIMEOUT_COUNT)
        {
            timer_stop();
            return ULTRA_NO_ECHO;
        }
    }

    /* ------------------
       Start Timer from zero
       ------------------ */

    timer_stop();
    timer_reset();
    timer_start();

    /* ------------------
       Wait for Echo LOW
       (with no object the echo lasts ~38 ms, which would
       overflow the 16-bit count, so stop at 30 ms)
       ------------------ */

    while (
        gpio_read(
            ULTRA_ECHO_PORT,
            ULTRA_ECHO_PIN
        ) == HIGH
    )
    {
        if (timer_get_count() >= ULTRA_TIMEOUT_COUNT)
        {
            timer_stop();
            return ULTRA_NO_ECHO;
        }
    }

    /* ------------------
       Stop Timer
       ------------------ */

    timer_stop();

    /* ------------------
       Read Timer Count
       ------------------ */

    timer_count = timer_get_count();

    /*
       Each timer count = 0.5 us
    */

    time_us = timer_count / 2;

    /*
       Distance in cm = time / 58
    */

    distance = time_us / 58;

    return distance;
}