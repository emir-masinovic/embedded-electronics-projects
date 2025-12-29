#ifndef ICONS_H
#define ICONS_H

#include <Arduino.h>

// uint8_t for compatibility with lcd.createChar
const uint8_t icon_dragon[8]  = {0b00111,0b01101,0b00111,0b11111,0b01111,0b00111,0b11011,0b00000};
const uint8_t icon_pokemon[8] = {0b00100,0b01110,0b11111,0b11111,0b11111,0b11111,0b01110,0b00000};
const uint8_t icon_console[8] = {0b00000,0b01110,0b11111,0b10101,0b11111,0b11111,0b01010,0b00000};
const uint8_t icon_weather[8] = {0b00100,0b10101,0b01110,0b11111,0b01110,0b10101,0b00100,0b00000};

#endif