#ifndef CONNECTION_H
#define CONNECTION_H

#include "_global.h"

typedef struct Connection {
    char *ip;
    short unsigned int port;
    int socket;
} Connection;

Connection *newConnection(char *port);
void receiveData(int socket_id);

// void initialise();
// void listen();
// void close();

#endif  // CONNECTION_H