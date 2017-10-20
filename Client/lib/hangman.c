#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <windows.h>
#include <sys/socket.h>

#include "hangman.h"

Hangman *createGame() {
    Hangman *game = malloc(sizeof(Hangman));
    // game->firstWordLength = getFirstWordLength();
    // game->secondWordLength = getSecondWordLength();

    game->status = 1; //game currently ongoing
    // int guessTemp = game->firstWordLength + game->secondWordLength + 10;
    // game->guessesLeft = (guessTemp > 26)? 26: guessTemp;
    // game->guessesMade = 0;

    // //TODO: this is almost definitely wrong.
    // game->guessedLetters = calloc(game->guessesLeft, sizeof(char));

    return game;
}

void *playHangman(Hangman *h, Connection *c) {
    printf("playhangman\n");

    int guessTemp = h->firstWordLength + h->secondWordLength + 10;
    h->guessesLeft = (guessTemp > 26)? 26: guessTemp;

    h->guessedLetters = calloc(h->guessesLeft, sizeof(char));

    // printf("%d\n", h->guessesLeft);
    // printf("%d\n", h->guessesMade);

    // printWords(h);
    while (h->guessesLeft != 0) {
        displayHangman(h);
        getWords(h, c); 
        printWords(h);
        getGuess(h, c);
    }
    // exit(1);
}

void displayHangman(Hangman *h) {
    printf("Guessed letters: %s\n\n", h->guessedLetters);
    printf("Number of guesses left: %d\n\n", h->guessesLeft);
}

void *getGuess(Hangman *h, Connection *con) {
    printf("\n\nEnter your guess - ");
    char c;
    scanf("%c", &c);
    getchar();

    if (c != '\n') {
        if (isalpha(c)) {
            printf("isalpha()\n");
            // appendGuess(h->guessedLetters, c);
            h->guessesLeft = h->guessesLeft - 1;
            send(con->socket, c, sizeof(c), 0);
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

void getWords(Hangman *h, Connection *c) {
    char* buf[MAXDATASIZE], buf2[MAXDATASIZE];
    memset(buf, 0, sizeof(buf));
    memset(buf2, 0, sizeof(buf2));

    if (recv(c->socket, buf, sizeof(buf), 0) == RETURNED_ERROR) {
        perror("[hangman] Error receiving first word");
    } else {
        h->word_a = buf;
        printf("%s\n", h->word_a);
        h->firstWordLength = getWordLength(h->word_a);
        printf("%d\n", h->firstWordLength);
    }

    if (recv(c->socket, buf2, sizeof(buf2), 0) == RETURNED_ERROR) {
        perror("[hangman] Error receiving first word");
    } else {
        h->word_b = buf2;
        printf("%s\n", h->word_b);
        h->secondWordLength = getWordLength(h->word_b);
        printf("%d\n", h->secondWordLength);
    }

    // printWords(h);
}

void printWords(Hangman *h) {
    // printf("%s %s\n", h->word_a, h->word_b);
    printf("Word: ");
    int i, k;
    for (i = 0; i < h->firstWordLength; i++) {
        printf("%c ", h->word_a[i]);
    }
    printf("  ");
    for (k = 0; k < h->secondWordLength; k++) {
        printf("%c ", h->word_b[k]);
    }
    printf("\n");
}

int getWordLength(char* word) {
    return (size_t) strlen(word);
}
