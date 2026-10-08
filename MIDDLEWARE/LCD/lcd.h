#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include "gpio.h"

void lcd_init(void);
void lcd_command(uint8_t command);
void lcd_data(uint8_t data);
void lcd_print(const char *text);
void lcd_set_cursor(uint8_t row, uint8_t column);
void lcd_clear(void);

#endif