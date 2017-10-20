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
    int count;
} Leaderboard;

Leaderboard *createLeaderboard();
void clearLeaderboard(Leaderboard l);
void displayLeaderboard(Leaderboard *lb);

Leaderboard *lb;

#endif  // LEADERBOARD_H