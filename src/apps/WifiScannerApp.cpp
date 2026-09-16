#include "WifiScannerApp.h"
#include "../core/AppManager.h"
#include "../core/DisplayManager.h"
#include <WiFi.h>

void WifiScannerApp::begin() {
    selected = 0;
    networkCount = 0;
    scanning = false;
    if (!system.wifiEnabled()) return;
    WiFi.scanDelete();
    WiFi.scanNetworks(true, true);
    scanning = true;
    scanStartedAt = millis();
    Serial.println("[WIFI] Scan started");
}

void WifiScannerApp::update() {
    if (!scanning) return;
    const int16_t result = WiFi.scanComplete();
    if (result >= 0) {
        networkCount = result;
        scanning = false;
        Serial.printf("[WIFI] Found %d networks\n", networkCount);
    } else if (result == WIFI_SCAN_FAILED || millis() - scanStartedAt > 15000) {
        scanning = false;
        networkCount = 0;
        Serial.println("[ERROR] WiFi scan failed");
    }
}

void WifiScannerApp::render(DisplayManager& display) {
    display.header("WiFi Scanner", system.wifiEnabled(), system.bleEnabled());
    if (!system.wifiEnabled()) { display.text("WiFi disabled", 2, 22); display.text("RIGHT: Settings", 2, 42); return; }
    if (scanning) { display.text("Scanning...", 2, 24); display.text("Please wait", 2, 40); return; }
    if (networkCount == 0) { display.text("No networks", 2, 22); display.text("RIGHT: Rescan", 2, 42); return; }
    const int16_t index = min<int16_t>(selected, networkCount - 1);
    display.text(String(networkCount).c_str(), 105, 0);
    display.text(WiFi.SSID(index).c_str(), 2, 17);
    display.text((String(WiFi.RSSI(index)) + " dBm").c_str(), 2, 29);
    display.text((String("CH ") + WiFi.channel(index)).c_str(), 2, 41);
    display.text(WiFi.encryptionType(index) == WIFI_AUTH_OPEN ? "OPEN" : "SECURED", 68, 41);
    display.text((String(selected + 1) + "/" + networkCount).c_str(), 48, 55);
}

void WifiScannerApp::onButton(Button button) {
    if (button == Button::LEFT) manager.home();
    if (button == Button::UP && networkCount > 0) selected = selected == 0 ? networkCount - 1 : selected - 1;
    if (button == Button::DOWN && networkCount > 0) selected = (selected + 1) % networkCount;
    if (button == Button::RIGHT && !scanning) begin();
}
