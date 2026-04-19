#include "WiFiActor.h"
#include <WiFi.h>

static QueueHandle_t _uiQueue;

void wifiTask(void *pvParameters)
{
    SystemMessage msg;

    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));

        if (WiFi.status() == WL_CONNECTED)
        {
            msg.type = MSG_WIFI_STATUS_UPDATE;
            msg.value = WiFi.RSSI();
            strncpy(msg.text, WiFi.localIP().toString().c_str(), sizeof(msg.text) - 1);

            xQueueSend(_uiQueue, &msg, portMAX_DELAY);
        }
    }
}

void startWiFiActor(QueueHandle_t uiQueue)
{
    _uiQueue = uiQueue;
    xTaskCreatePinnedToCore(wifiTask, "WiFiActor", 4096, NULL, 1, NULL, 0);
}