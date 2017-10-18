#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>

#include "hangman.h"

void gameSetup() {
    printf("setting up game\n");
    Hangman *h = malloc(sizeof(Hangman));

    h->word_pair = (char **) selectWords();
    h->word1 = h->word_pair[0];
    h->word2 = h->word_pair[1];

    printf("Word 1 = %s\n", h->word_pair[0]);
    printf("Word 1 len = %d\n", (int)strlen(h->word_pair[0]));

    printf("Word 2 = %s\n", h->word_pair[1]);
    printf("Word 2 len = %d\n", (int)strlen(h->word_pair[1]));

    printf("Word 1 = %s\n", h->word1);
    printf("Word 2 = %s\n", h->word2);
}

void **selectWords() {
    int num = -1;

    num = rand() % controller->c_wordList->numWords;

    printf("Word 1 = %s\n", controller->c_wordList->words[num]);

    printf("Number: %d\n", num);

    
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
    const char sep1[2] = ",";
    const char sep2[2] = "\n";
    char buffer[150];
    char *token;
    void **wordPair;

    if (file == NULL) {
        perror("Unable to read Hangman file");
        exit(1);
    }

    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        int numWords = 2;
        wordPair = malloc(2 * sizeof(char*));

        token = strtok(buffer, sep1); //word 1
        wordPair[0] = token;
        printf("%s\n", wordPair[0]);
        while(numWords > 1) {
            token = strtok(NULL, sep2); //word 2
            wordPair[1] = token;
            printf("%s\n", wordPair[1]);
            numWords--;
        }
        
        printf("%s,%s\n", wordPair[0], wordPair[1]);
        saveWords(wordPair, controller->c_wordList);
    }
}

void saveWords(void *wPair, WordList *list) {
    printf("saving word...%d\n", list->numWords);
    size_t size = (size_t) list->numWords + 1;
    size_t char_size = (size_t) (2 * sizeof(char*));
    void **re_wordList = realloc(list->words, size * char_size);

    list->words = re_wordList;
    list->words[list->numWords] = wPair;
    list->numWords += 1;
    
}