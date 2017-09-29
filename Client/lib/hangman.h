#ifndef HANGMAN_H
#define HANGMAN_H

#include "_global.h"

typedef struct Hangman {
    int guesses;
    char *guess_letters;
    char *word;
    char *currentWord;
} Hangman;

Hangman *createGame(char *word);
void PlayHangman();
char GetGuess();

Hangman *new_game;

#endif  // HANGMAN_H