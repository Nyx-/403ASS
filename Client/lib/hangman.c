#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <windows.h>

#include "hangman.h"

Hangman *createGame(char *word) {
    Hangman *game = malloc(sizeof(Hangman));
    
    game->guesses = min(strlen(word) + strlen(word) + 10, 26);
    game->guess_letters = calloc(sizeof(char), (size_t) game->guesses);
    
    game->word = word;
    game->currentWord = malloc(strlen(word));
}

void PlayHangman() {    
    printf("Guessed letters: \n\n");
    printf("Number of guesses left: %d\n\n", new_game->guesses);

    int i = 0;
    // print the word
    for (i = 0; i < strlen(new_game->word); i++) {
        new_game->currentWord[i] = '_';
        printf("%c ", new_game->currentWord[i]);
    }
    while (1) {
        GetGuess();
        //for some reason this repeats twice each time you enter a guess
    }
}

char GetGuess() {
    printf("\n\nEnter your guess - ");
    char c;
    scanf("%c", &c);
        if (c != '\n') {
            if (isalpha(c)) {
                printf("TESTING\n");
                return c;
            }
        }
}