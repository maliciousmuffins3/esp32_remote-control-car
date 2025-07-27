// CommandProcessor.h

#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include <Arduino.h>

enum CommandResult
{
    CMD_NONE,
    CMD_UNKNOWN,
    CMD_TURN_ON_VOICE,
    CMD_TURN_OFF_VOICE,
    CMD_SEQ1,
    CMD_SEQ2,
    CMD_SEQ3,
    CMD_SEQ4,
    CMD_SEQ5,
    CMD_SEQ6,
    CMD_STOP
};

CommandResult processCommand(String &msg);

#endif
