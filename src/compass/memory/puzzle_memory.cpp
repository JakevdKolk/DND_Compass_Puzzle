#include "puzzle_memory.hpp"
#include <EEPROM.h>

void PuzzleMemory::savePuzzle(const std::vector<directions> &puzzle, uint16_t delayMs)
{
    EEPROM.begin(64);

    EEPROM.write(EEPROM_ADDR_PUZZLE, puzzle.size());

    for (size_t i = 0; i < puzzle.size(); ++i)
    {
        EEPROM.write(EEPROM_ADDR_PUZZLE + 1 + i, static_cast<uint8_t>(puzzle[i]));
    }

    EEPROM.write(EEPROM_ADDR_PUZZLE + 1 + MAX_PUZZLE_LENGTH, delayMs & 0xFF);        
    EEPROM.write(EEPROM_ADDR_PUZZLE + 2 + MAX_PUZZLE_LENGTH, (delayMs >> 8) & 0xFF);  

    EEPROM.commit(); 
}

std::vector<directions> PuzzleMemory::loadPuzzle(uint16_t &delayMsOut)
{
    EEPROM.begin(64); 

    uint8_t length = EEPROM.read(EEPROM_ADDR_PUZZLE);
    std::vector<directions> puzzle;

    for (uint8_t i = 0; i < length && i < MAX_PUZZLE_LENGTH; ++i)
    {
        directions dir = static_cast<directions>(EEPROM.read(EEPROM_ADDR_PUZZLE + 1 + i));
        puzzle.push_back(dir);
    }

    uint8_t low = EEPROM.read(EEPROM_ADDR_PUZZLE + 1 + MAX_PUZZLE_LENGTH);
    uint8_t high = EEPROM.read(EEPROM_ADDR_PUZZLE + 2 + MAX_PUZZLE_LENGTH);
    delayMsOut = (static_cast<uint16_t>(high) << 8) | low;

    return puzzle;
}
