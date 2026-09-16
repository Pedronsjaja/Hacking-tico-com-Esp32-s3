#include "config.h"
#include "core/AppManager.h"

DisplayManager displayManager;
InputManager inputManager;
SystemManager systemManager;
AppManager appManager;

void setup() {
    Serial.begin(115200);
    const uint32_t serialWaitStartedAt = millis();
    while (!Serial && millis() - serialWaitStartedAt < 3000) {
        delay(10);
    }
    delay(250);
    Serial.println("[BOOT] Initializing ESP Tool");
    systemManager.begin();
    inputManager.begin();
    if (!displayManager.begin()) Serial.println("[ERROR] OLED init failed");
    appManager.begin(displayManager, inputManager, systemManager);
}

void loop() {
    appManager.update();
    static uint32_t lastHeartbeat = 0;
    if (millis() - lastHeartbeat >= 5000) {
        Serial.println("[BOOT] Loop alive");
        lastHeartbeat = millis();
    }
    delay(1);
}
