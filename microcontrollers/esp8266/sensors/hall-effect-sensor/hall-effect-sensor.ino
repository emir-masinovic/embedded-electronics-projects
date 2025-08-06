// Hall effect sensor:  D0 (3.3V | can distinguish HIGH and LOW)
// ESP8266:             D5
const int hallSensorPin = 14; // D5 -> GPIO14 on ESP8266

void setup() {
  Serial.begin(115200);   // Higher baud communication, but will be blocked by delay()
  Serial.println("");     // ESP spits out some garbage
  Serial.println("Hall Effect Sensor Test");
  Serial.println("---------------------------------");
  pinMode(hallSensorPin, INPUT);
}

void loop() {
  int sensorState = digitalRead(hallSensorPin);
  if (sensorState == HIGH) { Serial.println("Magnet Detected!"); }
  else { Serial.println("No Magnet"); }
  delay(200);   // Blocking but enough for a simple test
}