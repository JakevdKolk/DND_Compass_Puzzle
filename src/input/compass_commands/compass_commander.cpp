
#include "compass_commander.hpp"

compassHandleDirectonCommand::compassHandleDirectonCommand(compass_context *context, compass_state *state, directions dir) : context_(context), state_(state), direction_(dir) {}

void compassHandleDirectonCommand::Execute(String args) const
{
    context_->transitionTo(state_);
    context_->handleDirection(direction_);
};

compassPulseDirectonCommand::compassPulseDirectonCommand(compass_context *context, compass_state *state, directions dir) : context_(context), state_(state), direction_(dir) {};

void compassPulseDirectonCommand::Execute(String args) const
{
    context_->transitionTo(state_);

    int pulseCount = 1;
    int pulseTimeout = 200;

    int spaceIndex = args.indexOf(' ');
    if (spaceIndex > 0)
    {
        pulseCount = args.substring(0, spaceIndex).toInt();
        pulseTimeout = args.substring(spaceIndex + 1).toInt();
    }

    context_->pulseDirection(state_, direction_, pulseCount, pulseTimeout);
}

compassPuzzleCommand::compassPuzzleCommand(compass_context *context)
    : context_(context) {}

directions compassPuzzleCommand::parseDirection(const String &token)
{
    if (token == "N")
        return directions::North;
    if (token == "E")
        return directions::East;
    if (token == "S")
        return directions::South;
    if (token == "W")
        return directions::West;
    if (token == "NE")
        return directions::North_East;
    if (token == "NW")
        return directions::North_West;
    if (token == "SE")
        return directions::South_East;
    if (token == "SW")
        return directions::South_West;
    if (token == "ALL")
        return directions::All;
    if (token == "OFF")
        return directions::Off;
    return directions::Off;
}

void compassPuzzleCommand::Execute(String args) const
{
    std::vector<directions> puzzle;
    int delayMs = 300;

    int lastSpace = args.lastIndexOf(' ');
    String possibleDelay = args.substring(lastSpace + 1);

    if (possibleDelay.toInt() > 0)
    {
        delayMs = possibleDelay.toInt();
        args = args.substring(0, lastSpace);
    }

    while (args.length() > 0)
    {
        int spaceIndex = args.indexOf(' ');
        String token = (spaceIndex == -1) ? args : args.substring(0, spaceIndex);
        puzzle.push_back(parseDirection(token));
        if (spaceIndex == -1)
            break;
        args = args.substring(spaceIndex + 1);
    }

    if (puzzle.empty() || puzzle.back() != directions::Off)
    {
        puzzle.push_back(directions::Off);
    }

    context_->playPuzzle(puzzle, delayMs);
}

directions compassSavePuzzleCommand::parseDirection(const String &token)
{
    if (token == "N")
        return directions::North;
    if (token == "E")
        return directions::East;
    if (token == "S")
        return directions::South;
    if (token == "W")
        return directions::West;
    if (token == "NE")
        return directions::North_East;
    if (token == "NW")
        return directions::North_West;
    if (token == "SE")
        return directions::South_East;
    if (token == "SW")
        return directions::South_West;
    if (token == "ALL")
        return directions::All;
    if (token == "OFF")
        return directions::Off;
    return directions::Off;
}

compassSavePuzzleCommand::compassSavePuzzleCommand(compass_context *context)
    : context_(context) {}

void compassSavePuzzleCommand::Execute(String args) const
{
    std::vector<directions> steps;
    int delayMs = 300;

    int lastSpace = args.lastIndexOf(' ');
    String possibleDelay = args.substring(lastSpace + 1);

    if (possibleDelay.toInt() > 0)
    {
        delayMs = possibleDelay.toInt();
        args = args.substring(0, lastSpace);
    }

    while (args.length() > 0)
    {
        int spaceIndex = args.indexOf(' ');
        String token = (spaceIndex == -1) ? args : args.substring(0, spaceIndex);
        steps.push_back(parseDirection(token));
        if (spaceIndex == -1)
            break;
        args = args.substring(spaceIndex + 1);
    }

    if (steps.empty() || steps.back() != directions::Off)
    {
        steps.push_back(directions::Off);
    }

    PuzzleMemory::savePuzzle(steps, delayMs);
    Serial.println("Puzzle saved");
}

compassLoadPuzzleCommand::compassLoadPuzzleCommand(compass_context *context)
    : context_(context) {}

void compassLoadPuzzleCommand::Execute(String args) const
{
    uint16_t delay;
    auto puzzle = PuzzleMemory::loadPuzzle(delay);
    Serial.println("Playing puzzle");
    context_->playPuzzle(puzzle, delay);
}


extern state_north north;
extern state_east east;
extern state_south south;
extern state_west west;
extern state_on all;
extern state_off off;

CompassColorRegistration compassCommandList[] = {
    {"COMPASS_N", &north, directions::North},
    {"COMPASS_E", &east, directions::East},
    {"COMPASS_S", &south, directions::South},
    {"COMPASS_W", &west, directions::West},
    {"COMPASS_NE", &north, directions::North_East},
    {"COMPASS_NW", &north, directions::North_West},
    {"COMPASS_SE", &east, directions::South_East},
    {"COMPASS_SW", &west, directions::South_West},
    {"COMPASS_ALL", &all, directions::All},
};

const int compassCommandListSize = sizeof(compassCommandList) / sizeof(compassCommandList[0]);