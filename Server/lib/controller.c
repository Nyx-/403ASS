#include <stdlib.h>
#include <signal.h>

#include "controller.h"

Controller *createController(char *port) {
    Controller *c = malloc(sizeof(Controller));

    c->connection = newConnection(port);
    c->c_wordList = createWordList();
    c->quit_signal = false;

    return c;
}

void quitSignalHandler() {
    printf("quitSignalHandler...\n");
    controller->quit_signal = true;
    exitGracefully();
    //close connections and threads etc
}

void exitGracefully() {
    printf("exitGraceully...\n");
    exit(1);
    // clear(memorystuffs);
    // close(socket);
    // close(filedescriptors);
}