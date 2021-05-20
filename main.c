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

    gridClass *gameBoard = malloc(sizeof(gridClass));
    tokenClass *token = malloc(sizeof(tokenClass));
    int player;
    int column;
    int shot = 0;
    int hasPlayed = 0;
    int hasWon = 0;
    int quit = 0;
    int *toAlign = malloc(sizeof(int)); // pointer on int

    switch (startGame())
    {
    case 1:
        clear();
        printf(BWHT BLK "Démarrage de la nouvelle partie...\n" RST);
        createAndInitializeGrid(gameBoard, toAlign);
        player = rand() % 2 + 1;
        while(hasWon < 1)
        {
            printf("\nJoueur %d\n", player);
            token->type = ((player == 1) ? 'O' : 'X');
            hasPlayed = 0;
            do
            {
                switch (moveChoice(shot))
                {
                case 1:

                    printf("\nAjouter un jeton dans quelle colonne ? ");
                    column = safeIntInput();
                    hasPlayed = addToken(gameBoard, column, token->type);

                    break;
                case 2:

                    printf("\nRetirer un jeton dans quelle colonne ? ");
                    column = safeIntInput();
                    hasPlayed = removeToken(gameBoard, column);

                    break;
                case 3:
                    quit = 1;
                    saveToFile(gameBoard); //TODO Add next player in saved file
                    break;
                default:
                    break;
                }
            } while (hasPlayed != 1 && quit < 1);

            if (quit < 1)
            {
                clear();
                showGrid(gameBoard);
                player = (player == 1) ? 2 : 1;
                shot++;
                hasWon = checkWinner(gameBoard, toAlign, token);
            }
            else
            {
                printf("La partie a été enregistrée, pour la continuer, sélectionnez 'Continuer la dernière partie' au prochain démarrage du jeu.\nA bientôt !");
            }
        }
        
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