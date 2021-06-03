#include <ConnectN.h>

typedef enum
{
    FALSE = 0,
    TRUE = 1
} Boolean;

typedef struct
{
    int nbCol; // Number of columns in the table
    int nbLin; // Number of lines in the table
} tableSize;

/**
* Indicates whether a column is playable.
* @param col: 0-based index of column to play
* @return true if the column is playable, false if the column is already full.
*/
Boolean canPlay(int col);

/**
* Indicates whether a column is playable.
* @param col: 0-based index of column to play
* @return true if the column is playable, false if the column is already full.
*/
Boolean canPlay(int col);

/**
* Plays a playable column.
* This function should not be called on a non-playable column or a column making an alignment.
*
* @param col: 0-based index of a playable column.
*/
void play(int col);

/**
* Indicates whether the current player wins by playing a given column.
* This function should never be called on a non-playable column.
* @param col: 0-based index of a playable column.
* @return true if current player makes an alignment by playing the corresponding column col.
*/
Boolean isWinningMove(int col);

/**    
* @return number of moves played from the beginning of the game.
*/
int nbMoves();
