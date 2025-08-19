#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

extern Adafruit_SSD1306 display;

void setupOLED();
void loopOLED(const String& ip, const String& mode, int joyX, int joyY,
              bool joySW);

#endif