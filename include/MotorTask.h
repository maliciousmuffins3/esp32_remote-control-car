#ifndef MOTORTASK_H
#define MOTORTASK_H

// Includes
#include <Arduino.h>
#include <L298NMotor.h>

enum Motor_State
{
    SEQUENCE1,
    SEQUENCE2,
    SEQUENCE3,
    SEQUENCE4,
    SEQUENCE5,
    SEQUENCE6,
    STANDBY,
};

#define ENA 5
#define IN1 18
#define IN2 19

#define ENA2 25
#define IN3 26
#define IN4 27

extern MotorDriver::L298NMotor motor1;
extern MotorDriver::L298NMotor motor2;

extern TaskHandle_t TaskHandle_MotorTask;
extern SemaphoreHandle_t motorMutex;
extern Motor_State motorState;
extern int motor1Speed;
extern int motor1Speed;

void MotorTaskInit();
void motorTask(void *pvParameters);
void ChangeMotorState(Motor_State state);

#endif