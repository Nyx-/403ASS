#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

#include "controller.h"

Controller *createController(char *port) {
    Controller *c = malloc(sizeof(Controller));

    c->connection = newConnection(port);
    c->c_wordList = createWordList();
    c->leaderboard = createLeaderboard();
    c->quit_signal = false;

    return c;
}

void quitSignalHandler() {
    printf("quitSignalHandler...\n");
    controller->quit_signal = true;
    exitGracefully();
}

void exitGracefully() {
    closeConnection(controller->connection);
    endGame(h);
    freeLeaderboard(controller->leaderboard);
    exit(1);
}