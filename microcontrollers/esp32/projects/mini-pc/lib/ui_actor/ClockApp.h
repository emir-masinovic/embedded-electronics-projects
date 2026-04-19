#ifndef CLOCK_APP_H
#define CLOCK_APP_H

#include "interfaces/IApp.h"
#include <Adafruit_SSD1306.h>
#include <time.h>

class ClockApp : public IApp
{
    Adafruit_SSD1306 *_display;
    const char *ntpServer = "pool.ntp.org";
    const long gmtOffset_sec = 3600;     // Sarajevo - UTC+1
    const int daylightOffset_sec = 3600; // DST

public:
    ClockApp(Adafruit_SSD1306 *display) : _display(display) {}

    void onEnter() override
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        }
    }

    void onKeyEvent(char key) override {}

    void draw() override
    {
        struct tm timeinfo;
        _display->clearDisplay();
        _display->setCursor(0, 0);
        _display->println("DIGITAL CLOCK");
        _display->drawLine(0, 10, 128, 10, 1);

        if (!getLocalTime(&timeinfo))
        {
            _display->setCursor(0, 30);
            _display->println("Waiting for NTP...");
            return;
        }

        _display->setTextSize(2);
        _display->setCursor(15, 30);
        _display->printf("%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
        _display->setTextSize(1);
    }
};

#endif