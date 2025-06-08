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

  pinMode(buzzer, OUTPUT);
  Serial.begin(115200);
  Serial.setTimeout(10000);
  // Party Member Colors
  manager.registerCommand("RGB_PA", new RGBSetColorCommand(&colorHandler, colorCodes::Aether));    // RGB_PARTYAETHER
  manager.registerCommand("RGB_PL", new RGBSetColorCommand(&colorHandler, colorCodes::Lucian));    // RGB_PARTYLUCIAN
  manager.registerCommand("RGB_PJ", new RGBSetColorCommand(&colorHandler, colorCodes::Jiji));      // RGB_PARTYJIJI
  manager.registerCommand("RGB_PT", new RGBSetColorCommand(&colorHandler, colorCodes::Taron));     // RGB_PARTYTARON
  manager.registerCommand("RGB_PS", new RGBSetColorCommand(&colorHandler, colorCodes::Seraphine)); // RGB_PARTYSERAPHINE

  // Core Colors
  manager.registerCommand("RGB_RED", new RGBSetColorCommand(&colorHandler, colorCodes::Red));         // RGB_COLORRED
  manager.registerCommand("RGB_BLUE", new RGBSetColorCommand(&colorHandler, colorCodes::Blue));       // RGB_COLORBLUE
  manager.registerCommand("RGB_CGREEN", new RGBSetColorCommand(&colorHandler, colorCodes::Green));    // RGB_COLORGREEN
  manager.registerCommand("RGB_YELLOW", new RGBSetColorCommand(&colorHandler, colorCodes::Yellow));   // RGB_COLORYELLOW
  manager.registerCommand("RGB_MAGENTA", new RGBSetColorCommand(&colorHandler, colorCodes::Magenta)); // RGB_COLORMAGENTA
  manager.registerCommand("RGB_CYAN", new RGBSetColorCommand(&colorHandler, colorCodes::Cyan));       // RGB_COLORCYAN
  manager.registerCommand("RGB_WHITE", new RGBSetColorCommand(&colorHandler, colorCodes::White));     // RGB_COLORWHITE

  // Pulse: Party Member Colors
  manager.registerCommand("P_RGB_PA", new RGBPulseLEDCommand(&colorHandler, colorCodes::Aether, 5, 250));    // PULSE_RGB_PARTYAETHER
  manager.registerCommand("P_RGB_PL", new RGBPulseLEDCommand(&colorHandler, colorCodes::Lucian, 5, 250));    // PULSE_RGB_PARTYLUCIAN
  manager.registerCommand("P_RGB_PJ", new RGBPulseLEDCommand(&colorHandler, colorCodes::Jiji, 5, 250));      // PULSE_RGB_PARTYJIJI
  manager.registerCommand("P_RGB_PT", new RGBPulseLEDCommand(&colorHandler, colorCodes::Taron, 5, 250));     // PULSE_RGB_PARTYTARON
  manager.registerCommand("P_RGB_PS", new RGBPulseLEDCommand(&colorHandler, colorCodes::Seraphine, 5, 250)); // PULSE_RGB_PARTYSERAPHINE

  // Pulse: Core Colors
  manager.registerCommand("P_RGB_RED", new RGBPulseLEDCommand(&colorHandler, colorCodes::Red, 5, 250));         // PULSE_RGB_COLORRED
  manager.registerCommand("P_RGB_BLUE", new RGBPulseLEDCommand(&colorHandler, colorCodes::Blue, 5, 250));       // PULSE_RGB_COLORBLUE
  manager.registerCommand("P_RGB_CGREEN", new RGBPulseLEDCommand(&colorHandler, colorCodes::Green, 5, 250));    // PULSE_RGB_COLORGREEN
  manager.registerCommand("P_RGB_YELLOW", new RGBPulseLEDCommand(&colorHandler, colorCodes::Yellow, 5, 250));   // PULSE_RGB_COLORYELLOW
  manager.registerCommand("P_RGB_MAGENTA", new RGBPulseLEDCommand(&colorHandler, colorCodes::Magenta, 5, 250)); // PULSE_RGB_COLORMAGENTA
  manager.registerCommand("P_RGB_CYAN", new RGBPulseLEDCommand(&colorHandler, colorCodes::Cyan, 5, 250));       // PULSE_RGB_COLORCYAN
  manager.registerCommand("P_RGB_WHITE", new RGBPulseLEDCommand(&colorHandler, colorCodes::White, 5, 250));     // PULSE_RGB_COLORWHITE

  manager.registerCommand("COMP_N", new compassHandleDirectonCommand(&context, &north, directions::North));
  manager.registerCommand("COMP_NE", new compassHandleDirectonCommand(&context, &north, directions::North_East));
  manager.registerCommand("COMP_NW", new compassHandleDirectonCommand(&context, &north, directions::North_West));

  manager.registerCommand("COMP_S", new compassHandleDirectonCommand(&context, &south, directions::South));
  manager.registerCommand("COMP_SE", new compassHandleDirectonCommand(&context, &south, directions::South_East));
  manager.registerCommand("COMP_SW", new compassHandleDirectonCommand(&context, &south, directions::South_West));

  manager.registerCommand("COMP_E", new compassHandleDirectonCommand(&context, &east, directions::East));
  manager.registerCommand("COMP_W", new compassHandleDirectonCommand(&context, &west, directions::West));

  manager.registerCommand("COMP_OFF", new compassHandleDirectonCommand(&context, &off, directions::Off));
  manager.registerCommand("COMP_ALL", new compassHandleDirectonCommand(&context, &all, directions::All));
  // pulse compass
  manager.registerCommand("P_COMP_N", new compassPulseDirectonCommand(&context, &north, directions::North, 5, 300));
  manager.registerCommand("P_COMP_NE", new compassPulseDirectonCommand(&context, &north, directions::North_East, 5, 300));
  manager.registerCommand("P_COMP_NW", new compassPulseDirectonCommand(&context, &north, directions::North_West, 5, 300));

  manager.registerCommand("P_COMP_S", new compassPulseDirectonCommand(&context, &south, directions::South, 5, 300));
  manager.registerCommand("P_COMP_SE", new compassPulseDirectonCommand(&context, &south, directions::South_East, 5, 300));
  manager.registerCommand("P_COMP_SW", new compassPulseDirectonCommand(&context, &south, directions::South_West, 5, 300));

  manager.registerCommand("P_COMP_E", new compassPulseDirectonCommand(&context, &east, directions::East, 5, 300));
  manager.registerCommand("P_COMP_W", new compassPulseDirectonCommand(&context, &west, directions::West, 5, 300));

  manager.registerCommand("P_COMP_ALL", new compassPulseDirectonCommand(&context, &all, directions::All, 5, 300));
}

void loop()
{

  if (Serial.available())
  {
    Serial.println("Type command:");
    String input = Serial.readStringUntil('\n');
    input.trim();
    input.toUpperCase();
    manager.executeCommand(input);
    Serial.println("command used: " + input);
  }
}
