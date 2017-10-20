#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "lib/_global.h"
#include "lib/controller.h"
#include "lib/menu.h"

int main(int argc, char *argv[]) {
    Controller *controller;

    if (argc == 3) {
        controller = createController(argv[1], argv[2]);
    } else if (argc > 3 || argc < 2) {
        fprintf(stderr, "Incorrect usage. Correct usage below:\n");
        fprintf(stderr, "./client your_ip port_number\n");        
        fprintf(stderr, "./client your_ip\n");
        exit(1);
    } else {
        controller = createController(argv[1], DEFAULT_PORT);
    }
    if (controller->connection != NULL) {

        login(controller);

        int numbytes;
        char* buf[MAXDATASIZE];
        char* loginAuth;

        memset(buf, 0, sizeof(buf));  

        if (recv(controller->connection->socket, buf, MAXDATASIZE, 0) == RETURNED_ERROR) {
            perror("[authentication] Error receiving authentication check");
            exit(1);
        }

        loginAuth = buf;

        if (strcmp(loginAuth, "correct") == 0) {
            //show main game menu
            displayGameMenu(controller);
        } else if (strcmp(loginAuth, "incorrect") == 0) {
            //show exit game message
            invalidConnection();
        } else {
            perror("Server sent something weird");
            exit(1);
        }

    }

    
    /* Receive message back from server */
    // if ((numbytes = recv(controller->connection->socket, buf, MAXDATASIZE, 0)) == RETURNED_ERROR) {
    //     perror("recv");
    //     exit(1);
    // }
    
    // buf[numbytes] = '\0';

    // printf("Received: %s", buf);

    // close(controller->connection->socket);

    // return 0;
}