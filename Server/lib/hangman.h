#ifndef HANGMAN_H
#define HANGMAN_H

#include "controller.h"

typedef struct Hangman {
    int guesses;
    char* guess_letters;
    char** word_pair;
    char* word1;
    char* word2;
} Hangman;

typedef struct WordList {
    void **words;
    volatile int numWords;
} WordList;

void gameSetup();
void **selectWords();
WordList *createWordList();
void loadWords();
void saveWords(void *wPair, WordList *list);

Hangman *h;

#endif  // HANGMAN_H