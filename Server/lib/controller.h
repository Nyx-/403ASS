#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "_global.h"
#include "connection.h"

typedef struct Connection Connection;

typedef struct Controller {
    Connection *connection;
} Controller;

Controller *createController(char *port);

Controller *controller;

#endif  // CONTROLLER_H