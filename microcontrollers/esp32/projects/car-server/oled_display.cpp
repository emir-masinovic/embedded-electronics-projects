#include "oled_display.h"

#include <Wire.h>

const uint8_t SCREEN_WIDTH = 128;
const uint8_t SCREEN_HEIGHT = 64;
const int OLED_RESET = -1;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initOLED() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Starting Server...");
  display.display();
}

void updateOLED(const String& ip, const String& mode, int joyX, int joyY,
                bool joySW) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(mode + " Mode Active");
  display.println("IP: " + ip);
  display.println("Joy X: " + String(joyX));
  display.println("Joy Y: " + String(joyY));
  display.println("Switch: " + String(joySW ? "ON" : "OFF"));
  display.display();
}