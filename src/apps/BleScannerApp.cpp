#include "BleScannerApp.h"
#include "../core/AppManager.h"
#include "../core/DisplayManager.h"
#include <BLEDevice.h>
#include <BLEScan.h>

void BleScannerApp::begin() {
    selected = 0;
    scanning = false;
    hasResults = false;
    if (!system.bleEnabled()) return;
    BLEDevice::init("");
    scan = BLEDevice::getScan();
    scan->setActiveScan(false);
    scan->setInterval(100);
    scan->setWindow(80);
    scan->start(0, false);
    scanning = true;
    scanStartedAt = millis();
    Serial.println("[BLE] Scan started");
}

void BleScannerApp::update() {
    if (!scanning || scan == nullptr) return;
    if (millis() - scanStartedAt >= Timing::BLE_SCAN_MS) {
        scan->stop();
        results = scan->getResults();
        hasResults = true;
        scanning = false;
        Serial.printf("[BLE] Found %d devices\n", results.getCount());
    }
}

void BleScannerApp::render(DisplayManager& display) {
    display.header("BLE Scanner", system.wifiEnabled(), system.bleEnabled());
    if (!system.bleEnabled()) { display.text("BLE disabled", 2, 24); return; }
    if (scanning) { display.text("Scanning...", 2, 24); return; }
    if (!hasResults || results.getCount() == 0) { display.text("No devices", 2, 24); display.text("RIGHT: Rescan", 2, 43); return; }
    const int16_t count = results.getCount();
    selected = min<int16_t>(selected, count - 1);
    BLEAdvertisedDevice device = results.getDevice(selected);
    String name = device.haveName() ? device.getName().c_str() : "Unknown";
    display.text(name.c_str(), 2, 17);
    display.text((String(device.getRSSI()) + " dBm").c_str(), 2, 30);
    display.text(device.getAddress().toString().c_str(), 2, 42);
    display.text((String(selected + 1) + "/" + count).c_str(), 48, 55);
}

void BleScannerApp::onButton(Button button) {
    if (button == Button::LEFT) manager.home();
    if (button == Button::UP && hasResults && results.getCount() > 0) selected = selected == 0 ? results.getCount() - 1 : selected - 1;
    if (button == Button::DOWN && hasResults && results.getCount() > 0) selected = (selected + 1) % results.getCount();
    if (button == Button::RIGHT && !scanning) begin();
}
