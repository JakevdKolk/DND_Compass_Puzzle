#include <Arduino.h>
#include "colors/colors.h"
#include "compass/directions/state_directions.hpp"

Colors colorHandler;

state_north north;
state_east east;
state_south south;
state_west west;
state_off off;
state_on all;

compass_context context(&off);

int buzzer = 23;

colorCodes colors[] = {
    colorCodes::Red,
    colorCodes::Green,
    colorCodes::Blue,
    colorCodes::Magenta,
    colorCodes::Yellow,
    colorCodes::Cyan,
    colorCodes::White};

colorCodes partyColors[] = {
    colorCodes::Aether,
    colorCodes::Jiji,
    colorCodes::Seraphine,
    colorCodes::Taron,
    colorCodes::Lucian};

void setup()
{

  pinMode(buzzer, OUTPUT);
}

void loop()
{
  context.pulseDirection(&east, directions::East, 3, 500);
  delay(500);
  context.pulseDirection(&north, directions::North, 5, 500);
  delay(500);
  context.pulseDirection(&north, directions::North_East, 5, 250);
  delay(500);
  context.pulseDirection(&all, directions::All, 10, 300);
  delay(500);

  context.transitionTo(&north);
  context.handleDirection(directions::North);
  delay(500);

  context.handleDirection(directions::North_East);
  delay(500);

  context.transitionTo(&south);
  context.handleDirection(directions::South);
  delay(500);
  context.handleDirection(directions::South_West);
  delay(500);

  context.transitionTo(&west);
  context.handleDirection(directions::West);
  delay(500);
  context.handleDirection(directions::North_West);
  delay(500);

  context.transitionTo(&east);
  context.handleDirection(directions::East);
  delay(500);
  context.handleDirection(directions::South_East);
  delay(500);

  context.transitionTo(&all);
  context.handleDirection(directions::All);
  delay(500);

  context.transitionTo(&off);
  context.handleDirection(directions::Off);
  delay(500);

  for (int i = 0; i < 5; i++)
  {
    colorHandler.pulse_rgbLED(partyColors[i], 5, 1000);
  }
}
