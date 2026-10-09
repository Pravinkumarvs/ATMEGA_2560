# ATmega2560 Driver Development

A modular low-level driver development project for the **ATmega2560 microcontroller**.

The purpose of this repository is to develop and test reusable hardware drivers by directly accessing microcontroller registers instead of depending completely on high-level Arduino functions.

---

## 📌 Project Overview

This project focuses on building a layered embedded software architecture for the ATmega2560.

The drivers provide simple functions to control and communicate with hardware peripherals.

### Architecture

```text
Application
     │
     ▼
Middleware / Device Drivers
     │
     ├── LED
     ├── Switch
     ├── IR Sensor
     ├── Ultrasonic Sensor
     ├── ADC
     ├── PWM
     └── Timer
     │
     ▼
GPIO / Hardware Registers
     │
     ▼
ATmega2560
```

The main objective is to keep the application independent from low-level register operations.

---

# 📂 Repository Structure

```text
ATMEGA_2560/
│
├── ADC/
│   ├── adc.c
│   └── adc.h
│
├── GPIO/
│   ├── gpio.c
│   └── gpio.h
│
├── IR SENSOR/
│   ├── ir.c
│   └── ir.h
│
├── MIDDLEWARE/
│   ├── LED/        (led.c, led.h)
│   ├── SWITCH/     (switch.c, switch.h)
│   ├── 7-SEGMENT/  (segment.c, segment.h)
│   └── LCD/        (lcd.c, lcd.h)
│
├── APP/
│   └── main.c      (LCD test application)
│
├── Makefile
├── PWM/
│   ├── pwm.c
│   └── pwm.h
│
├── TIMER/
│   ├── timer.c
│   └── timer.h
│
├── ULTRASONIC SENSOR/
│   ├── ultra.c
│   └── ultra.h
│
└── README.md
```

---

# 🔌 Pin Connections (Arduino Mega 2560)

All modules must share **one common GND** with the Mega. Power the modules from the Mega **5V** pin.

## Summary

| Module | Signal | AVR pin | Mega pin | Set in |
|---|---|---|---|---|
| Ultrasonic (HC-SR04) | TRIG | PB7 | D13 | `ULTRASONIC SENSOR/ultra.h` |
| Ultrasonic (HC-SR04) | ECHO | PB6 | D12 | `ULTRASONIC SENSOR/ultra.h` |
| Buzzer (PWM) | OC3A | PE3 | D5 | `PWM/pwm.c` (fixed, Timer3) |
| IR sensor | Analog out | PF0 (ADC0) | A0 | `ir_init(ADC0)` in the app |
| LCD 16x2 | RS | PK0 | A8 | `MIDDLEWARE/LCD/lcd.h` |
| LCD 16x2 | E | PK1 | A9 | `MIDDLEWARE/LCD/lcd.h` |
| LCD 16x2 | DB4 | PK4 | A12 | `MIDDLEWARE/LCD/lcd.h` |
| LCD 16x2 | DB5 | PK5 | A13 | `MIDDLEWARE/LCD/lcd.h` |
| LCD 16x2 | DB6 | PK6 | A14 | `MIDDLEWARE/LCD/lcd.h` |
| LCD 16x2 | DB7 | PK7 | A15 | `MIDDLEWARE/LCD/lcd.h` |
| 7-segment | a–g, dp | PA0–PA7 | D22–D29 | `c_segment(PORT_A, digit)` in the app |
| LED | Anode | any pin | e.g. PB5 / D11 | `led_init(PORT_B, 5)` in the app |
| Switch | Input | any pin | e.g. PE4 / D2 | `switch_init(PORT_E, 4)` in the app |

## Ultrasonic sensor (HC-SR04)

| HC-SR04 pin | Connect to |
|---|---|
| VCC | 5V |
| TRIG | D13 (PB7) |
| ECHO | D12 (PB6) |
| GND | GND |

- `ultra_getDistance()` returns the distance in cm, or `ULTRA_NO_ECHO` (0) when nothing is detected within 30 ms (no object, or sensor not connected).
- D13 also drives the on-board "L" LED, so that LED flickers on every trigger. This is normal.

## Buzzer (PWM)

| Buzzer pin | Connect to |
|---|---|
| + | D5 (PE3 / OC3A) |
| − | GND |

- Use a **passive** buzzer for tones. If the buzzer draws more than about 20 mA, drive it through an NPN transistor (base via 1 kΩ from D5).
- PWM frequency is 2 kHz; `pwm_set_duty(0–100)` sets the duty cycle.

## IR sensor (slot occupancy)

| IR module pin | Connect to |
|---|---|
| VCC | 5V |
| GND | GND |
| AO (analog out) | A0 (ADC0) |

