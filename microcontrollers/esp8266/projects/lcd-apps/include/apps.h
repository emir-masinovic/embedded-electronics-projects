#ifndef APPS_H
#define APPS_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "keypad_config.h"

enum SystemState { STATE_MENU, STATE_WEATHER, STATE_DINO, STATE_CONSOLE };
extern SystemState currentState;

void dispatchApp(char key, LiquidCrystal_I2C &lcd);

void runWeatherApp(char key, LiquidCrystal_I2C &lcd);
void runDinoApp(char key, LiquidCrystal_I2C &lcd);
void runConsoleApp(char key, LiquidCrystal_I2C &lcd);

#endif