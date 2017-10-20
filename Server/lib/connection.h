#ifndef CONNECTION_H
#define CONNECTION_H

#include "_global.h"
#include "controller.h"

typedef struct Controller Controller;

typedef struct Connection {
    char *ip;
    short unsigned int port;
    int socket;
} Connection;

Connection *newConnection(char *port);
void receiveData(int socket_id);
void closeConnection(Controller *c);

// void initialise();
// void listen();

#endif  // CONNECTION_H