#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include "gpio.h"

/* ==========================
   LCD PIN CONFIGURATION (4-bit mode)
   R/W (LCD pin 5) must be tied to GND
   ========================== */

#define LCD_PORT PORT_K

#define LCD_RS  0   /* PK0 / A8  */
#define LCD_EN  1   /* PK1 / A9  */
#define LCD_D4  4   /* PK4 / A12 */
#define LCD_D5  5   /* PK5 / A13 */
#define LCD_D6  6   /* PK6 / A14 */
#define LCD_D7  7   /* PK7 / A15 */

void lcd_init(void);
void lcd_command(uint8_t command);
void lcd_data(uint8_t data);
void lcd_print(const char *text);
void lcd_print_number(uint16_t number);
void lcd_set_cursor(uint8_t row, uint8_t column);
void lcd_clear(void);

#endif
