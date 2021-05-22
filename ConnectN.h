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
    int tokenNumber;
} gridClass;

typedef struct
{
    int posLin;
    int posCol;
    char type;
} tokenClass;

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
gridClass *createAndInitializeGrid(gridClass *newGrid, int *align);

/**
 * @brief Initalizing the grid with '_' characters for empty slots.
 * 
 * @param newGrid The grid to work with.
 * @return GRID* An initialized version of the grid
 */
gridClass *initializeGrid(gridClass *newGrid);

/**
 * @brief Function for printing the grid of characters.
 * 
 * @param grid The grid to print.
 */
void showGrid(gridClass *grid);

/**
 * @brief 
 * 
 * @param grid 
 * @param num 
 */
void freeMemory(gridClass *grid, int *num);

/**
 * @brief 
 * 
 * @param num
 * @return int 
 */
int moveChoice(int num);

/**
 * @brief Function for adding a token to the initialized grid
 * 
 * @param grid The grid to add the token to.
 * @param col The column to add the token to if possible
 * @param token The type of token to add (O for yellow and X for red)
 * @return int Either 1 if adding succedded or 0 if not.
 */
int addToken(gridClass *grid, int col, tokenClass *token);

/**
 * @brief 
 * 
 * @param grid 
 * @param col 
 * @return int 
 */
int removeToken(gridClass *grid, int col);

/**
 * @brief 
 * 
 * @param grid 
 * @param N 
 * @param token 
 * @return int 
 */
int checkWinner(gridClass *grid, int *N, tokenClass *token);

/**
 * @brief 
 * 
 * @param grid 
 * @param N 
 * @param token 
 * @return int 
 */
int checkVert(gridClass *grid, int N, tokenClass *token);

/**
 * @brief 
 * 
 * @param grid 
 * @param N 
 * @param token 
 * @return int 
 */
int checkHoriz(gridClass *grid, int N, tokenClass *token);

/**
 * @brief 
 * 
 * @param grid 
 * @param N 
 * @param token 
 * @return int 
 */
int checkDiagTopBot(gridClass *grid, int N, tokenClass *token);

/**
 * @brief 
 * 
 * @param grid 
 * @param N 
 * @param token 
 * @return int 
 */
int checkDiagBotTop(gridClass *grid, int N, tokenClass *token);

/**
 * @brief Function saving the current grid to a .bin file
 * 
 * @param grid The grid to save
 */
void saveToFile(gridClass *grid, int player);

/**
 * @brief 
 * 
 */
void loadFromFile();

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