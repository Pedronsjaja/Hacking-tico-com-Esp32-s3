#include "HomeApp.h"
#include "../core/AppManager.h"
#include "../core/DisplayManager.h"

void HomeApp::render(DisplayManager& display) {
    display.header("ESP TOOL", system.wifiEnabled(), system.bleEnabled());
    static const char* items[] = {"WiFi Scanner", "Bluetooth", "WiFi Info", "System", "Settings"};
    for (uint8_t i = 0; i < itemCount; ++i) display.line(items[i], 15 + i * 9, i == selected);
}

void HomeApp::onButton(Button button) {
    if (button == Button::UP) selected = selected == 0 ? itemCount - 1 : selected - 1;
    if (button == Button::DOWN) selected = (selected + 1) % itemCount;
    if (button == Button::OK) manager.openApp(selected + 1);
}
