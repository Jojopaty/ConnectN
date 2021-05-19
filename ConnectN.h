#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <colors.h>

typedef struct
{
    int lin;
    int col;
    char **grille;

} GRID;

/**
 * @brief Function for the user to choose what to do when openning the game with entry check.
 * 
 * @return int The choice of the user. 1 for "New Game", 2 for "Continue last saved game" and 3 for "Quit".
 */
int startGame();

/**
 * @brief Create a And Initialize Grid object
 * 
 * @param newGrid 
 * @param align 
 * @return GRID* 
 */
GRID *createAndInitializeGrid(GRID *newGrid, int* align);

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
void showGrid(GRID *grid);

/**
 * @brief 
 * 
 * @param grid 
 * @param num 
 */
void freeMemory(GRID *grid, int *num);

/**
 * @brief 
 * 
 * @param round 
 * @return int 
 */
int moveChoice(int round);

/**
 * @brief Function for adding a token to the initialized grid
 * 
 * @param grid The grid to add the token to.
 * @param col The column to add the token to if possible
 * @param token The type of token to add (O for yellow and X for red)
 * @return int Either 1 if adding succedded or 0 if not.
 */
int addToken(GRID *grid, int col, char token);

// int re

/**
 * @brief Function saving the current grid to a .bin file
 * 
 * @param grid The grid to save
 */
void saveToFile(GRID *grid);

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