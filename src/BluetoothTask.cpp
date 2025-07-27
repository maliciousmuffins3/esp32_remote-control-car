#include "BluetoothTask.h"

BluetoothModule bt("ESP32_BT-Matthew");
TaskHandle_t TaskHandle_BluetoothTask = NULL;
COMMAND_STATE commandState = AUTOMATIC;
SemaphoreHandle_t CMDMutex = NULL;

void BluetoothTaskInit()
{
    // Initialize Bluetooth module
    bt.begin();

    CMDMutex = xSemaphoreCreateMutex();
    if (CMDMutex == NULL)
    {
        Serial.println("Failed to create CMDMutex!");
        return; // or handle error safely
    }
    // Create the Bluetooth task
    xTaskCreate(BluetoothTask, "BluetoothTask", 3064, NULL, 1, &TaskHandle_BluetoothTask);
}

void BluetoothTask(void *pvParameters)
{
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(100));

        if (!bt.isConnected())
        {
            continue;
        }

        String msg = bt.receive();
        Serial.println(msg);
        msg.trim();
        msg.toLowerCase();

        if (msg.length() == 0)
        {
            continue;
        }

        CommandResult commandResult = processCommand(msg);

        switch (commandResult)
        {
        case CMD_NONE:
            break;
        case CMD_TURN_ON_VOICE:
            ChangeCommandState(VOICE_COMMAND);
            break;
        case CMD_TURN_OFF_VOICE:
            ChangeCommandState(AUTOMATIC);
            break;
        case CMD_SEQ1:
            ChangeLCDState(LCD_SEQUENCE1);
            break;
        case CMD_SEQ2:
            ChangeLCDState(LCD_SEQUENCE2);
            break;
        case CMD_SEQ3:
            ChangeLCDState(LCD_SEQUENCE3);
            break;
        case CMD_SEQ4:
            ChangeLCDState(LCD_SEQUENCE4);
            break;
        case CMD_SEQ5:
            ChangeLCDState(LCD_SEQUENCE5);
            break;
        case CMD_SEQ6:
            ChangeLCDState(LCD_SEQUENCE6);
            break;
        case CMD_STOP:
            ChangeLCDState(LCD_STANDBY);
            break;
        case CMD_UNKNOWN:
            Serial.println("Unknown command");
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void ChangeCommandState(COMMAND_STATE state)
{
    // Attempt to take the mutex, block forever if necessary
    if (xSemaphoreTake(CMDMutex, portMAX_DELAY) == pdTRUE)
    {
        commandState = state;
        xSemaphoreGive(CMDMutex);
    }
    else
    {
        Serial.println("Failed to acquire display mutex");
    }
}
