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

    /* Send trigger pulse */
    gpio_write(ULTRA_TRIG_PORT, ULTRA_TRIG_PIN, LOW);
    timer_delay_us(8);

    gpio_write(ULTRA_TRIG_PORT, ULTRA_TRIG_PIN, HIGH);
    timer_delay_us(12);
    gpio_write(ULTRA_TRIG_PORT, ULTRA_TRIG_PIN, LOW);

    /*
     * Start Timer1 at 0.5 us per count.
     * Timeout: 60000 counts = 30 ms.
     */
    timer_reset();
    timer_start();

    /* Wait for ECHO HIGH */
    while (gpio_read(ULTRA_ECHO_PORT, ULTRA_ECHO_PIN) == LOW)
    {
        if (timer_get_count() >= 60000U)
        {
            timer_stop();
            return 0;
        }
    }

    /* Start measuring the ECHO HIGH pulse */
    timer_reset();

    while (gpio_read(ULTRA_ECHO_PORT, ULTRA_ECHO_PIN) == HIGH)
    {
        if (timer_get_count() >= 60000U)
        {
            timer_stop();
            return 0;
        }
    }

    timer_stop();

    timer_count = timer_get_count();

    /*
     * Timer1 tick = 0.5 us.
     * Distance in cm = echo time in us / 58.
     * Therefore distance = timer_count / 116.
     */
    return (uint16_t)(timer_count / 116U);
}