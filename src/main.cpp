#include <Arduino.h>
#include "colors/colors.h"

Colors colorHandler;
colorCodes colorCodeList;

int LEDPins[4] = {4, 5, 16, 17};
int rgbLED[3] = {12, 13, 14};

colorCodes colors[] = {
    colorCodes::Red,
    colorCodes::Green,
    colorCodes::Blue,
    colorCodes::Yellow,
    colorCodes::Cyan,
    colorCodes::Magenta,
    colorCodes::White};

colorCodes partyColors[] = {
    colorCodes::Aether,
    colorCodes::Jiji,
    colorCodes::Seraphine,
    colorCodes::Taron,
    colorCodes::Lucian};

void setup()
{
  for (int i = 0; i < 4; i++)
  {
    pinMode(LEDPins[i], OUTPUT);
  }

  ledcSetup(RED_CHANNEL, 5000, 8);
  ledcSetup(GREEN_CHANNEL, 5000, 8);
  ledcSetup(BLUE_CHANNEL, 5000, 8);

  ledcAttachPin(rgbLED[0], RED_CHANNEL);
  ledcAttachPin(rgbLED[1], GREEN_CHANNEL);
  ledcAttachPin(rgbLED[2], BLUE_CHANNEL);
}

void loop()
{
  int direction[4] = {0, 1, 2, 3};

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      digitalWrite(LEDPins[j], j == direction[i] ? LOW : HIGH);
    }
  }

  for (int i = 0; i < 5; i++)
  {
    colorHandler.pulse_rgbLED(partyColors[i], 1);
  }
}
