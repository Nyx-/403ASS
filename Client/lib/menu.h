#ifndef MENU_H
#define MENU_H

#include "_global.h"
#include "hangman.h"

void *displayGameMenu(Hangman *game);
void displayGameTitle();
void displayGameOptions();
void *makeSelection(Hangman *game); 

#endif  // MENU_H