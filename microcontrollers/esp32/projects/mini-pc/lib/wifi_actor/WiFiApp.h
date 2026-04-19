#include "interfaces/IApp.h"
#include <WiFi.h>
#include <Adafruit_SSD1306.h>

class WiFiApp : public IApp
{
    Adafruit_SSD1306 *_display;
    bool _connecting = false;

public:
    WiFiApp(Adafruit_SSD1306 *display) : _display(display) {}

    void onEnter() override
    {
        _connecting = true;
        WiFi.begin("ssid", "pass");
    }

    void onKeyEvent(char key) override
    {
        // 'q' handled by MenuManager/UIActor
    }

    void draw() override
    {
        _display->clearDisplay();
        _display->setCursor(0, 0);
        _display->println("WIFI SETTINGS");
        _display->drawLine(0, 10, 128, 10, 1);

        if (WiFi.status() != WL_CONNECTED)
        {
            _display->setCursor(0, 25);
            _display->print("Status: Connecting...");
        }
        else
        {
            _display->setCursor(0, 25);
            _display->print("IP: ");
            _display->println(WiFi.localIP());
            _display->print("RSSI: ");
            _display->println(WiFi.RSSI());
        }
    }
};