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
#include <pthread.h>

#include "lib/_global.h"
#include "lib/controller.h"
#include "lib/connection.h"
#include "lib/authentication.h"
#include "lib/hangman.h"

int main(int argc, char* argv[]) {
    /* Thread attributes here */
    pthread_t client_thread;
    pthread_attr_t attr;

    int new_fd; /* listen on sock_fd, new connection on new_fd */
    struct sockaddr_in client_addr; /* Client address info */
    socklen_t sin_size;
    int i = 0;

    // block to detect CLI usage was correct or not.
    if (argc == 2) {
        controller = createController(argv[1]);
    } else if (argc > 2 || argc < 1) {
        fprintf(stderr, "Incorrect usage. Correct usage below:\n"); 
        fprintf(stderr, "./server port_number\n");
        fprintf(stderr, "./server\n");
        exit(1); 
    } else {
        controller = createController(DEFAULT_PORT);
    }
    if (controller->connection != NULL) {
        fprintf(stderr, "Port successfully opened! Listening now...\n");

        signal(SIGINT, quitSignalHandler);

        /* Main accept() loop */
        while (!controller->quit_signal) {
            sin_size = sizeof(struct sockaddr_in);
            if ((new_fd = accept(controller->connection->socket, (struct sockaddr*)&client_addr,
                                &sin_size)) == RETURNED_ERROR) {
                perror("accept");
                continue;
            }
            printf("server: got connection from %s\n",
                inet_ntoa(client_addr.sin_addr));

            controller->new_fd = new_fd;
            /* Create a thread to accept client */
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            pthread_create(&client_thread, &attr, authenticateUser, new_fd);

            pthread_join(client_thread, NULL);
            char* msg[MAXDATASIZE];
            if (recv(new_fd, msg, sizeof(msg), 0) == RETURNED_ERROR) {
                perror("Error accepting option\n");
            } else {
                loadWords();
                gameSetup(controller);
            }

            // if (send(new_fd, "All of array data sent by server\n", 40, 0) == RETURNED_ERROR) {
            //     perror("send");
            // }
        }
        printf("Thread %d has disconnected\n", new_fd);
        close(new_fd);
    }

    
}