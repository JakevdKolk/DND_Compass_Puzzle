#include "vibration_motor_commander.hpp"

VibrationMotorCommands::VibrationMotorCommands(vibration_context *context, vibration_state *state, vibration_statuses statuses, bool isPulse, int pulseTimeout)
    : context_(context), state_(state), statuses_(statuses), isPulse_(isPulse), pulseTimeout_(pulseTimeout) {}

void VibrationMotorCommands::Execute(String args) const
{
    context_->transitionTo(state_);

    if (isPulse_)
    {
        state_->hanldeVibrationPulse(statuses_, pulseTimeout_);
    }
    else
    {
        context_->handleState(statuses_);
    }
}
