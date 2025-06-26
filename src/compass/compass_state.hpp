#pragma once
#include <Arduino.h>
#include <vector>

enum class directions
{
    North,
    East,
    South,
    West,
    North_East,
    South_East,
    South_West,
    North_West,
    All,
    Off
};

class compass_context;

class compass_state
{

protected:
    int northPin_ = 4;
    int eastPin_ = 5;
    int southPin_ = 16;
    int westPin_ = 17;

public:
    compass_context *context_;
    void setAllHigh();
    void setAllLow();
    bool isPulsing = false;
    int pulseCount = 0;
    int pulseTimeout = 0;
    int currentPulse = 0;
    bool ledOn = false;
    unsigned long lastToggleTime = 0;
    directions dir_;

    compass_state() : context_(nullptr), dir_(directions::Off)
    {
        pinMode(northPin_, OUTPUT);
        pinMode(eastPin_, OUTPUT);
        pinMode(southPin_, OUTPUT);
        pinMode(westPin_, OUTPUT);
    }
    virtual ~compass_state()
    {
    }

    void set_context(compass_context *context)
    {
        this->context_ = context;
    }

    virtual void handleDirection(directions dir) = 0;
    virtual void playPuzzle(const std::vector<directions> &steps, int puzzleDelay);
    virtual void pulseDirection(compass_state *state, directions dir, int pulseCount, int pulseTimeout);
    virtual void updateCompassPulse();
};

class compass_context
{
private:
    compass_state *state_;

public:
    explicit compass_context(compass_state *state) : state_(nullptr)
    {
        this->transitionTo(state);
    }
    ~compass_context()
    {
        delete state_;
    }

    void transitionTo(compass_state *state)
    {
        // if (this->state_ != nullptr)
        //     delete this->state_;
        this->state_ = state;
        this->state_->set_context(this);
    }

    void playPuzzle(const std::vector<directions> &steps, int puzzleDelay) { state_->playPuzzle(steps, puzzleDelay); }
    void handleDirection(directions dir) { state_->handleDirection(dir); }
    void pulseDirection(compass_state *state, directions dir, int pulseCount, int pulseTimeout) { state_->pulseDirection(state, dir, pulseCount, pulseTimeout); };
    void updateCompassPulse() { state_->updateCompassPulse(); };
};
