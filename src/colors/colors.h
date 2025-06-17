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

    // Pulse state tracking
    bool isPulsing = false;
    colorCodes pulseColor;
    int pulseCount = 0;
    int pulseTimeout = 0;
    int currentPulse = 0;
    bool ledOn = false;
    unsigned long lastToggleTime = 0;

public:
    explicit Colors(int r = RED_CHANNEL, int g = GREEN_CHANNEL, int b = BLUE_CHANNEL);

    void applyColor(colorCodes color);
    void SetColor(int r, int g, int b);
    void resetColor();

    void startPulse(colorCodes color, int loopCount, int timeout);
    void updatePulse();
    void pulse_rgbLED(colorCodes color, int loopCount, int timeout);
};
