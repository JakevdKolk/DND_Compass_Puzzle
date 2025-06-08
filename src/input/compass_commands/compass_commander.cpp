
#include "compass_commander.hpp"

compassHandleDirectonCommand::compassHandleDirectonCommand(compass_context *context, compass_state *state, directions dir) : context_(context), state_(state), direction_(dir) {}

void compassHandleDirectonCommand::Execute(String args) const
{
    context_->transitionTo(state_);
    context_->handleDirection(direction_);
};

compassPulseDirectonCommand::compassPulseDirectonCommand(compass_context *context, compass_state *state, directions dir) : context_(context), state_(state), direction_(dir) {};

void compassPulseDirectonCommand::Execute(String args) const
{
    context_->transitionTo(state_);

    int pulseCount = 1;
    int pulseTimeout = 200;

    int spaceIndex = args.indexOf(' ');
    if (spaceIndex > 0)
    {
        pulseCount = args.substring(0, spaceIndex).toInt();
        pulseTimeout = args.substring(spaceIndex + 1).toInt();
    }

    context_->pulseDirection(state_, direction_, pulseCount, pulseTimeout);
}

extern state_north north;
extern state_east east;
extern state_south south;
extern state_west west;
extern state_on all;
extern state_off off;

CompassColorRegistration compassCommandList[] = {
    {"COMPASS_N", &north, directions::North},
    {"COMPASS_E", &east, directions::East},
    {"COMPASS_S", &south, directions::South},
    {"COMPASS_W", &west, directions::West},
    {"COMPASS_NE", &north, directions::North_East},
    {"COMPASS_NW", &north, directions::North_West},
    {"COMPASS_SE", &east, directions::South_East},
    {"COMPASS_SW", &west, directions::South_West},
    {"COMPASS_ALL", &all, directions::All},
};

const int compassCommandListSize = sizeof(compassCommandList) / sizeof(compassCommandList[0]);