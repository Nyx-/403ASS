#include <stdlib.h>

#include "controller.h"

Controller *createController(char *port) {
    Controller *c = malloc(sizeof(Controller));

    c->connection = newConnection(port);
    c->c_wordList = createWordList();

    return c;
}