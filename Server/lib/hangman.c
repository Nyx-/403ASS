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
    h->guess_letters[0] = ' ';

    printf("Guesses %d\n", h->guesses);

    h->client_word1 = malloc(h->word1_len * sizeof(char) + 1);
    h->client_word2 = malloc(h->word2_len * sizeof(char) + 1);
    for (int i=0; i < h->word1_len; i++) {
        h->client_word1[i] = ' ';
    }
    for (int k=0; k < h->word2_len; k++) {
        h->client_word2[k] = ' ';
    }

    char charac1 = '_';
    char charac2 = 'a';

    prepareWord(h, charac1);

    printf("client 1: %s\n", h->client_word1);
    printf("client 2: %s\n", h->client_word2);

    // char* sendWords = (char*) malloc(3 + h->word1_len + h->word2_len);
    

    // strcpy(sendWords, h->client_word1);
    // strcat(sendWords, ",");
    // strcat(sendWords, h->client_word2);

    // send(controller->new_fd, sendWord1, strlen(sendWord1), 0);
    // send(controller->new_fd, sendWord2, strlen(sendWord2), 0);

    sendToClient(h->client_word1, h->client_word2, h->guess_letters, h->guesses);

    while(h->status == 1) {
        printf("Listening\n");
        listenForGuess(h);
    }

    
}

void sendToClient(char* word1, char* word2, char* guess_chars, int guesses) {
    uint16_t num = htons(guesses);

    //send first word
    send(controller->new_fd, word1, (size_t) strlen(word1), 0);
    printf("sent\n");
    confirmRecv();
    //send second word
    send(controller->new_fd, word2, (size_t) strlen(word2), 0);
    printf("sent\n");
    confirmRecv();
    //send letters guessed
    send(controller->new_fd, guess_chars, (size_t) strlen(guess_chars), 0);
    printf("sent\n");
    confirmRecv();
    //send guesses remaining
    send(controller->new_fd, &num, sizeof(uint16_t), 0);
    printf("sent\n");
    confirmRecv();
}

void confirmRecv() {
    int msg;
    if(recv(controller->new_fd, &msg, sizeof(int), 0) == RETURNED_ERROR) {
        perror("[confirmation] Error.");
    }
}

void listenForGuess(Hangman *h) {
    char* msg[MAXDATASIZE];
    memset(msg, 0, sizeof(msg));
    if (recv(controller->new_fd, msg, sizeof(msg), 0) == RETURNED_ERROR) {
        perror("[listenForGuess] Error receiving character guess");
    } else {
        //check if its a valid guess?
        printf("received a thing \n");
        h->c_guessed = msg[0];
        prepareWord(h, h->c_guessed);
        //send the prepared words to the client
    }
}

void prepareWord(Hangman *h, char letter) {
    int w1_len, w2_len;
    w1_len = h->word1_len;
    w2_len = h->word2_len;
    
    int i, k;
    //if no letter was chosen AKA client hasn't guessed
    if (letter == '_') {
        for (i = 0; i < w1_len; i++) {
            h->client_word1[i] = '_';
        }
        for (k = 0; k < w2_len; k++) {
            h->client_word2[k] = '_';
        }
    } else {
        for (i = 0; i < w1_len; i++) {
            
            if (h->word1[i] == letter) {
                h->client_word1[i] = letter;
            } else {
                h->client_word1[i] = '_';
            }
        }
        h->client_word1[w1_len + 1] = '\0';
        for (k = 0; k < w2_len; k++) {
            
            if (h->word2[k] == letter) {
                h->client_word2[k] = letter;
            } else {
                h->client_word2[k] = '_';
            }
        }
        h->client_word1[w2_len + 1] = '\0';
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
        joinedWords = calloc(500, sizeof(char));
        word_1 = calloc(256, sizeof(char));
        word_2 = calloc(256, sizeof(char));

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

void endGame(Hangman *h) {
    h->status = 0;
    clearGameMemory(h);
}

void clearGameMemory(Hangman *h) {
    free(h->status);
    free(h->guesses);
    free(h->guess_letters);
    free(h->c_guessed);
    free(h->word_pair);
    free(h->word1);
    free(h->word1_len);
    free(h->client_word1);
    free(h->word2);
    free(h->word2_len);
    free(h->client_word2);
    free(h);
}