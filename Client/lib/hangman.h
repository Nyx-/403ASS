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

void PlayHangman(char *word);

Hangman *createGame(char *word);
char getGuess();
void checkGuess(char letter);
void display();
void displayWord();

Hangman *new_game;

#endif  // HANGMAN_H