#pragma once
#include "../compass_state.hpp"

class state_north : public compass_state
{
public:
    void handleDirection(directions dir) override;
};
class state_east : public compass_state
{
public:
    void handleDirection(directions dir) override;
};
class state_south : public compass_state
{
public:
    void handleDirection(directions dir) override;
};
class state_west : public compass_state
{
public:
    void handleDirection(directions dir) override;
};
class state_off : public compass_state
{
    void handleDirection(directions dir) override;
};
class state_on : public compass_state
{
    void handleDirection(directions dir) override;
};