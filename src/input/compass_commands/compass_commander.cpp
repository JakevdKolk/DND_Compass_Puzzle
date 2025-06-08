
#include "compass_commander.hpp"

compassHandleDirectonCommand::compassHandleDirectonCommand(compass_context *context, compass_state *state, directions dir) : context_(context), state_(state), direction_(dir) {}

void compassHandleDirectonCommand::Execute() const
{
    context_->transitionTo(state_);
    context_->handleDirection(direction_);
};

compassPulseDirectonCommand::compassPulseDirectonCommand(compass_context *context, compass_state *state, directions dir, int count, int timeout) : context_(context), state_(state), direction_(dir), pulseCount_(count), pulseTimeout_(timeout) {};

void compassPulseDirectonCommand::Execute() const
{
    context_->transitionTo(state_);
    context_->pulseDirection(state_, direction_, pulseCount_, pulseTimeout_);
}