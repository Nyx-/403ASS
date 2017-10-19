#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "_global.h"
#include "connection.h"
#include "hangman.h"

typedef struct Connection Connection;
typedef struct WordList WordList;

typedef struct Controller {
    Connection *connection;
    WordList *c_wordList;
    volatile int quit_signal;
} Controller;

Controller *createController(char *port);
void quitSignalHandler();

Controller *controller;

#endif  // CONTROLLER_H