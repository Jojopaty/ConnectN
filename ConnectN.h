#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <colors.h>
#include <ncurses.h>
#include <locale.h>


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
    char lastMove;
} tokenClass;

/**
 * @brief Function for the user to choose what to do when openning the game with entry check.
 * 
 * @return int The choice of the user. 1 for "New Game", 2 for "Continue last saved game" and 3 for "Quit".
 */
int startGame(int *nbPlayer);

/**
 * @brief Create a And Initialize Grid object
 * 
 * @param newGrid 
 * @param align 
 * @return GRID* 
 */
gridClass *createAndInitializeGrid(gridClass *newGrid, int *align);

/**
 * @brief 
 * 
 * @param grid 
 * @param align 
 * @return gridClass* 
 */
gridClass *initializeGridSize(gridClass *grid, int *align);

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
 * @param gameBoard 
 * @param token 
 * @param toAlign 
 * @param nbPlayers 
 * @param player 
 */
void game(gridClass *gameBoard, tokenClass *token, int *toAlign, int *nbPlayers, int *player);

/**
 * @brief 
 * 
 * @return int 
 */
int aiAddOrRemove();

/**
 * @brief 
 * 
 * @param grid 
 * @return int 
 */
int aiSelectColumn(gridClass *grid);

/**
 * @brief 
 * 
 * @param grid 
 * @param token 
 * @param num 
 * @param num2 
 * @param num3 
 */
void freeMemory(gridClass *grid, tokenClass* token, int *num, int *num2, int *num3);

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
 * @param token 
 * @param col 
 * @return int 
 */
int removeToken(gridClass *grid, tokenClass* token, int col);

int checkDraw(gridClass* grid);

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
 * @param grid 
 * @param player 
 * @return int 
 */
int loadFromFile(gridClass *grid, int *player, int *align);

/**
 * @brief Functions that clears the command prompt supporting both Windows and Linux OS.
 * 
 */
void consoleClear();

/**
 * @brief Funtion that checks the input of an integer
 * 
 * @return int The desired integer or -INT_MAX if not valid
 */
int safeIntInput();

/**
 * @brief 
 * 
 * @param milliseconds 
 */
void delay(int milliseconds);