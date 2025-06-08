#pragma once
#include <map>
#include <Arduino.h>

class userCommand
{
public:
    virtual ~userCommand() {}
    virtual void Execute(String args = "") const = 0;
};

class commandManager
{
private:
    std::map<String, userCommand *> commands_;

public:
    void registerCommand(const String &key, userCommand *command)
    {
        commands_[key] = command;
    }

    void executeCommand(const String &fullCommand)
    {
        int spaceIndex = fullCommand.indexOf(' ');
        String commandKey = fullCommand;
        String args = "";

        if (spaceIndex != -1)
        {
            commandKey = fullCommand.substring(0, spaceIndex);
            args = fullCommand.substring(spaceIndex + 1);
        }

        if (commands_.count(commandKey))
        {
            commands_[commandKey]->Execute(args);
        }
        else
        {
            Serial.println("Unknown command: " + commandKey);
        }
    }
};
