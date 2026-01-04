#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <Arduino.h>

namespace MenuManager
{
    void init();
    void run();

    const char *getSSID();
    const char *getWifiPass();

    void setSSID(const char *s);
    void setWifiPass(const char *s);
}

#endif