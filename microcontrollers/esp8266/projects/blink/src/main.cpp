#include <Arduino.h>

const int redPins[] = {D1, D2, D3};
const int redDrain = D4;
const int bluePins[] = {D5, D6, D7};
const int blueDrain = D8;

void setup() {

  // Bind inputs (power feed to the breadboard)
  for (int i = 0; i < 3; i++) {
    pinMode(redPins[i], OUTPUT);
    pinMode(bluePins[i], OUTPUT);
  }

  // Bind drain (ground replacements to the ESP)
  pinMode(redDrain, OUTPUT);
  pinMode(blueDrain, OUTPUT);

  digitalWrite(redDrain, LOW); 
  digitalWrite(blueDrain, LOW);
}

void runIndividualTest(int speed) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(redPins[i], HIGH);
    digitalWrite(bluePins[i], HIGH);
    delay(speed);
    digitalWrite(redPins[i], LOW);
    digitalWrite(bluePins[i], LOW);
  }
}

void displayBinary(const int pins[], int number) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(pins[i], (number >> i) & 1 ? HIGH : LOW);
  }
}

void runBinaryCounter(int speed) {
  for (int count = 0; count <= 7; count++) {
    displayBinary(redPins, count);
    displayBinary(bluePins, count);
    delay(speed);
  }
  displayBinary(redPins, 0);
  displayBinary(bluePins, 0);
}

// Sixteen Tons song
// Red = Bass, Blue = Snap
void sixteenTonsRhythm() {
  
  int bassDuration = 80;
  int snapDuration = 80;
  int beatGap = 300;    
  int measureGap = 300;
  
  // Bass (Red LED 1)
  digitalWrite(redPins[0], HIGH); 
  delay(bassDuration); 
  digitalWrite(redPins[0], LOW);
  
  delay(beatGap);

  // Snap (All blue LEDs flash)
  displayBinary(bluePins, 7); 
  delay(snapDuration); 
  displayBinary(bluePins, 0);
  
  delay(measureGap);

  // Bass (Red LED 2)
  digitalWrite(redPins[1], HIGH); 
  delay(bassDuration); 
  digitalWrite(redPins[1], LOW);
  
  delay(beatGap);

  // Snap (All blue LEDs flash)
  displayBinary(bluePins, 7); 
  delay(snapDuration); 
  displayBinary(bluePins, 0);
  
  delay(measureGap);
}

void loop() {
  // runIndividualTest(500);
  // runBinaryCounter(800);
  sixteenTonsRhythm(); 
}