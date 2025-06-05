#pragma once

#define RED_CHANNEL 0
#define GREEN_CHANNEL 1
#define BLUE_CHANNEL 2

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
public:
    void applyColor(colorCodes color);
    void SetColor(int r, int g, int b);
    void resetColor();
    void pulse_rgbLED(colorCodes color, int loopCount);
};
