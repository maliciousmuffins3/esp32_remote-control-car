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

#define ENA 13
#define IN1 14
#define IN2 15

#define ENA2 18
#define IN3 19
#define IN4 25

extern MotorDriver::L298NMotor motor1;
extern MotorDriver::L298NMotor motor2;

extern TaskHandle_t TaskHandle_MotorTask;
extern SemaphoreHandle_t motorMutex;
extern SemaphoreHandle_t motor1SpeedMutex;
extern SemaphoreHandle_t motor1SpeedMutex;
extern Motor_State motorState;
extern int motor1Speed;
extern int motor1Speed;

void MotorTaskInit();
void motorTask(void *pvParameters);
void ChangeMotorState(Motor_State state);

#endif