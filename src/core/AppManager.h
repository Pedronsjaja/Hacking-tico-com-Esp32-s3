#pragma once

#include "DisplayManager.h"
#include "InputManager.h"
#include "SystemManager.h"
#include "../apps/App.h"

class AppManager {
public:
    void begin(DisplayManager& display, InputManager& input, SystemManager& system);
    void update();
    void render();
    void openApp(uint8_t index);
    void home();

private:
    DisplayManager* display = nullptr;
    InputManager* input = nullptr;
    SystemManager* system = nullptr;
    App* activeApp = nullptr;
    App* apps[6] = {};
    uint8_t appCount = 0;
    uint32_t lastRender = 0;
    bool splashActive = true;
};
