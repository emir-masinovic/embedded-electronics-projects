#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>

enum WiFiMode { AP_MODE, STA_MODE };

struct WiFiState {
  String ip;
  String mode;
};

extern WiFiMode wifi_state;

void setupWiFi();
void changeWiFiMode();
void startAPMode();
void startSTAMode();
WiFiState getWiFiState();

#endif
