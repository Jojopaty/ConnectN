#include "ConnectN.h"

int startGame()
{
    clear();
    int startChoice;
    printf(GRN "Bievenue dans le jeu du Puissance N" RST "\n1. Nouvelle partie\n2. Continuer la dernière partie\n3. Quitter\nQuel est votre choix ? ");
    startChoice = safeIntInput();

    while (startChoice < 1 || startChoice > 3)
    {
        clear();
        printf(RED "Entrée incorrecte, veuillez recommencer" RST "\n1. Nouvelle partie\n2. Continuer la dernière partie\n3. Quitter\nQuel est votre choix ? ");
        //scanf("%d", &startChoice);
        startChoice = safeIntInput();
    }
    return startChoice;
}

GRID *createAndInitializeGrid(GRID *newGrid)
{
    int input = 0;
    printf("Quel est le nombre de colonnes du jeu ? ");
    input = safeIntInput();
    while (input < 1)
    {
        printf(RED "Le nombre entré n'est pas correct\n" RST "Quel est le nombre de colonnes du jeu ? ");
        input = safeIntInput();
    }
    newGrid->col = input;

    printf("Quel est le nombre de lignes du jeu ? ");
    input = safeIntInput();
    while (input < 1)
    {
        printf(RED "Le nombre entré n'est pas correct\n" RST "Quel est le nombre de lignes du jeu ? ");
        input = safeIntInput();
    }
    newGrid->lin = input;

    initializeGrid(newGrid);

    return newGrid;
}

GRID *initializeGrid(GRID *newGrid)
{
    newGrid->grille = (char **)malloc(newGrid->lin * sizeof(char *));

    for (int i = 0; i < (newGrid->lin); i++)
    {
        newGrid->grille[i] = (char *)malloc(newGrid->col * sizeof(char));

        for (int j = 0; j < (newGrid->col); j++)
        {
            newGrid->grille[i][j] = '_';
        }
    }
    showGrid(newGrid);

    return newGrid;
}

void showGrid(GRID *grid)
{
    for (int i = 0; i < grid->lin; i++)
    {
        for (int j = 0; j < grid->col; j++)
        {
            printf("| %c ", grid->grille[i][j]);
        }
        printf("|\n");
    }
}

void freeMemory(GRID *grid)
{
    for (int i = 0; i < grid->col; i++)
    {
        free(grid->grille[i]);
    }
    free(grid->grille);
    free(grid);
}

void clear()
{
#if defined(_WIN64) || defined(_WIN32)
    system("cls");
#elif defined(__linux__)
    system("clear");
#else
#error "OS not supported compilation aborted!"
#endif
}

int safeIntInput()
{
    int num = 0;
    char input[64];
    fgets(input, 63, stdin);

    if (sscanf(input, "%d", &num) != 1)
    {
        return -__INT_MAX__;
    }
    return num;
}