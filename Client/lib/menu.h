#ifndef MENU_H
#define MENU_H

#include "_global.h"
#include "controller.h"
#include "hangman.h"
#include "leaderboard.h"

typedef struct Controller Controller;
typedef struct Hangman Hangman;

void *displayGameMenu(Controller *c);
void displayGameTitle();
void displayGameOptions();
void *makeSelection(Controller *c); 

#endif  // MENU_H