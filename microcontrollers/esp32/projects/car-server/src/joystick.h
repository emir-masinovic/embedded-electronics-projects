#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>

const uint8_t JOY_X_PIN = 32;
const uint8_t JOY_Y_PIN = 35;
const uint8_t JOY_SW_PIN = 27;

struct JoystickState {
  int joyX;
  int joyY;
  bool joySW;
};

void setupJoystick();

JoystickState getJoystickState();

#endif
