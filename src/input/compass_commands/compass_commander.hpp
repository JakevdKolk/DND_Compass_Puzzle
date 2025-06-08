#pragma once
#include "../InputCommander.hpp"
#include "compass/directions/state_directions.hpp"
#include "compass/compass_state.hpp"

class compassHandleDirectonCommand : public userCommand
{
private:
    compass_context *context_;
    compass_state *state_;
    directions direction_;

public:
    compassHandleDirectonCommand(compass_context *context, compass_state *state, directions dir);
    void Execute() const override;
};

class compassPulseDirectonCommand : public userCommand
{
private:
    compass_context *context_;
    compass_state *state_;
    directions direction_;
    int pulseCount_;
    int pulseTimeout_;

public:
    compassPulseDirectonCommand(compass_context *context, compass_state *state, directions dir, int count, int timeout);
    void Execute() const override;
};