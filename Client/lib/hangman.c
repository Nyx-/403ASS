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
    game->guessesLeft = min(game->firstWordLength + game->secondWordLength + 10, 26);
    game->guessesMade = 0;

    //TODO: this is almost definitely wrong.
    game->guessedLetters = malloc((game->firstWordLength + game->secondWordLength) * sizeof(char*));

    return game;
}

void *playHangman(Hangman *h, Connection *c) {
    getWords(h, c); 
    printf("playhangman\n");
    // printf("%d\n", h->firstWordLength);
    // printf("%d\n", h->secondWordLength);
    printf("%d\n", h->guessesLeft);
    printf("%d\n", h->guessesMade);

    printWords(h);
    
    getGuess(h);
    // exit(1);
}

void *getGuess(Hangman *h) {
    printf("\n\nEnter your guess - ");
    char c;
    scanf("%c", &c);

    if (c != '\n') {
        if (isalpha(c)) {
            printf("isalpha()\n");
            printf("somehow add to h->guessedLetters\n");
        }
    }
}

void getWords(Hangman *h, Connection *c) {
    char* buf[MAXDATASIZE], buf2[MAXDATASIZE];

    if (recv(c->socket, buf, MAXDATASIZE, 0) == RETURNED_ERROR) {
        perror("[hangman] Error receiving first word");
    } else {
        h->word_a = buf;
        printf("%s\n", h->word_a);
        h->firstWordLength = getFirstWordLength(h);
        printf("%d\n", h->firstWordLength);
    }

    if (recv(c->socket, buf2, MAXDATASIZE, 0) == RETURNED_ERROR) {
        perror("[hangman] Error receiving first word");
    } else {
        h->word_b = buf2;
        printf("%s\n", h->word_b);
        h->secondWordLength = getSecondWordLength(h);
        printf("%d\n", h->secondWordLength);
    }
    // if (recv(c->socket, buf2, MAXDATASIZE, 0) == RETURNED_ERROR) {
    //     h->word_a = buf;
    //     printf("%s\n", h->word_a);
    //     h->firstWordLength = getFirstWordLength(h);
    //     printf("%d\n", h->firstWordLength);
    // }
}

void printWords(Hangman *h) {
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

// void *checkGuess(Hangman *h, char letter) {
//     int i;
//     char *word1 = h->word;
//     char *word2 = h->word;

//     letter = tolower(letter);

//     for (i = 0; i < strlen(h->word); i++) {
//         if (tolower(h->word[i]) == letter) {
//             h->currentWord[i] = letter;
//         }
//     }
// }

// void *display(Hangman *h) {
//     printf("Guessed letters: %s\n\n", h->guess_letters);
//     printf("Number of guesses left: %d\n\n", h->guesses);

//     displayWord(h);

// }

// void *displayWord(Hangman *h) {
//     int i = 0;
//     // print the word
//     printf("Word: ");
//     for (i = 0; i < strlen(h->word); i++) {
//         printf("%c ", h->currentWord[i]);
//     }
//     printf("\n\n");
// }

int getFirstWordLength(Hangman *h) {
    //TODO: Get word length from server
    // return 5;
    return (int) strlen(h->word_a);
}

int getSecondWordLength(Hangman *h) {
    //TODO: Get word length from server
    // return 5;
    return (int) strlen(h->word_b);
}