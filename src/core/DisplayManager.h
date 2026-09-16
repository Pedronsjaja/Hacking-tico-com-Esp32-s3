#pragma once

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "../config.h"

class DisplayManager {
public:
    bool begin();
    void clear();
    void commit();
    void splash();
    void header(const char* title, bool wifi, bool ble);
    void text(const char* value, int16_t x, int16_t y, uint8_t size = 1);
    void line(const char* value, int16_t y, bool selected = false);
    Adafruit_SSD1306& canvas() { return display; }

private:
    Adafruit_SSD1306 display{DisplayConfig::WIDTH, DisplayConfig::HEIGHT, &Wire, -1};
};
