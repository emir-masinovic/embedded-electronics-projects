#ifndef SETTINGS_WIFI_H
#define SETTINGS_WIFI_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

namespace SettingsWifi {
    struct WifiDisplayData {
        const char* ssid;
        const char* pass;
        int cursorX;
        int activeRow;
        int inputMode;
        int charIdx;
        bool privacyMode;
        int savedIdx;
        int totalActive;
        bool currentProfileActive;
        const char* carouselSsid;
    };

    void init(LiquidCrystal_I2C &lcd);
    void run(char key, LiquidCrystal_I2C &lcd);
}

#endif