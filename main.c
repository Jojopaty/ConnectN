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
    srand(time(NULL));

    GRID *gameBoard = malloc(sizeof(GRID));
    int player;
    int column;
    int shot = 0;
    int *toAlign = malloc(sizeof(int)); // pointer on int

    switch (startGame())
    {
    case 1:
        clear();
        printf(BWHT BLK "Démarrage de la nouvelle partie...\n" RST);
        createAndInitializeGrid(gameBoard, toAlign);
        player = rand() % 2 + 1;
        for (int i = 0; i < 4; i++)
        {
            printf("\nJoueur %d\n", player);

            int hasPlayed;

            switch (moveChoice(shot))
            {
            case 1:
                
                hasPlayed = 0;
                do
                {
                    printf("\nAjouter un jeton dans quelle colonne ? ");
                    column = safeIntInput();
                    hasPlayed = addToken(gameBoard, column, ((player == 1) ? 'O' : 'X'));
                } while (hasPlayed != 1);
                break;
            case 2:
                break;
            default:
                break;
            }

            clear();
            showGrid(gameBoard);
            player = (player == 1) ? 2 : 1;
            shot++;
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

    freeMemory(gameBoard, toAlign);

    return EXIT_SUCCESS;
}