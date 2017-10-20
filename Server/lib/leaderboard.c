#include <stdio.h>
#include <stdlib.h>

#include "leaderboard.h"

// UNTESTED
Leaderboard *createLeaderboard() {
    Leaderboard *lb = malloc(sizeof(Leaderboard));
    lb->list = malloc(BACKLOG * sizeof(User));
    lb->userCount = 0;

    return lb;
}

// // UNTESTED
// void *addUserToLeaderboard(Leaderboard *lb, char *user) {
//     lb->list[lb->userCount]->name = user;
//     lb->list[lb->userCount]->played = 0;
//     lb->list[lb->userCount]->wins = 0;
//     lb->userCount++;
// }

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