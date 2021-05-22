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

gridClass *createAndInitializeGrid(gridClass *newGrid, int *align)
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
    newGrid->tokenNumber = 0;
    clear();
    initializeGrid(newGrid);
    return newGrid;
}

gridClass *initializeGrid(gridClass *newGrid)
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

void showGrid(gridClass *grid)
{
    for (int i = 0; i < grid->lin; i++)
    {
        for (int j = 0; j < grid->col; j++)
        {
            printf("| ");
            if (grid->grille[i][j] == 'O')
            {
                printf(YEL "%c " RST, grid->grille[i][j]);
            }
            else if (grid->grille[i][j] == 'X')
            {
                printf(RED "%c " RST, grid->grille[i][j]);
            }
            else
            {
                printf("%c ", grid->grille[i][j]);
            }
        }
        printf("|\n");
    }
}

void freeMemory(gridClass *grid, int *num)
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

int moveChoice(int num)
{
    if (num > 0)
    {
        printf(GRN "\nQue souhaitez-vous faire ?" RST "\n1. Ajouter un jeton\n2. Retirer un jeton\n3. Sauvegarder et quitter\nQuel est votre choix ? ");
        int choice = safeIntInput();

        while (choice < 1 || choice > 3)
        {
            printf(RED "\nEntrée incorrecte, veuillez recommencer" RST "\n1. Ajouter un jeton\n2. Retirer un jeton\n3. Sauvegarder et quitter\nQuel est votre choix ? ");
            choice = safeIntInput();
        }
        return choice;
    }
    else
    {
        return 1; // First game round -> no token to remove -> function addToken called;
    }
}

int addToken(gridClass *grid, int col, tokenClass *token)
{
    int line = grid->lin;

    if (col > (grid->col) || col < 1)
    {
        printf(RED "La colonne %d n'existe pas, impossible d'ajouter le jeton.\n" RST, col);
        return 0;
    }
    else if ((token->type) != 'X' && (token->type) != 'O')
    {
        printf(RED "Type de jeton %c non reconnu.\n" RST, (token->type));
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
            grid->grille[line - 1][col - 1] = (token->type);
            grid->tokenNumber++;
            token->posLin = line - 1;
            token->posCol = col - 1;
            return 1;
        }
    }
}

int removeToken(gridClass *grid, int col)
{
    int line = 0;

    if (col > grid->col || col < 1)
    {
        printf(RED "La colonne %d n'existe pas, impossible d'y retirer un jeton.\n" RST, col);
        return 0;
    }
    else
    {
        while (line < grid->lin && grid->grille[line][col - 1] == '_')
        {
            line++;
        }
        if (line >= grid->lin)
        {
            printf(RED "La colonne %d est vide, aucun jeton n'a pu y être retiré.\n" RST, col);
            return 0;
        }
        else
        {
            grid->grille[line][col - 1] = '_';
            grid->tokenNumber--;
            return 1;
        }
    }
}

int checkWinner(gridClass *grid, int *N, tokenClass *token)
{
    int winner = checkVert(grid, *N, token) + checkHoriz(grid, *N, token) + checkDiagTopBot(grid, *N, token) + checkDiagBotTop(grid, *N, token);
    if (winner != 0)
    {
        return ((token->type == 'O') ? 0 : 1);
    }
    else
    {
        return -1;
    }
}

int checkVert(gridClass *grid, int N, tokenClass *token)
{
    int aligned = 0;
    for (int i = 0; i < grid->lin; i++)
    {
        if ((grid->grille[i][(token->posCol)]) == (token->type))
        {
            aligned++;
        }
        else if (aligned == N)
        {
            return 1;
        }
        else
        {
            aligned = 0;
        }
    }
    if (aligned == N)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int checkHoriz(gridClass *grid, int N, tokenClass *token)
{
    int aligned = 0;
    for (int i = 0; i < grid->lin; i++)
    {
        if ((grid->grille[(token->posLin)][i]) == (token->type))
        {
            aligned++;
        }
        else if (aligned == N)
        {
            return 1;
        }
        else
        {
            aligned = 0;
        }
    }
    if (aligned == N)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int checkDiagTopBot(gridClass *grid, int N, tokenClass *token)
{
    int aligned = 0;
    int lin = token->posLin;
    int col = token->posCol;

    while (lin > 0 && col > 0)
    {
        lin--;
        col--;
    }
    while (lin < grid->lin && col < grid->col)
    {
        if ((grid->grille[lin][col]) == (token->type))
        {
            aligned++;
        }
        else if (aligned == N)
        {
            return 1;
        }
        else
        {
            aligned = 0;
        }
        lin++;
        col++;
    }
    if (aligned == N)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int checkDiagBotTop(gridClass *grid, int N, tokenClass *token)
{
    int aligned = 0;
    int lin = token->posLin;
    int col = token->posCol;

    while (col > 0 && lin < (grid->lin - 1))
    {
        lin++;
        col--;
    }

    while (lin > 0 && col < grid->col)
    {
        if ((grid->grille[lin][col]) == (token->type))
        {
            aligned++;
        }
        else if (aligned == N)
        {
            return 1;
        }
        else
        {
            aligned = 0;
        }
        lin--;
        col++;
    }
    if (aligned == N)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void saveToFile(gridClass *grid)
{
    FILE *file = fopen("game.save", "w");
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