#ifndef BLUETOOTHTASK_H
#define BLUETOOTHTASK_H

#include <Arduino.h>
#include "BluetoothModule.h"
#include "LCDTask.h"
#include "CommandProcessor.h"

enum COMMAND_STATE
{
    VOICE_COMMAND,
    AUTOMATIC
};

extern BluetoothModule bt;
extern TaskHandle_t TaskHandle_BluetoothTask;
extern COMMAND_STATE commandState;
extern SemaphoreHandle_t CMDMutex;

void BluetoothTask(void *pvParameters);
void BluetoothTaskInit();
void ChangeCommandState(COMMAND_STATE state);

#endif