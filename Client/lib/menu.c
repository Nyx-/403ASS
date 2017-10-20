#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <ctype.h>

#include "menu.h"

void *displayGameMenu(Controller *c) {
    displayGameTitle();
    displayGameOptions();
    makeSelection(c);
}

void displayGameTitle() {
    printf("\n=============================================================================\n\n\n"
            "Welcome to the Hangman Gaming System\n\n\n\n");
}

void displayGameOptions() {
    printf("Please enter a selection\n"
            "<1> Play Hangman\n"
            "<2> Show Leaderboard\n"
            "<3> Quit\n\n");
}

void *makeSelection(Controller *c) {
    char option[50];

    printf("Selection option 1-3 -> ");
    scanf("%s", option);

    if (strcmp(option, "1") == 0) {
        //PLAY HANGMAN
        printf("Play hangman\n");
        send(c->connection->socket, option, sizeof(option), 0);
        playHangman(c->hangman, c->connection);
    } else if (strcmp(option, "2") == 0) {
        //SHOW LEADERBOARD
        printf("Show leaderboard\n");
        displayLeaderboard(c->leaderboard);
    } else if (strcmp(option, "3") == 0) {
        //QUIT
        printf("Quit\n");
    } else {
        printf("\nSelection error, please try again.\n");
        makeSelection(c);
    }
    displayGameOptions();
    makeSelection(c);
}