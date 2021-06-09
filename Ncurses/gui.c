#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <ConnectN.h>

#define KEY_ENTER 0x0A // BugFix from ncurses library

void delay(int milliseconds);

WINDOW *createShadow(WINDOW *window);

int main()
{
    setlocale(LC_ALL, "");

    // setlocale(LC_ALL, "fr-FR");

    initscr();
    start_color();
    noecho();

    cbreak();
    curs_set(0);
    int yMax, xMax;

    int nbPlayers=0;

    getmaxyx(stdscr, yMax, xMax);

    if (!(yMax < 35 || xMax < 130))
    {
        init_pair(1, COLOR_WHITE, COLOR_BLUE);  // Background color
        init_pair(2, COLOR_BLACK, COLOR_WHITE); // Menu and game window color
        init_pair(3, COLOR_WHITE, COLOR_RED);   // Selection color (in menus or in game)

        bkgd(COLOR_PAIR(1));

        char players[2][45];

        WINDOW *gameWin;
        WINDOW *menuWin;
        WINDOW *shadowMenuWin;
        WINDOW *input;
        WINDOW *gameBoradWin;
        WINDOW *playerWin;
        WINDOW *timeWin;
        WINDOW *playerNamesWin;
        WINDOW *playerNamesWinShadow;

        shadowMenuWin = newwin(15, 40, 15, (xMax / 2) - 19);
        menuWin = newwin(15, 40, 14, (xMax / 2) - 20);

        char *msg = "Welcome to the fabulous game of";

        for (int i = 0; i < 32; i++)
        {
            mvprintw(2, (xMax / 2) - 16 + i, "%c", msg[i]);
            refresh();
            delay(50);
        }
        delay(600);
        char welcomeMsg[6][74] = {{" .o88b.  .d88b.  d8b   db d8b   db d88888b  .o88b. d888888b      d8b   db"},
                                  {"d8P  Y8 .8P  Y8. 888o  88 888o  88 88'     d8P  Y8 `~~88~~'      888o  88"},
                                  {"8P      88    88 88V8o 88 88V8o 88 88ooooo 8P         88         88V8o 88"},
                                  {"8b      88    88 88 V8o88 88 V8o88 88~~~~~ 8b         88         88 V8o88"},
                                  {"Y8b  d8 `8b  d8' 88  V888 88  V888 88.     Y8b  d8    88         88  V888"},
                                  {" `Y88P'  `Y88P'  VP   V8P VP   V8P Y88888P  `Y88P'    YP         VP   V8P"}};

        for (int i = 0; i < 6; i++)
        {
            mvprintw(i + 4, (xMax / 2) - 37, "%s", welcomeMsg[i]);
            delay(75);
            refresh();
        }
        mvprintw(yMax - 1, 0, "Created by Thibaut Lemaitre, Matis Ressicaud and Edgar Boule - TC02");
        refresh();
        wrefresh(shadowMenuWin);

        wbkgd(menuWin, COLOR_PAIR(2));
        box(menuWin, 0, 0);
        mvwprintw(menuWin, 0, 9, " What is your choice? ");
        char items[3][25] = {{"New game"}, {"Continue last saved game"}, {"Quit"}};
        char currentItem[25];
        for (int i = 0; i < 3; i++)
        {
            mvwprintw(menuWin, 2 * i + 4, 3, "%s", items[i]);
        }
        wrefresh(menuWin);

        int choice = 0, curr = 0;

        keypad(menuWin, TRUE);

        wattron(menuWin, COLOR_PAIR(3));
        sprintf(currentItem, "%-25s", items[choice]);
        mvwprintw(menuWin, 2 * choice + 4, 3, "%s", currentItem);
        wattroff(menuWin, COLOR_PAIR(3));

        while ((curr = wgetch(menuWin)) != KEY_ENTER)
        {
            sprintf(currentItem, "%-25s", items[choice]);
            mvwprintw(menuWin, 2 * choice + 4, 3, "%s", currentItem);

            switch (curr)
            {
            case KEY_UP:
                choice--;
                choice = (choice < 0) ? 2 : choice;
                break;

            case KEY_DOWN:
                choice++;
                choice = (choice > 2) ? 0 : choice;
                break;
            default:
                break;
            }
            wattron(menuWin, COLOR_PAIR(3));
            sprintf(currentItem, "%-25s", items[choice]);
            mvwprintw(menuWin, 2 * choice + 4, 3, "%s", currentItem);
            wattroff(menuWin, COLOR_PAIR(3));
        }

        switch (choice)
        {
        case 0:
            werase(menuWin);
            box(menuWin, 0, 0);
            mvwprintw(menuWin, 0, 15, " Players ");
            mvwprintw(menuWin, 4, 3, "How many players are there ?");

            for (int i = 1; i < 3; i++)
            {
                mvwprintw(menuWin, 7, 10 + (i * 5), " %d ", i);
            }

            wattron(menuWin, COLOR_PAIR(3));
            wrefresh(menuWin);

            choice = 1;
            mvwprintw(menuWin, 7, 10 + (choice * 5), " %d ", choice);
            wattroff(menuWin, COLOR_PAIR(3));

            while ((curr = wgetch(menuWin)) != KEY_ENTER)
            {
                mvwprintw(menuWin, 7, 10 + (choice * 5), " %d ", choice);

                switch (curr)
                {
                case KEY_RIGHT:
                    choice--;
                    choice = (choice < 1) ? 2 : choice;
                    break;

                case KEY_LEFT:
                    choice++;
                    choice = (choice > 2) ? 1 : choice;
                    break;
                default:
                    break;
                }
                wattron(menuWin, COLOR_PAIR(3));
                mvwprintw(menuWin, 7, 10 + (choice * 5), " %d ", choice);
                wattroff(menuWin, COLOR_PAIR(3));
            }
            nbPlayers = choice;

            wrefresh(menuWin);

            clear();
            playerNamesWin = newwin(7, 50, 14, (xMax / 2) - 25);
            playerNamesWinShadow = createShadow(playerNamesWin);
            wbkgd(playerNamesWin, COLOR_PAIR(2));
            box(playerNamesWin, 0, 0);
            refresh();
            wrefresh(playerNamesWinShadow);
            mvwprintw(playerNamesWin, 0, 21, " Names ");
            input = newwin(1, 45, 18, (xMax / 2) - 22);
            wbkgd(input, COLOR_PAIR(2));
            echo();
            curs_set(1);
            for (int i = 0; i < nbPlayers; i++)
            {
                mvwprintw(playerNamesWin, 2, 3, "What's the name of player %d?", i + 1);
                wrefresh(playerNamesWin);
                wrefresh(input);
                mvwprintw(input, 0, 0, "> ");
                wrefresh(input);
                wgetnstr(input, players[i], 44);
                werase(input);
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

void delay(int milliseconds)
{
    long pause;
    clock_t now, then;

    pause = milliseconds * (CLOCKS_PER_SEC / 1000);
    now = then = clock();
    while ((now - then) < pause)
        now = clock();
}

WINDOW *createShadow(WINDOW *window)
{
    int yBeg, xBeg, yMax, xMax;
    getbegyx(window, yBeg, xBeg);
    getmaxyx(window, yMax, xMax);
    return newwin(yMax, xMax, (yBeg + 1), (xBeg + 1));
}