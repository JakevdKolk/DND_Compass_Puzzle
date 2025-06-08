#include <Arduino.h>
#include "colors/colors.h"
#include "compass/directions/state_directions.hpp"
#include "input/InputCommander.hpp"
#include "input/rgb_commands/rgb_commander.hpp"
#include "input/compass_commands/compass_commander.hpp"


Colors colorHandler;

state_north north;
state_east east;
state_south south;
state_west west;
state_off off;
state_on all;

commandManager manager;


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
  colorHandler.applyColor(colorCodes::Off);
  context.handleDirection(directions::Off);

  pinMode(buzzer, OUTPUT);
  Serial.begin(115200);
  Serial.setTimeout(10000);

  for (int i = 0; i < commandListSize; i++)
  {
    RGBColorRegistration reg = commandList[i];
    manager.registerCommand(reg.name, new RGBSetColorCommand(&colorHandler, reg.color));

    String pulseName = "P_" + String(reg.name);
    manager.registerCommand(pulseName, new RGBPulseLEDCommand(&colorHandler, reg.color));
  }

  for (int i = 0; i < compassCommandListSize; ++i)
  {
    const auto &reg = compassCommandList[i];

    manager.registerCommand(reg.name, new compassHandleDirectonCommand(&context, reg.state, reg.dir));

    String pulseName = "P_" + String(reg.name);
    manager.registerCommand(pulseName, new compassPulseDirectonCommand(&context, reg.state, reg.dir));
  }

  manager.registerCommand("RGB_OFF", new RGBSetColorCommand(&colorHandler, colorCodes::White)); // RGB_COLORWHITE
  manager.registerCommand("COMPASS_OFF", new compassHandleDirectonCommand(&context, &off, directions::Off));
}
void loop()
{

  if (Serial.available())
  {
    Serial.print("> ");
    String input = Serial.readStringUntil('\n');
    input.trim();
    input.toUpperCase();

    manager.executeCommand(input);

    Serial.println("Command executed: " + input);

  }
}
