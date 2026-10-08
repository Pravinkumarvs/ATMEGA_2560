#include "keypad.h"
#include "timer.h"

#define ROW_PORT PORT_A
#define COL_PORT PORT_B

#define KEYPAD_DEBOUNCE_MS  20
#define KEYPAD_SETTLE_US    5

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

        /* enable internal pull-up so idle columns read HIGH */
        gpio_write(COL_PORT, col_pin[i], HIGH);

        gpio_write(ROW_PORT, row_pin[i], HIGH);
    }
}

static uint8_t keypad_is_down(uint8_t row, uint8_t col)
{
    uint8_t down;

    gpio_write(ROW_PORT, row_pin[row], LOW);
    timer_delay_us(KEYPAD_SETTLE_US);

    down = (gpio_read(COL_PORT, col_pin[col]) == LOW);

    gpio_write(ROW_PORT, row_pin[row], HIGH);

    return down;
}

/*
 * Returns the pressed key, or 0 if none.
 * A key is returned once per press: after debouncing,
 * this waits for the key to be released.
 */
char keypad_get_key(void)
{
    for(uint8_t row = 0; row < 4; row++)
    {
        for(uint8_t col = 0; col < 4; col++)
        {
            if(!keypad_is_down(row, col))
                continue;

            timer_delay_ms(KEYPAD_DEBOUNCE_MS);

            if(!keypad_is_down(row, col))
                return 0;

            while(keypad_is_down(row, col))
            {
            }

            timer_delay_ms(KEYPAD_DEBOUNCE_MS);

            return key_map[row][col];
        }
    }

    return 0;
}
