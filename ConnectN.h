#include <stdio.h>
#include <stdlib.h>
#include "colors.h"

/**
 * @brief Function for the user to choose what to do when openning the game with entry check.
 * 
 * @return int The choice of the user. 1 for "New Game", 2 for "Continue last saved game" and 3 for "Quit".
 */
int startGame();

/**
 * @brief Functions that clears the command prompt supporting both Windows and Linux OS.
 * 
 */
void clear();