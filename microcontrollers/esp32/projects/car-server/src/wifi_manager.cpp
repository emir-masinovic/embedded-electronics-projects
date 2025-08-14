#include "wifi_manager.h"

const char* sta_ssid = "";
const char* sta_password = "";
const char* ap_ssid = "VanServer";
const char* ap_password = "123";

WiFiMode wifi_state = AP_MODE;

void initWiFi() { startAPMode(); }

void startAPMode() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_ssid, ap_password);
  wifi_state = AP_MODE;
  Serial.println("Switched to AP Mode!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
}

void startSTAMode() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(sta_ssid, sta_password);
  wifi_state = STA_MODE;
  Serial.println("Connecting to WiFi...");

  unsigned long connection_start_time = millis();
  while (WiFi.status() != WL_CONNECTED &&
         millis() - connection_start_time < 20000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to WiFi. Switching back to AP Mode.");
    startAPMode();
  }
}