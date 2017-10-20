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

Connection *newConnection(char *ip, char *port);
int initialiseConnection();
void closeConnection(Connection *c);
void freeConnection(Connection *c);

void invalidConnection();
void *login(Controller *c);

#endif  // CONNECTION_H