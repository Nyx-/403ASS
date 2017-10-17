#ifndef CONNECTION_H
#define CONNECTION_H

#include "_global.h"
#include <pthread.h>

typedef struct Connection {
    char *ip;
    short unsigned int port;
    int socket;
    pthread_t thread;
} Connection;

Connection *newConnection(char *ip, char *port);
int initialiseConnection();
void closeConnection();

void Receive_Array_Int_Data(int socket_identifier, int size);
void invalidConnection();

// void initialise();
// void login();
// void listen();
// void close();

#endif  // CONNECTION_H