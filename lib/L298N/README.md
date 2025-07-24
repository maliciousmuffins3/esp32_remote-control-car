# L298NMotor Module

A simple class for controlling a single DC motor using an L298N motor driver.

## 🚀 Usage Example

```cpp
#include "modules/L298NMotor/L298NMotor.h"

L298NMotor motor(8, 9, 10); // IN1=8, IN2=9, ENA=10 (PWM pin)

void setup() {
    motor.begin();
    motor.forward(200); // move forward at 200/255 speed
    delay(2000);
    motor.backward(150); // backward at 150
    delay(2000);
    motor.stop();
}

void loop() {
}
```
