#pragma once
#include <map>
#include "Command.h"

class KeyBinding {
private:
    std::map<char, Command*> bindings;

public:
    void bind(char key, Command* command);
    Command* get(char key);
};
