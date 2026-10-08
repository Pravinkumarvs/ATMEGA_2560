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
   DISTANCE
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
        LOW);

    /* ------------------
       Wait for Echo HIGH
       ------------------ */

    timer_reset();
    timer_start();

    while(
        gpio_read(
            ULTRA_ECHO_PORT,
            ULTRA_ECHO_PIN
        ) == LOW
    )
    {
        if(timer_get_count() >= ULTRA_TIMEOUT_COUNT)
        {
            timer_stop();
            return ULTRA_NO_ECHO;
        }
    }

    /* ------------------
       Time the Echo pulse
       ------------------ */

    timer_reset();

    while(
        gpio_read(
            ULTRA_ECHO_PORT,
            ULTRA_ECHO_PIN
        ) == HIGH
    )
    {
        if(timer_get_count() >= ULTRA_TIMEOUT_COUNT)
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
       Read Count
       ------------------ */

    timer_count = timer_get_count();

    /*
    Each count = 0.5 us, distance = time_us / 58
    */

    time_us = timer_count / 2;

    distance = time_us / 58;

    return distance;
}
