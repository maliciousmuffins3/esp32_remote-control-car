#include "LCDTask.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
SemaphoreHandle_t displayMutex = NULL;
DisplayState displayState = SCROLLNAME;
TaskHandle_t TaskHandle_LCDTask = NULL;

void LCDTask(void *pvParameters)
{
    DisplayState prevState = LCD_STANDBY;
    COMMAND_STATE prevMode = AUTOMATIC;
    TickType_t lastWakeTime = xTaskGetTickCount();
    while (true)
    {
        bool isVoiceCommand = commandState == VOICE_COMMAND;
        if (prevMode != commandState)
        {
            if (prevMode == VOICE_COMMAND && !isVoiceCommand)
            {
                ChangeLCDState(LCD_SEQUENCE1);
            }
            else
            {
                ChangeLCDState(LCD_STANDBY); // What if prev is VOICE COMMAND
            }
            prevMode = commandState;
        }

        int sequenceDelay = 5000; // Delay for motor actions
        if (prevState != displayState)
            lcd.clear();
        switch (displayState)
        {
        case SCROLLNAME:
            prevState = SCROLLNAME;
            Serial.println("Scrolling Name");
            scrollText("MATTHEW ARELLANO ROXAS", 300);
            ChangeLCDState(BLINKNAME); // Safely change state
            break;
        case BLINKNAME:
            prevState = BLINKNAME;
            Serial.println("Blinking Name");
            blinkText("MATTHEW A. ROXAS", 1000, 3);
            ChangeLCDState(PRINTREADY); // Safely change state
            break;
        case PRINTREADY:
            prevState = PRINTREADY;
            Serial.println("Display Ready");
            lcd.setCursor(0, 0); // Set cursor to first row
            lcd.print("READY!");
            vTaskDelay(pdMS_TO_TICKS(3000)); // Delay to show "Ready" message
            ChangeLCDState(LCD_SEQUENCE1);
            break;

        case LCD_SEQUENCE1:
            displaySequenceNumber("SEQUENCE 1", prevState);
            prevState = LCD_SEQUENCE1;
            displayMotorAction("MOTOR 1 > CW", "MOTOR 2 > CW");
            ChangeMotorState(SEQUENCE1);
            isNotVoiceCommand(isVoiceCommand, sequenceDelay, LCD_SEQUENCE2);
            break;
        case LCD_SEQUENCE2:
            displaySequenceNumber("SEQUENCE 2", prevState);
            prevState = LCD_SEQUENCE2;
            displayMotorAction("MOTOR 1 > C-CW", "MOTOR 2 > C-CW");
            ChangeMotorState(SEQUENCE2);
            isNotVoiceCommand(isVoiceCommand, sequenceDelay, LCD_SEQUENCE3);
            break;
        case LCD_SEQUENCE3:
            displaySequenceNumber("SEQUENCE 3", prevState);
            prevState = LCD_SEQUENCE3;
            displayMotorAction("MOTOR 1 > CW", "MOTOR 2 > C-CW");
            ChangeMotorState(SEQUENCE3);
            isNotVoiceCommand(isVoiceCommand, sequenceDelay, LCD_SEQUENCE1);
            break;
        case LCD_STANDBY:
            prevState = LCD_STANDBY;
            lcd.setCursor(0, 0);
            lcd.print("STANDBY");
            vTaskDelay(pdMS_TO_TICKS(1000));
            ChangeMotorState(STANDBY);
            break;

        default:
            Serial.println("Nothing to do");
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void LCDTaskInit()
{
    lcd.init();      // Initialize the LCD
    lcd.backlight(); // Turn on the backlight
    displayMutex = xSemaphoreCreateMutex();
    // xTaskCreatePinnedToCore(LCDTask, "LCDTask", (1024 * 7), NULL, 1, &TaskHandle_LCDTask, 0);
    xTaskCreate(LCDTask, "LCDTask", (1024 * 7), NULL, 1, &TaskHandle_LCDTask);
}

void scrollText(String text, int delayMs)
{
    int lcdCols = 16;

    // Pad message with spaces to scroll cleanly
    String padded = "                " + text + "                ";

    // Total scroll steps = padded.length() - visible columns
    for (int i = 0; i <= padded.length() - lcdCols; i++)
    {
        lcd.setCursor(0, 0);                         // First row
        lcd.print(padded.substring(i, i + lcdCols)); // Print slice
        vTaskDelay(pdMS_TO_TICKS(300));              // Delay
    }

    lcd.clear(); // Clear the display after scrolling
}

void blinkText(String text, int delayMs, int blinkCount)
{
    for (int i = 0; i < blinkCount; i++)
    {
        lcd.setCursor(0, 0); // ✅ FIX: Set position
        lcd.print(text);
        vTaskDelay(pdMS_TO_TICKS(delayMs));
        lcd.clear();
        vTaskDelay(pdMS_TO_TICKS(delayMs));
    }
}

void ChangeLCDState(DisplayState state)
{
    // Attempt to take the mutex, block forever if necessary
    if (xSemaphoreTake(displayMutex, portMAX_DELAY) == pdTRUE)
    {
        displayState = state;
        xSemaphoreGive(displayMutex);
    }
    else
    {
        Serial.println("Failed to acquire display mutex");
    }
}

void isNotVoiceCommand(bool isVoiceCommand, int sequenceDelay, DisplayState nextState)
{
    if (!isVoiceCommand)
    {
        vTaskDelay(pdMS_TO_TICKS(sequenceDelay)); // Wait for motor action
        ChangeMotorState(STANDBY);
        ChangeLCDState(nextState);
    }
    else
    {
        // Add small delay to prevent infinite fast looping
        vTaskDelay(pdMS_TO_TICKS(200)); // Prevent screen spamming
    }
}

void displaySequenceNumber(String sequence_str, DisplayState prevState)
{
    if (prevState == displayState)
        return;
    lcd.setCursor(0, 0);
    lcd.print(sequence_str);
    vTaskDelay(pdMS_TO_TICKS(1000));
    lcd.clear();
}

void displayMotorAction(String row1_str, String row2_str)
{
    lcd.setCursor(0, 0);
    lcd.print(row1_str);
    lcd.setCursor(0, 1);
    lcd.print(row2_str);
}
