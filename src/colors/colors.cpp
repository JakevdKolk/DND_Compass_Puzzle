#include "colors.h"

int rgbLED[3] = {12, 13, 14}; // Define RGB LED pins globally

Colors::Colors(int r, int g, int b) : redChannel(r), greenChannel(g), blueChannel(b)
{
    ledcSetup(redChannel, 5000, 8);
    ledcSetup(greenChannel, 5000, 8);
    ledcSetup(blueChannel, 5000, 8);

    ledcAttachPin(rgbLED[0], redChannel);
    ledcAttachPin(rgbLED[1], greenChannel);
    ledcAttachPin(rgbLED[2], blueChannel);
}

void Colors::SetColor(int r, int g, int b)
{
    ledcWrite(redChannel, 255 - r);
    ledcWrite(greenChannel, 255 - g);
    ledcWrite(blueChannel, 255 - b);
}

void Colors::resetColor()
{
    SetColor(0, 0, 0);
}

void Colors::startPulse(colorCodes color, int loopCount, int timeout)
{
    pulseColor = color;
    pulseCount = loopCount;
    pulseTimeout = timeout;
    currentPulse = 0;
    ledOn = false;
    isPulsing = true;
    lastToggleTime = millis();
}

void Colors::updatePulse()
{
    if (!isPulsing)
        return;

    unsigned long currentTime = millis();
    if (currentTime - lastToggleTime >= pulseTimeout / 2)
    {
        lastToggleTime = currentTime;

        if (ledOn)
        {
            resetColor();
            ledOn = false;
            currentPulse++;
        }
        else
        {
            applyColor(pulseColor);
            ledOn = true;
        }

        if (currentPulse >= pulseCount)
        {
            isPulsing = false;
            resetColor();
        }
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
    case colorCodes::Yellow:
        SetColor(255, 255, 0);
        break;
    case colorCodes::Cyan:
        SetColor(0, 255, 255);
        break;
    case colorCodes::Magenta:
        SetColor(255, 0, 255);
        break;
    case colorCodes::White:
        SetColor(255, 255, 255);
        break;
    case colorCodes::Aether:
        SetColor(0, 197, 179);
        break;
    case colorCodes::Lucian:
        SetColor(35, 0, 90);
        break;
    case colorCodes::Jiji:
        SetColor(255, 75, 5);
        break;
    case colorCodes::Taron:
        SetColor(140, 28, 171);
        break;
    case colorCodes::Seraphine:
        SetColor(172, 39, 44);
        break;
    default:
        resetColor();
        break;
    }
}
