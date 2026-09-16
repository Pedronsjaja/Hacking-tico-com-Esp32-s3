#include "WifiInfoApp.h"
#include "../core/AppManager.h"
#include "../core/DisplayManager.h"

void WifiInfoApp::render(DisplayManager& display) {
    display.header("WiFi Info", system.wifiEnabled(), system.bleEnabled());
    display.text((String("MAC ") + WiFi.macAddress()).c_str(), 2, 15);
    display.text((String("Mode ") + (WiFi.getMode() == WIFI_MODE_STA ? "STA" : "Other")).c_str(), 2, 25);
    display.text((String("IP ") + WiFi.localIP().toString()).c_str(), 2, 35);
    display.text((String("RSSI ") + WiFi.RSSI()).c_str(), 2, 45);
    display.text(page == 0 ? "RIGHT: more" : (String("CH ") + WiFi.channel()).c_str(), 2, 55);
    if (page == 1) {
        display.text((String("GW ") + WiFi.gatewayIP().toString()).c_str(), 2, 55);
        display.text((String("DNS ") + WiFi.dnsIP().toString()).c_str(), 2, 15);
        display.text((String("Host ") + WiFi.getHostname()).c_str(), 2, 25);
        display.text(system.signalQuality(), 2, 35);
    }
}

void WifiInfoApp::onButton(Button button) {
    if (button == Button::LEFT) manager.home();
    if (button == Button::RIGHT) page = page == 0 ? 1 : 0;
}
