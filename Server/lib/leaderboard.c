#include <stdio.h>
#include <stdlib.h>

#include "controller.h"
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

// TODO: free()
void freeLeaderboard(Leaderboard *lb) {
    printf("free leaderboard\n");
}

// UNTESTED
void sendLeaderboardUpdateToClient(Leaderboard *lb) {
    //send char
    send(controller->new_fd, lb->list->name, (size_t) strlen(lb->list->name), 0);
    confirmLeaderboardRecv();

    //send int
    send(controller->new_fd, lb->list->played, sizeof(uint16_t), 0);
    confirmLeaderboardRecv();

    //send int
    send(controller->new_fd, lb->list->wins, sizeof(uint16_t), 0);
    confirmLeaderboardRecv();
    
    //send int
    send(controller->new_fd, lb->userCount, sizeof(uint16_t), 0);
    confirmLeaderboardRecv();
}

// UNTESTED
void confirmLeaderboardRecv() {
    int msg;
    if(recv(controller->new_fd, &msg, sizeof(int), 0) == RETURNED_ERROR) {
        perror("[confirmLeaderboardRecv] Error.");
    }
}
