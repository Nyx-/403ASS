#include <stdlib.h>

#include "controller.h"

Controller *createController(char *host, char *port) {
    Controller *c = malloc(sizeof(Controller));

    //register the connection
    c->connection = newConnection(host, port);
    c->hangman = createGame(c->connection);
    c->leaderboard = createLeaderboard();

    return c;
}