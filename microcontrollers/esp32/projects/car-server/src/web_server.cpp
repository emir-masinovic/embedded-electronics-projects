#include "web_server.h"

#include <LittleFS.h>

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// NOTE: The AsyncTCP library has a message limit
const unsigned long UPDATE_INTERVAL_MS = 200;
unsigned long lastJoystickUpdate = 0;

void setupWebServer() {
  Serial.println("Setting up the Web Server");

  if (!LittleFS.begin(true)) {
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  server.addHandler(&ws);

  server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");
  server.begin();
  Serial.println("Web Server and WebSocket started.");
}

void loopWebServer(JoystickState joystick) {
  if (millis() - lastJoystickUpdate > UPDATE_INTERVAL_MS) {
    String json = "{\"x\":" + String(joystick.joyX) +
                  ",\"y\":" + String(joystick.joyY) + ",\"sw\":\"" +
                  (joystick.joySW ? "ON" : "OFF") + "\"}";
    ws.textAll(json);
    lastJoystickUpdate = millis();
  }
}
