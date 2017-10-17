#include <stdio.h>
#include <sys/socket.h>

#include "leaderboard.h"
#include "controller.h"

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

    while(1) {
        
    }
}