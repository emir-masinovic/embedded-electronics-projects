#ifndef MESSAGES_H
#define MESSAGES_H

#include <Arduino.h>

enum MessageType {
    MSG_KEY_EVENT,
    MSG_WIFI_STATUS_UPDATE
};

struct SystemMessage {
    MessageType type;
    char key;
    char text[32];
    int value;
};

#endif