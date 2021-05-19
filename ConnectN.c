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
        startChoice = safeIntInput();
    }
    return startChoice;
}

GRID *createAndInitializeGrid(GRID *newGrid, int *align)
{
    int input = 0;
    printf("Combien de jetons doivent être alignés pour gagner ? ");
    input = safeIntInput();

    while (input < 1)
    {
        printf(RED "Le nombre entré n'est pas correct\n" RST "Combien de jetons doivent être alignés pour gagner ? ");
        input = safeIntInput();
    }
    *align = input;
    newGrid->col = newGrid->lin = input + 2;
    clear();
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

void freeMemory(GRID *grid, int *num)
{
    for (int i = 0; i < grid->col; i++)
    {
        free(grid->grille[i]);
        grid->grille[i] = NULL;
    }

    free(grid->grille);
    grid->grille = NULL;
    free(grid);
    grid = NULL;

    free(num);
    num = NULL;
}

int moveChoice(int round)
{
    if (round > 0)
    {
        printf(GRN "\nQue souhaitez-vous faire ?" RST "\n1. Ajouter un jeton\n2. Retirer un jeton\nQuel est votre choix ? ");
        int choice = safeIntInput();

        while (choice < 1 || choice > 2)
        {
            printf(RED "\nEntrée incorrecte, veuillez recommencer" RST "\n1. Ajouter un jeton\n2. Retirer un jeton\nQuel est votre choix ? ");
            choice = safeIntInput();
        }
        return choice;
    }
    else
    {
        return 1; // First game round -> no token to remove -> function addToken called;
    }
}

int addToken(GRID *grid, int col, char token)
{
    int line = grid->lin;

    if (col > (grid->col) || col < 1)
    {
        printf(RED "La colonne %d n'existe pas, impossible d'ajouter le jeton.\n" RST, col);
        return 0;
    }
    else if (token != 'X' && token != 'O')
    {
        printf(RED "Type de jeton %c non reconnu.\n" RST, token);
        return 0;
    }
    else
    {

        while (line > 0 && grid->grille[line - 1][col - 1] != '_')
        {
            line--;
        }

        if (line <= 0)
        {
            printf(RED "La colonne %d est pleine, le jeton n'a pas pu être ajouté.\n" RST, col);
            return 0;
        }
        else
        {
            grid->grille[line - 1][col - 1] = token;
            return 1;
        }
    }
}

void saveToFile(GRID *grid)
{
    FILE *file = fopen("file.bin", "w");
    char array[(grid->lin - 1)];
    char size[16];
    sprintf(size, "%d\n", grid->col);
    fputs(size, file);
    for (int i = 0; i < grid->lin; i++)
    {
        strcpy(array, grid->grille[i]);

        fputs(array, file);
        fputs("\n", file);
    }
    fclose(file);
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