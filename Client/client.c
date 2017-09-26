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
    int sock_fd, numbytes, i = 0;
    char buf[MAXDATASIZE];
    struct hostent *he;
    struct sockaddr_in serv_addr; /* connector's address information */

    if (argc != 3) {
        fprintf(stderr, "usage: client_hostname port_number\n");
        exit(1);
    }

    if ((he = gethostbyname(argv[1])) == NULL) { /* get the host info */
        herror("gethostbyname");
        exit(1);
    }

    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;            /* host byte order */
    serv_addr.sin_port = htons(atoi(argv[2])); /* short, network byte order */
    serv_addr.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(serv_addr.sin_zero), 8); /* zero the rest of the struct */

    if (connect(sock_fd, (struct sockaddr *)&serv_addr,
                sizeof(struct sockaddr)) == -1) {
        perror("connect");
        exit(1);
    }

    /* Receive data from server */
    Receive_Array_Int_Data(sock_fd, STRING_SIZE);

    /* Receive message back from server */
    if ((numbytes = recv(sock_fd, buf, MAXDATASIZE, 0)) == -1) {
        perror("recv");
        exit(1);
    }

    buf[numbytes] = '\0';

    printf("Received: %s", buf);

    close(sock_fd);

    return 0;
}