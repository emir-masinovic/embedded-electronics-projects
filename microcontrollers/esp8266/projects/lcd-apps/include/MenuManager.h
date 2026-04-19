#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

namespace MenuManager
{
    void init();
    void run();

    typedef void (*AppInitFn)(LiquidCrystal_I2C &);
    typedef void (*AppRunFn)(char, LiquidCrystal_I2C &);
    const char *getSSID();
    const char *getWifiPass();
    void setSSID(const char *newSsid);
    void setWifiPass(const char *newPass);
}
#endif