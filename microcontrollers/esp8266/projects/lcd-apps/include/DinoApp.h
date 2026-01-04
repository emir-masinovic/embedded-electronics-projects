#ifndef DINO_APP_H
#define DINO_APP_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

namespace DinoApp
{
    void init(LiquidCrystal_I2C &lcd);
    void run(char key, LiquidCrystal_I2C &lcd);
}

#endif