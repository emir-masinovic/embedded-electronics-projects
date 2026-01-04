#include "MenuView.h"
#include <string.h>

namespace MenuView
{
    void draw(LiquidCrystal_I2C &lcd, int currentIdx, int total, const char *appName)
    {
        lcd.clear();
        int titleCenter = (16 - strlen(appName)) / 2;

        // clang-format off
        
        // Row 1: Logo and Title
        lcd.setCursor(0, 0); lcd.write(currentIdx);
        lcd.setCursor(titleCenter, 0); lcd.print(appName);
        
        // Row 2: Carousel logic
        int prev = (currentIdx - 1 + total) % total;
        int next = (currentIdx + 1) % total;

        lcd.setCursor(0, 1); lcd.print("<     [ ]     >");
        lcd.setCursor(3, 1); lcd.write(prev);
        lcd.setCursor(7, 1); lcd.write(currentIdx); 
        lcd.setCursor(11, 1); lcd.write(next);
        // clang-format on
    }
}