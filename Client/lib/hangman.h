#ifndef HANGMAN_H
#define HANGMAN_H

#include "_global.h"
#include "controller.h"

typedef struct Hangman {
    int status; 
    char* word_a;
    char* word_b;
    int firstWordLength;
    int secondWordLength;
    int guessesLeft;
    int guessesMade;
    char* guessedLetters;
} Hangman; 

Hangman *createGame();
void setUpGame(Hangman *h, Connection *c);
void *playHangman(Hangman *h, Connection *c);
void displayHangman(Hangman *h);
void printWords(Hangman *h);
void *getGuess(Hangman *h, Connection *c);
int appendGuess(char *s, char c);
void getWords(Hangman *h, Connection *c);
void *checkGuess(Hangman *h, char letter);
void *display(Hangman *h);
void *displayWord(Hangman *h);
int getWordLength(char* word);

#endif  // HANGMAN_H