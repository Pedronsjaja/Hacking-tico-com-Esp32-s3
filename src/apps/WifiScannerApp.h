#pragma once

#include "App.h"
#include "../core/SystemManager.h"

class AppManager;

class WifiScannerApp : public App {
public:
    WifiScannerApp(AppManager& manager, SystemManager& system) : manager(manager), system(system) {}
    void begin() override;
    void update() override;
    void render(DisplayManager& display) override;
    void onButton(Button button) override;

private:
    AppManager& manager;
    SystemManager& system;
    int16_t selected = 0;
    int16_t networkCount = 0;
    bool scanning = false;
    uint32_t scanStartedAt = 0;
};
