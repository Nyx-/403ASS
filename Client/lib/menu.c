#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <ctype.h>

#include "menu.h"

void *displayGameMenu(Controller *c) {
    displayGameOptions();
    makeSelection(c);
}

void printGameLine() {
    printf("\n=============================================================================\n\n");
}

void displayGameTitle() {
    printGameLine();
    printf("Welcome to the Hangman Gaming System\n");
    printGameLine();
}

void displayGameOptions() {
    printf("\nPlease enter a selection\n"
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
        send(c->connection->socket, option, sizeof(option), 0);
        printf("\n\n");
        playHangman(c->hangman, c->connection);
    } else if (strcmp(option, "2") == 0) {
        //SHOW LEADERBOARD
        displayLeaderboard(c->leaderboard);
    } else if (strcmp(option, "3") == 0) {
        //QUIT
        exitGracefully(c);
    } else {
        printf("\nSelection error, please try again.\n");
        makeSelection(c);
    }
    displayGameOptions();
    makeSelection(c);
}