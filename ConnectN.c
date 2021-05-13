#include "ConnectN.h"

int startGame()
{
    clear();
    int startChoice;
    printf(GRN "Bievenue dans le jeu du Puissance N" RESET "\n1. Nouvelle partie\n2. Continuer la dernière partie\n3. Quitter\nQuel est votre choix ? ");
    scanf("%d", &startChoice);
    while (startChoice < 1 || startChoice > 3)
    {
        clear();
        printf(RED "Entrée incorrecte, veuillez recommencer" RESET "\n1. Nouvelle partie\n2. Continuer la dernière partie\n3. Quitter\nQuel est votre choix ? ");
        scanf("%d", &startChoice);
    }
    return startChoice;
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