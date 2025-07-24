#ifndef L298NMOTOR_H
#define L298NMOTOR_H

#include <Arduino.h>

namespace MotorDriver{
        class L298NMotor {
    private:
        int in1Pin;
        int in2Pin;
        int enablePin;
        int speed;
        bool reversed;

    public:
        L298NMotor(int in1, int in2, int en); // constructor
        void begin();
        void forward(int speed = 255);        // optional speed
        void backward(int speed = 255);
        void stop();
        void setSpeed(int speed);            // updates speed only
        void reverseDirection(bool reverse); // invert forward/backward
    };

}

#endif



