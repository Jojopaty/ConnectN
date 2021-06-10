#include <ConnectN.h>

gridClass *createAndInitializeGrid_GUI(gridClass *newGrid, int *align)
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
    initializeGridSize(newGrid, align);
    return newGrid;
}

gridClass *initializeGridSize_GUI(gridClass *grid, int *align)
{
    grid->col = grid->lin = *align + 2;
    grid->tokenNumber = 0;
    initializeGrid(grid);
    return grid;
}

gridClass *initializeGrid_GUI(gridClass *newGrid)
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

int safeIntInput_GUI(WINDOW *win)
{
    int num = 0;
    char input[45];

    wgetnstr(win, input, 45);

    if (sscanf(input, "%d", &num) != 1 || num != strtof(input, NULL))
    {
        return -__INT_MAX__;
    }
    return num;
}