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
    turn_off();
}
void vib_state_pulse::hanldeVibrationPulse(vibration_statuses statuses, int timeout)
{
    turn_off();
    while (statuses == vibration_statuses::Pulsing)
    {
        turn_on();
        delay(timeout / 2);
        turn_off();
        delay(timeout / 2);
    }
}