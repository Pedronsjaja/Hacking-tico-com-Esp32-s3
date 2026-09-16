#include "SystemInfoApp.h"
#include "../core/AppManager.h"
#include "../core/DisplayManager.h"

void SystemInfoApp::render(DisplayManager& display) {
    display.header("System Info", system.wifiEnabled(), system.bleEnabled());
    display.text("ESP32-S3", 2, 15);
    if (page == 0) {
        display.text((String("Flash ") + ESP.getFlashChipSize() / 1048576 + " MB").c_str(), 2, 25);
        display.text((String("PSRAM ") + ESP.getPsramSize() / 1024 + " KB").c_str(), 2, 35);
        display.text((String("Heap ") + ESP.getFreeHeap() / 1024 + " KB").c_str(), 2, 45);
        display.text((String("CPU ") + getCpuFrequencyMhz() + " MHz").c_str(), 2, 55);
    } else {
        display.text((String("Used ") + ESP.getSketchSize() / 1024 + " KB").c_str(), 2, 25);
        display.text((String("PS free ") + ESP.getFreePsram() / 1024 + " KB").c_str(), 2, 35);
        display.text((String("Up ") + millis() / 1000 + " s").c_str(), 2, 45);
        display.text((String("FW ") + FW_VERSION).c_str(), 2, 55);
    }
}

void SystemInfoApp::onButton(Button button) {
    if (button == Button::LEFT) manager.home();
    if (button == Button::RIGHT) page = page == 0 ? 1 : 0;
}
