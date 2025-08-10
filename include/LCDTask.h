#ifndef LCDTASK_H
#define LCDTASK_H
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "MotorTask.h"
#include "BluetoothTask.h"
#include "ServoTask.h"

enum DisplayState
{
    SCROLLNAME,
    BLINKNAME,
    PRINTREADY,
    LCD_SEQUENCE1,
    LCD_SEQUENCE2,
    LCD_SEQUENCE3,
    LCD_SEQUENCE4,
    LCD_SEQUENCE5,
    LCD_SEQUENCE6,
    LCD_SEQUENCE7,
    LCD_SEQUENCE8,
    LCD_STANDBY
};

extern SemaphoreHandle_t displayMutex; // Mutex for display access
extern DisplayState displayState;      // Current state of the display
extern TaskHandle_t TaskHandle_LCDTask;
extern LiquidCrystal_I2C lcd; // LCD object

void LCDTaskInit();
void LCDTask(void *pvParameters);
void scrollText(String text, int delayMs);
void blinkText(String text, int delayMs, int blinkCount);
void ChangeLCDState(DisplayState state);

void isNotVoiceCommand(bool isVoiceCommand, int sequenceDelay, DisplayState nextState);
void displaySequenceNumber(String sequence_str, DisplayState prevState);
void displayText(String row1_str, String row2_str = "");

#endif // LCDTASK_H