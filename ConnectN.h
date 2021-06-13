/**
 * @file ConnectN.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <colors.h>
#include <ncurses.h>
#include <locale.h>
#include <wchar.h>

/**
 * @brief Structure for storing all the data about the game and the grid.
 * 
 */
typedef struct
{
    int lin;            // The number of lines in the grid.
    int col;            // The number of columns in the grid. col and lin should be equal as the grid is a square.
    char **grille;      // The game grid. A 2D array of char.
    int tokenNumber;    // The number of tokens in grid (used to determine if the program should propose removeToken()).
} gridClass;

/**
 * @brief Structure for storing the data about the last added token.
 * 
 */
typedef struct
{
    int posLin;     // The line coordinate (y) of the last added token.
    int posCol;     // The column coorditate (x) of the last added token.
    char type;      // The type of token. Either 'O' for yellow or 'X' for red.
    char lastMove;  // Either '-' when the last move was removeToken() or '+' if the last move was addToken().
} tokenClass;


/**
 * @brief Function for the user to choose what to do when openning the game with entry check. Changes the value of nbPlayers (pointer on int) for the game to know if the game will be against the IA or a human player.
 * 
 * @return int The choice of the user. 1 for "New Game", 2 for "Continue last saved game" and 3 for "Quit".
 */
int startGame(int *nbPlayer);

/**
 * @brief Create a And Initialize the structure newGrid by asking the user the size of the grid.
 * 
 * @param newGrid Pointer on gridClass used to store the newly created grid.
 * @param align Pointer on int used to store the number of tokens to align.
 * @return GRID* Pointer on gridClass where the initialized grid is stored.
 */
gridClass *createAndInitializeGrid(gridClass *newGrid, int *align);

/**
 * @brief Function for initializing the grid size by storing the value of align + 2 in col and lin and sets tokenNumber to 0.
 * 
 * @param grid The gridClass to work with.
 * @param align The number of tokens to align.
 * @return gridClass* Pointer on gridCalss with the size values and tokenNumber initialized.
 */
gridClass *initializeGridSize(gridClass *grid, int *align);

/**
 * @brief Initalizing the grid with '_' characters for empty slots.
 * 
 * @param newGrid The grid to work with.
 * @return GRID* An initialized version of the grid with the corresponding memory allocated.
 */
gridClass *initializeGrid(gridClass *newGrid);

/**
 * @brief Function for printing the grid of characters in the console.
 * 
 * @param grid Pointer on the gridCalss to print.
 */
void showGrid(gridClass *grid);

/**
 * @brief Function containing all the loops and the sub-functions for running the game. All parameters are pointers.
 * 
 * @param gameBoard Pointer on gridClass storing the previously initialized game grid.
 * @param token Pointer on tokenClass storing the data of the last added token.
 * @param toAlign Pointer on int storing the number of tokens to align to win the game.
 * @param nbPlayers Pointer on int storing the number of players (1 for player vs AI or 2 for player vs player)
 * @param player Pointer on int storing which player is starting the game (set by random if it is a newly initialized game, or by loadFromFile());
 */
void game(gridClass *gameBoard, tokenClass *token, int *toAlign, int *nbPlayers, int *player);

/**
 * @brief Function for the AI to choose weather to add or remove a token. Always adds when tokenNumber is 0.
 * 
 * @return int 1 for adding or 2 for removing.
 */
int aiAddOrRemove(gridClass* grid);

/**
 * @brief Function for selecting randomly a column to add or remove a token to.
 * 
 * @param grid Pointer on gridClass to access the size of the grid to return an index of column suitable for addToken() or removeToken().
 * @return int The index of the column to add or remove a token to. If it is impossible to add or remove a token to this column, the functions restarts.
 */
int aiSelectColumn(gridClass *grid);

