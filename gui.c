#include <ncurses.h>
#include <ConnectN.h>

#define KEY_ENTER 0x0A // BugFix from ncurses library

WINDOW *createShadow(WINDOW *window);

void gui(gridClass *gameBoard, tokenClass *token, int *toAlign, int *nbPlayers, int *player)
{
    setlocale(LC_ALL, "");

    // setlocale(LC_ALL, "fr-FR");

    initscr();
    start_color();
    noecho();

    cbreak();
    curs_set(0);
    int yMax, xMax;

    getmaxyx(stdscr, yMax, xMax);

    if (!(yMax < 35 || xMax < 130))
    {
        init_pair(1, COLOR_WHITE, COLOR_BLUE);  // Background color
        init_pair(2, COLOR_BLACK, COLOR_WHITE); // Menu and game window color
        init_pair(3, COLOR_WHITE, COLOR_RED);   // Selection color (in menus)
        init_pair(4, COLOR_RED, COLOR_WHITE);   // Color of an error in an input

        init_pair(5, COLOR_WHITE, COLOR_YELLOW); // Color of player YELLOW (player 1)
        init_pair(6, COLOR_WHITE, COLOR_RED);    // Color of player RED (player 2)

        init_pair(7, COLOR_RED, COLOR_WHITE); // Color of the arrow in select column

        bkgd(COLOR_PAIR(1));

        char **players;
        players = (char **)malloc(2 * sizeof(char *));
        for (int i = 0; i < 2; i++)
        {
            players[i] = (char *)malloc(45 * sizeof(char));
        }

        WINDOW *menuWin;
        WINDOW *menuWinShadow;
        WINDOW *smallWin;
        WINDOW *smallWinShadow;
        WINDOW *input;

        menuWin = newwin(15, 40, 14, (xMax / 2) - 20);
        menuWinShadow = createShadow(menuWin);

        smallWin = newwin(7, 50, 14, (xMax / 2) - 25);
        smallWinShadow = createShadow(smallWin);
        wbkgd(smallWin, COLOR_PAIR(2));

        input = newwin(1, 45, 19, (xMax / 2) - 22);
        wbkgd(input, COLOR_PAIR(2));

        WINDOW *gameWinBkgdShadow;
        WINDOW *gameWinBkgd;
        WINDOW *gameBoardWin;
        WINDOW *playerWin;
        WINDOW *moveChoiceWin;
        WINDOW *columnChoiceWin;

        gameWinBkgd = newwin(33, 120, 3, (xMax / 2) - 60);
        wbkgd(gameWinBkgd, COLOR_PAIR(2));
        gameWinBkgdShadow = createShadow(gameWinBkgd);

        gameBoardWin = newwin(23, 54, 5, (xMax / 2) - 55);
        wbkgd(gameBoardWin, COLOR_PAIR(2));

        playerWin = newwin(12, 50, 5, (xMax / 2) + 5);
        wbkgd(playerWin, COLOR_PAIR(2));

        moveChoiceWin = newwin(9, 50, 19, (xMax / 2) + 5);
        wbkgd(moveChoiceWin, COLOR_PAIR(2));

        columnChoiceWin = newwin(1, 1, 0, 0);
        wbkgd(columnChoiceWin, COLOR_PAIR(2));

        startupAnimation(yMax, xMax);

        switch (startupMenu(menuWin, menuWinShadow))
        {
        case 0:

            *nbPlayers = playerNumChoice(smallWin, smallWinShadow);

            playerNames(smallWin, smallWinShadow, input, xMax, nbPlayers, players);

            *toAlign = gridSizeChoice(smallWin, smallWinShadow, input);

            curs_set(0);
            noecho();

            gameBoard = initializeGridSize(gameBoard, toAlign);

            *player = rand() % 2;

            clear();
            refresh();

            initializeGameWin(gameWinBkgdShadow, gameWinBkgd, gameBoardWin, playerWin, moveChoiceWin, columnChoiceWin, gameBoard, players);

            showGrid_GUI(gameBoard, gameBoardWin);


            int column = 0;
            int hasPlayed = 0;
            int hasWon = -1;
            int quit = 0;
            int draw = 0;
            int removedColumn = 0;
            int moveChoice = 0;
            while (hasWon < 0 && quit < 1 && draw < 1)
            {
                token->type = ((*player == 1) ? 'O' : 'X');
                hasPlayed = 0;

                centerPrint(playerWin, 3, players[*player]);
                wrefresh(playerWin);

                if (*nbPlayers > 1 || *player == 1)
                {
                    do
                    {
                        moveChoice = moveChoice_GUI(moveChoiceWin, gameBoard->tokenNumber);
                        switch (moveChoice)
                        {
                        case 1:

                            column = selectColumn_GUI(gameBoard, columnChoiceWin, moveChoice, removedColumn);
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

                            column = selectColumn_GUI(gameBoard, columnChoiceWin, moveChoice, removedColumn);
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
                    showGrid_GUI(gameBoard, gameBoardWin);
                    // for (int i = 0; i < (4 * column - 2); i++)
                    // {
                    //     printf(" ");
                    // }
                    // (*player == 1) ? printf(YEL "%c\n" RST, token->lastMove) : printf(RED "%c\n" RST, token->lastMove);
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

            getch();
            endwin();

            break;
        case 1:

            getch();
            endwin();
            break;
        case 2:
            clear();
            beep();
            mvprintw(6, (xMax / 2) - 2, "Bye!");
            refresh();
            delay(1000);
            endwin();
            break;
        default:
            break;
        }
    }
    else
    {
        printw("La taille de la fenêtre est trop petite, impossible de lancer le programe.\nCe programme necessite une taille minimale de 40 lignes et 130 colonnes pour fonctionner correctement.\nLa taille actuelle est : %d lignes et %d colonnes.\nPour jouer sans interface graphique, lancez le programme avec la commande : \"./ConnectN.exe -nogui\"\n\nYour window size is too small for the game to properly function.\nThis game needs a window size of at least 40 lines by 130 columns.\nThe current window size is %d lines and %d columns.\nIf you don't want to play with GUI, lanuch the game with \"./ConnectN.exe -nogui\"\n\nAppuyez sur une touche pour continuer.\nPress any key to continue", yMax, xMax, yMax, xMax);
        getch();
        endwin();
    }
}