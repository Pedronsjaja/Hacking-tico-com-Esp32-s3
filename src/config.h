#pragma once

#include <Arduino.h>

#define FW_VERSION "0.1.0"

namespace Pins {
constexpr uint8_t OLED_SDA = 8;
constexpr uint8_t OLED_SCL = 9;
constexpr uint8_t JOYSTICK_X = 1;
constexpr uint8_t JOYSTICK_Y = 2;
constexpr uint8_t JOYSTICK_OK = 15;
constexpr int8_t RGB_LED = -1;
}

namespace DisplayConfig {
constexpr uint8_t WIDTH = 128;
constexpr uint8_t HEIGHT = 64;
constexpr uint8_t I2C_ADDRESS = 0x3C;
constexpr uint32_t SPLASH_MS = 1000;
}

namespace Timing {
constexpr uint32_t INPUT_DEBOUNCE_MS = 35;
constexpr uint32_t SCREEN_SAVER_DEFAULT_MS = 120000;
constexpr uint32_t WIFI_SCAN_POLL_MS = 250;
constexpr uint32_t BLE_SCAN_MS = 5000;
constexpr uint16_t JOYSTICK_CENTER = 2048;
constexpr uint16_t JOYSTICK_DEADZONE = 700;
constexpr uint32_t JOYSTICK_REPEAT_MS = 180;
}
