#include "MenuManager.h"

void MenuManager::setup()
{
    lcd.init();
    lcd.backlight();
    lcd.setCursor(3, 0);
    lcd.print("ADA-OS");
    delay(1000);
    lcd.clear();
    lcd.print("Main Menu:");
}

void MenuManager::loop()
{
    char key = keypad.getKey();

    if (key)
    {
        lcd.setCursor(0, 1);
        lcd.print("Action: ");
        lcd.print(key);
    }
}