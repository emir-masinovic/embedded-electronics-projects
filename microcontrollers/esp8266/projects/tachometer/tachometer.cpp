// clang-format off
#include "tachometer.h"
#include <Wire.h>
#include "oled_display.h"
// clang-format on

// Pins
const uint8_t HALL_SENSOR_PIN = 14;  // 8266 D5
const uint8_t FLASH_BUTTON_PIN = 0;

// Tachometer data
const uint8_t MAGNETS_PER_REVOLUTION = 2;
const unsigned long SD_UPDATE_MS = 1000;
const unsigned long DEBOUNCE_TIME_MS = 7;  // Very sensetive to calibrate
const unsigned long RPM_TIMEOUT_MS = 2000;
volatile unsigned long pulseCount = 0;
volatile unsigned long lastPulseMS = 0;
volatile float rpm = 0.0;
unsigned short roundedRPM = 0;

// Gauge or Digital style
bool displayModeIsGauge = true;

void setupTachometer() {
  setupOLED();
  pinMode(HALL_SENSOR_PIN, INPUT);
  pinMode(FLASH_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(HALL_SENSOR_PIN), detectPulse, RISING);
}

void loopTachometer() {
  handleDisplayMode();
  processRPMData();
  updateSerialDisplay();
  loopOLED(displayModeIsGauge, roundedRPM, MAGNETS_PER_REVOLUTION);
}

void handleDisplayMode() {
  // Pressed = LOW ; Not pressed = HIGH
  bool isFlashPressed = digitalRead(FLASH_BUTTON_PIN);
  static bool lastFlashState = HIGH;

  // Pressed and activated only once
  if (isFlashPressed == LOW && lastFlashState == HIGH) {
    displayModeIsGauge = !displayModeIsGauge;
  }
  lastFlashState = isFlashPressed;
}

void processRPMData() {
  // Create local copies isolated form interrupts
  noInterrupts();
  static float smoothedRPM = 0.0;
  float copyOfRPM = rpm;
  unsigned long copyOfLastPulseMS = lastPulseMS;
  interrupts();

  // clang-format off
  if (millis() - copyOfLastPulseMS > RPM_TIMEOUT_MS) { copyOfRPM = 0.0; }
  // clang-format on

  // Exponential Moving Average (EMA) filter
  smoothedRPM = (smoothedRPM * 0.9) + (copyOfRPM * 0.1);
  // Round the smoothed value to the nearest 10 for easier display
  roundedRPM = static_cast<unsigned short>(round(smoothedRPM / 10.0) * 10.0);
}

void updateSerialDisplay() {
  static unsigned long lastPrintTimeMS = 0;
  if (millis() - lastPrintTimeMS > SD_UPDATE_MS) {
    Serial.printf("RPM: %d\n", roundedRPM);
    lastPrintTimeMS = millis();
  }
}

void IRAM_ATTR detectPulse() {
  unsigned long currentTimeMS = millis();
  unsigned long timeDifference = currentTimeMS - lastPulseMS;

  // clang-format off
  if (timeDifference < DEBOUNCE_TIME_MS) { return; }
  // clang-format on

  if (lastPulseMS != 0 && timeDifference > 0) {
    rpm = (60000.0 / timeDifference) / MAGNETS_PER_REVOLUTION;
  }

  lastPulseMS = currentTimeMS;
  pulseCount++;
}