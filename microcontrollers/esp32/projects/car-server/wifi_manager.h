#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>

#include "oled_display.h"

enum WiFiMode { AP_MODE, STA_MODE };

extern WiFiMode wifi_state;

void initWiFi();
void startAPMode();
void startSTAMode();

#endif