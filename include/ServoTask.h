#ifndef SERVOTASK_H
#define SERVOTASK_H

// Includes
#include <Arduino.h>
#include <ESP32Servo.h>
#include "Pins.h"

enum Servo_State
{
    SERVO_SEQUENCE1,
    SERVO_SEQUENCE2,
    SERVO_SEQUENCE3,
    SERVO_SEQUENCE4,
    SERVO_SEQUENCE5,
    SERVO_STANDBY,
};

extern TaskHandle_t TaskHandle_ServoTask;
extern SemaphoreHandle_t servoMutex; // Mutex for servo access
extern Servo_State servoState;
extern Servo servo; // Servo object

void ServoTaskInit();
void servoTask(void *pvParameters);
void ChangeServoState(Servo_State state);
void steerTo(Servo &servo, int startPos, int endPos, int stepDelay);

#endif