#include "ServoTask.h"

TaskHandle_t TaskHandle_ServoTask = NULL;
SemaphoreHandle_t servoMutex = NULL;
Servo_State servoState = SERVO_STANDBY;
Servo servo; // Servo object

void ServoTaskInit()
{
    servo.attach(SERVO_PIN); // Attach the servo to the defined pin
    servo.write(90);         // Set initial position to 90 degrees (neutral position)
    servoMutex = xSemaphoreCreateMutex();
    xTaskCreate(servoTask, "Motor Task", (2048 * 3), NULL, 1, &TaskHandle_ServoTask);
}

void servoTask(void *pvParameters)
{
    while (true)
    {
        switch (servoState)
        {
        case SERVO_SEQUENCE1:
            servo.write(0); // Instant jump to 0 degrees
            break;
        case SERVO_SEQUENCE2:
            servo.write(90); // Instant jump to 90 degrees
            break;
        case SERVO_SEQUENCE3:
            servo.write(180); // Instant jump to 180 degrees
            break;
        case SERVO_SEQUENCE4:
            servo.write(0); // Instant jump to 0 degrees
            break;
        case SERVO_SEQUENCE5:
            servo.write(90); // Instant jump to 90 degrees
            break;
        case SERVO_STANDBY:
            servo.write(90); // Instant jump to 90 degrees
            break;
        default:
            servo.write(90); // Neutral position
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); // 1 second delay
    }
}

void ChangeServoState(Servo_State state)
{
    if (xSemaphoreTake(servoMutex, portMAX_DELAY) == pdTRUE)
    {
        servoState = state;
        xSemaphoreGive(servoMutex);
    }
    else
    {
        Serial.println("Failed to acquire motor mutex");
    }
}

void steerTo(Servo &servo, int startPos, int endPos, int stepDelay)
{
    if (startPos < endPos)
    {
        for (int pos = startPos; pos <= endPos; pos++)
        {
            servo.write(pos); // Move to this position
            vTaskDelay(pdMS_TO_TICKS(stepDelay));
        }
    }
    else
    {
        for (int pos = startPos; pos >= endPos; pos--)
        {
            servo.write(pos);
            vTaskDelay(pdMS_TO_TICKS(stepDelay));
        }
    }
}