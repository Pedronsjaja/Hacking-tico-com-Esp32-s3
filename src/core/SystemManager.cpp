#include "SystemManager.h"

void SystemManager::begin() {
    loadSettings();
    if (currentSettings.wifiEnabled) {
        WiFi.mode(WIFI_STA);
    }
    Serial.printf("[BOOT] PSRAM: %u bytes\n", ESP.getPsramSize());
    printMemory("[BOOT]");
}

void SystemManager::loadSettings() {
    preferences.begin("esp-tool", false);
    currentSettings.wifiEnabled = preferences.getBool("wifi", true);
    currentSettings.bleEnabled = preferences.getBool("ble", true);
    currentSettings.screenSaverMs = preferences.getULong("saver", 120000);
    currentSettings.brightness = preferences.getUChar("bright", 255);
}

void SystemManager::saveSettings() {
    preferences.putBool("wifi", currentSettings.wifiEnabled);
    preferences.putBool("ble", currentSettings.bleEnabled);
    preferences.putULong("saver", currentSettings.screenSaverMs);
    preferences.putUChar("bright", currentSettings.brightness);
}

const char* SystemManager::signalQuality() const {
    if (WiFi.status() != WL_CONNECTED) return "Offline";
    const int32_t rssi = WiFi.RSSI();
    if (rssi >= -55) return "Excelente";
    if (rssi >= -67) return "Bom";
    if (rssi >= -75) return "Medio";
    return "Fraco";
}

void SystemManager::printMemory(const char* prefix) const {
    Serial.printf("%s Heap livre: %u | PSRAM livre: %u\n", prefix, ESP.getFreeHeap(), ESP.getFreePsram());
}
