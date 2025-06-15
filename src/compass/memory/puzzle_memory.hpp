#pragma once
#include <Arduino.h>
#include <vector>
#include "../../compass/directions/state_directions.hpp"

#define EEPROM_ADDR_PUZZLE 0
#define MAX_PUZZLE_LENGTH 32

class PuzzleMemory
{
public:
    static void savePuzzle(const std::vector<directions> &puzzle, uint16_t delayMs);
    static std::vector<directions> loadPuzzle(uint16_t &delayMsOut);
};
