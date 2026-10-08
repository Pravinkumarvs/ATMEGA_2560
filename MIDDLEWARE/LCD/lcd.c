#include "lcd.h"
#include "timer.h"

#define LCD_PORT PORT_C

#define LCD_RS 0
#define LCD_EN 1

static void lcd_nibble(uint8_t data)
{
    for(uint8_t i = 0; i < 4; i++)
    {
        gpio_write(LCD_PORT, i + 4, (data >> i) & 1);
    }

    gpio_write(LCD_PORT, LCD_EN, HIGH);
    timer_delay_us(1);
    gpio_write(LCD_PORT, LCD_EN, LOW);
    timer_delay_us(50);
}

void lcd_init(void)
{
    gpio_mode(LCD_PORT, LCD_RS, OUTPUT);
    gpio_mode(LCD_PORT, LCD_EN, OUTPUT);

    for(uint8_t i = 4; i < 8; i++)
        gpio_mode(LCD_PORT, i, OUTPUT);

    gpio_write(LCD_PORT, LCD_RS, LOW);
    gpio_write(LCD_PORT, LCD_EN, LOW);

    timer_delay_ms(20);

    lcd_nibble(0x03);
    timer_delay_ms(5);

    lcd_nibble(0x03);
    timer_delay_us(150);

    lcd_nibble(0x03);
    lcd_nibble(0x02);

    lcd_command(0x28);
    lcd_command(0x0C);
    lcd_command(0x06);
    lcd_command(0x01);

    timer_delay_ms(2);
}

void lcd_command(uint8_t command)
{
    gpio_write(LCD_PORT, LCD_RS, LOW);

    lcd_nibble(command >> 4);
    lcd_nibble(command & 0x0F);

    if(command == 0x01 || command == 0x02)
        timer_delay_ms(2);
}

void lcd_data(uint8_t data)
{
    gpio_write(LCD_PORT, LCD_RS, HIGH);

    lcd_nibble(data >> 4);
    lcd_nibble(data & 0x0F);
}

void lcd_print(const char *text)
{
    while(*text)
    {
        lcd_data(*text++);
    }
}

void lcd_set_cursor(uint8_t row, uint8_t column)
{
    uint8_t address;

    if(row == 0)
        address = 0x80 + column;
    else
        address = 0xC0 + column;

    lcd_command(address);
}

void lcd_clear(void)
{
    lcd_command(0x01);
    timer_delay_ms(2);
}