/**
 * @file main.c
 * @author Edgar Boule (edgar.boule@utbm.fr), Thibaut Lemaître (thibaut.lemaitre@utbm.fr), Matis Ressicaud (matis.ressicaud@utbm.fr)
 * @brief 
 * @version 0.1
 * @date 2021-05-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// Ligne de compilation : gcc -Wall -g main.c ConnectN.c gui.c lib_gui.c -o main.exe -I . -lncursesw

#include <ConnectN.h>
// #include <negamaxAI.h>

int main(int argc, char **argv)
{
    srand(time(NULL));

    gridClass *gameBoard = malloc(sizeof(gridClass)); // Pointer on gridClass
    tokenClass *token = malloc(sizeof(tokenClass));   // Pointer on tokenClass
    int *player = malloc(sizeof(int));                // Pointer on int
    int *nbPlayers = malloc(sizeof(int));             // Pointer on int
    int *toAlign = malloc(sizeof(int));               // Pointer on int


    if (argc == 2 && strcasecmp(argv[1], "-nogui") == 0)
    {
        switch (startGame(nbPlayers))
        {
        case 1:
            consoleClear();
            printf(BWHT BLK "Démarrage de la nouvelle partie...\n" RST);
            gameBoard = createAndInitializeGrid(gameBoard, toAlign);
            consoleClear();
            showGrid(gameBoard);
            *player = rand() % 2 + 1;

            game(gameBoard, token, toAlign, nbPlayers, player);

            break;
        case 2:
            printf(BLU "Loading last saved game\n" RST);
            if (loadFromFile(gameBoard, player, toAlign) == -1)
            {
                printf(RED "Une erreur est survenue lors de la lecture du fichier. Celui-ci est peut-être inexistant ou corrompu.\n" RST);
                return EXIT_FAILURE;
            }
            else
            {
                consoleClear();
                showGrid(gameBoard);

                game(gameBoard, token, toAlign, nbPlayers, player);
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
    }
    else
    {
        gui(gameBoard, token, toAlign, nbPlayers, player);
    }
    freeMemory(gameBoard, token, toAlign, player, nbPlayers);

    return EXIT_SUCCESS;
}