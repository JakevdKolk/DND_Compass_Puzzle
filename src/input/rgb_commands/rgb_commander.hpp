#pragma once
#include "../InputCommander.hpp"
#include "colors/colors.h"

class RGBSetColorCommand : public userCommand
{
private:
    Colors *colors_;
    colorCodes color_;

public:
    RGBSetColorCommand(Colors *colors, colorCodes color);
    void Execute() const override;
};

class RGBPulseLEDCommand : public userCommand
{
private:
    colorCodes color_;
    Colors *colors_;
    int loopcount_;
    int looptimeout_;

public:
    RGBPulseLEDCommand(Colors *colors, colorCodes color, int count, int timeout);
    void Execute() const override;
};