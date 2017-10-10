#ifndef LEADERBOARD_H
#define LEADERBOARD_H

typedef struct Leaderboard {
    char names;
    int played;
    int wins;
    int count;
} Leaderboard;

Leaderboard *createLeaderboard();
void clearLeaderboard(Leaderboard l);

#endif  // LEADERBOARD_H