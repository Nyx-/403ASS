#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "_global.h"
#include "connection.h"
#include "hangman.h"
#include "leaderboard.h"
#include "menu.h"

typedef struct Connection Connection;
typedef struct Hangman Hangman;

typedef struct Controller {
    Connection *connection;
    Hangman *hangman;
    Leaderboard *leaderboard;
} Controller;

Controller *createController(char *host, char *port);

#endif  // CONTROLLER_H