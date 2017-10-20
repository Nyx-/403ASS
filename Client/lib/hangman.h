#ifndef HANGMAN_H
#define HANGMAN_H

#include "_global.h"
#include "controller.h"

typedef struct Hangman { 
    char* word_a;
    char* word_b;
    int firstWordLength;
    int secondWordLength;
    int guessesLeft;
    int guessesMade;
    char* guessedLetters;
} Hangman; 

Hangman *createGame();
void *playHangman(Hangman *h, Connection *c);
void printWords(Hangman *h);
void *getGuess(Hangman *h);
void getWords(Hangman *h, Connection *c);
void *checkGuess(Hangman *h, char letter);
void *display(Hangman *h);
void *displayWord(Hangman *h);
int getFirstWordLength(Hangman *h);
int getSecondWordLength(Hangman *h);

#endif  // HANGMAN_H