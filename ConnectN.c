#include <ConnectN.h>

int startGame(int *nbPlayer)
{
    consoleClear();
    int startChoice;
    printf(GRN "Bievenue dans le jeu du Puissance N" RST "\n1. Nouvelle partie\n2. Continuer la dernière partie\n3. Quitter\nQuel est votre choix ? ");
    startChoice = safeIntInput();

    while (startChoice < 1 || startChoice > 3)
    {
        consoleClear();
        printf(RED "Entrée incorrecte, veuillez recommencer" RST "\n1. Nouvelle partie\n2. Continuer la dernière partie\n3. Quitter\nQuel est votre choix ? ");
        startChoice = safeIntInput();
    }
    consoleClear();

    if (startChoice != 3)
    {
        printf(GRN "Choix du nombre de joueurs\n" RST "1. Partie solo contre l'ordinateur\n2. Partie à deux joueurs\nQuel est votre choix ? ");
        *nbPlayer = safeIntInput();
        while (*nbPlayer < 1 || *nbPlayer > 2)
        {
            consoleClear();
            printf(RED "Entrée incorrecte, veuillez recommencer\n" RST "Choix du nombre de joueurs\n1. Partie solo contre l'ordinateur\n2. Partie à deux joueurs\nQuel est votre choix ? ");
            *nbPlayer = safeIntInput();
        }
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
    newGrid = initializeGridSize(newGrid, align);
    return newGrid;
}

gridClass *initializeGridSize(gridClass *grid, int *align)
{
    grid->col = grid->lin = *align + 2;
    grid->tokenNumber = 0;
    grid = initializeGrid(grid);
    return grid;
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

void game(gridClass *gameBoard, tokenClass *token, int *toAlign, int *nbPlayers, int *player)
{
    int column = 0;
    int hasPlayed = 0;
    int hasWon = -1;
    int quit = 0;
    int draw = 0;
    int removedColumn = 0;
    while (hasWon < 0 && quit < 1 && draw < 1)
    {
        token->type = ((*player == 1) ? 'O' : 'X');
        hasPlayed = 0;

        if (*nbPlayers > 1 || *player == 1)
        {
            printf("\nJoueur %d\n", *player);

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
                    hasPlayed = removeToken(gameBoard, token, column);
                    removedColumn = (hasPlayed > 0) ? column : 0;
                    break;
                case 3:
                    saveToFile(gameBoard, (*player == 1) ? 2 : 1);
                    quit = 1;
                    break;
                default:
                    break;
                }

            } while (quit != 1 && hasPlayed != 1);
        }
        else
        {
            printf("\nL'ordinateur joue\n");

            switch (aiAddOrRemove())
            {
            case 1:
                do
                {
                    column = aiSelectColumn(gameBoard);
                    hasPlayed = addToken(gameBoard, column, token);
                } while (hasPlayed != 1);
                printf(GRN "L'ordinateur a ajouté un jeton dans la colonne %d\n" RST, column);
                break;
            case 2:
                do
                {
                    column = aiSelectColumn(gameBoard);
                    hasPlayed = removeToken(gameBoard, token, column);
                } while (hasPlayed != 1);
                printf(GRN "L'ordinateur a retiré un jeton de la colonne %d\n" RST, column);
                break;
            default:
                break;
            }
            delay(1500);
        }
        if (quit < 1)
        {
            consoleClear();
            showGrid(gameBoard);
            for (int i = 0; i < (4 * column - 2); i++)
            {
                printf(" ");
            }
            (*player == 1) ? printf(YEL "%c\n" RST, token->lastMove) : printf(RED "%c\n" RST, token->lastMove);
            hasWon = checkWinner(gameBoard, toAlign, token);
            draw = checkDraw(gameBoard);
            if (hasWon > -1)
            {
                if (*nbPlayers > 1 || *player == 1)
                {
                    printf(CYN "Le joueur %d a gagné. Félicitations !\n" RST, *player);
                }
                else
                {
                    printf(CYN "L'ordinateur a gagné !\n" RST);
                }
            }
            else if (draw > 0)
            {
                printf(YEL "Egalité ! Toute la surface de jeu a été remplie sans qu'un joueur ne gagne.\n" RST);
            }
            *player = (*player == 1) ? 2 : 1;
        }
        else
        {
            printf(GRN "\nLa partie a été enregistrée. Pour la continuer, sélectionnez 'Continuer la dernière partie' au prochain démarrage du jeu.\n" CYN "A bientôt !\n" RST);
        }
    }
}

