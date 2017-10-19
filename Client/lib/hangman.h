#ifndef HANGMAN_H
#define HANGMAN_H

#include "_global.h"

typedef struct Hangman { 
    int firstWordLength;
    int secondWordLength;
    int guessesLeft;
    int guessesMade;
    char* guessedLetters;
} Hangman; 

Hangman *createGame();
void *playHangman(Hangman *h);
void *getGuess(Hangman *h);
void *checkGuess(Hangman *h, char letter);
void *display(Hangman *h);
void *displayWord(Hangman *h);
int getFirstWordLength();
int getSecondWordLength();

#endif  // HANGMAN_H