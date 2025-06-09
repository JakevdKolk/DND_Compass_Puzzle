#include "pusling.hpp"

int pulsing::applyPulsing(pulsingCodes pCodes)
{
    switch (pCodes)
    {
    case pulsingCodes::Fast:
        return 100;
        break;
    case pulsingCodes::Normal:
        return 300;
        break;
    case pulsingCodes::Slow:
        return 600;
        break;
    default:
        return 300;
        break;
    }
};