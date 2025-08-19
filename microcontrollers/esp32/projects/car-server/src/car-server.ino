#include <Arduino.h>

#include "joystick.h"
#include "oled_display.h"
#include "web_server.h"
#include "wifi_manager.h"

bool last_switch_state = false;

void setup() {
  Serial.begin(115200);
  setupOLED();
  setupJoystick();
  setupWiFi();
  setupWebServer();
}

void loop() {
  JoystickState joystick = getJoystickState();
  WiFiState wifiSettings = getWiFiState();

  if (joystick.joySW && !last_switch_state) {
    changeWiFiMode();
  }
  last_switch_state = joystick.joySW;

  loopOLED(wifiSettings.ip, wifiSettings.mode, joystick.joyX, joystick.joyY,
           joystick.joySW);

  loopWebServer(joystick);
}
