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

RGBColorRegistration commandList[] = {
    {"RGB_PA", colorCodes::Aether},
    {"RGB_PL", colorCodes::Lucian},
    {"RGB_PJ", colorCodes::Jiji},
    {"RGB_PT", colorCodes::Taron},
    {"RGB_PS", colorCodes::Seraphine},
    {"RGB_RED", colorCodes::Red},
    {"RGB_BLUE", colorCodes::Blue},
    {"RGB_CGREEN", colorCodes::Green},
    {"RGB_YELLOW", colorCodes::Yellow},
    {"RGB_MAGENTA", colorCodes::Magenta},
    {"RGB_CYAN", colorCodes::Cyan},
    {"RGB_WHITE", colorCodes::White},
};

const int commandListSize = sizeof(commandList) / sizeof(commandList[0]);
