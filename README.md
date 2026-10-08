# ATMEGA_2560

Bare-metal drivers for the ATmega2560 (Arduino Mega), 16 MHz.

## Drivers

| Folder | Driver | Notes |
|---|---|---|
| `GPIO` | `gpio_mode`, `gpio_write`, `gpio_read` | Ports A–L. Writing HIGH to an input pin enables its pull-up. |
| `TIMER` | `timer_delay_s/ms/us`, `timer_start/stop/reset/get_count` | All use Timer1, so they cannot overlap. |
| `PWM` | `pwm_init`, `pwm_set_duty`, `pwm_on`, `pwm_off` | Timer4, OC4A = PH3 = **D6**, 2 kHz. |
| `ADC` | `adc_init`, `adc_read` | AVCC reference, channels 0–15. |
| `EXTERNAL INTERRUPT` | `extint_init`, `extint_enable`, `extint_disable` | INT0–INT7. Write the `ISR()` and call `sei()` yourself. |
| `IR SENSOR` | `ir_init`, `ir_read`, `ir_get_value` | Analog IR on an ADC channel. |
| `ULTRASONIC SENSOR` | `ultra_init`, `ultra_getDistance` | HC-SR04, TRIG = PB7, ECHO = PB6. Returns cm, or `ULTRA_NO_ECHO`. Uses Timer1. |
| `MIDDLEWARE/LED` | `led_init(&led, port, pin)`, `led_on/off/toggle(&led)` | One `led_t` per LED. |
| `MIDDLEWARE/SWITCH` | `switch_init(&sw, port, pin)`, `switch_read(&sw)` | Switch to GND, internal pull-up. |
| `MIDDLEWARE/KEYPAD` | `keypad_init`, `keypad_get_key` | 4x4: rows PA0–PA3, columns PB0–PB3. Debounced. |
| `MIDDLEWARE/LCD` | `lcd_init`, `lcd_print`, `lcd_set_cursor`, ... | HD44780 16x2, 4-bit: RS = PC0, EN = PC1, D4–D7 = PC4–PC7, RW to GND. |
| `MIDDLEWARE/7-SEGMENT` | `c_segment(port, digit)`, `a_segment(port, digit)` | Segments a–g, dp on pins 0–7 of the port. |

## Building

The folder names contain spaces, so quote the include paths:

```sh
avr-g++ -mmcu=atmega2560 -DF_CPU=16000000UL -Os \
  -IGPIO -ITIMER -IADC -IPWM "-IEXTERNAL INTERRUPT" "-IIR SENSOR" "-IULTRASONIC SENSOR" \
  -IMIDDLEWARE/LED -IMIDDLEWARE/SWITCH -IMIDDLEWARE/KEYPAD -IMIDDLEWARE/LCD -IMIDDLEWARE/7-SEGMENT \
  main.cpp GPIO/gpio.cpp TIMER/timer.cpp ... -o app.elf
avr-objcopy -O ihex app.elf app.hex
avrdude -p m2560 -c wiring -P /dev/ttyACM0 -b 115200 -D -U flash:w:app.hex
```
