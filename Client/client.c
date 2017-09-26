#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <windows.h>

#include "lib/_global.h"

void PlayHangman(char *word) {
    int guesses = min(strlen(word) + strlen(word) + 10, 26);
    char *guessedLetters = malloc(guesses);
    char *currentWord = malloc(strlen(word));

    printf("Guessed letters: \n\n");
    printf("Number of guesses left: %d\n\n", guesses);

    int i = 0;
    // print the word
    for (i = 0; i < strlen(word); i++) {
        currentWord[i] = '_';
        printf("%c ", currentWord[i]);
    }
    printf("\n\nEnter your guess - ");

    // while there are still guesses available
    char c;
    while (1) {
        scanf("%c", &c);
        if (c != '\n') {
            if (isalpha(c)) {
                printf("TESTING\n");
            }
        }
    }
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