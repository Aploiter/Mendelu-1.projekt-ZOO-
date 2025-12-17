#include "KeyBinding.h"

void KeyBinding::bind(char key, Command* command) {
    bindings[key] = command;
}

Command* KeyBinding::get(char key) {
    if (bindings.count(key))
        return bindings[key];
    return nullptr;
}
