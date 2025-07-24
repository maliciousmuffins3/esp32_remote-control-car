#include "MotorTask.h"

MotorDriver::L298NMotor motor1(IN1, IN2, ENA);
MotorDriver::L298NMotor motor2(IN3, IN4, ENA2);

TaskHandle_t TaskHandle_MotorTask = NULL;
SemaphoreHandle_t motorMutex = NULL;
SemaphoreHandle_t motor1SpeedMutex = NULL;
SemaphoreHandle_t motor2SpeedMutex = NULL;
Motor_State motorState = STANDBY;

int motor1Speed = 255;
int motor2Speed = 255;

void MotorTaskInit()
{
    motor1.begin();
    motor2.begin();
    motor1.setSpeed(motor1Speed);
    motor2.setSpeed(motor2Speed);
    motor1.stop();
    motor2.stop();

    motorMutex = xSemaphoreCreateMutex();
    xTaskCreate(motorTask, "Motor Task", (2048 * 2), NULL, 1, &TaskHandle_MotorTask);
}

void motorTask(void *pvParameters)
{
    while (true)
    {
        switch (motorState)
        {
        case SEQUENCE1:
            motor1.backward();
            break;
        case SEQUENCE2:
            motor1.forward();
            break;
        case SEQUENCE3:
            motor2.backward();
            break;
        case SEQUENCE4:
            motor2.forward();
            break;
        case SEQUENCE5:
            motor1.backward();
            motor2.forward();
            break;
        case SEQUENCE6:
            motor1.forward();
            motor2.backward();
            break;
        case STANDBY:
            motor1.stop();
            motor2.stop();
            break;
        default:
            Serial.println("Nothing to do");
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // Prevent task from hogging CPU
    }
}

void ChangeMotorState(Motor_State state)
{
    if (xSemaphoreTake(motorMutex, portMAX_DELAY) == pdTRUE)
    {
        motorState = state;
        xSemaphoreGive(motorMutex);
    }
    else
    {
        Serial.println("Failed to acquire motor mutex");
    }
}

void ChangeMotor1Speed(int speed)
{
    if (xSemaphoreTake(motor1SpeedMutex, portMAX_DELAY) == pdTRUE)
    {
        motor1Speed = speed;
        xSemaphoreGive(motor1SpeedMutex);
    }
    else
    {
        Serial.println("Failed to acquire motor speed mutex");
    }
}

void ChangeMotor2Speed(int speed)
{
    if (xSemaphoreTake(motor2SpeedMutex, portMAX_DELAY) == pdTRUE)
    {
        motor2Speed = speed;
        xSemaphoreGive(motor2SpeedMutex);
    }
    else
    {
        Serial.println("Failed to acquire motor speed mutex");
    }
}
