#include <Arduino.h>
#include "colors/colors.h"
#include "compass/directions/state_directions.hpp"
#include "vibration_motor/states/vibration_motor_states.hpp"
#include "input/InputCommander.hpp"
#include "input/rgb_commands/rgb_commander.hpp"
#include "input/compass_commands/compass_commander.hpp"
#include "input/vibration_motor_commands/vibration_motor_commander.hpp"

Colors colorHandler;

state_north north;
state_east east;
state_south south;
state_west west;
state_off off;
state_on all;

vib_state_on vib_on;
vib_state_off vib_off;

commandManager manager;

compass_context context(&off);
vibration_context vib_context(&vib_off);

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

  manager.registerCommand("VIB_ON", new VibrationMotorCommands(&vib_context, &vib_on, vibration_statuses::On));
  manager.registerCommand("VIB_OFF", new VibrationMotorCommands(&vib_context, &vib_off, vibration_statuses::Off));

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
