#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../views/Display.h"
#include "../models/Manager.h"

class Controller
{
private:
    Display &view;
    SystemState currentState;

public:
    Controller(Display &v);
    void begin();
    void update();
    void handleSerial();
};

#endif