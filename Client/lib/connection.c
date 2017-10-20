#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <windows.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netdb.h>
#include <unistd.h>

#include "connection.h"
#include "leaderboard.h"

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
    server.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(server.sin_zero), 8);

    //Connect and validate connection to remote server
    if (connect(c->socket, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1) {
        perror("[newConnection] Connection to server failed\n");
        return NULL;
    }

    return c;
}

void invalidConnection() {
    printf("You entered either an incorrect username or password - disconnecting\n");
    char* send[MAXDATASIZE];
    exit(1);
}

void *login(Controller *c) {
    char user[50];
    char pass[50];
    char buf[MAXDATASIZE];

    displayGameTitle();

    printf("You are required to logon with your registered Username and Password\n\n"); 
    printf("Please enter your username--> "); 
    scanf("%s", user); 
    c->currentPlayer = user;
    addUserToLeaderboard(c->leaderboard, user);
    send(c->connection->socket, user, sizeof(user), 0);
    printf("Please enter your password--> "); 
    scanf("%s", pass);
    send(c->connection->socket, pass, sizeof(pass), 0);
}

void closeConnection(Connection *c) {
    close(c->socket);
    freeConnection(c);
}

void freeConnection(Connection *c) {
    // free(c->ip);
    // free(c->port);
    // free(c->socket);
    free(c);
}