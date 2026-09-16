#pragma once

#include "App.h"
#include "../core/SystemManager.h"

class AppManager;

class HomeApp : public App {
public:
    HomeApp(AppManager& manager, SystemManager& system) : manager(manager), system(system) {}
    void begin() override { selected = 0; }
    void update() override {}
    void render(DisplayManager& display) override;
    void onButton(Button button) override;

private:
    AppManager& manager;
    SystemManager& system;
    uint8_t selected = 0;
    static constexpr uint8_t itemCount = 5;
};
