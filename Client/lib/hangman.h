#ifndef HANGMAN_H
#define HANGMAN_H

#include "_global.h"

typedef struct Hangman { 
    int guesses; 
    char* guess_letters; 
    char* word; 
    char* currentWord; 

    char* word1;
    char* word2;
} Hangman; 

Hangman *createGame();
void *PlayHangman(Hangman *h);
char getGuess();
void *checkGuess(Hangman *h, char letter);
void *display(Hangman *h);
void *displayWord(Hangman *h);

#endif  // HANGMAN_H