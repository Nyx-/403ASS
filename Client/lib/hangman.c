#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <windows.h>
#include <sys/socket.h>

#include "hangman.h"

Hangman *createGame(Connection *c) {
    Hangman *game = malloc(sizeof(Hangman));
    game->status = 1; //game currently ongoing

    return game;
}

void *playHangman(Hangman *h, Connection *c) {
    h->wordPair = (char**) splitWords(h, getWords(c));
    h->word_a = h->wordPair[0];
    h->word_b = h->wordPair[1];
    printf("%s, %s\n", h->word_a, h->word_b);

    h->firstWordLength = strlen(h->word_a);
    h->secondWordLength = strlen(h->word_b);

    int guessTemp = h->firstWordLength + h->secondWordLength + 10;
    h->guessesLeft = (guessTemp > 26)? 26: guessTemp;

    h->guessedLetters = calloc(h->guessesLeft + 1, sizeof(char));

    printf("Guessed letters: %s\n\n", h->guessedLetters);
    printf("Number of guesses left: %d\n\n", h->guessesLeft);

    printWords(h->word_a, h->firstWordLength, h->word_b, h->secondWordLength);

    while (h->guessesLeft != 0) {
        getGuess(h, c);
        h->wordPair = (char**) splitWords(h, getWords(c));
        h->word_a = h->wordPair[0];
        h->word_b = h->wordPair[1];
        printf("Guessed letters: %s\n\n", h->guessedLetters);
        printf("Number of guesses left: %d\n\n", h->guessesLeft);
        printWords(h->word_a, h->firstWordLength, h->word_b, h->secondWordLength);
    }
    // exit(1);
}


void *getGuess(Hangman *h, Connection *c) {
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

void** splitWords(Hangman *h, char* wordPair) {
    char *token;
    void** splitPair;
    char *word_1; 
    char *word_2;

    splitPair = malloc(2 * sizeof(char*));
    word_1 = calloc(256, sizeof(char));
    word_2 = calloc(256, sizeof(char));

    token = strtok(wordPair, ",");
    word_1 = token;
    token = strtok(NULL, ",");
    word_2 = token;

    splitPair[0] = word_1;
    splitPair[1] = word_2;
    printf("%s, %s\n", word_1, word_2);

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

