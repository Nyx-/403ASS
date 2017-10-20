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
    h->status = 1; //game currently ongoing

    h->word_pair = (char **) selectWords();
    h->word1 = h->word_pair[0];
    h->word2 = h->word_pair[1];

    printf("Word 1 = %s\n", h->word1);
    printf("Word 1 size = %d\n", strlen(h->word1));
    printf("Word 2 = %s\n", h->word2);
    printf("Word 2 size = %d\n", strlen(h->word2));

    h->word1_len = strlen(h->word1);
    h->word2_len = strlen(h->word2);

    int guessTemp = 0;
    guessTemp = h->word1_len + h->word2_len + 10;
    h->guesses = (guessTemp > 26)? 26: guessTemp;
    h->guess_letters = calloc(h->guesses + 1, sizeof(char));

    printf("Guesses %d\n", h->guesses);

    //not sure if this is necessary
    h->client_word1 = calloc(h->word1_len + 1, sizeof(char));
    h->client_word2 = calloc(h->word1_len + 1, sizeof(char));

    char charac1 = '0';
    char charac2 = 'a';

    prepareWord(h, charac1);

    // char *sendingString = malloc(strlen(h->word1_len) + strlen(h->word2_len) + 1);
    // if (sendingString) {
    //     strcpy(sendingString, h->client_word1);
    //     strcat(sendingString, ",");
    //     strcat(sendingString, h->client_word2);
    // }
    
    // printf("%s\n", &sendingString);

    // prepareWord(h, charac2);

    // printf("client 1: %s\n", h->client_word1);
    // printf("client 2: %s\n", h->client_word2);
    // printf("guesses: %s\n", h->guess_letters);

    send(controller->new_fd, h->client_word1, (size_t) h->word1_len * sizeof(char), 0);
    send(controller->new_fd, h->client_word2, (size_t) h->word2_len * sizeof(char), 0);
    // send(controller->new_fd, sendingString, sizeof(sendingString), 0);

    listenForGuess(h);
}

void listenForGuess(Hangman *h) {
    while(h->status) {
        char* msg[MAXDATASIZE];
        if (recv(controller->new_fd, msg, sizeof(msg), 0) == RETURNED_ERROR) {
            //check if its a valid guess?
            h->c_guessed = msg;
            prepareWord(h, h->c_guessed);
            //send the prepared words to the client
        }
    }
}

void prepareWord(Hangman *h, char letter) {
    int w1_len, w2_len;
    w1_len = h->word1_len;
    w2_len = h->word2_len;
    
    size_t i, k;
    //if no letter was chosen AKA client hasn't guessed
    if (letter == '0') {
        for (i = 0; i < w1_len; i++) {
            h->client_word1[i] = '_';
        }
        for (k = 0; k < w2_len; k++) {
            h->client_word2[k] = '_';
        }
    } else {
        for (i = 0; i < w1_len; i++) {
            printf("%c\n", h->word1[i]);
            if (h->word1[i] == letter) {
                h->client_word1[i] = letter;
            } else {
                h->client_word1[i] = '_';
            }
        }
        for (k = 0; k < w2_len; k++) {
            printf("%c\n", h->word2[k]);
            if (h->word2[k] == letter) {
                h->client_word2[k] = letter;
            } else {
                h->client_word2[k] = '_';
            }
        }
        appendGuess(h->guess_letters, letter);
    }

}

int appendGuess(char *s, char c) {
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
    return 0;
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