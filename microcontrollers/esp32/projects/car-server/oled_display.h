#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;

void initOLED();
void updateOLED(const String& ip, const String& mode, int joyX, int joyY,
                bool joySW);

#endif