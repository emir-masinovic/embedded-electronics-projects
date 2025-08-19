#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "joystick.h"

extern AsyncWebServer server;
extern AsyncWebSocket ws;

void setupWebServer();
void loopWebServer(JoystickState joystick);

#endif
