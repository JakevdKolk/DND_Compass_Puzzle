#include <Arduino.h>
#include "colors/colors.h"

Colors colorHandler;

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
  for (int i = 0; i < 4; i++)
  {
    pinMode(LEDPins[i], OUTPUT);
  }
  pinMode(buzzer, OUTPUT);

}

void loop()
{
  int direction[4] = {0, 1, 2, 3};

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      digitalWrite(LEDPins[j], j == direction[i] ? LOW : HIGH);
      // tone(buzzer, 50 * j);
      delay(100);
    }
  }
  // noTone(buzzer);


  for (int i = 0; i < 5; i++)
  {
    colorHandler.pulse_rgbLED(partyColors[i], 1);
  }
}
