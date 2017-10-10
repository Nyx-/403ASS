#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <windows.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>

#include "connection.h"

Connection *newConnection(char *ip, int *port) {
    if (port == 0) {
        perror("[newConnection] Invalid Port\n");
        return NULL;
    }
    printf("Port valid\n");

    struct hostent *he;
    if (he = gethostbyname(ip) == NULL) {
        herror("[newConnection] Invalid host IP\n");
        return NULL;
    }
    printf("Host IP valid\n");

    Connection *c = malloc(sizeof(Connection));
    c->ip = ip;
    c->port = atoi(port);
    //Create socket
    c->socket = socket(AF_INET , SOCK_STREAM , 0);

    //validate socket connection
    if (c->socket == -1) {
        perror("[newConnection] Could not create socket\n");
        return NULL;
    }
    printf("Socket created\n");
    printf("Connection object filled\n");
    
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(c->port);
    server.sin_addr.s_addr = inet_addr(c->ip); // OR server.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(server.sin_zero), 8); /* zero the rest of the struct */

//DEBUGGING
printf("socket value: %d\n", c->socket);
printf("Server address: %d\n", (struct sockaddr *)&server);
printf("Server size: %d\n", sizeof(server));
    
    int connectfd = connect(c->socket, (struct sockaddr *)&server, sizeof(server));

//DEBUGGING
printf("Connection fd value: %d\n", connectfd);

    //Connect to remote server
    // if (connect(c->socket, (struct sockaddr *)&server, sizeof(server)) < 0) {
    if (connectfd == -1) {
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
    PlayHangman(finalOutput);
}
