#include "state_directions.hpp"

void compass_state::setAllHigh()
{
    digitalWrite(northPin_, HIGH);
    digitalWrite(eastPin_, HIGH);
    digitalWrite(southPin_, HIGH);
    digitalWrite(westPin_, HIGH);
}
void compass_state::setAllLow()
{
    digitalWrite(northPin_, LOW);
    digitalWrite(eastPin_, LOW);
    digitalWrite(southPin_, LOW);
    digitalWrite(westPin_, LOW);
}

extern state_north north;
extern state_east east;
extern state_south south;
extern state_west west;
extern state_on all;
extern state_off off;

compass_state *directionToState(directions dir)
{
    if (dir == directions::North || dir == directions::North_East || dir == directions::North_West)
    {
        return &north;
    }
    if (dir == directions::East)
        return &east;
    if (dir == directions::South || dir == directions::South_East || dir == directions::South_West)
        return &south;
    if (dir == directions::West)
        return &west;
    if (dir == directions::All)
        return &all;
    return &off;
}

void compass_state::playPuzzle(const std::vector<directions> &steps, int puzzleDelay)
{
    for (directions dir : steps)
    {
        compass_state *nextState = directionToState(dir);
        context_->transitionTo(nextState);
        context_->handleDirection(dir);
        delay(puzzleDelay);
    }
}

void compass_state::pulseDirection(compass_state *state, directions dir, int pulseCount, int pulseTimeout)
{
    context_->transitionTo(state);
    for (int i = 0; i < pulseCount; i++)
    {
        context_->handleDirection(dir);
        delay(pulseTimeout / 2);
        setAllHigh();
        delay(pulseTimeout / 2);
    }
}

void state_north::handleDirection(directions dir)
{
    setAllHigh();

    if (dir == directions::North || dir == directions::North_East || dir == directions::North_West)
    {
        digitalWrite(northPin_, LOW);

        if (dir == directions::North_East)
            digitalWrite(eastPin_, LOW);
        if (dir == directions::North_West)
            digitalWrite(westPin_, LOW);
    }
}

void state_east::handleDirection(directions dir)
{
    setAllHigh();

    if (dir == directions::East || dir == directions::North_East || dir == directions::South_East)
    {
        digitalWrite(eastPin_, LOW);
        if (dir == directions::North_East)
            digitalWrite(northPin_, LOW);
        if (dir == directions::South_East)
            digitalWrite(southPin_, LOW);
    }
}

void state_south::handleDirection(directions dir)
{
    setAllHigh();

    if (dir == directions::South || dir == directions::South_East || dir == directions::South_West)
    {
        digitalWrite(southPin_, LOW);
        if (dir == directions::South_East)
            digitalWrite(eastPin_, LOW);
        if (dir == directions::South_West)
            digitalWrite(westPin_, LOW);
    }
}

void state_west::handleDirection(directions dir)
{
    setAllHigh();

    if (dir == directions::West || dir == directions::North_West || dir == directions::South_West)
    {
        digitalWrite(westPin_, LOW);
        if (dir == directions::South_West)
            digitalWrite(southPin_, LOW);
        if (dir == directions::North_West)
            digitalWrite(northPin_, LOW);
    }
}
void state_off::handleDirection(directions dir)
{
    if (dir == directions::Off)
        setAllHigh();
}
void state_on::handleDirection(directions dir)
{
    if (dir == directions::All)
        setAllLow();
}
