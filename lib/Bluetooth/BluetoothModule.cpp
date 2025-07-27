#include "BluetoothModule.h"

BluetoothModule::BluetoothModule(const String &deviceName)
    : name(deviceName)
{
    // No constructor needed for BluetoothSerial when using default object
}

void BluetoothModule::begin()
{
    if (!btSerial.begin(name.c_str()))
    { // ESP32 expects const char*, not String
        Serial.println("Failed to initialize Bluetooth");
    }
    else
    {
        Serial.println("Bluetooth Initialized: " + name);
    }
}

bool BluetoothModule::isConnected()
{
    return btSerial.hasClient();
}

String BluetoothModule::receive()
{
    String message = "";
    while (btSerial.available())
    {
        char c = btSerial.read();
        message += c;
    }
    return message;
}

void BluetoothModule::send(const String &message)
{
    btSerial.println(message);
}
