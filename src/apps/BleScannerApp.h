#pragma once

#include "App.h"
#include "../core/SystemManager.h"
#include <BLEScan.h>

class AppManager;

class BleScannerApp : public App {
public:
    BleScannerApp(AppManager& manager, SystemManager& system) : manager(manager), system(system) {}
    void begin() override;
    void update() override;
    void render(DisplayManager& display) override;
    void onButton(Button button) override;

private:
    AppManager& manager;
    SystemManager& system;
    class BLEScan* scan = nullptr;
    BLEScanResults results;
    bool hasResults = false;
    int16_t selected = 0;
    bool scanning = false;
    uint32_t scanStartedAt = 0;
};
