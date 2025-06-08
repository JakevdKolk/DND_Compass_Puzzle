#pragma once
#include "../InputCommander.hpp"
#include "../../colors/colors.h"


class RGBSetColorCommand : public userCommand
{
private:
    Colors *colors_;
    colorCodes color_;

public:
    RGBSetColorCommand(Colors *colors, colorCodes color);
    void Execute(String args) const override;
};

class RGBPulseLEDCommand : public userCommand
{
private:
    colorCodes color_;
    Colors *colors_;

public:
    RGBPulseLEDCommand(Colors *colors, colorCodes color);
    void Execute(String args) const override;
};

struct RGBColorRegistration
{
    const char *name;
    colorCodes color;
};

extern RGBColorRegistration commandList[];
extern const int commandListSize;
