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

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Incorrect parameters\n");
        fprintf(stderr, "Usage: client_ip port_number\n");
        exit(1);
    } else {
        controller = createController(argv);
        if (controller->connection != NULL) {
            fprintf(stderr, "hey you made it, this must mean connection is established\n");
            //initialise controller->connection->thread
                //in the initialise thingo, check for if it fails to start the thread, and throw error.
            //game initialise
        }
    }
    
    /* Receive data from server */
    Receive_Array_Int_Data(controller->connection->socket, STRING_SIZE);

    int numbytes;
    char buf[MAXDATASIZE];
    
    /* Receive message back from server */
    if ((numbytes = recv(controller->connection->socket, buf, MAXDATASIZE, 0)) == -1) {
        perror("recv");
        exit(1);
    }
    
    buf[numbytes] = '\0';

    printf("Received: %s", buf);

    close(controller->connection->socket);

    return 0;
}