#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "authentication.h"

void authenticateUser(int new_fd) {
    char* userReceived[MAXDATASIZE], passReceived[MAXDATASIZE], sendData[MAXDATASIZE];
    char* password;
    User *u = malloc(sizeof(User));

    char* cor = "correct";
    char* inc = "incorrect";
    
    memset(sendData, 0, sizeof(sendData));
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

    strcpy(sendData, checkAuth(u->name, password));
    send(new_fd, sendData, strlen(sendData), 0);
}

char* checkAuth(char* name, char* pass) {
    FILE *file = fopen("Authentication.txt", "r");
    if (file == NULL) {
        perror("Unable to read Auth file");
        exit(1);
    }

    char buffer[150];
    char* fileU = malloc(strlen(name) * sizeof(char));
    char* fileP = malloc(strlen(pass) * sizeof(char));

    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        sscanf(buffer, "%s %s", fileU, fileP);
        //printf("File username %s and password %s\n", fileU, fileP);
        if(strcmp(name, fileU) == 0 && strcmp(pass, fileP) == 0) {
            return "correct";
        }
    }

    fclose(file);

    return "incorrect";
}

