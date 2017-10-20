#include <stdio.h>
#include <stdlib.h>

#include "leaderboard.h"

Leaderboard *createLeaderboard() {
    Leaderboard *lb = malloc(sizeof(Leaderboard));
    lb->list = malloc(sizeof(User));
    lb->userCount = 0;

    return lb;
}

void freeLeaderboard(Leaderboard *lb) {
    // free(lb->list->name);
    // free(lb->list->played);
    // free(lb->list->wins);
    // free(lb->list);
    // free(lb->userCount);
    free(lb);
}

void printLeaderboardLine() {
    printf("\n=============================================================================\n\n");
}

void *displayLeaderboard(Leaderboard *lb) {
    //fetchLeaderboardDataFromServer, and update local lb->list
    if (lb->userCount == 0) {
        printLeaderboardLine();
        printf("There is no information currently stored in the Leaderboard. Try again later\n");
        printLeaderboardLine();
    } else {
        //TODO: For each user, print the following:
        printLeaderboardLine();
        printf("\nPlayer\t- %s\nNumber of games won  - %d\nNumber of games played  - %d\n",
        lb->list->name,
        lb->list->played,
        lb->list->wins );
        printLeaderboardLine();
    }
}

void addUserToLeaderboard(Leaderboard *lb, char *user) {
    lb->list->name = user;
    lb->list->played = 0;
    lb->list->wins = 0;
    lb->userCount += 1;
}
