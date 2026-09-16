#pragma once

#include "../core/InputManager.h"

class DisplayManager;

class App {
public:
    virtual ~App() = default;
    virtual void begin() = 0;
    virtual void update() = 0;
    virtual void render(DisplayManager& display) = 0;
    virtual void onButton(Button button) = 0;
};
