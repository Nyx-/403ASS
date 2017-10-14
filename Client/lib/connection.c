#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <windows.h>

#include "connection.h"
#include "hangman.h"

void Receive_Array_Int_Data(int socket_identifier, int size) {
    int number_of_bytes, i = 0;
    uint8_t statistics;
    char finalOutput[MAXDATASIZE] = "";

    char *results = malloc(sizeof(char) * STRING_SIZE);

    for (i = 0; i < size; i++) {
        if ((number_of_bytes = recv(socket_identifier, &statistics,
                                    sizeof(uint8_t), 0)) == RETURNED_ERROR) {
            perror("recv");
            exit(EXIT_FAILURE);
        }
        results[i] = statistics;
    }
    for (i = 0; i < STRING_SIZE; i++) {
        // THIS JOINS THE STRING TOGETHER
        strncat(finalOutput, &results[i], 1);
    }

    printf("%s\n", finalOutput);
    login();
}

void login() {
    printf("====================================================\n\n\n Welcome to the Online Hangman Gaming System\n\n\n====================================================\n\n\n");
    
    char user[50];
    char pass[50];
    
    printf("You are required to logon with your registered Username and Password\n\n");
    printf("Please enter your username--> ");
    scanf("%s", user);
    printf("Please enter your password--> ");
    scanf("%s", pass);

    // new_game = createGame(finalOutput);
    PlayHangman();
}