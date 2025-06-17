#include "vibration_motor_states.hpp"
#include <Arduino.h>

void vibration_state::turn_off()
{
    digitalWrite(vibPin_, LOW);
}
void vibration_state::turn_on()
{
    digitalWrite(vibPin_, HIGH);
}

void vib_state_on::handleState(vibration_statuses statuses)
{
    turn_on();
}
void vib_state_off::handleState(vibration_statuses statuses)
{
    isPulsing = false;
    turn_off();
}
void vib_state_pulse::startVibrationPulse(vibration_statuses statuses, int timeout)
{
    pulseTimeout = timeout;
    isPulsing = true;
    vibOn = false;
    lastToggleTime = millis();
}

void vib_state_pulse::updateVibrationPulse()
{
    if (!isPulsing)
        return;

    unsigned long currentTime = millis();
    if (currentTime - lastToggleTime >= pulseTimeout / 2)
    {
        lastToggleTime = currentTime;

        if (vibOn)
        {
            turn_off();
            vibOn = false;
        }
        else
        {
            turn_on();
            vibOn = true;
        }
    }
}