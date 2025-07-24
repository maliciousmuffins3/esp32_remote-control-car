#include "LCDTask.h"
#include "MotorTask.h"

void setup()
{
    Serial.begin(115200);

    // Initialize LCD display task
    LCDTaskInit();
    MotorTaskInit();
}

void loop()
{
    // Do nothing; everything runs in tasks
}
