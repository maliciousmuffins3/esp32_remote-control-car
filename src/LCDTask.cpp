#include "LCDTask.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
SemaphoreHandle_t displayMutex = NULL;
DisplayState displayState = SCROLLNAME;
TaskHandle_t TaskHandle_LCDTask = NULL;

void LCDTask(void *pvParameters)
{
    while (true)
    {
        switch (displayState)
        {
        case SCROLLNAME:
            Serial.println("Scrolling Name");
            lcd.clear();
            scrollText("MATTHEW ARELLANO ROXAS", 300);
            ChangeLCDState(BLINKNAME); // Safely change state
            break;
        case BLINKNAME:
            Serial.println("Blinking Name");
            lcd.clear();
            blinkText("MATTHEW A. ROXAS", 1000, 3);
            ChangeLCDState(PRINTREADY); // Safely change state
            break;
        case PRINTREADY:
            Serial.println("Display Ready");
            lcd.clear();
            lcd.setCursor(0, 0); // Set cursor to first row
            lcd.print("READY!");
            vTaskDelay(pdMS_TO_TICKS(3000)); // Delay to show "Ready" message
            ChangeLCDState(LCD_SEQUENCE1);
            break;

        case LCD_SEQUENCE1:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("SEQUENCE 1");
            vTaskDelay(pdMS_TO_TICKS(1000));
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("MOTOR 1 > CW");
            ChangeMotorState(SEQUENCE1);
            vTaskDelay(pdMS_TO_TICKS(3000)); // Wait for motor action
            ChangeMotorState(STANDBY);       // Stop motor after action
            ChangeLCDState(LCD_SEQUENCE2);
            break;
        case LCD_SEQUENCE2:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("SEQUENCE 2");
            vTaskDelay(pdMS_TO_TICKS(1000));
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("MOTOR 1 > C-CW");
            ChangeMotorState(SEQUENCE2);
            vTaskDelay(pdMS_TO_TICKS(3000)); // Wait for motor action
            ChangeMotorState(STANDBY);       // Stop motor after action
            ChangeLCDState(LCD_SEQUENCE3);
            break;
        case LCD_SEQUENCE3:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("SEQUENCE 3");
            vTaskDelay(pdMS_TO_TICKS(1000));
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("MOTOR 2 > CW");
            ChangeMotorState(SEQUENCE3);
            vTaskDelay(pdMS_TO_TICKS(3000)); // Wait for motor action
            ChangeMotorState(STANDBY);       // Stop motor after action
            ChangeLCDState(LCD_SEQUENCE4);
            break;
        case LCD_SEQUENCE4:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("SEQUENCE 4");
            vTaskDelay(pdMS_TO_TICKS(1000));
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("MOTOR 2 > C-CW");
            ChangeMotorState(SEQUENCE4);
            vTaskDelay(pdMS_TO_TICKS(3000)); // Wait for motor action
            ChangeMotorState(STANDBY);       // Stop motor after action
            ChangeLCDState(LCD_SEQUENCE5);
            break;
        case LCD_SEQUENCE5:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("SEQUENCE 5");
            vTaskDelay(pdMS_TO_TICKS(1000));
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("MOTOR 1 > CW");
            lcd.setCursor(0, 1);
            lcd.print("MOTOR 2 > C-CW");
            ChangeMotorState(SEQUENCE5);
            vTaskDelay(pdMS_TO_TICKS(3000)); // Wait for motor action
            ChangeMotorState(STANDBY);       // Stop motor after action
            ChangeLCDState(LCD_SEQUENCE6);
            break;
        case LCD_SEQUENCE6:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("SEQUENCE 5");
            vTaskDelay(pdMS_TO_TICKS(1000));
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("MOTOR 1 > C-CW");
            lcd.setCursor(0, 1);
            lcd.print("MOTOR 2 > CW");
            ChangeMotorState(SEQUENCE6);
            vTaskDelay(pdMS_TO_TICKS(3000)); // Wait for motor action
            ChangeMotorState(STANDBY);       // Stop motor after action
            ChangeLCDState(LCD_SEQUENCE1);
            break;

        default:
            Serial.println("Nothing to do");
            break;
        }
    }
}

void LCDTaskInit()
{
    lcd.init();      // Initialize the LCD
    lcd.backlight(); // Turn on the backlight
    displayMutex = xSemaphoreCreateMutex();
    xTaskCreatePinnedToCore(LCDTask, "LCDTask", (2048 * 4), NULL, 1, &TaskHandle_LCDTask, 0);
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
        displayState = state;         // Safely update shared state
        xSemaphoreGive(displayMutex); // Always give it back
    }
    else
    {
        // Optional: log or handle failure (shouldn’t happen with portMAX_DELAY)
        Serial.println("Failed to acquire display mutex");
    }
}
