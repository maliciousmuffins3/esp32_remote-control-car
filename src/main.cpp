#include "LCDTask.h"
#include "MotorTask.h"
#include "BluetoothTask.h"

void setup()
{
    Serial.begin(115200);

    // Initialize LCD display task
    LCDTaskInit();
    MotorTaskInit();
    BluetoothTaskInit();
}

void loop()
{
    // Do nothing; everything runs in tasks
}
