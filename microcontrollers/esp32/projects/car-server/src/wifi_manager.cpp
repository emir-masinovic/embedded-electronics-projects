#include "wifi_manager.h"

#include <WiFi.h>

const char* sta_ssid = "";
const char* sta_password = "";
const char* ap_ssid = "VanServer";
const char* ap_password = "123456789";

WiFiMode wifi_state = AP_MODE;

void setupWiFi() {
  Serial.println("Setting up the WiFi Manager");
  startAPMode();
}

void changeWiFiMode() {
  if (wifi_state == AP_MODE) {
    startSTAMode();
  } else {
    startAPMode();
  }
}

void startAPMode() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_ssid, ap_password);
  wifi_state = AP_MODE;
  Serial.println("Starting AP Mode");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
}

void startSTAMode() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(sta_ssid, sta_password);
  wifi_state = STA_MODE;
  Serial.println("Starting STA Mode");
  Serial.println("Connecting to WiFi...");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP().toString());
}

WiFiState getWiFiState() {
  WiFiState state;
  if (wifi_state == AP_MODE) {
    state.ip = WiFi.softAPIP().toString();
    state.mode = "AP";
  } else {
    state.ip = WiFi.localIP().toString();
    state.mode = "STA";
  }
  return state;
}
