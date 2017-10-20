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
    printf("exitGraceully...\n");
    //join/gracefully handle threads
    closeConnection(controller);
    endGame(controller->hangman);
    freeLeaderboard(controller->leaderboard);
    exit(1);
}