#ifndef APPS_H
#define APPS_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

enum AppStatus { 
    APP_RUNNING, 
    APP_WIN, 
    APP_RESTART, 
    APP_EXIT 
};

extern AppStatus currentAppStatus;

void dispatchApp(char key, LiquidCrystal_I2C &lcd);

#endif