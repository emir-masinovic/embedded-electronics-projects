#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include <LiquidCrystal_I2C.h>

namespace MenuView
{
    void draw(LiquidCrystal_I2C &lcd, int currentIdx, int total, const char *names);
}

#endif