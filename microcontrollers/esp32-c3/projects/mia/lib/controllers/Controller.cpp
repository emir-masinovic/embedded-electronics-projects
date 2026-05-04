#include "Controller.h"

Controller::Controller(Display &v) : view(v), currentState(STATE_BOOT) {}

int sekunde = 0;
int minute = 0;
int sati = 12;
unsigned long lastUpdate = 0;

void Controller::begin()
{
    view.init();
    currentState = STATE_INSPECTOR;
    Serial.println("--- INIT ---");
    Serial.println("Komande: x:VAL, y:VAL, r:VAL (rotacija), t:TEXT (ispis), c:1 (krug), s:1 (kvadrat)");
}

void Controller::handleSerial()
{
    if (Serial.available() > 0)
    {
        String input = Serial.readStringUntil('\n');
        input.trim();

        if (input.startsWith("t:"))
        { // Text: x,y,text
            String val = input.substring(2);
            int firstComma = val.indexOf(',');
            int secondComma = val.indexOf(',', firstComma + 1);
            int x = val.substring(0, firstComma).toInt();
            int y = val.substring(firstComma + 1, secondComma).toInt();
            String msg = val.substring(secondComma + 1);
            view.drawText(x, y, msg);
        }
        else if (input.startsWith("r:"))
        { // Rect: x,y,w,h
          // view.drawRect(x, y, w, h);
        }

        else if (input == "show")
        {
            view.render();
        }
        else if (input == "clear")
        {
            view.clear();
        }
    }
}

void Controller::update()
{
    handleSerial();

    if (millis() - lastUpdate >= 1000)
    {
        lastUpdate = millis();
        sekunde++;
        if (sekunde >= 60)
        {
            sekunde = 0;
            minute++;
        }
        if (minute >= 60)
        {
            minute = 0;
            sati++;
        }
        if (sati >= 24)
        {
            sati = 0;
        }

        char timeBuffer[10];
        sprintf(timeBuffer, "%02d:%02d:%02d", sati, minute, sekunde);

        view.drawClock(timeBuffer);
    }
}