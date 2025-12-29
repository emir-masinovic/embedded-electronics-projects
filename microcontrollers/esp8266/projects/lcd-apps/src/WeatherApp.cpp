#include "WeatherApp.h"

namespace WeatherApp {
    unsigned long lastUpdate;
    int temp;

    void init(LiquidCrystal_I2C &lcd){
        lastUpdate = 0;
        temp = 0;
        lcd.setCursor(0,0); lcd.print("Weather App...");
    }
    void run(char key, LiquidCrystal_I2C &lcd) {
        if (millis() - lastUpdate > 2000) {
            lastUpdate = millis();
            lcd.setCursor(0, 1);
            lcd.print("Temp: ");
            lcd.print(temp);
            temp++; 
        }
    }
}