#include <stdio.h>
#include <stdlib.h>

#include "leaderboard.h"

Leaderboard *createLeaderboard() {
    Leaderboard *lb = malloc(sizeof(Leaderboard));
    lb->list = malloc(sizeof(User));
    lb->count = 0;

    return lb;
}

void displayLeaderboard(Leaderboard *lb) {
    if (lb->count == 0) {
        printf("\n=============================================================================\n\n"
                "There is no information currently stored in the Leader Board. Try again later\n\n"
                "=============================================================================\n\n\n\n");
        
    }
}