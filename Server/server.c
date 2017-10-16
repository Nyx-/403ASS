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
#include "lib/controller.h"
#include "lib/connection.h"

int main(int argc, char* argv[]) {
    /* Thread attributes here */
    pthread_t client_thread;
    pthread_attr_t attr;

    int new_fd; /* listen on sock_fd, new connection on new_fd */
    struct sockaddr_in client_addr; /* Client address info */
    socklen_t sin_size;
    int i = 0;

    /* Get port number for server to listen on */
    if (argc != 2) {
        fprintf(stderr, "usage: client port_number\n");
        exit(1);
    } else {
        controller = createController(argv[1]);
        if (controller->connection != NULL) {
            fprintf(stderr, "Something happened correctly woo!\n");

            /* Main accept() loop */
            while (1) {
                sin_size = sizeof(struct sockaddr_in);
                if ((new_fd = accept(controller->connection->socket, (struct sockaddr*)&client_addr,
                                    &sin_size)) == -1) {
                    perror("accept");
                    continue;
                }
                printf("server: got connection from %s\n",
                    inet_ntoa(client_addr.sin_addr));

                /* Create a thread to accept client */
                pthread_attr_t attr;
                pthread_attr_init(&attr);
                pthread_create(&client_thread, &attr, receiveData, new_fd);

                pthread_join(client_thread, NULL);

                if (send(new_fd, "All of array data sent by server\n", 40, 0) == -1) {
                    perror("send");
                }
            }
            close(new_fd);
        }
    }

    
}