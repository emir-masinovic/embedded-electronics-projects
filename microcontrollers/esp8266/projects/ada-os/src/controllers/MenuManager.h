#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include "config_keypad.h"
#include "config_lcd.h"

class MenuManager
{
private:
    LiquidCrystal_I2C lcd;
    Keypad keypad;

public:
    MenuManager() : lcd(LCD_ADDR, LCD_COLS, LCD_ROWS),
                    keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS) {}

    void setup();
    void loop();
};

#endif