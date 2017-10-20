#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "connection.h"

Connection *newConnection(char *port) {
    struct sockaddr_in server;
    memset (&server, 0, sizeof(server));

    Connection *c = malloc(sizeof(Connection));
    c->port = atoi(port);
    

    if ((c->socket = socket(AF_INET, SOCK_STREAM, 0)) == RETURNED_ERROR) {
        perror("[newConnection] Could not create socket\n");
        exit(1);
    }

    /* Generate end point */
    server.sin_family = AF_INET; /* host byte order */
    server.sin_port = htons(c->port); /* short, network byte order (IP put in my server when you first run) */
    server.sin_addr.s_addr = INADDR_ANY; /* auto-fill with my IP */

    /* Bind socket to end point */
    if (bind(c->socket, (struct sockaddr*)&server, sizeof(struct sockaddr)) == RETURNED_ERROR) {
        perror("[newConnection] Error binding to port\n");
        exit(1);
    }

    if (listen(c->socket, BACKLOG) == RETURNED_ERROR) {
        perror("[newConnection] Error listening\n");
        exit(1);
    }

    return c;
}

void receiveData(int socket_id) {
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

void closeConnection(Controller *c) {
    close(c->connection->socket);
    c->connection = NULL;
}