- The IR driver reads the sensor through the ADC. Readings below `IR_THRESHOLD` (512) mean **SLOT_OCCUPIED**.
- Use channels **ADC0–ADC7 (A0–A7) only**. A8–A15 are used by the LCD.
- Turn the blue potentiometer on the module until its LED reacts at the right distance.

## LCD 16x2 (HD44780, 4-bit mode)

| LCD pin | Name | Connect to | Note |
|---|---|---|---|
| 1 | VSS | GND | |
| 2 | VCC | 5V | |
| 3 | VEE / V0 | 10 kΩ pot middle leg (outer legs to 5V and GND) | Contrast, about 0.5–0.8 V |
| 4 | RS | A8 (PK0) | |
| 5 | R/W | GND | Write-only, the driver never reads the LCD |
| 6 | E | A9 (PK1) | |
| 7–10 | DB0–DB3 | not connected | Not used in 4-bit mode |
| 11 | DB4 | A12 (PK4) | |
| 12 | DB5 | A13 (PK5) | |
| 13 | DB6 | A14 (PK6) | |
| 14 | DB7 | A15 (PK7) | |
| 15 | LED+ | 5V through 220 Ω | Backlight |
| 16 | LED− | GND | Backlight |

No pot? Use a divider: 10 kΩ from 5V to pin 3 and 1–2 kΩ from pin 3 to GND.

| Symptom | Cause |
|---|---|
| Blank screen | Contrast too low (VEE too high) — turn the pot |
| Top row of solid boxes | LCD powered but not initialised — check RS, E, DB4–DB7 wiring and that R/W is on GND |
| Garbage characters | A data wire is swapped or loose (DB4–DB7 order) |

## 7-segment display (common cathode)

The 7-segment driver uses **all 8 pins of one port**: pin 0 = a, 1 = b, … 6 = g, 7 = dp.
Example with `PORT_A`:

| Segment | AVR pin | Mega pin |
|---|---|---|
| a | PA0 | D22 |
| b | PA1 | D23 |
| c | PA2 | D24 |
| d | PA3 | D25 |
| e | PA4 | D26 |
| f | PA5 | D27 |
| g | PA6 | D28 |
| dp | PA7 | D29 |
| COM | GND | (common cathode) |

- Put a **220 Ω resistor on each segment line**, none on the COM pin.
- For a common-anode display use `a_segment()` and connect COM to 5V.

## LED

Mega pin → 220 Ω resistor → LED long leg (anode); LED short leg (cathode) → GND.

## Switch

The switch input has no internal pull-up, so it needs a pull-down resistor:

- One side of the switch → 5V
- Other side → input pin (e.g. D2) **and** 10 kΩ resistor → GND

Pressed reads `SWITCH_PRESSED` (HIGH), released reads `SWITCH_RELEASED` (LOW).

## Timer usage

Timer1 is shared by the delay functions, the ultrasonic driver and the LCD driver, so they run one after another, never at the same time. PWM uses Timer3.

---

# 🔨 Build and Flash

Needs `avr-gcc` and `avrdude` (both come with the Arduino IDE).

```sh
make                          # build APP/main.c with all drivers
make flash PORT=/dev/ttyACM0  # upload to the Mega (COMx on Windows)
make clean
```

`APP/main.c` is an LCD test: line 1 shows "Smart Parking" and line 2 counts seconds.

---

# 🔧 Drivers

## 1. GPIO Driver

The GPIO driver provides low-level control of the ATmega2560 GPIO ports.

### Main role

- Configure pins as input or output
- Write digital values
- Read digital values
- Access GPIO hardware through registers

### Basic concept

```text
Application
     ↓
GPIO Driver
     ↓
GPIO Registers
     ↓
ATmega2560 Pin
```

---

# 2. ADC Driver

The ADC driver handles analog-to-digital conversion.

### Main role

It converts an analog voltage from a sensor into a digital value that can be processed by the microcontroller.

### Basic flow

```text
Analog Sensor
      ↓
     ADC
      ↓
Digital Value
      ↓
Application
```

### Main functions

```c
adc_init();
adc_read(channel);
```

The driver supports ADC channel selection and returns the converted digital value.

---

# 3. Timer Driver

The Timer driver provides hardware-based timing functions using Timer1.

### Main role

- Generate delays
- Start and stop the timer
- Reset the timer
- Read the current timer count

### Delay functions

```c
timer_delay_s();
timer_delay_ms();
timer_delay_us();
```

### Timer control

```c
timer_start();
timer_stop();
timer_reset();
timer_get_count();
```

### Basic flow

