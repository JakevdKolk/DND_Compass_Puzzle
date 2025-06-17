#pragma once
#include "../vibration_state.hpp"

class vib_state_off : public vibration_state
{
public:
    void handleState(vibration_statuses statuses) override;
};

class vib_state_on : public vibration_state
{
public:
    void handleState(vibration_statuses statuses) override;
};

class vib_state_pulse : public vibration_state
{
public:
    void hanldeVibrationPulse(vibration_statuses statuses, int timeout) override;
};
