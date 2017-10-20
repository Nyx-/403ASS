#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "_global.h"
#include "connection.h"
#include "hangman.h"
#include "leaderboard.h"

typedef struct Connection Connection;
typedef struct Hangman Hangman;
typedef struct Leaderboard Leaderboard;

typedef struct Controller {
    Connection *connection;
    Hangman *hangman;
    Leaderboard *leaderboard;
} Controller;

Controller *createController(char *host, char *port);
void exitGracefully(Controller *c);

Controller *controller;

#endif  // CONTROLLER_H