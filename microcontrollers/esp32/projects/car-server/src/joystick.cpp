#include "joystick.h"

void setupJoystick() {
  pinMode(JOY_SW_PIN, INPUT_PULLUP);
  Serial.println("Setting up the Joystick");
}

JoystickState getJoystickState() {
  JoystickState state;
  state.joyX = analogRead(JOY_X_PIN);
  state.joyY = analogRead(JOY_Y_PIN);
  state.joySW = !digitalRead(JOY_SW_PIN);
  return state;
}
