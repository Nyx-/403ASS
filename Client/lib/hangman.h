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

#endif  // HANGMAN_H