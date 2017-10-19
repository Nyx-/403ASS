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

void PlayHangman(char *word) {    
    int i = 0;
    // print the word
    for (i = 0; i < strlen(new_game->word); i++) {
        new_game->currentWord[i] = '_';
    }

    display();

    while (new_game->guesses > 0) {
        checkGuess(getGuess());
        //for some reason this repeats twice each time you enter a guess
        display();
    }
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

void checkGuess(char letter) {
    int i;
    char *word1 = new_game->word;
    char *word2 = new_game->word;

    letter = tolower(letter);

    for (i = 0; i < strlen(new_game->word); i++) {
        if (tolower(new_game->word[i]) == letter) {
            new_game->currentWord[i] = letter;
        }
    }
}

void display() {
    printf("Guessed letters: %s\n\n", new_game->guess_letters);
    printf("Number of guesses left: %d\n\n", new_game->guesses);

    displayWord();

}

void displayWord() {
    int i = 0;
    // print the word
    printf("Word: ");
    for (i = 0; i < strlen(new_game->word); i++) {
        printf("%c ", new_game->currentWord[i]);
    }
    printf("\n\n");
}