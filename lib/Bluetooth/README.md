# 🔷 Bluetooth Module for ESP32

This module provides a clean and reusable wrapper around the built-in Bluetooth capabilities of the ESP32 using `BluetoothSerial`.

## 📦 Files

modules/
└── Bluetooth/
├── Bluetooth.h
├── Bluetooth.cpp
└── README.md

## 🚀 Features

- Easy initialization of Bluetooth with a custom device name
- Send and receive data over Bluetooth
- Check for connection status
- Listen for incoming data (non-blocking)

## 🧠 Dependencies

- `BluetoothSerial` (built-in for ESP32 board in Arduino IDE)

## 🔧 Example Usage

```cpp
#include "BluetoothModule.h"

ESP32::BluetoothModule bt("ESP32_BT_Device");

void setup() {
    Serial.begin(115200);
    bt.begin();
}

void loop() {
    if (bt.isConnected()) {
        String msg = bt.receive();
        if (msg.length() > 0) {
            Serial.println("Received: " + msg);
            bt.send("Echo: " + msg);
        }
    }
}
```