```text
Configure Timer
      ↓
Start Timer
      ↓
Count Clock Cycles
      ↓
Compare / Flag
      ↓
Stop Timer
```

The timer driver is also used by the ultrasonic sensor driver for measuring echo pulse duration.

---

# 4. PWM Driver

The PWM driver provides pulse-width modulation functionality.

### Main role

PWM can be used to control:

- Motor speed
- LED brightness
- Actuator output
- Other variable-duty-cycle applications

### Basic concept

```text
PWM Signal
     ↓
Duty Cycle
     ↓
Controlled Output
```

---

# 5. IR Sensor Driver

The IR sensor driver uses the ADC driver to process the sensor output.

### Main role

The raw ADC value is converted into a meaningful status.

```text
IR Sensor
    ↓
ADC Driver
    ↓
Raw ADC Value
    ↓
IR Driver
    ↓
SLOT AVAILABLE / SLOT OCCUPIED
```

### Main functions

```c
ir_init();
ir_get_value();
ir_read();
```

A threshold is used to determine the sensor status.

---

# 6. Ultrasonic Sensor Driver

The ultrasonic driver is used to measure distance using an ultrasonic sensor such as the HC-SR04.

### Pin configuration

```text
TRIG → PORT B, Pin 7 (D13)
ECHO → PORT B, Pin 6 (D12)
```

### Measurement process

```text
TRIG HIGH
   ↓
10 µs pulse
   ↓
Ultrasonic sensor sends sound
   ↓
Wait for ECHO HIGH
   ↓
Start Timer
   ↓
Wait for ECHO LOW
   ↓
Stop Timer
   ↓
Read Timer Count
   ↓
Calculate Distance
```

### Distance calculation

The driver uses:

```text
Time → Distance
```

and calculates distance in centimeters using the measured echo time.

### Main functions

```c
ultra_init();
ultra_getDistance();
```

---

# 🧩 Middleware

The middleware layer is used to build higher-level functionality using the low-level drivers.

Instead of directly accessing registers, middleware can use functions such as:

```c
led_on();
led_off();

switch_read();

ir_read();

ultra_getDistance();

timer_delay_ms();
```

This makes the application code easier to understand and maintain.

---

# 🏗️ Driver Architecture

The project follows a layered architecture.

```text
┌─────────────────────────────┐
│        APPLICATION          │
└──────────────┬──────────────┘
               │
┌──────────────▼──────────────┐
│         MIDDLEWARE           │
└──────────────┬──────────────┘
               │
┌──────────────▼──────────────┐
│       DEVICE DRIVERS         │
│                              │
│ ADC │ IR │ PWM │ ULTRA       │
│ LED │ SWITCH │ TIMER         │
└──────────────┬──────────────┘
               │
┌──────────────▼──────────────┐
│        GPIO / PERIPHERALS    │
└──────────────┬──────────────┘
               │
┌──────────────▼──────────────┐
│          ATmega2560          │
└─────────────────────────────┘
```

---

# 📄 `.h` and `.c` Files

Each driver is separated into two files.

### Header file — `.h`

Contains:

- Function declarations
- Macros
- Constants
- Configuration definitions

Example:

```c
void timer_start(void);
void timer_stop(void);
```

### Source file — `.c`

Contains the actual implementation of the functions.

```text
.h → WHAT the driver provides
.c → HOW the driver works
```

This separation improves modularity and maintainability.

---

# 🎯 Design Goals

The project is designed around:

- **Modularity**
- **Reusability**
- **Hardware abstraction**
- **Low-level register programming**
- **Easy debugging**
- **Easy maintenance**
- **Separation of application and hardware code**

---

# 🧠 Why Develop Drivers?

Instead of writing hardware register operations repeatedly in application code:

```c
REGISTER = VALUE;
```

the application can use simple functions:

```c
led_on();
timer_delay_ms(500);
ultra_getDistance();
```

This hides hardware-specific implementation details from the application.

---

# 🛠️ Technologies

- **Microcontroller:** ATmega2560
- **Language:** C / C++
- **Development Environment:** Arduino IDE
- **Architecture:** Modular Driver Architecture
- **Hardware Access:** Direct Register Programming

---

# 🚀 Future Improvements

Possible future improvements include:

- Interrupt-based drivers
- Non-blocking timer implementation
- UART driver
- SPI driver
- I2C driver
- Keypad driver
- Motor driver
- Improved sensor timeout handling
- Error handling and status codes
- More hardware validation and testing

---

# 👨‍💻 Author

**Pravinkumar V S**

ATmega2560 Low-Level Driver Development Project

---

## ⭐ Project Philosophy

> **Build the driver first, abstract the hardware, and keep the application simple.**
