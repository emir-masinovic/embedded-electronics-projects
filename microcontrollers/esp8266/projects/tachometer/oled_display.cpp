#include "oled_display.h"

#include <Arduino.h>

const uint8_t SCREEN_WIDTH = 128;
const uint8_t SCREEN_HEIGHT = 64;
const uint8_t CENTER_X = 64;
const int OLED_RESET = -1;
const unsigned long LOGO_DELAY_MS = 2000;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setupOLED() {
  Wire.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  display.clearDisplay();
  display.setTextColor(WHITE);
  delay(LOGO_DELAY_MS);  // To see the lovely Adafruit logo
  display.setTextSize(2);
  displayCenterText("Tachometer", SCREEN_HEIGHT / 2 - 10);
  display.setTextSize(1);
  displayCenterText("v1.0", SCREEN_HEIGHT / 2 + 10);
  display.display();
  delay(LOGO_DELAY_MS);
}

void displayCenterText(String textToBeAligned, int alignmentHeight) {
  int16_t x1, y1;
  uint16_t w, h;

  display.getTextBounds(textToBeAligned, 0, 0, &x1, &y1, &w, &h);
  display.setCursor(CENTER_X - w / 2, alignmentHeight);
  display.print(textToBeAligned);
}

void loopOLED(bool displayModeIsGauge, unsigned short roundedRPM,
              unsigned int magnets) {
  display.clearDisplay();
  display.setTextColor(WHITE);

  String stringRoundedRPM = String(roundedRPM);
  String stringRPM = "RPM";
  String screenMagnets = "Magnets:" + String(magnets);

  if (displayModeIsGauge) {
    unsigned short maxRpm = 4000;
    int padding = 30;
    int gaugeRadius = SCREEN_WIDTH / 2 - padding;
    int gaugeCenterY = SCREEN_HEIGHT;

    // clang-format off
    display.drawCircle(CENTER_X, gaugeCenterY - padding, gaugeRadius, WHITE);
    display.drawCircle(CENTER_X, gaugeCenterY - padding, gaugeRadius - 1, WHITE);
    display.drawCircle(CENTER_X, gaugeCenterY - padding, gaugeRadius - 2, WHITE);
    

    for (float angle = 210; angle >= -30; angle -= 30) {
      float tickRadians = angle * PI / 180.0;

      int startX = CENTER_X + (gaugeRadius - 8) * cos(tickRadians);
      int startY = (gaugeCenterY - padding) - (gaugeRadius - 8) * sin(tickRadians);

      int endX = CENTER_X + gaugeRadius * cos(tickRadians);
      int endY = (gaugeCenterY - padding) - gaugeRadius * sin(tickRadians);

      display.drawLine(startX, startY, endX, endY, WHITE);
    }

    // clang-format on

    // int clippingLineY = SCREEN_HEIGHT - 10;
    // display.fillRect(0, clippingLineY, SCREEN_WIDTH, SCREEN_HEIGHT -
    // clippingLineY, BLACK); // Bottom gauge clipping
    display.fillTriangle(CENTER_X, SCREEN_HEIGHT / 2,
                         gaugeCenterY - gaugeRadius - 10, SCREEN_HEIGHT,
                         gaugeCenterY + gaugeRadius + 10, SCREEN_HEIGHT, BLACK);

    display.setTextSize(1);
    display.setCursor(gaugeCenterY - gaugeRadius + 8, SCREEN_HEIGHT - 10);
    display.print("0");
    display.setCursor(gaugeCenterY + gaugeRadius - 16, SCREEN_HEIGHT - 10);
    display.print("4K");

    float angle =
        map(min(roundedRPM, maxRpm), 0, maxRpm, 180 + padding, -padding);

    float radians = angle * PI / 180.0;

    int handOriginY = SCREEN_HEIGHT - padding;
    int handX = CENTER_X + gaugeRadius * cos(radians);
    int handY = handOriginY - gaugeRadius * sin(radians);

    display.drawLine(CENTER_X, handOriginY, handX, handY, WHITE);
    display.fillCircle(CENTER_X, handOriginY, 3, WHITE);

    displayCenterText(stringRoundedRPM, SCREEN_HEIGHT - 16);

    // Box to make RPM value stand out
    int boxWidth = 26;
    int boxHeight = 12;
    int boxX = CENTER_X - (boxWidth / 2);
    int boxY = SCREEN_HEIGHT - 18;
    display.fillRect(boxX, boxY, boxWidth, boxHeight, INVERSE);
  } else  // Digital style
  {
    // Outline for positioning
    // display.drawRect(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, WHITE);
    display.setTextSize(4);
    displayCenterText(stringRoundedRPM, 5);
    display.setTextSize(1);
    displayCenterText(stringRPM, SCREEN_HEIGHT - 20);
    displayCenterText(screenMagnets, SCREEN_HEIGHT - 10);
  }

  display.display();
}
