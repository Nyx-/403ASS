#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "_global.h"

void authenticateUser(int new_fd);
char* checkAuth(char* name, char* pass);
// char* strToLower(char* string);

#endif  // AUTHENTICATION_H