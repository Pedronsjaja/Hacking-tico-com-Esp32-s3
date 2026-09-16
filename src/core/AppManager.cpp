#include "AppManager.h"
#include "../apps/HomeApp.h"
#include "../apps/WifiScannerApp.h"
#include "../apps/BleScannerApp.h"
#include "../apps/WifiInfoApp.h"
#include "../apps/SystemInfoApp.h"
#include "../apps/SettingsApp.h"

void AppManager::begin(DisplayManager& displayRef, InputManager& inputRef, SystemManager& systemRef) {
    display = &displayRef;
    input = &inputRef;
    system = &systemRef;
    apps[0] = new HomeApp(*this, systemRef);
    apps[1] = new WifiScannerApp(*this, systemRef);
    apps[2] = new BleScannerApp(*this, systemRef);
    apps[3] = new WifiInfoApp(*this, systemRef);
    apps[4] = new SystemInfoApp(*this, systemRef);
    apps[5] = new SettingsApp(*this, systemRef);
    appCount = 6;
    activeApp = apps[0];
    for (uint8_t i = 0; i < appCount; ++i) apps[i]->begin();
    display->splash();
    Serial.println("[BOOT] ESP Tool starting");
}

void AppManager::update() {
    if (splashActive) {
        if (millis() >= DisplayConfig::SPLASH_MS) splashActive = false;
        return;
    }
    const Button button = input->update();
    if (button != Button::NONE) activeApp->onButton(button);
    activeApp->update();
    if (millis() - lastRender >= 100) {
        render();
        lastRender = millis();
    }
}

void AppManager::render() {
    display->clear();
    activeApp->render(*display);
    display->commit();
}

void AppManager::openApp(uint8_t index) {
    if (index >= appCount) return;
    activeApp = apps[index];
    activeApp->begin();
    Serial.printf("[UI] Opened app %u\n", index);
}

void AppManager::home() { openApp(0); }
