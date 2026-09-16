#pragma once

#include "App.h"
#include "../core/SystemManager.h"

class AppManager;

class WifiInfoApp : public App {
public:
    WifiInfoApp(AppManager& manager, SystemManager& system) : manager(manager), system(system) {}
    void begin() override { page = 0; }
    void update() override {}
    void render(DisplayManager& display) override;
    void onButton(Button button) override;

private:
    AppManager& manager;
    SystemManager& system;
    uint8_t page = 0;
};
