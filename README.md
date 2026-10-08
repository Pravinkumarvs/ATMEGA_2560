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
│    ├── led.c
│    ├── 7-segemnt.c
|    ├── switch.c
|
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
TRIG → PORT B, Pin 7
ECHO → PORT B, Pin 6
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
- LCD driver
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
