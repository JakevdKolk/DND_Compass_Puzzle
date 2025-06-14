#pragma once
#include "../InputCommander.hpp"
#include "../../compass/directions/state_directions.hpp"

class compassHandleDirectonCommand : public userCommand
{
private:
    compass_context *context_;
    compass_state *state_;
    directions direction_;

public:
    compassHandleDirectonCommand(compass_context *context, compass_state *state, directions dir);
    void Execute(String args) const override;
};

class compassPulseDirectonCommand : public userCommand
{
private:
    compass_context *context_;
    compass_state *state_;
    directions direction_;

public:
    compassPulseDirectonCommand(compass_context *context, compass_state *state, directions dir);
    void Execute(String args) const override;
};

class compassPuzzleCommand : public userCommand
{
private:
    compass_context *context_;
    static directions parseDirection(const String &token);

public:
    explicit compassPuzzleCommand(compass_context *context);
    void Execute(String args) const override;
};

struct CompassColorRegistration
{
    const char *name;
    compass_state *state;
    directions dir;
};

extern CompassColorRegistration compassCommandList[];
extern const int compassCommandListSize;