#pragma once

class Controls;

class InputState {
public:
    virtual void handle(Controls* controls, char input) = 0;
    virtual ~InputState() = default;
};
