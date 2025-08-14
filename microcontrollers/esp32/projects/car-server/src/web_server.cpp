#include "web_server.h"

#include <LittleFS.h>

#include "oled_display.h"
// #include "web_files.h"

const uint8_t JOY_X_PIN = 34;
const uint8_t JOY_Y_PIN = 35;
const uint8_t JOY_SW_PIN = 27;

AsyncWebServer server(80);

void setupWebServer() {
  if (!LittleFS.begin(true)) {
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  // Remember to do "Upload Filesystem Image" from pio menu for new pages
  // setDefaultFile necessary
  server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

  // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
  //   request->send_P(200, "text/html", INDEX_HTML);
  // });

  // server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
  //   request->send_P(200, "text/css", STYLE_CSS);
  // });

  // server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
  //   request->send_P(200, "text/javascript", SCRIPT_JS);
  // });

  server.on("/joystick", HTTP_GET, [](AsyncWebServerRequest *request) {
    int xValue = analogRead(JOY_X_PIN);
    int yValue = analogRead(JOY_Y_PIN);
    bool switchState = !digitalRead(JOY_SW_PIN);
    String json = "{\"x\":" + String(xValue) + ",\"y\":" + String(yValue) +
                  ",\"sw\":\"" + (switchState ? "ON" : "OFF") + "\"}";
    request->send(200, "application/json", json);
  });

  server.begin();
}