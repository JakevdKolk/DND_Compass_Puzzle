#include <Arduino.h>

int LEDPins[4] = {4, 5, 16, 17};

int rgbLED[3] = {12, 13, 14};

#define RED_CHANNEL 0
#define GREEN_CHANNEL 1
#define BLUE_CHANNEL 2

// Setup function
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

void SetColor(int r, int g, int b)
{
  ledcWrite(RED_CHANNEL, 255 - r);
  ledcWrite(GREEN_CHANNEL, 255 - g);
  ledcWrite(BLUE_CHANNEL, 255 - b);
}

// Main loop
void loop()
{
  int direction[4] = {0, 1, 2, 3}; // 0=N, 1=E, 2=S, 3=W

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      digitalWrite(LEDPins[j], j == direction[i] ? LOW : HIGH);
    }

    SetColor(255, 0, 0);
    delay(1000);
    SetColor(0, 255, 0);
    delay(1000);
    SetColor(0, 0, 255);
    delay(5000);
    SetColor(255, 255, 0);
    delay(1000);
    SetColor(0, 255, 255);
    delay(1000);
    SetColor(255, 0, 255);
    delay(1000);
    SetColor(255, 255, 255);
    delay(5000);
  }
}
