#include "WeatherApp.h"
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

namespace WeatherApp
{

    WiFiUDP ntpUDP;
    NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600);

    unsigned long lastWeatherCheck = 0;
    unsigned long lastDisplayUpdate = 0;
    const unsigned long weatherInterval = 60000; // 1 minute
    const unsigned long displayInterval = 500;   // 0.5 seconds

    float realTemp = 0.0;
    String currentCity = "Sarajevo";
    float lat = 43.85;
    float lon = 18.41;
    bool locationFound = false;

    void discoverLocation()
    {
        if (WiFi.status() != WL_CONNECTED)
            return;
        WiFiClient client;
        HTTPClient http;
        if (http.begin(client, "http://ip-api.com/json/"))
        {
            if (http.GET() == HTTP_CODE_OK)
            {
                JsonDocument doc;
                deserializeJson(doc, http.getString());
                lat = doc["lat"];
                lon = doc["lon"];
                currentCity = doc["city"].as<String>();
                locationFound = true;
            }
            http.end();
        }
    }

    void fetchWeather()
    {
        if (WiFi.status() != WL_CONNECTED)
            return;
        WiFiClient client;
        HTTPClient http;
        String url = "http://api.open-meteo.com/v1/forecast?latitude=" + String(lat, 4) +
                     "&longitude=" + String(lon, 4) + "&current_weather=true";

        if (http.begin(client, url))
        {
            if (http.GET() == HTTP_CODE_OK)
            {
                JsonDocument doc;
                if (!deserializeJson(doc, http.getString()))
                {
                    realTemp = doc["current_weather"]["temperature"];
                }
            }
            http.end();
        }
    }

    void init(LiquidCrystal_I2C &lcd)
    {
        lastWeatherCheck = 0;
        lastDisplayUpdate = 0;

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Weather Boot...");

        if (WiFi.status() == WL_CONNECTED)
        {
            timeClient.begin();
            discoverLocation();
            fetchWeather();
        }
        lcd.clear();
    }

    void run(char key, LiquidCrystal_I2C &lcd)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            timeClient.update();

            if (millis() - lastWeatherCheck > weatherInterval)
            {
                if (!locationFound)
                    discoverLocation();
                fetchWeather();
                lastWeatherCheck = millis();
            }
        }

        if (millis() - lastDisplayUpdate > displayInterval)
        {
            lastDisplayUpdate = millis();

            if (WiFi.status() == WL_CONNECTED)
            {
                lcd.setCursor(4, 0);
                lcd.print(timeClient.getFormattedTime());

                String line2 = currentCity + " " + String(realTemp, 1) + "C";
                int padding = (16 - line2.length()) / 2;

                lcd.setCursor(0, 1);
                for (int i = 0; i < 16; i++)
                {
                    if (i >= padding && i < (padding + (int)line2.length()))
                    {
                        lcd.print(line2[i - padding]);
                    }
                    else
                    {
                        lcd.print(" ");
                    }
                }
            }
            else
            {
                lcd.setCursor(0, 0);
                lcd.print("  OFFLINE MODE  ");
                lcd.setCursor(0, 1);
                lcd.print("Waiting for WiFi");
            }
        }
    }
}