/**
 * @brief Function for freeing the memory manually allocated.
 * 
 * @param grid Pointer on gridClass storing the data about the grid and its size.
 * @param token pointer on tokenClass storing the data about the last added token.
 * @param num A pointer on int.
 * @param num2 A pointer on int.
 * @param num3 A pointer on int.
 */
void freeMemory(gridClass *grid, tokenClass *token, int *num, int *num2, int *num3);

/**
 * @brief Function asking the user what to do : either adding or removing a token or saving the game to a file and quitting the game.
 * 
 * @param num Int representing the number of tokens in the grid.
 * @return int 1 for adding a token, 2 for removing a token or 3 for saving and quitting the game.
 */
int moveChoice(int num);

/**
 * @brief Function for adding a token to the initialized grid
 * 
 * @param grid The grid to add the token to.
 * @param col The column to add the token to if possible
 * @param token Pointer on tokenClass to store the data about the last added token (coordinates, type and '+' for last move).
 * @return int Either 1 for adding success or 0 if it was impossible (column does not exists or column is full).
 */
int addToken(gridClass *grid, int col, tokenClass *token);

/**
 * @brief Function for removing a token to the initialized grid.
 * 
 * @param grid The grid to add the token to.
 * @param token Pointer on tokenClass to store the data about the last removed token(only '-' for last move). This function does not store the coordinates of the last removed token as these informations are useless.
 * @param col The column to remove the last added token if possible.
 * @return int Either 1 for removing success or 0 if it was impossible (column does not exists or column is empty).
 */
int removeToken(gridClass *grid, tokenClass *token, int col);

/**
 * @brief Function for checking if the game grid is full with no winner.
 * 
 * @param grid Pointer on gridClass storing the grid.
 * @return int 1 if there is a tie (the grid is full) or 0 of not.
 */
int checkTie(gridClass *grid);

/**
 * @brief Function for checking if there is a winner
 * 
 * @param grid Pointer on gridClass with the grid to check if N tokens are aligned.
 * @param N Pointer on int storing number of tokens to align to win.
 * @param token Pointer on tokenClass with the coordinates and the type of the last added token.
 * @return int -1 if there is no winner, 0 if yellow has won or 1 if red has won.
 */
int checkWinner(gridClass *grid, int *N, tokenClass *token);

/**
 * @brief Function for checking if the last added token leads to the last player to win vertically.
 * 
 * @param grid Pointer on gridClass storing the grid to check if at least N tokens are aligned.
 * @param N Pointer on int storing the number of tokens to align to win.
 * @param token Pointer on tokenClass storing the type and coordinates of the last added token.
 * @return int 1 if the last player has succesfully aligned at least N tokens and thus has won, 0 if he did not.
 */
int checkVert(gridClass *grid, int N, tokenClass *token);

/**
 * @brief Function for checking if the last added token leads to the last player to win horizontally.
 * 
 * @param grid Pointer on gridClass storing the grid to check if at least N tokens are aligned.
 * @param N Pointer on int storing the number of tokens to align to win.
 * @param token Pointer on tokenClass storing the type and coordinates of the last added token.
 * @return int 1 if the last player has succesfully aligned at least N tokens and thus has won, 0 if he did not.
 */
int checkHoriz(gridClass *grid, int N, tokenClass *token);

/**
 * @brief Function for checking if the last added token leads to the last player to win in diagonal from top to bottom to the right.
 * 
 * @param grid Pointer on gridClass storing the grid to check if at least N tokens are aligned.
 * @param N Pointer on int storing the number of tokens to align to win.
 * @param token Pointer on tokenClass storing the type and coordinates of the last added token.
 * @return int 1 if the last player has succesfully aligned at least N tokens and thus has won, 0 if he did not.
 */
int checkDiagTopBot(gridClass *grid, int N, tokenClass *token);

