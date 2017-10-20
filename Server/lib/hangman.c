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

    h->word1_len = strlen(h->word1);
    h->word2_len = strlen(h->word2);

    int guessTemp = 0;
    guessTemp = h->word1_len + h->word2_len + 10;
    h->guesses = (guessTemp > 26)? 26: guessTemp;
    h->guess_letters = calloc(h->guesses + 1, sizeof(char));
    h->guess_letters[0] = ' ';

    h->client_word1 = malloc(h->word1_len * sizeof(char) + 1);
    h->client_word2 = malloc(h->word2_len * sizeof(char) + 1);
    for (int i=0; i < h->word1_len; i++) {
        h->client_word1[i] = ' ';
    }
    for (int k=0; k < h->word2_len; k++) {
        h->client_word2[k] = ' ';
    }

    char charac1 = '_';

    h->client_word1 = prepareWord(h, h->client_word1, h->word1, charac1);
    h->client_word2 = prepareWord(h, h->client_word2, h->word2, charac1);

    while(h->status) {
        sendToClient(h->client_word1, h->client_word2, h->guess_letters, h->guesses);
        printf("Listening\n");

        char* msg[MAXDATASIZE];
        memset(msg, 0, sizeof(msg));
        if (recv(controller->new_fd, msg, sizeof(msg), 0) == RETURNED_ERROR) {
            perror("[listenForGuess] Error receiving character guess");
            exit(1);
        }
        appendGuess(h->guess_letters, (char*) msg[0]);
        h->client_word1 = prepareWord(h, h->client_word1, h->word1, (char*) msg[0]);
        h->client_word2 = prepareWord(h, h->client_word2, h->word2, (char*) msg[0]);

        h->guesses = h->guesses - 1;

        //Check win condition
    }

    
}

void sendToClient(char* word1, char* word2, char* guess_chars, int guesses) {
    uint16_t num = htons(guesses);
    //send first word
    send(controller->new_fd, word1, strlen(word1), 0);
    confirmRecv();
    //send second word
    send(controller->new_fd, word2, strlen(word2), 0);
    confirmRecv();
    //send letters guessed
    send(controller->new_fd, guess_chars, strlen(guess_chars), 0);
    confirmRecv();
    //send guesses remaining
    send(controller->new_fd, &num, sizeof(uint16_t), 0);
    confirmRecv();
}

void confirmRecv() {
    int msg;
    if(recv(controller->new_fd, &msg, sizeof(int), 0) == RETURNED_ERROR) {
        perror("[confirmation] Error.");
    }
}

char* prepareWord(Hangman *h, char* word, char* matchWord, char letter) {
    int len;
    len = strlen(word);

    int i, k;
    //if no letter was chosen AKA client hasn't guessed
    if (letter == '_') {
        for (i = 0; i < len; i++) {
            word[i] = '_';
        }
    } else {
        for (i = 0; i < len; i++) {
            if (matchWord[i] == letter) {
                word[i] = letter;
            }
        }
    }

    return word;

}

int appendGuess(char *s, char c) {
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
    return 0;
}

void **selectWords() {
    int num = -1;
    srand((unsigned int)time(NULL));
    srand(rand());
    num = rand() % controller->c_wordList->numWords;

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
    free(h->winCondition);
    free(h->guesses);
    free(h->guess_letters);
    free(h->word_pair);
    free(h->word1);
    free(h->word1_len);
    free(h->client_word1);
    free(h->word2);
    free(h->word2_len);
    free(h->client_word2);
    free(h);
}