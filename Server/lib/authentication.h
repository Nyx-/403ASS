#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "_global.h"

// stuff

typedef struct User {
    char* name;
} User;

void authenticateUser(int new_fd);
char* checkAuth(char* name, char* pass);
// char* strToLower(char* string);

#endif  // AUTHENTICATION_H