/**
 * @brief Function for checking if the last added token leads to the last player to win in diagonal from bottom to top to the right.
 * 
 * @param grid Pointer on gridClass storing the grid to check if at least N tokens are aligned.
 * @param N Pointer on int storing the number of tokens to align to win.
 * @param token Pointer on tokenClass storing the type and coordinates of the last added token.
 * @return int 1 if the last player has succesfully aligned at least N tokens and thus has won, 0 if he did not.
 */
int checkDiagBotTop(gridClass *grid, int N, tokenClass *token);

/**
 * @brief Function saving the current grid to a 'game.save' file.
 * 
 * @param grid The grid to save
 */
void saveToFile(gridClass *grid, int player);

/**
 * @brief Function for loadinf the game from a previously saved game.
 * 
 * @param grid Pointer on gridClass to store the loaded grid and data to.
 * @param player Pointer on int storing the next player to play.
 * @param align Pointer on int storing the number of tokens to align to win the game.
 * @return int The next player to play : 0 for player 1 or 1 for player 2.
 */
int loadFromFile(gridClass *grid, int *player, int *align);

/**
 * @brief Functions that clears the command prompt supporting both Windows and Linux OS.
 * 
 */
void consoleClear();

/**
 * @brief Funtion that checks the input of an integer.
 * 
 * @return int The desired integer or -INT_MAX if not valid.
 */
int safeIntInput();

/**
 * @brief Function for pausinf the game for some time.
 * 
 * @param milliseconds How long to pause the program, in milliseconds.
 */
void delay(int milliseconds);

/*----------------- GUI functions -----------------*/

/**
 * @brief Function used to lauch and initialize the game with GUI
 * 
 * @param gameBoard Pointer on gridClass storing the data about the grid.
 * @param token Pointer on tokenClass used to store the data about the last added token.
 * @param toAlign Pointer on int storing the number of tokens to align to win the game.
 * @param nbPlayers Pointer on int storing the number of players (1 if on players against AI or 2 if player vs player).
 * @param player Pointer on int storing the next player to play (1 for yellow or 2 for red).
 */
void gui(gridClass *gameBoard, tokenClass *token, int *toAlign, int *nbPlayers, int *player);

/**
 * @brief Create a Shadow to the specified window.
 * 
 * @param window The window to create the shadow of.
 * @return WINDOW* Pointer on window of the shadow.
 */
WINDOW *createShadow(WINDOW *window);

/**
 * @brief Function used to check if a user entry is an int. 
 * 
 * @param win The win the user inputs text or numbers to.
 * @return int The int entered or - INT_MAX if it wansn't an int.
 */
int safeIntInput_GUI(WINDOW *win);

/**
 * @brief Function used to print in the center of a specified window at a specified line.
 * 
 * @param win The window th print to.
 * @param title The text to print.
 * @param line The line to print to.
 */
void centerPrint(WINDOW *win, int line, char *title);

/**
 * @brief Function used to set a speficied windo in error mode (for example when the user entered a wrong input).
 * 
 * @param win The window to set in error mode.
 */
void errorON(WINDOW *win, int box);

/**
 * @brief Function used to reset un specified window from error mode.
 * 
 * @param win The window to reset from error mode.
 */
void errorOFF(WINDOW *win, int box);

/**
 * @brief Function used to set text in strong standout (blink, bold and underlined) in a specified window.
 * 
 * @param win The window to print text in strong standout mode to.
 */
void strongStandoutON(WINDOW *win);

/**
 * @brief Function used to reset text from strong standout in a specified window.
 * 
 * @param win The window to reset standard mode to.
 */
void strongStandoutOFF(WINDOW *win);

/**
 * @brief Function used to print the startup animation (characters printing afeter each other) in the center of the console.
 * 
 * @param yMax The number of lines of the console.
 * @param xMax The number of columns of the console.
 */
void startupAnimation(int yMax, int xMax);

/**
 * @brief Function used to show the startup menu.
 * 
 * @param menuWin Pointer on window to print the menu to.
 * @param menuWinShadow Pointer on window of the shadow of the previous window.
 * @return int The index of the choice of the user (1 for new game, 2 for load last saved game and 3 for quit).
 */
