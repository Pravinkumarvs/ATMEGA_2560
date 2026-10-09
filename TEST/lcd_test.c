/*
 * lcd_test.c - test for 16x2 LCD (1602A / HD44780), 4-bit mode
 *
 * Wiring (Arduino Mega):
 *   RS (4)  -> D40 = PG1
 *   EN (6)  -> D41 = PG0
 *   D4 (11) -> D42 = PL7
 *   D5 (12) -> D43 = PL6
 *   D6 (13) -> D44 = PL5
 *   D7 (14) -> D45 = PL4
 *   RW (5)  -> GND,  VSS (1) -> GND,  VDD (2) -> 5V
 *   VO (3)  -> contrast pot wiper
 *
 * Expected result:
 *   1. all 32 boxes filled for 2 s (checks contrast + every position)
 *   2. line 1 "LCD TEST OK", line 2 "Count: N" counting up every second
 *
 * Needs: GPIO/gpio.c, TIMER/timer.c
 */

#include <stdint.h>
#include "gpio.h"
#include "timer.h"

/* control pins */
#define LCD_RS_PORT  PORT_G
#define LCD_RS_PIN   1          /* D40 */
#define LCD_EN_PORT  PORT_G
#define LCD_EN_PIN   0          /* D41 */

/* data pins D4..D7, NOT in bit order on PORTL */
#define LCD_DATA_PORT  PORT_L
static const uint8_t lcd_data_pin[4] = { 7, 6, 5, 4 };   /* D4=PL7, D5=PL6, D6=PL5, D7=PL4 */

/* put 4 bits on D4..D7 and pulse EN */
static void lcd_nibble(uint8_t nibble)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        gpio_write(LCD_DATA_PORT, lcd_data_pin[i], (nibble >> i) & 1);
    }

    gpio_write(LCD_EN_PORT, LCD_EN_PIN, HIGH);
    timer_delay_us(1);
    gpio_write(LCD_EN_PORT, LCD_EN_PIN, LOW);   /* LCD reads on falling edge */
    timer_delay_us(50);                          /* most commands need 37 us */
}

/* rs = 0 command, rs = 1 character */
static void lcd_byte(uint8_t value, uint8_t rs)
{
    gpio_write(LCD_RS_PORT, LCD_RS_PIN, rs);
    lcd_nibble(value >> 4);
    lcd_nibble(value & 0x0F);
}

static void lcd_command(uint8_t cmd)
{
    lcd_byte(cmd, 0);
    if (cmd == 0x01 || cmd == 0x02)
    {
        timer_delay_ms(2);                       /* clear / home need 1.52 ms */
    }
}

static void lcd_char(char c)
{
    lcd_byte((uint8_t)c, 1);
}

static void lcd_print(const char *text)
{
    while (*text)
    {
        lcd_char(*text++);
    }
}

static void lcd_goto(uint8_t row, uint8_t col)
{
    lcd_command((row == 0 ? 0x80 : 0xC0) + col);
}

static void lcd_print_number(uint16_t num)
{
    char digits[5];
    uint8_t count = 0;

    do
    {
        digits[count++] = '0' + (num % 10);
        num /= 10;
    } while (num > 0);

    while (count > 0)
    {
        lcd_char(digits[--count]);
    }
}

static void lcd_init(void)
{
    gpio_mode(LCD_RS_PORT, LCD_RS_PIN, OUTPUT);
    gpio_mode(LCD_EN_PORT, LCD_EN_PIN, OUTPUT);
    gpio_write(LCD_RS_PORT, LCD_RS_PIN, LOW);
    gpio_write(LCD_EN_PORT, LCD_EN_PIN, LOW);

    for (uint8_t i = 0; i < 4; i++)
    {
        gpio_mode(LCD_DATA_PORT, lcd_data_pin[i], OUTPUT);
        gpio_write(LCD_DATA_PORT, lcd_data_pin[i], LOW);
    }

    /* HD44780 4-bit start sequence */
    timer_delay_ms(50);          /* power-up */
    lcd_nibble(0x03);
    timer_delay_ms(5);
    lcd_nibble(0x03);
    timer_delay_us(150);
    lcd_nibble(0x03);
    lcd_nibble(0x02);            /* now 4-bit */

    lcd_command(0x28);           /* 4-bit, 2 lines, 5x8 */
    lcd_command(0x0C);           /* display on, cursor off */
    lcd_command(0x06);           /* cursor moves right */
    lcd_command(0x01);           /* clear */
}

int main(void)
{
    uint16_t count = 0;

    lcd_init();

    /* step 1: fill every position with a full block */
    for (uint8_t row = 0; row < 2; row++)
    {
        lcd_goto(row, 0);
        for (uint8_t col = 0; col < 16; col++)
        {
            lcd_char((char)0xFF);
        }
    }
    timer_delay_s(2);

    /* step 2: text + counter */
    lcd_command(0x01);
    lcd_goto(0, 0);
    lcd_print("LCD TEST OK");
    lcd_goto(1, 0);
    lcd_print("Count: ");

    while (1)
    {
        lcd_goto(1, 7);
        lcd_print_number(count);
        count++;
        timer_delay_s(1);
    }

    return 0;
}
