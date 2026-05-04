#include <Arduino.h>
#include <Display.h>
#include <Controller.h>

Display miaView;
Controller miaApp(miaView);

void setup()
{
    Serial.begin(115200);
    delay(2000);
    miaApp.begin();
}

void loop()
{
    miaApp.update();
}