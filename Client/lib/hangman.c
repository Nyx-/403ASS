#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <windows.h>

#include "hangman.h"

Hangman *createGame() {
    Hangman *game = malloc(sizeof(Hangman));
    game->firstWordLength = getFirstWordLength();
    game->secondWordLength = getSecondWordLength();

    game->guessesLeft = min(game->firstWordLength + game->secondWordLength + 10, 26);
    game->guessesMade = 0;

    //TODO: this is almost definitely wrong.
    game->guessedLetters = malloc((game->firstWordLength + game->secondWordLength) * sizeof(char*));

    return game;
}

void *playHangman(Hangman *h) {  
    printf("playhangman\n");
    printf("%d\n", h->firstWordLength);
    printf("%d\n", h->secondWordLength);
    printf("%d\n", h->guessesLeft);
    printf("%d\n", h->guessesMade);
    
    getGuess(h);
    exit(1);
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

int getFirstWordLength() {
    //TODO: Get word length from server
    return 5;
}

int getSecondWordLength() {
    //TODO: Get word length from server
    return 5;
}