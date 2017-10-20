#include <stdlib.h>
#include <stdio.h>

#include "controller.h"
#include "connection.h"
#include "leaderboard.h"

Controller *createController(char *host, char *port) {
    Controller *c = malloc(sizeof(Controller));

    //register the connection
    c->connection = newConnection(host, port);
    c->hangman = createGame();
    c->leaderboard = createLeaderboard();

    return c;
}

void exitGracefully(Controller *c) {
    closeConnection(c->connection);
    endGame(c->hangman);
    freeLeaderboard(c->leaderboard);
    clearGameMemory(c->hangman);
    printf("\nGoodbye...\n");
    exit(1);
}