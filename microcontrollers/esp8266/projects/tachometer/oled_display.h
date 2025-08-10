// clang-format off
#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ESP8266 D1 -> OLED SCL (Serial Clock)
// ESP8266 D2 -> OLED SDA (Serial Data)
// ESP8266 5V or 3.3V

extern Adafruit_SSD1306 display;

void setupOLED();
void loopOLED(bool displayModeIsGauge, unsigned short roundedRPM,unsigned int magnets);
void displayCenterText(String textToBeAligned, int alignmentHeight);

#endif
