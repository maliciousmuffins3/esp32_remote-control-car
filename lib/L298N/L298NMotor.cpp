#include "L298NMotor.h"

namespace MotorDriver {
        L298NMotor::L298NMotor(int in1, int in2, int en)
        : in1Pin(in1), in2Pin(in2), enablePin(en), speed(255), reversed(false) {}

    void L298NMotor::begin() {
        pinMode(in1Pin, OUTPUT);
        pinMode(in2Pin, OUTPUT);
        pinMode(enablePin, OUTPUT);
        stop(); // start off
    }

    void L298NMotor::setSpeed(int s) {
        speed = constrain(s, 0, 255);
        analogWrite(enablePin, speed);
    }

    void L298NMotor::forward(int s) {
        setSpeed(s);
        if (reversed) {
            digitalWrite(in1Pin, LOW);
            digitalWrite(in2Pin, HIGH);
        } else {
            digitalWrite(in1Pin, HIGH);
            digitalWrite(in2Pin, LOW);
        }
    }

    void L298NMotor::backward(int s) {
        setSpeed(s);
        if (reversed) {
            digitalWrite(in1Pin, HIGH);
            digitalWrite(in2Pin, LOW);
        } else {
            digitalWrite(in1Pin, LOW);
            digitalWrite(in2Pin, HIGH);
        }
    }

    void L298NMotor::stop() {
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, LOW);
        analogWrite(enablePin, 0);
    }

    void L298NMotor::reverseDirection(bool reverse) {
        reversed = reverse;
    }

}