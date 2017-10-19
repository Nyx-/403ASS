#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <windows.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netdb.h>

#include "connection.h"
#include "hangman.h"
#include "menu.h"

Connection *newConnection(char *ip, char *port) {
    int connectfd;
    struct hostent *he;
    struct sockaddr_in server;
    memset (&server, 0, sizeof(server));

    Connection *c = malloc(sizeof(Connection));
    c->ip = ip;
    c->port = atoi(port);

    if (port == 0) {
        perror("[newConnection] Invalid Port\n");
        return NULL;
    }

    if ((he = gethostbyname(c->ip)) == NULL) {
        herror("[newConnection] Invalid host IP\n");
        return NULL;
    }

    //create and validate socket connection
    if ((c->socket = socket(AF_INET , SOCK_STREAM , 0)) == RETURNED_ERROR) {
        perror("[newConnection] Could not create socket\n");
        return NULL;
    }
    
    server.sin_family = AF_INET;
    server.sin_port = htons(c->port);
    server.sin_addr = *((struct in_addr *)he->h_addr); // OR server.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(server.sin_zero), 8);

    //Connect and validate connection to remote server
    if (connect(c->socket, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1) {
        perror("[newConnection] Connection to server failed\n");
        return NULL;
    }

    return c;
}

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
}

void invalidConnection() {
    printf("You entered either an incorrect username or password - disconnecting\n");
    char* send[MAXDATASIZE];
    exit(1);
}

void *login(Connection *c) {
    char user[50]; 
    char pass[50]; 
    char buf[MAXDATASIZE];

    printf("====================================================\n\n\n" 
            "Welcome to the Online Hangman Gaming System\n\n\n"
            "====================================================\n\n\n"); 

    printf("You are required to logon with your registered Username and Password\n\n"); 
    printf("Please enter your username--> "); 
    scanf("%s", user); 
    send(c->socket, user, sizeof(user), 0);
    printf("Please enter your password--> "); 
    scanf("%s", pass);
    send(c->socket, pass, sizeof(pass), 0);
}