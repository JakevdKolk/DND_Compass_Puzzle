#pragma once
#include <map>
#include <Arduino.h>

class userCommand
{
public:
    virtual ~userCommand()
    {
    }
    virtual void Execute() const = 0;
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

    void executeCommand(const String &key)
    {
        if (commands_.count(key))
        {
            commands_[key]->Execute();
        }
        else
        {
            Serial.println("Unknown command: " + key);
        }
    }
};
