#include <stdio.h>

#include "connection.h"

void Testing_Function(int socket_id) {
    char* testStr = "testing";
    int stringSize = 7;
    int i = 0;

    char sendingArray[stringSize];
    for (i = 0; i < stringSize; i++) {
        sendingArray[i] = testStr[i];
    }

    uint8_t charBytes;
    for (i = 0; i < stringSize; i++) {
        charBytes = sendingArray[i];
        send(socket_id, &charBytes, sizeof(uint8_t), 0);
    }
}