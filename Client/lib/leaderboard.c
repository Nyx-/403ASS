#include <stdio.h>
#include <stdlib.h>

#include "leaderboard.h"

Leaderboard *createLeaderboard() {
    Leaderboard *lb = malloc(sizeof(Leaderboard));
    lb->list = malloc(sizeof(User));
    lb->userCount = 0;

    return lb;
}

// // UNTESTED
// void *freeLeaderboard(Leaderboard *lb) {
//     if (lb != NULL) {
//         for (int i = 0; i < (*lb)->userCount; i++) {
//             free((*lb)->list[i]->name);
//             free((*lb)->list[i]->played);
//             free((*lb)->list[i]->wins);
//             free((*lb)->list);
//         }
//         free((*lb)->userCount);
//         free((*lb));
//         (*lb) = NULL;
//     }
// }

void *displayLeaderboard(Leaderboard *lb) {
    if (lb->userCount == 0) {
        printf("\n=============================================================================\n\n"
                "There is no information currently stored in the Leaderboard. Try again later\n\n"
                "=============================================================================\n\n\n\n");
    } else {
        // UNTESTED
        //fetchLeaderboardDataFromServer
        printf("\n=============================================================================\n\n");
        for (int i = lb->userCount - 1; i >= 0; i--) {
            // printf("\n\nPlayer\t- %s\nNumber of games won  - %d\nNumber of games played  - %d\n\n",
            // lb->list[i]->name,
            // lb->list[i]->played,
            // lb->list[i]->wins );
        }
    }
}