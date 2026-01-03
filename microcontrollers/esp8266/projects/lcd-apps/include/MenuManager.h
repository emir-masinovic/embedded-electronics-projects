#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <Arduino.h>

namespace MenuManager
{
    extern char globalSsid[33];
    extern char globalPass[65];

    void init();
    void run();
}

#endif