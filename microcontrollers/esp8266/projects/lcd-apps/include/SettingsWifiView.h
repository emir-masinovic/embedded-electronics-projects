#ifndef SETTINGS_WIFI_VIEW_H
#define SETTINGS_WIFI_VIEW_H

#include <LiquidCrystal_I2C.h>
#include "SettingsWifi.h"

namespace SettingsWifiView {
    void draw(LiquidCrystal_I2C &lcd, const SettingsWifi::WifiDisplayData &data);
    void drawMessage(LiquidCrystal_I2C &lcd, const char* line1, const char* line2);
}

#endif