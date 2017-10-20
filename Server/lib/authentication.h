#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "_global.h"

void authenticateUser(int new_fd);
char* checkAuth(char* name, char* pass);

#endif  // AUTHENTICATION_H