#include <Arduino.h>
#include "messages.h"
#include "UIActor.h"
#include "WiFiActor.h"
#include "InputActor.h"

QueueHandle_t uiQueue;

void setup()
{
    Serial.begin(115200);

    uiQueue = xQueueCreate(10, sizeof(SystemMessage));

    startUIActor(uiQueue);
    startWiFiActor(uiQueue);
    startInputActor(uiQueue);

    Serial.println("System initialized");
}

void loop() { vTaskDelete(NULL); }