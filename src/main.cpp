#include <Arduino.h>

int ledPins[4] = {2, 5, 16, 17};

void setup()
{
  for (int i = 0; i < 4; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop()
{
  int direction[5] = {0, 1, 2, 3, 3}; // 0=N, 1=E, 2=S, 3=W
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      digitalWrite(ledPins[j], j == direction[i] ? LOW : HIGH);
    }
    delay(5000);
  }
}
