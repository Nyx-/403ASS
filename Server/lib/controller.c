#include <stdlib.h>
#include <signal.h>

#include "controller.h"

Controller *createController(char *port) {
    Controller *c = malloc(sizeof(Controller));

    c->connection = newConnection(port);
    c->c_wordList = createWordList();
    c->quit_signal = 0;

    return c;
}

void quitSignalHandler() {
    controller->quit_signal = 1;
    //close connections and threads etc
}