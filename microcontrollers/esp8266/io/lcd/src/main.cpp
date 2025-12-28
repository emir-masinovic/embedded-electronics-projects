#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "WiFi name";
const char* password = "";
const int wifiTimeout = 10; // Seconds

LiquidCrystal_I2C lcd(0x27, 16, 2);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600);

float realTemp = 0;
unsigned long lastWeatherCheck = 0;
const unsigned long weatherInterval = 60000; // 1 minute (ms)

// Fallback to Sarajevo
String currentCity = "Sarajevo";
float lat = 43.85; 
float lon = 18.41;

void discoverLocation() {
  WiFiClient client;
  HTTPClient http;
  if (http.begin(client, "http://ip-api.com/json/")) {
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      JsonDocument doc;
      deserializeJson(doc, http.getString());
      lat = doc["lat"];
      lon = doc["lon"];
      currentCity = doc["city"].as<String>();
    }
    http.end();
  }
}

void fetchWeather() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    
    String url = "http://api.open-meteo.com/v1/forecast?";
    url += "latitude="    + String(lat, 4); 
    url += "&longitude="   + String(lon, 4);
    url += "&current_weather=true";  

    if (http.begin(client, url)) {
      int httpCode = http.GET();
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        
        Serial.println("Raw API Data: " + payload);

        JsonDocument doc; 
        DeserializationError error = deserializeJson(doc, payload);

        if (!error) {
          // Open-Meteo structure: current_weather -> temperature
          if (doc["current_weather"].is<JsonObject>()) {
             realTemp = doc["current_weather"]["temperature"];
             Serial.printf("Parsed Temp: %.1f\n", realTemp);
          } else {
             Serial.println("Error: 'current_weather' key not found in JSON");
          }
        } else {
          Serial.print("JSON Parse Failed: ");
          Serial.println(error.c_str());
        }
      } else {
        Serial.printf("HTTP Error: %d\n", httpCode);
      }
      http.end();
    }
  }
}

void statusMsg(String l1, String l2) {
  lcd.clear();
  lcd.setCursor(0,0); lcd.print(l1);
  lcd.setCursor(0,1); lcd.print(l2);
}

void setup() {
  lcd.init();
  lcd.backlight();
  
  statusMsg("WiFi Connecting", ssid);
  WiFi.begin(ssid, password);

  int counter = 0;
  while (WiFi.status() != WL_CONNECTED && counter < wifiTimeout) {
    delay(1000);
    lcd.setCursor(counter % 16, 1); lcd.print(".");
    counter++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    statusMsg("Online!", "Fetching Data...");
    timeClient.begin();
    discoverLocation();
    fetchWeather();
    delay(1000);
  } else {
    statusMsg("Offline Mode", "Using Backup");
    delay(1500);
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    timeClient.update();
    if (millis() - lastWeatherCheck > weatherInterval) {
      fetchWeather();
      lastWeatherCheck = millis();
    }
  }

  // Row 1: Time
  lcd.setCursor(0, 0);
  lcd.print("    ");
  lcd.print(timeClient.getFormattedTime());
  lcd.print("    ");

  // Row 2: Weather
  String line2 = currentCity + " " + String(realTemp, 1) + (char)223 + "C";
  int padding = (16 - line2.length()) / 2;
  lcd.setCursor(0, 1);
  for(int i=0; i<padding; i++) lcd.print(" ");
  lcd.print(line2);
  for(int i=0; i < (int)(16 - padding - line2.length()); i++)
  
  delay(1000); 
}