#include <stdio.h>
#include <stdlib.h>

#include "leaderboard.h"

Leaderboard *createLeaderboard() {
    Leaderboard *board = malloc(sizeof(Leaderboard));
    return board;
}