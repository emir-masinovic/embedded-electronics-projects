#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "bitmaps.h"

const uint8_t SCREEN_WIDTH = 128;
const uint8_t SCREEN_HEIGHT = 64;
const int8_t OLED_RESET = -1;

const unsigned long DISPLAY_TIME_MS = 5000;

Adafruit_SSD1306 screenOLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

uint8_t imageIndex = 0;
unsigned long lastImageTime = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  if (!screenOLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED SSD1306 allocation failed"));
    for (;;);
  }
  lastImageTime = millis();
  screenOLED.display();
  delay(2000);  // To see the lovely Adafruit logo
  screenOLED.clearDisplay();
}

void loop() {
  if (millis() - lastImageTime >= DISPLAY_TIME_MS) {
    screenOLED.clearDisplay();

    if (imageIndex >= TOTAL_BITMAPS) {
      imageIndex = 0;
    }

    screenOLED.drawBitmap(0, 0, (const uint8_t*)allBitmaps[imageIndex],
                          SCREEN_WIDTH, SCREEN_HEIGHT, 1);
    screenOLED.display();

    imageIndex++;
    lastImageTime = millis();
  }
}