#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "_global.h"

typedef struct User {
    char *name;
    int played;
    int wins;
} User;

typedef struct Leaderboard {
    User *list;
    int userCount;
} Leaderboard;

Leaderboard *createLeaderboard();
void *addUserToLeaderboard(Leaderboard *lb, char *user);
void *freeLeaderboard(Leaderboard *l);

#endif  // LEADERBOARD_H