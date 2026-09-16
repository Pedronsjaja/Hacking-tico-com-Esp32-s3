#pragma once

#include <Arduino.h>
#include "../config.h"

enum class Button { NONE, UP, DOWN, LEFT, RIGHT, OK };

class InputManager {
public:
    void begin();
    Button update();

private:
    bool lastOkReading = false;
    bool stableOkPressed = false;
    uint32_t okChangedAt = 0;
    uint32_t lastDirectionAt = 0;
    Button lastDirection = Button::NONE;
};