int aiAddOrRemove()
{
    int choice = rand() % 100;
    if (choice > 5)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

int aiSelectColumn(gridClass *grid)
{
    int choice = rand() % grid->col + 1;
    return choice;
}

int checkDraw(gridClass *grid)
{
    if (grid->tokenNumber == (grid->col * grid->lin))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void freeMemory(gridClass *grid, tokenClass *token, int *num, int *num2, int *num3)
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

    free(token);
    token = NULL;

    free(num);
    num = NULL;
    free(num2);
    num2 = NULL;
    free(num3);
    num3 = NULL;
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
        printf(GRN "\nQue souhaitez-vous faire ?" RST "\n1. Ajouter un jeton\n2. Sauvegarder et quitter\nQuel est votre choix ? ");
        int choice = safeIntInput();

        while (choice < 1 || choice > 2)
        {
            printf(RED "\nEntrée incorrecte, veuillez recommencer" RST "\n1. Ajouter un jeton\n2. Sauvegarder et quitter\nQuel est votre choix ? ");
            choice = safeIntInput();
        }

        return (choice == 1) ? choice : choice + 1;
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
            token->lastMove = '+';
            return 1;
        }
    }
}

int removeToken(gridClass *grid, tokenClass *token, int col)
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
            token->lastMove = '-';
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
        else if (aligned >= N)
        {
            return 1;
        }
        else
        {
            aligned = 0;
        }
    }
    if (aligned >= N)
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
        else if (aligned >= N)
        {
            return 1;
        }
        else
        {
            aligned = 0;
        }
    }
    
    if (aligned >= N)
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
        else if (aligned >= N)
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
    if (aligned >= N)
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
        else if (aligned >= N)
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
    if (aligned >= N)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void saveToFile(gridClass *grid, int nextPlay)
{
    FILE *file = fopen("game.save", "w");
    char array[(grid->lin - 1)];
    // char size[16];
    // char player[16];
    // sprintf(player, "%d\n", nextPlay);
    // sprintf(size, "%d\n", grid->col);
    fprintf(file, "Next player :   \t%d\n", nextPlay);
    fprintf(file, "Tokens to align :\t%d\n", grid->col - 2);
    fprintf(file, "GameBoard :\n");
    for (int i = 0; i < grid->lin; i++)
    {
        strcpy(array, grid->grille[i]);

        fputs(array, file);
        fputs("\n", file);
    }
    fclose(file);
}

int loadFromFile(gridClass *grid, int *player, int *align)
{
    FILE *file = fopen("game.save", "r");
    if (file == NULL)
    {
        printf("Une erreur est survenue lors de la lecture du fichier");
        return -1;
    }
    else
    {
        char line[1024];

        fgets(line, 1024, file); // Reading first line of the file aka the next player
        sscanf(line, "Next player :   \t%d", player);

        fgets(line, 1024, file); // Reading second line of the file aka the number of columns and lines (they are equal since the board is a saquare)
        sscanf(line, "Tokens to align :\t%d", align);

        fgets(line, 1024, file); // Gets "GameBoard" but dumps it as it is not necessary in load function.

        initializeGridSize(grid, align);
        for (int i = 0; i < *align + 2; i++)
        {
            fgets(line, 1024, file); //Gets the line of characers corresponding to the line of the grid
            for (int j = 0; j < *align + 2; j++)
            {
                grid->grille[i][j] = line[j]; //Gets the individual character for the specified coordinates in the grid and stores it
                if (grid->grille[i][j] == 'X' || grid->grille[i][j] == 'O')
                {
                    grid->tokenNumber++;
                }
            }
        }
        return *player - 1; //Returns the next player to play (0 for player 1 and 1 for player 2 according to the directives)
    }
}

void consoleClear()
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
    char input[10];

    fgets(input, 10, stdin);
    fflush(stdin);

    if (sscanf(input, "%d", &num) != 1 || num != strtof(input, NULL))
    {
        return -__INT_MAX__;
    }
    return num;
}

void delay(int milliseconds)
{
    long pause;
    clock_t now, then;

    pause = milliseconds * (CLOCKS_PER_SEC / 1000);
    now = then = clock();
    while ((now - then) < pause)
        now = clock();
}