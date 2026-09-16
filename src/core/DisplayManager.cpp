#include "DisplayManager.h"

bool DisplayManager::begin() {
    Wire.begin(Pins::OLED_SDA, Pins::OLED_SCL);
    if (!display.begin(SSD1306_SWITCHCAPVCC, DisplayConfig::I2C_ADDRESS)) {
        return false;
    }
    display.setTextColor(SSD1306_WHITE);
    display.setTextWrap(false);
    clear();
    commit();
    return true;
}

void DisplayManager::clear() { display.clearDisplay(); }
void DisplayManager::commit() { display.display(); }

void DisplayManager::splash() {
    clear();
    display.setTextSize(2);
    display.setCursor(17, 8);
    display.print("ESP TOOL");
    display.setTextSize(1);
    display.setCursor(35, 34);
    display.print("ESP32-S3");
    display.setCursor(43, 49);
    display.print("FW ");
    display.print(FW_VERSION);
    commit();
}

void DisplayManager::header(const char* title, bool wifi, bool ble) {
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print(title);
    display.setCursor(91, 0);
    display.print(wifi ? "W" : "-");
    display.print(ble ? "B" : "-");
    display.print(" M OK");
    display.drawLine(0, 10, 127, 10, SSD1306_WHITE);
}

void DisplayManager::text(const char* value, int16_t x, int16_t y, uint8_t size) {
    display.setTextSize(size);
    display.setCursor(x, y);
    display.print(value);
}

void DisplayManager::line(const char* value, int16_t y, bool selected) {
    if (selected) {
        display.fillRect(0, y - 1, 128, 10, SSD1306_WHITE);
        display.setTextColor(SSD1306_BLACK);
    }
    display.setTextSize(1);
    display.setCursor(2, y);
    display.print(selected ? "> " : "  ");
    display.print(value);
    display.setTextColor(SSD1306_WHITE);
}
