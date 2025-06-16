#include "vibration_motor_commander.hpp"

VibrationMotorCommands::VibrationMotorCommands(vibration_context *context, vibration_state *state, vibration_statuses statuses, bool isPulse)
    : context_(context), state_(state), statuses_(statuses), isPulse_(isPulse) {}

void VibrationMotorCommands::Execute(String args) const
{
    context_->transitionTo(state_);

    if (isPulse_)
    {
        state_->hanldeVibrationPulse(statuses_, args.toInt());
    }
    else
    {
        context_->handleState(statuses_);
    }
}
