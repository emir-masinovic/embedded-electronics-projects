#ifndef CONFIG_KEYPAD_H
#define CONFIG_KEYPAD_H

#include <Arduino.h>
#include <Keypad.h>

#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

const byte ROWS = 4;
const byte COLS = 4;

static char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

// Static for multi use by files
// D3, D4, D8 boot - boot pins on 8266, avoid
static byte rowPins[ROWS] = {D0, D5, D6, D7};
static byte colPins[COLS] = {D3, D4, 3, 1};

#endif