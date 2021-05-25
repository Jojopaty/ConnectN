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
    int *player = malloc(sizeof(int)); // pointer on int
    int column;
    int hasPlayed = 0;
    int hasWon = -1;
    int quit = 0;
    int draw = 0;
    int removedColumn = 0;
    int *toAlign = malloc(sizeof(int)); // pointer on int

    switch (startGame())
    {
    case 1:
        clear();
        printf(BWHT BLK "Démarrage de la nouvelle partie...\n" RST);
        createAndInitializeGrid(gameBoard, toAlign);
        clear();
        showGrid(gameBoard);
        *player = rand() % 2 + 1;
        while (hasWon < 0 && quit < 1 && draw < 1)
        {
            printf("\nJoueur %d\n", *player);
            token->type = ((*player == 1) ? 'O' : 'X');
            hasPlayed = 0;
            do
            {
                switch (moveChoice(gameBoard->tokenNumber))
                {
                case 1:

                    printf("\nAjouter un jeton dans quelle colonne ? ");
                    column = safeIntInput();
                    if (column != removedColumn)
                    {
                        hasPlayed = addToken(gameBoard, column, token);
                        removedColumn = 0;
                    }
                    else
                    {
                        hasPlayed = 0;
                        printf(RED "Vous ne pouvez pas insérer de jeton dans cette colonne. Un jeton vient d'y être retiré." RST);
                    }
                    break;
                case 2:

                    printf("\nRetirer un jeton dans quelle colonne ? ");
                    column = safeIntInput();
                    hasPlayed = removeToken(gameBoard, column);
                    removedColumn = (hasPlayed > 0) ? column : 0;
                    break;
                case 3:
                    saveToFile(gameBoard, (*player == 1) ? 2 : 1);
                    quit = 1;
                    break;
                default:
                    break;
                }

                if (gameBoard->tokenNumber == (gameBoard->col * gameBoard->lin))
                {
                    draw = 1;
                }
                else
                {
                    draw = 0;
                }
            } while (quit != 1 && hasPlayed != 1 && draw != 1);

            if (quit < 1)
            {
                clear();
                showGrid(gameBoard);
                hasWon = checkWinner(gameBoard, toAlign, token);
                if (hasWon > -1)
                {
                    printf(CYN "Le joueur %d a gagné. Félicitations !\n" RST, *player);
                }
                if (draw > 0)
                {
                    printf(YEL "Egalité ! Toute la surface de jeu a été remplie sans qu'un joueur gagne.\n" RST);
                }
                *player = (*player == 1) ? 2 : 1;
            }
            else
            {
                printf(GRN "\nLa partie a été enregistrée. Pour la continuer, sélectionnez 'Continuer la dernière partie' au prochain démarrage du jeu.\n" CYN "A bientôt !\n" RST);
            }
        }

        break;
    case 2:
        printf(BLU "Loading last saved game\n" RST);
        if (loadFromFile(gameBoard, player, toAlign) == 0)
        {
            return EXIT_FAILURE;
        }
        else
        {
            clear();
            showGrid(gameBoard);
        }
        break;
    case 3:
        printf(BLU "Bye\n" RST);
        return EXIT_SUCCESS;
        break;
    default:
        // Should never be executed
        break;
    }

    freeMemory(gameBoard, toAlign, player);

    return EXIT_SUCCESS;
}