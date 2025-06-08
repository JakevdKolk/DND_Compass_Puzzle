#include "rgb_commander.hpp"

RGBSetColorCommand::RGBSetColorCommand(Colors *colors, colorCodes color)
    : colors_(colors), color_(color) {}

void RGBSetColorCommand::Execute() const
{
    colors_->applyColor(color_);
}

RGBPulseLEDCommand::RGBPulseLEDCommand(Colors *colors, colorCodes color, int count, int timeout)
    : colors_(colors), color_(color), loopcount_(count), looptimeout_(timeout) {}

void RGBPulseLEDCommand::Execute() const
{
    colors_->pulse_rgbLED(color_, loopcount_, looptimeout_);
}
