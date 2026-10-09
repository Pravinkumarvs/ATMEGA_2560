MCU   = atmega2560
F_CPU = 16000000UL
PORT  = /dev/ttyACM0
BAUD  = 115200
TARGET = APP/main

CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra \
         -IGPIO -ITIMER -IADC -IPWM -I"IR SENSOR" -I"ULTRASONIC SENSOR" \
         -IMIDDLEWARE/LED -IMIDDLEWARE/SWITCH -IMIDDLEWARE/7-SEGMENT \
         -IMIDDLEWARE/LCD

SRC = APP/main.c GPIO/gpio.c TIMER/timer.c ADC/adc.c PWM/pwm.c \
      "IR SENSOR/ir.c" "ULTRASONIC SENSOR/ultra.c" \
      MIDDLEWARE/LED/led.c MIDDLEWARE/SWITCH/switch.c \
      MIDDLEWARE/7-SEGMENT/segment.c MIDDLEWARE/LCD/lcd.c

.PHONY: all flash clean

all:
	avr-gcc $(CFLAGS) -ffunction-sections -fdata-sections -Wl,--gc-sections \
	        -o $(TARGET).elf $(SRC)
	avr-objcopy -O ihex -R .eeprom $(TARGET).elf $(TARGET).hex
	avr-size $(TARGET).elf

flash: all
	avrdude -p $(MCU) -c wiring -P $(PORT) -b $(BAUD) \
	        -D -U flash:w:$(TARGET).hex:i

clean:
	rm -f $(TARGET).elf $(TARGET).hex
