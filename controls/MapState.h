#pragma once
#include "InputState.h"

class MapState : public InputState {
public:
    void handle(Controls* controls, char input) override;
};
