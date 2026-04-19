#include "InputActor.h"

static QueueHandle_t _uiQueue;

void inputTask(void *pvParameters)
{
    SystemMessage msg;

    for (;;)
    {
        if (Serial.available() > 0)
        {
            char c = Serial.read();
            if (c == 'w' ||
                c == 's' ||
                c == 'a' ||
                c == 'd' ||
                c == 'e' ||
                c == 'q')
            {
                msg.type = MSG_KEY_EVENT;
                msg.key = c;
                xQueueSend(_uiQueue, &msg, portMAX_DELAY);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

void startInputActor(QueueHandle_t uiQueue)
{
    _uiQueue = uiQueue;
    xTaskCreatePinnedToCore(inputTask, "InputActor", 2048, NULL, 1, NULL, 1);
}