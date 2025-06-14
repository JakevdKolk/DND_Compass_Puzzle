#include "vibration_motor_states.hpp"
#include <Arduino.h>

void vib_state_on::handleState(vibration_statuses statuses)
{
    digitalWrite(vibPin_, HIGH);
}
void vib_state_off::handleState(vibration_statuses statuses)
{
    digitalWrite(vibPin_, LOW);
}