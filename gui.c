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
        init_pair(3, COLOR_WHITE, COLOR_RED);   // Selection color (in menus or in game)
        init_pair(4, COLOR_RED, COLOR_WHITE);   // Color of an error in an input

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
        WINDOW *gameBoradWin;
        WINDOW *playerWin;
        WINDOW *moveChoiceWin;
        WINDOW *columnChoiceWin;

        gameWinBkgd = newwin(33, 120, 3, (xMax / 2) - 60);
        wbkgd(gameWinBkgd, COLOR_PAIR(2));
        gameWinBkgdShadow = createShadow(gameWinBkgd);

        gameBoradWin = newwin(17, 48, 5, (xMax / 2) - 55);
        wbkgd(gameBoradWin, COLOR_PAIR(2));

        playerWin = newwin(5, 50, 5, (xMax / 2) + 5);
        wbkgd(playerWin, COLOR_PAIR(2));

        moveChoiceWin = newwin(9, 50, 12, (xMax / 2) + 5);
        wbkgd(moveChoiceWin, COLOR_PAIR(2));

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

            wrefresh(gameWinBkgdShadow);
            box(gameWinBkgd, 0, 0);
            centerPrint(gameWinBkgd, 0, " Connect N ");
            wrefresh(gameWinBkgd);

            box(gameBoradWin, 0, 0);
            centerPrint(gameBoradWin, 0, " Gameboard ");
            wrefresh(gameBoradWin);

            box(playerWin, 0, 0);
            centerPrint(playerWin, 0, " Player ");
            centerPrint(playerWin, 2, players[*player]);
            wrefresh(playerWin);

            box(moveChoiceWin, 0, 0);
            centerPrint(moveChoiceWin, 0, " Action Selection ");
            wrefresh(moveChoiceWin);



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