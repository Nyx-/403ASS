#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>

#include "hangman.h"

void gameSetup() {
    printf("Setting up game\n");
    Hangman *h = malloc(sizeof(Hangman));

    h->word_pair = (char **) selectWords();
    h->word1 = h->word_pair[0];
    h->word2 = h->word_pair[1];

    printf("Word 1 = %s\n", h->word1);
    printf("Word 2 = %s\n", h->word2);
}

void **selectWords() {
    int num = -1;
    //Need to do something here cause the same number pops up each time
    num = rand() % controller->c_wordList->numWords;
    printf("Word number: %d\n", num);

    return controller->c_wordList->words[num];
}

WordList *createWordList() {
    WordList *wl = malloc(sizeof(WordList));

    wl->words = malloc(0);
    wl->numWords = 0;

    return wl;
}

void loadWords() {
    FILE *file = fopen("hangman_text.txt", "r");
    const char sep1[1] = ",";
    const char sep2[2] = "\n";
    char buffer[150];
    char *token;
    void **wordPair;
    char *joinedWords;
    char *word_1; 
    char *word_2;

    if (file == NULL) {
        perror("Unable to read Hangman file");
        exit(1);
    }

    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        // int numWords = 2;
        wordPair = malloc(2 * sizeof(char*));
        joinedWords = malloc(256 * sizeof(char));
        word_1 = malloc(256 * sizeof(char));
        word_2 = malloc(256 * sizeof(char));

        sscanf(buffer, "%s", joinedWords);

        token = strtok(joinedWords, sep1);
        word_1 = token;
        token = strtok(NULL, sep1);
        word_2 = token;

        wordPair[0] = word_1;
        wordPair[1] = word_2;

        controller->c_wordList->numWords += 1;
        saveWords(wordPair, controller->c_wordList);
    }
}

void saveWords(void *wPair, WordList *list) {
    size_t size = (size_t) list->numWords;
    size_t char_size = (size_t) (2 * sizeof(char*));
    void **re_wordList = realloc(list->words, size * char_size);

    list->words = re_wordList;
    list->words[list->numWords - 1] = wPair;
}