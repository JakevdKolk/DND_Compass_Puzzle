#pragma once
#include <Arduino.h>

enum class vibration_statuses
{
    On,
    Off
};

class vibration_context;

class vibration_state
{

protected:
    vibration_context *context_;
    int vibPin_ = 23;
    void turn_off();
    void turn_on();

public:
    vibration_state() : context_(nullptr)
    {
        pinMode(vibPin_, OUTPUT);
    }

    void set_context(vibration_context *context)
    {
        this->context_ = context;
    }

    virtual void handleState(vibration_statuses statuses) = 0;
};

class vibration_context
{
private:
    vibration_state *state_;

public:
    explicit vibration_context(vibration_state *state) : state_(nullptr)
    {
        this->transitionTo(state);
    }
    ~vibration_context()
    {
        delete state_;
    }

    void transitionTo(vibration_state *state)
    {
        this->state_ = state;
        this->state_->set_context(this);
    }

    void handleState(vibration_statuses statuses) { state_->handleState(statuses); }
};