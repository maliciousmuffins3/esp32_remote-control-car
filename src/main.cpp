#include "LCDTask.h"
#include "MotorTask.h"
#include "BluetoothTask.h"
#include "ServoTask.h"

void setup()
{
    Serial.begin(115200);

    // Initialize LCD display task
    LCDTaskInit();
    MotorTaskInit();
    BluetoothTaskInit();
    ServoTaskInit();
}

void loop()
{
    // Do nothing; everything runs in tasks
}
