#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "authentication.h"

void authenticateUser(int new_fd) {
    char* userReceived[MAXDATASIZE], passReceived[MAXDATASIZE], send[MAXDATASIZE];
    char* password;
    User *u = malloc(sizeof(User));

    memset(userReceived, 0, sizeof(userReceived));
    memset(passReceived, 0, sizeof(passReceived));

    if (recv(new_fd, userReceived, sizeof(userReceived), 0) == RETURNED_ERROR) {
        perror("[authenticateUser] unable to receive username");
        exit(1);
    }
    u->name = userReceived;

    printf("Username received: %s\n", u->name);

    if (recv(new_fd, passReceived, sizeof(passReceived), 0) == RETURNED_ERROR) {
        perror("[authenticateUser] unable to receive password");
        exit(1);
    }
    password = passReceived;

    printf("Password received: %s\n", password);

    printf("before it all goes poop");

    checkAuth(u->name, password);

    printf("check");

    // if(checkAuth(u->name, password)) {
    //     printf("Correct login");
    //     //correct login
    // } else {
    //     printf("Incorrect login");
    //     //send wrong login message
    // }
}

int checkAuth(char* name, char* pass) {
    printf("into checkauth function");
    FILE *file = fopen("Authentication.txt", "r");
    if (file == NULL) {
        perror("Unable to read Auth file");
        exit(1);
    }
    printf("file opened");

    char buffer[150];
    char* fileU = malloc(strlen(name) * sizeof(char));
    char* fileP = malloc(strlen(pass) * sizeof(char));

    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        sscanf(buffer, "%s %s", fileU, fileP);
        printf("File username %s and password %s", fileU, fileP);
        if(strcmp(name, fileU) == 0 && strcmp(pass, fileP) == 0) {
            return 1;
        }
    }

    fclose(file);

    return 0;
}

// char* strToLower(char* string) {
//     char temp[strlen(string)];
//     int i;

//     for (i = 0; i < strlen(string); i++) {
//         temp[i] = tolower(temp[i]);
//     }

//     printf("to lower: %s", temp);
//     return temp;
// }

