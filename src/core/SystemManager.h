#pragma once

#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>

struct AppSettings {
    bool wifiEnabled = true;
    bool bleEnabled = true;
    uint32_t screenSaverMs = 120000;
    uint8_t brightness = 255;
};

class SystemManager {
public:
    void begin();
    void loadSettings();
    void saveSettings();
    AppSettings& settings() { return currentSettings; }
    bool wifiEnabled() const { return currentSettings.wifiEnabled; }
    bool bleEnabled() const { return currentSettings.bleEnabled; }
    const char* signalQuality() const;
    void printMemory(const char* prefix) const;
    void restart() const { ESP.restart(); }

private:
    Preferences preferences;
    AppSettings currentSettings;
};
