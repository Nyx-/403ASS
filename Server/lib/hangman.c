#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include <time.h>
#include <sys/socket.h>

#include "hangman.h"

void gameSetup() {
    printf("Setting up game\n");
    Hangman *h = malloc(sizeof(Hangman));

    h->word_pair = (char **) selectWords();
    h->word1 = h->word_pair[0];
    h->word2 = h->word_pair[1];

    printf("Word 1 = %s\n", h->word1);
    printf("Word 1 size = %d\n", strlen(h->word1));
    printf("Word 2 = %s\n", h->word2);
    printf("Word 2 size = %d\n", strlen(h->word2));

    h->word1_len = strlen(h->word1);
    h->word2_len = strlen(h->word2);

    //not sure if this is necessary
    h->client_word1 = malloc((size_t) h->word1_len * sizeof(char));
    h->client_word2 = malloc((size_t) h->word1_len * sizeof(char));

    h->client_word1 = h->word1;
    h->client_word2 = h->word2;
    prepareWord(h, "0");

    // char *sendingString = malloc(strlen(h->word1_len) + strlen(h->word2_len) + 1);
    // if (sendingString) {
    //     strcpy(sendingString, h->client_word1);
    //     strcat(sendingString, ",");
    //     strcat(sendingString, h->client_word2);
    // }
    
    // printf("%s\n", &sendingString);

    send(controller->new_fd, h->client_word1, sizeof(h->client_word1), 0);
    send(controller->new_fd, h->client_word2, sizeof(h->client_word2), 0);
    // send(controller->new_fd, sendingString, sizeof(sendingString), 0);
    
    
    //This was here for testing, I moved it to the client
    // int i, k;

    // for (i = 0; i < strlen(h->word1); i++) {
    //     printf("%c ", h->client_word1[i]);
    // }
    // printf("  ");
    // for (k = 0; k < strlen(h->word2); k++) {
    //     printf("%c ", h->client_word2[k]);
    // }
    // printf("\n");
}

void prepareWord(Hangman *h, char *letter) {
    int w1_len, w2_len;
    w1_len = (int) strlen(h->word1);
    w2_len = (int) strlen(h->word2);
    
    int i, k;
    //if no letter was chosen AKA client hasn't guessed
    if (strcmp(letter, "0") == 0) {
        for (i = 0; i < w1_len; i++) {
            h->client_word1[i] = '_';
        }
        for (k = 0; k < w2_len; k++) {
            h->client_word2[k] = '_';
        }
    }

}

void **selectWords() {
    int num = -1;
    // LOL, hopefully a little more random than the plain old 'srand(time(NULL))', but still speedy.
    srand((unsigned int)time(NULL));
    srand(rand());
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