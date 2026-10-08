#include "keypad.h"

#define ROW_PORT PORT_A
#define COL_PORT PORT_B

static const uint8_t row_pin[4] = {0, 1, 2, 3};
static const uint8_t col_pin[4] = {0, 1, 2, 3};

static const char key_map[4][4] =
{
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

void keypad_init(void)
{
    for(uint8_t i = 0; i < 4; i++)
    {
        gpio_mode(ROW_PORT, row_pin[i], OUTPUT);
        gpio_mode(COL_PORT, col_pin[i], INPUT);

        gpio_write(ROW_PORT, row_pin[i], HIGH);
    }
}

char keypad_get_key(void)
{
    for(uint8_t row = 0; row < 4; row++)
    {
        gpio_write(ROW_PORT, row_pin[row], LOW);

        for(uint8_t col = 0; col < 4; col++)
        {
            if(gpio_read(COL_PORT, col_pin[col]) == LOW)
            {
                gpio_write(ROW_PORT, row_pin[row], HIGH);
                return key_map[row][col];
            }
        }

        gpio_write(ROW_PORT, row_pin[row], HIGH);
    }

    return 0;
}