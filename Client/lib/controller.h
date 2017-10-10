#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "_global.h"
#include "connection.h"
#include "hangman.h"
#include "leaderboard.h"

typedef struct Connection Connection;
typedef struct Hangman Hangman;

typedef struct Controller {
    Connection *connection;
    Hangman *hangman;
    Leaderboard *leaderboard;
} Controller;

#endif  // CONTROLLER_H