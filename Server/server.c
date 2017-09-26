#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "lib/_global.h"

void Testing_Function(int socket_id) {
    char* testStr = "testing";
    int stringSize = 7;
    int i = 0;

    char sendingArray[stringSize];
    for (i = 0; i < stringSize; i++) {
        sendingArray[i] = testStr[i];
    }

    uint8_t charBytes;
    for (i = 0; i < stringSize; i++) {
        charBytes = sendingArray[i];
        send(socket_id, &charBytes, sizeof(uint8_t), 0);
    }
}

int main(int argc, char* argv[]) {
    /* Thread attributes here */
    pthread_t client_thread;
    pthread_attr_t attr;

    int sock_fd, new_fd; /* listen on sock_fd, new connection on new_fd */
    struct sockaddr_in serv_addr;   /* Server address info */
    struct sockaddr_in client_addr; /* Client address info */
    socklen_t sin_size;
    int i = 0;

    /* Get port number for server to listen on */
    if (argc != 2) {
        fprintf(stderr, "usage: client port_number\n");
        exit(1);
    }

    /* Generate socket */
    // The function creates a socket with AF_INET ( IP Addressing ) and of type
    // SOCK_STREAM. Data from all devices wishing to connect on this socket will
    // be redirected to sock_fd
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    /* Generate end point */
    serv_addr.sin_family = AF_INET; /* host byte order */
    serv_addr.sin_port = htons(
        atoi(argv[1])); /* short, network byte order (IP put in my server when
                           you first run) */
    serv_addr.sin_addr.s_addr = INADDR_ANY; /* auto-fill with my IP */

    /* Bind socket to end point */
    if (bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr)) ==
        -1) {
        perror("bind");
        exit(1);
    }

    /* Start listening */
    // Start Listening for connections , keep at the most 10 connection requests
    // waiting.If there are more than 10 computers wanting to connect at a time,
    // the 11th one fails to.
    if (listen(sock_fd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    /* Main accept() loop */
    while (1) {
        sin_size = sizeof(struct sockaddr_in);
        if ((new_fd = accept(sock_fd, (struct sockaddr*)&client_addr,
                             &sin_size)) == -1) {
            perror("accept");
            continue;
        }
        printf("server: got connection from %s\n",
               inet_ntoa(client_addr.sin_addr));

        /* Create a thread to accept client */

        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&client_thread, &attr, Testing_Function, new_fd);

        pthread_join(client_thread, NULL);

        if (send(new_fd, "All of array data sent by server\n", 40, 0) == -1) {
            perror("send");
        }
    }
    close(new_fd);
}