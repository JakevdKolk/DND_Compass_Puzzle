#include "rgb_commander.hpp"
#include "../../pulsing/pusling.hpp"

RGBSetColorCommand::RGBSetColorCommand(Colors *colors, colorCodes color)
    : colors_(colors), color_(color) {}

void RGBSetColorCommand::Execute(String args) const
{
    colors_->applyColor(color_);
}

RGBPulseLEDCommand::RGBPulseLEDCommand(Colors *colors, colorCodes color)
    : color_(color), colors_(colors) {}

void RGBPulseLEDCommand::Execute(String args) const
{

    pulsingCodes pulseCodes;

    int count = 1;
    pulsingCodes speed = pulsingCodes::Normal;

    int spaceIndex = args.indexOf(' ');
    if (spaceIndex > 0)
    {
        count = args.substring(0, spaceIndex).toInt();
        String timeout = args.substring(spaceIndex + 1);
        timeout.toLowerCase();

        getPulsingTimeout()
    }

    colors_->pulse_rgbLED(color_, count, speed);
}

int getPulsingTimeout(String speed)
{

    switch (speed)
    {
    case:

        break;

    default:
        break;
    }
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
