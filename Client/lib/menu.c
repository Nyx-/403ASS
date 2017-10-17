#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <ctype.h>

#include "leaderboard.h"
#include "controller.h"
#include "menu.h"

void login() {
    char user[50]; 
    char pass[50]; 
    char buf[MAXDATASIZE];

    printf("====================================================\n\n\n" 
            "Welcome to the Online Hangman Gaming System\n\n\n"
            "====================================================\n\n\n"); 

    printf("You are required to logon with your registered Username and Password\n\n"); 
    printf("Please enter your username--> "); 
    scanf("%s", user); 
    send(controller->connection->socket, user, sizeof(user), 0);
    printf("Please enter your password--> "); 
    scanf("%s", pass);
    send(controller->connection->socket, pass, sizeof(pass), 0);
}

void displayGameMenu() {
    displayGameTitle();
    displayGameOptions();
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

void makeSelection() {
    char option[50];

    printf("Selection option 1-3 -> ");
    scanf("%s", option);

    if (strcmp(option, "1") == 0) {
        //PLAY HANGMAN
        printf("Play hangman\n");

    } else if (strcmp(option, "2") == 0) {
        //SHOW LEADERBOARD
        printf("Show leaderboard\n");
    } else if (strcmp(option, "3") == 0) {
        //QUIT
        printf("Quit\n");
    } else {
        printf("\nSelection error, please try again.\n");
        makeSelection();
    }
}