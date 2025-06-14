#include "vibration_motor_commander.hpp"

VibrationMotorCommands::VibrationMotorCommands(vibration_context *context, vibration_state *state, vibration_statuses statuses) : context_(context), state_(state), statuses_(statuses) {}

void VibrationMotorCommands::Execute(String args) const
{
    context_->transitionTo(state_);
    context_->handleState(statuses_);
};