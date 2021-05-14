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

GRID* createAndInitializeGrid(){
    GRID* newGrid = NULL;
    newGrid = malloc(sizeof(GRID));
    int input = 0;
    printf("Quelle est le nombre de colones du jeu ? ");
    input = safeIntInput();
    while(input < 1){
        printf(RED "Le nombre entré n'est pas correct\n" RST "Quel est le nombre de colones du jeu ? ");
        input = safeIntInput();
    }
    newGrid->col = input;

    printf("Quelle est le nombre de lignes du jeu ? ");
    input = safeIntInput();
    while(input < 1){
        printf(RED "Le nombre entré n'est pas correct\n" RST "Quel est le nombre de lignes du jeu ? ");
        input = safeIntInput();
    }
    newGrid->lin = input;



    return newGrid;
}

GRID* initializeGrid(GRID* newGrid){
    for(int i = 0; i < (newGrid->col); i++){
        for(int j = 0; j < (newGrid->lin); j++){
            newGrid->grille[i][j] = 'X';
        }
    }
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