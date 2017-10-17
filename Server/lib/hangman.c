#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#include "hangman.h"

void gameSetup() {
    printf("setting up game\n");
    Hangman *h = malloc(sizeof(Hangman));

    h->word1 = malloc(10 * sizeof(char));
    h->word2 = malloc(10 * sizeof(char));

    char** randomWords = selectWords();

    printf("Word 1 = %s\n", randomWords[0]);
    printf("Word 2 = %s\n", randomWords[1]);

    h->word1 = randomWords[0];
    h->word2 = randomWords[1];

    printf("Word 1 = %s\n", h->word1);
    printf("Word 2 = %s\n", h->word2);
}

char** selectWords() {
    int num = -1;

    num = rand() % wl.numWords;

    printf("Word 1 = %s\n", wl.words[num]);

    printf("Number: %d\n", num);

    
    return wl.words[num];
}

void createWordList() {
    WordList *wl = malloc(sizeof(WordList));

    wl->words = malloc(0);
    wl->numWords = 0;
}

void loadWords() {
    createWordList();

    FILE *file = fopen("hangman_text.txt", "r");
    const char sep1[2] = ",";
    const char sep2[2] = "\n";
    char buffer[150];
    char* token;
    void** wordPair;

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
        saveWords(wordPair);
    }
}

void saveWords(void *wPair) {
    printf("saving word...%d\n", wl.numWords);
    size_t new = (size_t) wl.numWords + 1;
    void **re_wordList = realloc(wl.words, new * sizeof(char*));

    wl.words = re_wordList;
    wl.words[wl.numWords] = wPair;
    wl.numWords += 1;
}