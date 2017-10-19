#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdbool.h>

#include "_global.h"
#include "connection.h"
#include "hangman.h"

typedef struct Connection Connection;
typedef struct WordList WordList;

typedef struct Controller {
    Connection *connection;
    WordList *c_wordList;
    volatile bool quit_signal;
} Controller;

Controller *createController(char *port);
void quitSignalHandler();
void exitGracefully();

Controller *controller;

#endif  // CONTROLLER_H