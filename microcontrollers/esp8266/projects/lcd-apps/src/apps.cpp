#include "apps.h"

SystemState currentState = STATE_MENU;

void dispatchApp(char key, LiquidCrystal_I2C &lcd) {
    switch (currentState) {
        case STATE_WEATHER: runWeatherApp(key, lcd); break;
        case STATE_DINO:    runDinoApp(key, lcd);    break;
        case STATE_CONSOLE: runConsoleApp(key, lcd); break;
        default: break;
    }
}

void runWeatherApp(char key, LiquidCrystal_I2C &lcd) {
    lcd.setCursor(0, 0); lcd.print("Weather App");
    lcd.setCursor(0, 1); lcd.print("D: Exit");
    if (key == 'D') currentState = STATE_MENU;
}

void runDinoApp(char key, LiquidCrystal_I2C &lcd) {
    lcd.setCursor(0, 0); lcd.print("Dino Game");
    lcd.setCursor(0, 1); lcd.print("D: Exit");
    if (key == 'D') currentState = STATE_MENU;
}

void runConsoleApp(char key, LiquidCrystal_I2C &lcd) {
    lcd.setCursor(0, 0); lcd.print("Console Mode");
    lcd.setCursor(0, 1); lcd.print("D: Exit");
    if (key == 'D') currentState = STATE_MENU;
}