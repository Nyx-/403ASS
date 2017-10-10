#ifndef HANGMAN_H
#define HANGMAN_H

#include "_global.h"

typedef struct Hangman { 
    int guesses; 
    char *guess_letters; 
    char *word; 
    char *currentWord; 
} Hangman; 

void PlayHangman(char *word);

#endif  // HANGMAN_H