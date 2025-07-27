// CommandProcessor.cpp

#include "CommandProcessor.h"
#include "BluetoothTask.h"
CommandResult processCommand(String &msg)
{
    msg.replace("\r", "");
    msg.replace("\n", "");
    msg.trim();
    msg.toLowerCase();
    msg.replace(" ", "");

    Serial.print("COMMAND: ");
    Serial.println(msg);

    if (msg == "")
    {
        Serial.println("Received: <empty>");
        return CMD_NONE;
    }

    Serial.println("Received: " + msg);

    if (msg == "turnonvoicecommand" || msg == "turnonvoicecommands")
        return CMD_TURN_ON_VOICE;
    if (msg == "turnoffvoicecommand" || msg == "turnoffvoicecommands")
        return CMD_TURN_OFF_VOICE;
    if (msg == "sequencenumber1")
        return CMD_SEQ1;
    if (msg == "sequencenumber2")
        return CMD_SEQ2;
    if (msg == "sequencenumber3")
        return CMD_SEQ3;
    if (msg == "sequencenumber4")
        return CMD_SEQ4;
    if (msg == "sequencenumber5")
        return CMD_SEQ5;
    if (msg == "sequencenumber6")
        return CMD_SEQ6;
    if (msg == "stop")
        return CMD_STOP;

    return CMD_UNKNOWN;
}
