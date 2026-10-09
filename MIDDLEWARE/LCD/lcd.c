#include "lcd.h"
#include "timer.h"

/* Send 4 bits on D4-D7 and latch them with an Enable pulse */
static void lcd_nibble(uint8_t data)
{
    gpio_write(LCD_PORT, LCD_D4, (data >> 0) & 1);
    gpio_write(LCD_PORT, LCD_D5, (data >> 1) & 1);
    gpio_write(LCD_PORT, LCD_D6, (data >> 2) & 1);
    gpio_write(LCD_PORT, LCD_D7, (data >> 3) & 1);

    gpio_write(LCD_PORT, LCD_EN, HIGH);
    timer_delay_us(1);
    gpio_write(LCD_PORT, LCD_EN, LOW);

    /* Most commands need 37 us */
    timer_delay_us(50);
}

void lcd_command(uint8_t command)
{
    gpio_write(LCD_PORT, LCD_RS, LOW);

    lcd_nibble(command >> 4);
    lcd_nibble(command & 0x0F);

    /* Clear and Home need at least 1.52 ms; clone modules can be slower.
       Bytes sent while the LCD is busy are lost and put the 4-bit
       transfer out of step, which shows up as garbage characters. */
    if(command == 0x01 || command == 0x02)
        timer_delay_ms(5);
}

void lcd_data(uint8_t data)
{
    gpio_write(LCD_PORT, LCD_RS, HIGH);

    lcd_nibble(data >> 4);
    lcd_nibble(data & 0x0F);
}

void lcd_init(void)
{
    gpio_mode(LCD_PORT, LCD_RS, OUTPUT);
    gpio_mode(LCD_PORT, LCD_EN, OUTPUT);
    gpio_mode(LCD_PORT, LCD_D4, OUTPUT);
    gpio_mode(LCD_PORT, LCD_D5, OUTPUT);
    gpio_mode(LCD_PORT, LCD_D6, OUTPUT);
    gpio_mode(LCD_PORT, LCD_D7, OUTPUT);

    gpio_write(LCD_PORT, LCD_RS, LOW);
    gpio_write(LCD_PORT, LCD_EN, LOW);

    /* Wait for the LCD to power up */
    timer_delay_ms(50);

    /* HD44780 4-bit initialisation sequence */
    lcd_nibble(0x03);
    timer_delay_ms(5);

    lcd_nibble(0x03);
    timer_delay_ms(1);

    lcd_nibble(0x03);
    timer_delay_ms(1);

    lcd_nibble(0x02);
    timer_delay_ms(1);

    lcd_command(0x28);  /* 4-bit, 2 lines, 5x8 font */
    lcd_command(0x0C);  /* Display ON, cursor OFF */
    lcd_command(0x06);  /* Increment cursor */
    lcd_clear();
}

void lcd_print(const char *text)
{
    while(*text)
    {
        lcd_data((uint8_t)*text++);
    }
}

void lcd_print_number(uint16_t number)
{
    char digits[5];
    uint8_t i = 0;

    if(number == 0)
    {
        lcd_data('0');
        return;
    }

    while(number > 0)
    {
        digits[i++] = (char)('0' + (number % 10));
        number /= 10;
    }

    while(i > 0)
    {
        lcd_data((uint8_t)digits[--i]);
    }
}

void lcd_set_cursor(uint8_t row, uint8_t column)
{
    if(column > 15)
        column = 15;

    if(row == 0)
        lcd_command(0x80 + column);
    else
        lcd_command(0xC0 + column);
}

void lcd_clear(void)
{
    lcd_command(0x01);
}
