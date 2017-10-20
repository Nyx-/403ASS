#ifndef HANGMAN_H
#define HANGMAN_H

#include "_global.h"
#include "controller.h"

typedef struct Hangman {
    int status; 
    char** wordPair;
    char* word_a;
    char* word_b;
    int firstWordLength;
    int secondWordLength;
    int guessesLeft;
    int guessesMade;
    char* guessedLetters;
} Hangman; 

Hangman *createGame(Connection *c);
void setUpGame(Hangman *h, Connection *c);
void *playHangman(Hangman *h, Connection *c);
void *getGuess(Hangman *h, Connection *c);
int appendGuess(char *s, char c);
void** splitWords(Hangman *h, char* wordPair);
char *getWords(Connection *c);
void printWords(char* word1, int w1_len, char* word2, int w2_len);

#endif  // HANGMAN_H