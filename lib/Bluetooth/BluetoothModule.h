#ifndef BLUETOOTH_MODULE_H
#define BLUETOOTH_MODULE_H

#include <BluetoothSerial.h>

class BluetoothModule
{
public:
    BluetoothModule(const String &deviceName = "ESP32_BT");

    void begin();
    bool isConnected();
    String receive();
    void send(const String &message);

private:
    BluetoothSerial btSerial;
    String name;
};

#endif
