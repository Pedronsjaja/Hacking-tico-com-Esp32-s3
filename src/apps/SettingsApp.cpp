#include "SettingsApp.h"
#include "../core/AppManager.h"
#include "../core/DisplayManager.h"

void SettingsApp::render(DisplayManager& display) {
    display.header("Settings", system.wifiEnabled(), system.bleEnabled());
    display.line(system.wifiEnabled() ? "WiFi ON" : "WiFi OFF", 15, selected == 0);
    display.line(system.bleEnabled() ? "BLE ON" : "BLE OFF", 25, selected == 1);
    display.line("Saver 2 min", 35, selected == 2);
    display.line("Firmware", 45, selected == 3);
    display.line("Restart", 55, selected == 4);
}

void SettingsApp::onButton(Button button) {
    if (button == Button::LEFT) manager.home();
    if (button == Button::UP) selected = selected == 0 ? 4 : selected - 1;
    if (button == Button::DOWN) selected = (selected + 1) % 5;
    if (button != Button::OK && button != Button::RIGHT) return;
    if (selected == 0) system.settings().wifiEnabled = !system.settings().wifiEnabled;
    if (selected == 1) system.settings().bleEnabled = !system.settings().bleEnabled;
    if (selected == 2) system.settings().screenSaverMs = system.settings().screenSaverMs == 0 ? Timing::SCREEN_SAVER_DEFAULT_MS : 0;
    if (selected == 3) Serial.printf("[BOOT] Firmware %s\n", FW_VERSION);
    if (selected == 4) system.restart();
    system.saveSettings();
}
