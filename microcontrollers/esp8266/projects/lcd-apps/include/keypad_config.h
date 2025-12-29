#ifndef KEYPAD_CONFIG_H
#define KEYPAD_CONFIG_H

#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

const char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

const byte rowPins[ROWS] = {D0, D5, D6, D7}; 
const byte colPins[COLS] = {3, 1, D3, D4}; 

extern Keypad keypad;
#endif