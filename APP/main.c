/*
 * main.c - LCD test
 * Line 1 shows "Smart Parking", line 2 counts seconds
 */

#include <stdint.h>

#include "gpio.h"
#include "timer.h"
#include "lcd.h"

int main(void)
{
    uint16_t seconds = 0;

    lcd_init();

    lcd_set_cursor(0, 0);
    lcd_print("Smart Parking");
    lcd_set_cursor(1, 0);
    lcd_print("Time: 0 s");

    while(1)
    {
        timer_delay_s(1);
        seconds++;

        lcd_set_cursor(1, 6);
        lcd_print_number(seconds);
        lcd_print(" s");
    }

    return 0;
}
