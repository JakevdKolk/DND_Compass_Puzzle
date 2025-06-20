#pragma once

#define RED_CHANNEL 0
#define GREEN_CHANNEL 1
#define BLUE_CHANNEL 2

#include <Arduino.h>

enum class colorCodes
{
    Red,
    Green,
    Blue,
    Yellow,
    Cyan,
    Magenta,
    White,
    Off,
    Aether,
    Lucian,
    Seraphine,
    Jiji,
    Taron
};

class Colors
{
private:
    int redChannel;
    int greenChannel;
    int blueChannel;

public:
    explicit Colors(int r = RED_CHANNEL, int g = GREEN_CHANNEL, int b = BLUE_CHANNEL);

    void applyColor(colorCodes color);
    void SetColor(int r, int g, int b);
    void resetColor();
    void pulse_rgbLED(colorCodes color, int loopCount, int timeout);
};
