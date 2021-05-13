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
    switch (startGame())
    {
    case 1:
         
        createAndInitializeGrid();
        
        break;
    case 2:
        printf(BLU "Loading last saved game\n" RESET);
        break;
    case 3:
        printf(BLU "Bye\n" RESET);
        return EXIT_SUCCESS;
        break;
    default:
    // Should never be executed
        break;
    }

    return EXIT_SUCCESS;
}