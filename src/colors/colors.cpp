#include <Arduino.h>
#include "colors.h"

void Colors::SetColor(int r, int g, int b)
{
    ledcWrite(RED_CHANNEL, 255 - r);
    ledcWrite(GREEN_CHANNEL, 255 - g);
    ledcWrite(BLUE_CHANNEL, 255 - b);
}

void Colors::resetColor()
{
    SetColor(0, 0, 0);
}

void Colors::pulse_rgbLED(colorCodes color, int loopCount)
{
    for (int i = 0; i < loopCount; ++i)
    {
        applyColor(color);
        delay(500);
        resetColor();
        delay(500);
    }
}

void Colors::applyColor(colorCodes color)
{
    switch (color)
    {
    case colorCodes::Red:
        SetColor(255, 0, 0);
        break;
    case colorCodes::Green:
        SetColor(0, 255, 0);
        break;
    case colorCodes::Blue:
        SetColor(0, 0, 255);
        break;
    case colorCodes::Cyan:
        SetColor(255, 255, 0);
        break;
    case colorCodes::Yellow:
        SetColor(0, 255, 255);
        break;
    case colorCodes::Magenta:
        SetColor(255, 0, 255);
        break;
    case colorCodes::White:
        SetColor(255, 255, 255);
        break;
    case colorCodes::Aether:
        SetColor(85, 235, 235);
        break;
    case colorCodes::Lucian:
        SetColor(120, 0, 180);
        break;
    case colorCodes::Jiji:
        SetColor(190, 30, 45);
        break;
    case colorCodes::Taron:
        SetColor(255, 210, 0);
        break;
    case colorCodes::Seraphine:
        SetColor(230, 240, 255);
        break;
    default:
        SetColor(0, 0, 0);
        break;
    }
}
