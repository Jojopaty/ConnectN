#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"

#if defined(_WIN64) || defined(_WIN32)
#include <locale.h>
#endif


typedef struct
{
    int lin;
    int col;
    char** grille;

}GRID;

/**
 * @brief Function for the user to choose what to do when openning the game with entry check.
 * 
 * @return int The choice of the user. 1 for "New Game", 2 for "Continue last saved game" and 3 for "Quit".
 */
int startGame();

/**
 * @brief Create a And Initialize Grid object
 * 
 * @return GRID 
 */
GRID *createAndInitializeGrid(GRID* newGrid);

/**
 * @brief Initalizing the grid with '_' characters for empty slots.
 * 
 * @param newGrid The grid to work with.
 * @return GRID* An initialized version of the grid
 */
GRID *initializeGrid(GRID *newGrid);

/**
 * @brief Function for printing the grid of characters.
 * 
 * @param grid The grid to print.
 */
void printGrid(GRID *grid);

/**
 * @brief 
 * 
 * @param grid 
 */
void freeMemory(GRID *grid);

/**
 * @brief Functions that clears the command prompt supporting both Windows and Linux OS.
 * 
 */
void clear();

/**
 * @brief Funtion that checks the input of an integer
 * 
 * @return int The desired integer or -INT_MAX if not valid
 */
int safeIntInput();