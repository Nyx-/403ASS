#include "controller.h"

Controller *createController(char *argv[]) {
    Controller *c = malloc(sizeof(Controller));

    //register the connection
    c->connection = newConnection(argv[1], argv[2]);
    c->hangman = NULL;
    c->leaderboard = NULL;

    return c;
}