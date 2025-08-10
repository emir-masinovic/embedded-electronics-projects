// A simple Tachometer built with Hall effect sensor

#include "tachometer.h"

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("ESP8266 starting");
  Serial.println("Tachometer v1.0");
  setupTachometer();
}

void loop() {
  loopTachometer();
}
