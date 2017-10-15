#include "controller.h"

Controller *createController(char *host, int *port) {
    Controller *c = malloc(sizeof(Controller));

    //register the connection
    c->connection = newConnection(host, port);
    c->hangman = NULL;
    c->leaderboard = NULL;

    return c;
}