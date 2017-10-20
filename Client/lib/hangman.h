#ifndef HANGMAN_H
#define HANGMAN_H

#include "_global.h"
#include "controller.h"
#include "connection.h"

typedef struct Connection Connection;
typedef struct Hangman {
    int status; 
    int winCondition;

    char** wordPair;
    char* word_a;
    char* word_b;
    int firstWordLength;
    int secondWordLength;
    
    int guessesLeft;
    int guessesMade;
    char* guessedLetters;
} Hangman; 

Hangman *createGame();
void *playHangman();
int appendGuess(char *s, char c);
void** splitWords(char* wordPair);
char *getWords(Connection *c);
void printWords(char* word1, int w1_len, char* word2, int w2_len);
void endGame(Hangman *h);
void clearGameMemory(Hangman *h);

char* receiveItems(Connection *c);
void sendConfirm(Connection *c);
int receiveInt(Connection *c);



#endif  // HANGMAN_H