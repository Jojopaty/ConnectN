/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ConnectN.h"

int main(int argc, char *argv[])
{
    GRID *gameBoard = malloc(sizeof(GRID));
    int player = 1;
    // int column;

    switch (startGame())
    {
    case 1:
        clear();
        printf(BWHT BLK "Démarrage de la nouvelle partie...\n\n" RST);
        createAndInitializeGrid(gameBoard);
        for (int i = 0; i < 4; i++)
        {
            printf("Joueur %d\n", player);
            printf("Quelle colonne ? ");
            int hasAdded = 0;
            do
            {
                hasAdded = addToken(gameBoard, player);
            } while (hasAdded != 1);

            showGrid(gameBoard);
            player = (player == 1) ? 2 : 1;
        }
        saveToFile(gameBoard);
        break;
    case 2:
        printf(BLU "Loading last saved game\n" RST);
        break;
    case 3:
        printf(BLU "Bye\n" RST);
        return EXIT_SUCCESS;
        break;
    default:
        // Should never be executed
        break;
    }

    freeMemory(gameBoard);

    return EXIT_SUCCESS;
}