int startupMenu(WINDOW *menuWin, WINDOW *menuWinShadow);

/**
 * @brief Function for showing a window and ask the number of players to the user.
 * 
 * @param smallWin Pointer on window to print and ask the user the number of players.
 * @param smallWinShadow Pointer on window of the shadow of the previous window.
 * @return int Returns the amount of players (1 for player VS AI or 2 for player VS player).
 */
int playerNumChoice(WINDOW *smallWin, WINDOW *smallWinShadow);

/**
 * @brief Function for asking the number of players 
 * 
 * @param smallWin 
 * @param smallWinShadow 
 * @param input 
 * @param xMax 
 * @param nbPlayers 
 * @param players 
 */
void playerNames(WINDOW *smallWin, WINDOW *smallWinShadow, WINDOW *input, int xMax, int *nbPlayers, char ** players);

/**
 * @brief 
 * 
 * @param smallWin 
 * @param smallWinShadow 
 * @param input 
 * @return int 
 */
int gridSizeChoice(WINDOW *smallWin, WINDOW *smallWinShadow, WINDOW *input);

/**
 * @brief 
 * 
 * @param grid 
 * @param win 
 */
void showGrid_GUI(gridClass *grid, WINDOW* win);

/**
 * @brief 
 * 
 * @param gameWinBkgdShadow 
 * @param gameWinBkgd 
 * @param gameBoradWin 
 * @param playerWin 
 * @param moveChoiceWin 
 * @param columnChoiceWin 
 * @param grid 
 * @param players 
 * @param player 
 */
void initializeGameWin(WINDOW *gameWinBkgdShadow, WINDOW *gameWinBkgd, WINDOW *gameBoradWin, WINDOW *playerWin, WINDOW *moveChoiceWin, WINDOW *columnChoiceWin, gridClass *grid, char** players, int player);

/**
 * @brief 
 * 
 * @param moveChoiceWin 
 */
void initializeMoveChoiceWin(WINDOW *moveChoiceWin);

/**
 * @brief 
 * 
 * @param playerWin 
 * @param players 
 * @param player 
 */
void initializePlayerWin(WINDOW *playerWin, char **players, int player);

/**
 * @brief 
 * 
 * @param moveChoiceWin 
 * @param tokenNumber 
 * @return int 
 */
int moveChoice_GUI(WINDOW *moveChoiceWin, int tokenNumber);

/**
 * @brief 
 * 
 * @param grid 
 * @param columnChoiceWin 
 * @param moveChoice 
 * @param removedColumn 
 * @return int 
 */
int selectColumn_GUI(gridClass *grid, WINDOW *columnChoiceWin, int moveChoice, int removedColumn);

/**
 * @brief 
 * 
 * @param smallWin 
 * @param smallWinShadow 
 * @param gameWinBkgd 
 * @param playerWin 
 * @param moveChoiceWin 
 * @param columnChoiceWin 
 * @param gameBoardWin 
 * @param gameBoard 
 * @param token 
 * @param player 
 * @param nbPlayers 
 * @param toAlign 
 * @param players 
 */
void game_GUI(WINDOW* smallWin, WINDOW* smallWinShadow, WINDOW *gameWinBkgd, WINDOW *playerWin, WINDOW *moveChoiceWin, WINDOW *columnChoiceWin, WINDOW *gameBoardWin, gridClass *gameBoard, tokenClass *token, int *player, int *nbPlayers, int *toAlign, char **players);

/**
 * @brief 
 * 
 * @param grid 
 * @param col 
 * @param token 
 * @return int 
 */
int addToken_GUI(gridClass *grid, int col, tokenClass *token);

/**
 * @brief 
 * 
 * @param grid 
 * @param token 
 * @param col 
 * @return int 
 */
int removeToken_GUI(gridClass *grid, tokenClass *token, int col);