#ifndef WEATHER_APP_H
#define WEATHER_APP_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>


namespace WeatherApp {
    void init(LiquidCrystal_I2C &lcd);
    void run(char key, LiquidCrystal_I2C &lcd);
}

#endif