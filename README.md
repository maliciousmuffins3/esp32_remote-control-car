# ESP32 RC Car - Bluetooth + FreeRTOS

RC car controlled via Bluetooth with real-time display using ESP32, FreeRTOS, and PlatformIO.

## Hardware

- ESP32 DevKit
- L298N motor driver
- 4x DC motors
- 16x2 LCD display
- 7-12V battery

## Commands

- `F/B/L/R/S` - Movement + Stop
- `0-9` - Speed control

## Setup

1. Install PlatformIO
2. Connect L298N to ESP32 GPIO pins
3. Wire LCD (I2C recommended)
4. Upload firmware
5. Pair Bluetooth and control

## Pin Config

```cpp
// Motors
#define ENA 5
#define IN1 18
#define IN2 19

#define ENA2 25
#define IN3 26
#define IN4 27

// LCD I2C
#define SDA_PIN  21
#define SCL_PIN  22
```

## Features

- Real-time speed/status on LCD
- FreeRTOS task management
- Bluetooth control via phone
- Battery monitoring

Built with PlatformIO + ESP-IDF
