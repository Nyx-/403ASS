#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <windows.h>

#include "hangman.h"

Hangman *createGame() {
    Hangman *game = malloc(sizeof(Hangman));
    char *word = "help";
    
    game->guesses = min(strlen(word) + strlen(word) + 10, 26);
    game->guess_letters = calloc(sizeof(char), (size_t) game->guesses);
    
    game->word = word;
    game->currentWord = malloc(strlen(word));
    return game;
}

void *PlayHangman(Hangman *h) {  
    printf("playhangman");
    exit(1);
}

char getGuess() {
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

void *checkGuess(Hangman *h, char letter) {
    int i;
    char *word1 = h->word;
    char *word2 = h->word;

    letter = tolower(letter);

    for (i = 0; i < strlen(h->word); i++) {
        if (tolower(h->word[i]) == letter) {
            h->currentWord[i] = letter;
        }
    }
}

void *display(Hangman *h) {
    printf("Guessed letters: %s\n\n", h->guess_letters);
    printf("Number of guesses left: %d\n\n", h->guesses);

    displayWord(h);

}

void *displayWord(Hangman *h) {
    int i = 0;
    // print the word
    printf("Word: ");
    for (i = 0; i < strlen(h->word); i++) {
        printf("%c ", h->currentWord[i]);
    }
    printf("\n\n");
}