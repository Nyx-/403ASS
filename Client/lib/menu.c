#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <ctype.h>

#include "controller.h"

void *displayGameMenu(Hangman *game) {
    displayGameTitle();
    displayGameOptions();
    makeSelection(game);
}

void displayGameTitle() {
    printf("\n====================================================\n\n\n"
            "Welcome to the Hangman Gaming System\n\n\n\n");
}

void displayGameOptions() {
    printf("Please enter a selection\n"
            "<1> Play Hangman\n"
            "<2> Show Leaderboard\n"
            "<3> Quit\n\n");
}

void *makeSelection(Hangman *h) {
    char option[50];

    printf("Selection option 1-3 -> ");
    scanf("%s", option);

    if (strcmp(option, "1") == 0) {
        //PLAY HANGMAN
        printf("Play hangman\n");
        playHangman(h);
    } else if (strcmp(option, "2") == 0) {
        //SHOW LEADERBOARD
        printf("Show leaderboard\n");
    } else if (strcmp(option, "3") == 0) {
        //QUIT
        printf("Quit\n");
    } else {
        printf("\nSelection error, please try again.\n");
        makeSelection(h);
    }
}