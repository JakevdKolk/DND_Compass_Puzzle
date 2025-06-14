#pragma once
#include "../InputCommander.hpp"
#include "../../vibration_motor/vibration_state.hpp"

class VibrationMotorCommands : public userCommand
{
private:
    vibration_context *context_;
    vibration_state *state_;
    vibration_statuses statuses_;

public:
    VibrationMotorCommands(vibration_context *context, vibration_state *state, vibration_statuses statuses);
    void Execute(String args) const override;
};
