#ifndef HANGMAN_H
#define HANGMAN_H

// stuff

typedef struct Hangman {
    int guesses;
    char* guess_letters;
    char* word1;
    char* word2;
} Hangman;

typedef struct WordList {
    void **words;
    int numWords;
} WordList;

void gameSetup();
char** selectWords();
void createWordList();
void loadWords();
void saveWords(void *wPair);

Hangman *h;
//if this wl is set to a point and i change '.' to '->' it breaks everything & segfaults ¯\_(ツ)_/¯
WordList wl;

#endif  // HANGMAN_H