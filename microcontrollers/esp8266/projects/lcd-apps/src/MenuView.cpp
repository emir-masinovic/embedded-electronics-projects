#include "MenuView.h"
#include <string.h>

namespace MenuView {
    void draw(LiquidCrystal_I2C &lcd, int currentIdx, int total, const char* names[]) {
        lcd.clear();
        
        // Row 1: Logo and Title
        lcd.setCursor(0, 0); lcd.write(currentIdx);
        int titlePos = (16 - strlen(names[currentIdx])) / 2;
        lcd.setCursor(titlePos, 0); lcd.print(names[currentIdx]);
        
        // Row 2: Carousel logic
        int prev = (currentIdx - 1 + total) % total;
        int next = (currentIdx + 1) % total;

        lcd.setCursor(0, 1); lcd.print("<     [ ]     >");
        lcd.setCursor(3, 1); lcd.write(prev);
        lcd.setCursor(7, 1); lcd.write(currentIdx); 
        lcd.setCursor(11, 1); lcd.write(next);
    }
}