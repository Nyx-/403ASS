#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <windows.h>
#include <sys/socket.h>

#include "hangman.h"

Hangman *createGame() {
    Hangman *game = malloc(sizeof(Hangman));
    game->status = 1; //game currently ongoing

    return game;
}

void *playHangman() {
    Hangman *h = controller->hangman;
    Connection *c = controller->connection;

    h->word_a = receiveItems(c);
    sendConfirm(c);
    h->word_b = receiveItems(c);
    sendConfirm(c);
    h->guessedLetters = receiveItems(c);
    sendConfirm(c);
    h->guessesLeft = receiveInt(c);
    sendConfirm(c);

    h->firstWordLength = strlen(h->word_a);
    h->secondWordLength = strlen(h->word_b);

    printf("Guessed letters: %s\n\n", h->guessedLetters);
    printf("Number of guesses left: %d\n\n", h->guessesLeft);
    printWords(h->word_a, h->firstWordLength, h->word_b, h->secondWordLength);
    getGuess(c);
}

char* receiveItems(Connection *c) {
    char* buf = (char*) malloc(sizeof(char) * MAXDATASIZE);
    memset(buf, 0, sizeof(buf));

    if (recv(c->socket, buf, sizeof(buf), 0) == RETURNED_ERROR) {
        perror("[hangman] Error receiving char");
    }

    printf("received\n");

    return buf;
}

int receiveInt(Connection *c) {
    uint16_t buf;

    if (recv(c->socket, &buf, sizeof(uint16_t), 0) == RETURNED_ERROR) {
        perror("[hangman] Error receiving int");
    }

    return ntohs(buf);
}

void sendConfirm(Connection *c) {
    int msg = 1;
    if(send(c->socket, &msg, sizeof(int), 0) == RETURNED_ERROR) {
        perror("[confirmation] Error.");
    }
    printf("sent\n");
}

void *getGuess(Connection *c) {
    Hangman *h = controller->hangman;

    printf("\n\nEnter your guess - ");
    char sendChar[2];
    scanf("%c", sendChar);
    getchar();
    printf("%d\n", c->socket);
    if (sendChar[0] != '\n') {
        printf("isn't empty\n");
        if (isalpha(sendChar[0])) {
            printf("isalpha()\n");
            appendGuess(h->guessedLetters, sendChar[0]);
            h->guessesLeft = h->guessesLeft - 1;
            send(c->socket, sendChar, sizeof(sendChar), 0);
        }
    }
    printf("\n..........................................\n\n\n");
}

int appendGuess(char *s, char c) {
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
    return 0;
}

void** splitWords(char* wordPair) {
    Hangman *h = controller->hangman;

    char *token;
    void** splitPair;
    char *word_1; 
    char *word_2;

    splitPair = malloc(2 * sizeof(char*));
    word_1 = calloc(256, sizeof(char));
    word_2 = calloc(256, sizeof(char));

    token = strtok(wordPair, ",");
    h->word_a = token;
    token = strtok(NULL, ",");
    h->word_b = token;

    splitPair[0] = word_1;
    splitPair[1] = word_2;
    printf("%s, %s\n", h->word_a, h->word_b);

    // h->word_a = word_1;
    // h->word_b = word_2;

    return splitPair;

    // h->word_a = word_1;
    // h->firstWordLength = strlen(h->word_a);
    // h->word_b = word_2;
    // h->secondWordLength = strlen(h->word_b);
    // printf("%s, %s", h->word_a, h->word_b); 
}

char *getWords(Connection *c) {
    char* buf[MAXDATASIZE];
    memset(buf, 0, sizeof(buf));

    char* receivedMessage;

    if (recv(c->socket, buf, sizeof(buf), 0) == RETURNED_ERROR) {
        perror("[hangman] Error receiving first word");
    } else {
        receivedMessage = buf;
        // h->word_a = buf;
        // printf("%s\n", h->word_a);
        // h->firstWordLength = getWordLength(h->word_a);
        // printf("%d\n", h->firstWordLength);
        printf("%s\n", receivedMessage);
        return receivedMessage;
    }
    
    // if (recv(c->socket, buf2, sizeof(buf2), 0) == RETURNED_ERROR) {
    //     perror("[hangman] Error receiving first word");
    // } else {
    //     h->word_b = buf2;
    //     printf("%s\n", h->word_b);
    //     h->secondWordLength = getWordLength(h->word_b);
    //     printf("%d\n", h->secondWordLength);
    // }

    // printWords(h);
}

void printWords(char* word1, int w1_len, char* word2, int w2_len) { 
    // printf("%s, %s", h->word_a, h->word_b);  
    printf("Word: ");
    int i, k;
    for (i = 0; i < w1_len; i++) {
        printf("%c ", word1[i]);
    }
    printf("  ");
    for (k = 0; k < w2_len; k++) {
        printf("%c ", word2[k]);
    }
    printf("\n");
}


void endGame(Hangman *h) {
    h->status = 0;
}

void clearGameMemory(Hangman *h) {
    // free(h->status);
    // free(h->wordPair);
    // free(h->word_a);
    // free(h->word_b);
    // free(h->firstWordLength);
    // free(h->secondWordLength);
    // free(h->guessesLeft);
    // free(h->guessesMade);
    // free(h->guessedLetters);
    free(h);
}