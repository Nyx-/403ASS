#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <windows.h>

#include "hangman.h"

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