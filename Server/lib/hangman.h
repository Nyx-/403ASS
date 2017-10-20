#ifndef HANGMAN_H
#define HANGMAN_H

#include "controller.h"

typedef struct Hangman {
    int status;
    int guesses;
    char* guess_letters;
    char c_guessed;
    char** word_pair;
    char* word1;
    int word1_len;
    char* client_word1;
    char* word2;
    int word2_len;
    char* client_word2;
} Hangman;

typedef struct WordList {
    void **words;
    volatile int numWords;
} WordList;

void gameSetup();
void listenForGuess(Hangman *h);
void prepareWord(Hangman *h, char letter);
int appendGuess(char *s, char c);
void **selectWords();
WordList *createWordList();
void loadWords();
void saveWords(void *wPair, WordList *list);
void endGame(Hangman *h);

Hangman *h;

#endif  // HANGMAN_H