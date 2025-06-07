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
  delay(2000);
  context.pulseDirection(&north, directions::North, 5, 500);
  delay(2000);
  context.pulseDirection(&north, directions::North_East, 5, 250);
  delay(2000);
  context.pulseDirection(&all, directions::All, 5, 250);
  delay(2000);

  context.transitionTo(&north);
  context.handleDirection(directions::North);
  delay(2000);

  context.handleDirection(directions::North_East);
  delay(2000);

  context.transitionTo(&south);
  context.handleDirection(directions::South);
  delay(2000);
  context.handleDirection(directions::South_West);
  delay(2000);

  context.transitionTo(&west);
  context.handleDirection(directions::West);
  delay(2000);
  context.handleDirection(directions::North_West);
  delay(2000);

  context.transitionTo(&east);
  context.handleDirection(directions::East);
  delay(2000);
  context.handleDirection(directions::South_East);
  delay(2000);

  context.transitionTo(&all);
  context.handleDirection(directions::All);
  delay(2000);

  context.transitionTo(&off);
  context.handleDirection(directions::Off);
  delay(2000);
}
