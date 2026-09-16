#include "InputManager.h"

void InputManager::begin() {
    pinMode(Pins::JOYSTICK_X, INPUT);
    pinMode(Pins::JOYSTICK_Y, INPUT);
    pinMode(Pins::JOYSTICK_OK, INPUT_PULLUP);
    lastOkReading = digitalRead(Pins::JOYSTICK_OK) == LOW;
    stableOkPressed = lastOkReading;
    okChangedAt = millis();
}

Button InputManager::update() {
    const uint32_t now = millis();
    const bool okReading = digitalRead(Pins::JOYSTICK_OK) == LOW;
    if (okReading != lastOkReading) {
        lastOkReading = okReading;
        okChangedAt = now;
    }
    if ((now - okChangedAt) >= Timing::INPUT_DEBOUNCE_MS && okReading != stableOkPressed) {
        stableOkPressed = okReading;
        if (stableOkPressed) return Button::OK;
    }

    const int x = analogRead(Pins::JOYSTICK_X);
    const int y = analogRead(Pins::JOYSTICK_Y);
    Button direction = Button::NONE;
    if (x < Timing::JOYSTICK_CENTER - Timing::JOYSTICK_DEADZONE) direction = Button::LEFT;
    else if (x > Timing::JOYSTICK_CENTER + Timing::JOYSTICK_DEADZONE) direction = Button::RIGHT;
    else if (y < Timing::JOYSTICK_CENTER - Timing::JOYSTICK_DEADZONE) direction = Button::UP;
    else if (y > Timing::JOYSTICK_CENTER + Timing::JOYSTICK_DEADZONE) direction = Button::DOWN;

    if (direction == Button::NONE) {
        lastDirection = Button::NONE;
        return Button::NONE;
    }
    if (direction != lastDirection || now - lastDirectionAt >= Timing::JOYSTICK_REPEAT_MS) {
        lastDirection = direction;
        lastDirectionAt = now;
        return direction;
    }
    return Button::NONE;
}
