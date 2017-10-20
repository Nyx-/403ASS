#include <stdio.h>
#include <stdlib.h>

#include "leaderboard.h"

Leaderboard *createLeaderboard() {
    Leaderboard *lb = malloc(sizeof(Leaderboard));
    lb->list = malloc(sizeof(User));
    lb->userCount = 0;

    return lb;
}

// UNTESTED
void addUserToLeaderboard(Leaderboard *lb, char *user) {
    lb->list->name = user;
    lb->list->played = 0;
    lb->list->wins = 0;
    lb->userCount += 1;
}

void freeLeaderboard(Leaderboard *lb) {
    printf("free leaderboard\n");
}