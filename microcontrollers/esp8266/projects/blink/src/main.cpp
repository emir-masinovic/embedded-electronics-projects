#include <Arduino.h>

#define LED_PIN 5 // D1 ESP8266
// D1 (ESP) > Anode (+)(Longer leg) > Cathode (-) > 220 Ohm > Ground (ESP)

int rhythm[] = {150, 150, 150, 150, 400, 300}; 
int rhythmSize = sizeof(rhythm) / sizeof(rhythm[0]);

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {

  for (int i = 0; i < rhythmSize; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(rhythm[i]);
    
    digitalWrite(LED_PIN, LOW);
    delay(100); 
  }
  
  // Looks like a reset interval even though it's a gap
  delay(400); 
}