#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "_global.h"
#include "menu.h"

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
void *freeLeaderboard(Leaderboard *lb);
void *displayLeaderboard(Leaderboard *lb);

#endif  // LEADERBOARD_H