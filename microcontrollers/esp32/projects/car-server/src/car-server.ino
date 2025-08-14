#include "oled_display.h"
#include "web_server.h"
#include "wifi_manager.h"

const uint8_t JOY_X_PIN = 34;
const uint8_t JOY_Y_PIN = 35;
const uint8_t JOY_SW_PIN = 27;

bool last_switch_state = false;
unsigned long lastDisplayUpdate = 0;

void setup() {
  Serial.begin(115200);
  initOLED();
  pinMode(JOY_SW_PIN, INPUT_PULLUP);
  initWiFi();
  setupWebServer();
}

void loop() {
  bool current_switch_state = !digitalRead(JOY_SW_PIN);
  if (current_switch_state && !last_switch_state) {
    if (wifi_state == AP_MODE) {
      startSTAMode();
    } else {
      startAPMode();
    }
  }
  last_switch_state = current_switch_state;

  lastDisplayUpdate = millis();
  String currentIP = (wifi_state == AP_MODE) ? WiFi.softAPIP().toString()
                                             : WiFi.localIP().toString();
  String currentMode = (wifi_state == AP_MODE) ? "AP" : "STA";
  int joyX = analogRead(JOY_X_PIN);
  int joyY = analogRead(JOY_Y_PIN);
  bool joySW = !digitalRead(JOY_SW_PIN);
  updateOLED(currentIP, currentMode, joyX, joyY, joySW);
}