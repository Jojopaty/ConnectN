/**
 * @file gui.c
 * @author Edgar Boule (edgar.boule@utbm.fr), Thibaut Lemaître (thibaut.lemaitre@utbm.fr), Matis Ressicaud (matis.ressicaud@utbm.fr)
 * @brief File storing all the functions used in the GUI version of the game.
 * @version 1.0
 * @date 2021-05-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <ConnectN.h>

#define KEY_ENTER_FIXED 0x0A // BugFix from ncurses library

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
        init_pair(8, COLOR_GREEN, COLOR_WHITE);
        init_pair(9, COLOR_MAGENTA, COLOR_WHITE);

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

            initializeGameWin(gameWinBkgdShadow, gameWinBkgd, gameBoardWin, playerWin, moveChoiceWin, columnChoiceWin, gameBoard, players, *player);

            showGrid_GUI(gameBoard, gameBoardWin);

            game_GUI(smallWin, smallWinShadow, gameWinBkgd, playerWin, moveChoiceWin, columnChoiceWin, gameBoardWin, gameBoard, token, player, nbPlayers, toAlign, players);

            getch();

            delwin(menuWin);
            delwin(menuWinShadow);
            delwin(smallWin);
            delwin(smallWinShadow);
            delwin(input);
            delwin(gameWinBkgd);
            delwin(gameWinBkgdShadow);
            delwin(gameBoardWin);
            delwin(playerWin);
            delwin(moveChoiceWin);
            delwin(columnChoiceWin);

            for (int i = 0; i < 2; i++)
            {
                free(players[i]);
                players[i] = NULL;
            }
            free(players);
            players = NULL;

            endwin();

            break;
        case 1:
            if (loadFromFile(gameBoard, player, toAlign) == -1)
            {
                clear();
                refresh();

                werase(smallWin);
                box(smallWin, 0, 0);
                centerPrint(smallWin, 0, "ERROR");
                centerPrint(smallWin, 3, "An error occures when oppening");
                centerPrint(smallWin, 4, "the file. Maybe it does not exists.");
                smallWinShadow = createShadow(smallWin);
                wrefresh(smallWinShadow);
                wrefresh(smallWin);
            }
            else
            {
                *nbPlayers = playerNumChoice(smallWin, smallWinShadow);

                playerNames(smallWin, smallWinShadow, input, xMax, nbPlayers, players);

                curs_set(0);
                noecho();

                clear();
                refresh();

                initializeGameWin(gameWinBkgdShadow, gameWinBkgd, gameBoardWin, playerWin, moveChoiceWin, columnChoiceWin, gameBoard, players, *player);

                showGrid_GUI(gameBoard, gameBoardWin);

                game_GUI(smallWin, smallWinShadow, gameWinBkgd, playerWin, moveChoiceWin, columnChoiceWin, gameBoardWin, gameBoard, token, player, nbPlayers, toAlign, players);
            }
            getch();

            delwin(menuWin);
            delwin(menuWinShadow);
            delwin(smallWin);
            delwin(smallWinShadow);
            delwin(input);
            delwin(gameWinBkgd);
            delwin(gameWinBkgdShadow);
            delwin(gameBoardWin);
            delwin(playerWin);
            delwin(moveChoiceWin);
            delwin(columnChoiceWin);

            for (int i = 0; i < 2; i++)
            {
                free(players[i]);
                players[i] = NULL;
            }
            free(players);
            players = NULL;

            endwin();
            break;
        case 2:
            clear();
            beep();
            mvprintw(6, (xMax / 2) - 2, "Bye!");
            refresh();
            delay(1000);

            delwin(menuWin);
            delwin(menuWinShadow);
            delwin(smallWin);
            delwin(smallWinShadow);
            delwin(input);
            delwin(gameWinBkgd);
            delwin(gameWinBkgdShadow);
            delwin(gameBoardWin);
            delwin(playerWin);
            delwin(moveChoiceWin);
            delwin(columnChoiceWin);

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

void centerPrint(WINDOW *win, int line, char *title)
{
    int x = getmaxx(win);
    mvwprintw(win, line, (x - strlen(title)) / 2, title);
}

WINDOW *createShadow(WINDOW *window)
{
    int yBeg, xBeg, yMax, xMax;
    getbegyx(window, yBeg, xBeg);
    getmaxyx(window, yMax, xMax);
    return newwin(yMax, xMax, (yBeg + 1), (xBeg + 1));
}

void errorON(WINDOW *win, int box)
{
    beep();
    wbkgd(win, COLOR_PAIR(3));
    werase(win);
    if (box == true)
    {
        box(win, 0, 0);
        centerPrint(win, 0, "   ERROR   ");
    }

    wattron(win, COLOR_PAIR(3));
}

void errorOFF(WINDOW *win, int box)
{
    wbkgd(win, COLOR_PAIR(2));
    wattron(win, COLOR_PAIR(2));
    werase(win);
    if (box == true)
    {
        box(win, 0, 0);
    }
}

void strongStandoutON(WINDOW *win)
{
    wattron(win, A_UNDERLINE);
    wattron(win, A_BOLD);
    wattron(win, A_BLINK);
}

void strongStandoutOFF(WINDOW *win)
{
    wattroff(win, A_UNDERLINE);
    wattroff(win, A_BOLD);
    wattroff(win, A_BLINK);
}

void startupAnimation(int yMax, int xMax)
{
    clear();
    refresh();
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
}

int startupMenu(WINDOW *menuWin, WINDOW *menuWinShadow)
{
    wrefresh(menuWinShadow);
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
    sprintf(currentItem, "%-24s", items[choice]);
    mvwprintw(menuWin, 2 * choice + 4, 3, "%s", currentItem);
    wattroff(menuWin, COLOR_PAIR(3));

    while ((curr = wgetch(menuWin)) != KEY_ENTER_FIXED)
    {
        sprintf(currentItem, "%-24s", items[choice]);
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
        sprintf(currentItem, "%-24s", items[choice]);
        mvwprintw(menuWin, 2 * choice + 4, 3, "%s", currentItem);
        wattroff(menuWin, COLOR_PAIR(3));
    }
    keypad(menuWin, FALSE);

    return choice;
}

int playerNumChoice(WINDOW *smallWin, WINDOW *smallWinShadow)
{
    clear();
    refresh();
    box(smallWin, 0, 0);
    keypad(smallWin, TRUE);

    centerPrint(smallWin, 0, " Players ");
    centerPrint(smallWin, 2, "How many players are there?");

    for (int i = 1; i < 3; i++)
    {
        mvwprintw(smallWin, 4, 17 + ((i - 1) * 10), " %d ", i);
    }

    wattron(smallWin, COLOR_PAIR(3));
    wrefresh(smallWinShadow);
    wrefresh(smallWin);

    int choice = 1, curr = 0;

    mvwprintw(smallWin, 4, 17 + ((choice - 1) * 10), " %d ", choice);
    wattroff(smallWin, COLOR_PAIR(3));

    while ((curr = wgetch(smallWin)) != KEY_ENTER_FIXED)
    {
        mvwprintw(smallWin, 4, 17 + ((choice - 1) * 10), " %d ", choice);

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
        wattron(smallWin, COLOR_PAIR(3));
        mvwprintw(smallWin, 4, 17 + ((choice - 1) * 10), " %d ", choice);
        wattroff(smallWin, COLOR_PAIR(3));
        wrefresh(smallWin);
    }

    wclear(smallWin);

    return choice;
}

void playerNames(WINDOW *smallWin, WINDOW *smallWinShadow, WINDOW *inputWin, int xMax, int *nbPlayers, char **players)
{
    wresize(smallWin, 8, 50);
    smallWinShadow = createShadow(smallWin);
    box(smallWin, 0, 0);
    wrefresh(smallWinShadow);
    echo();
    curs_set(1);

    for (int i = 0; i < *nbPlayers; i++)
    {
        centerPrint(smallWin, 0, " Names ");
        mvwprintw(smallWin, 2, 3, "What's the name of player %d?", i + 1);
        mvwprintw(smallWin, 3, 3, "The name cannot be blank");
        wrefresh(smallWin);
        wrefresh(inputWin);
        mvwprintw(inputWin, 0, 0, "> ");
        wrefresh(inputWin);
        wgetnstr(inputWin, players[i], 44);
        // wgetnstr(inputWin, input, 45);
        // sscanf(input, "%s", &(players[i]));
        werase(inputWin);

        while (strcmp(players[i], "\0") == 0)
        {
            errorON(smallWin, TRUE);
            errorON(inputWin, FALSE);

            mvwprintw(smallWin, 2, 3, "What's the name of player %d?", i + 1);
            strongStandoutON(smallWin);
            mvwprintw(smallWin, 3, 3, "The name cannot be blank");
            strongStandoutOFF(smallWin);
            wrefresh(smallWin);
            wrefresh(inputWin);
            mvwprintw(inputWin, 0, 0, "> ");
            wrefresh(inputWin);
            wgetnstr(inputWin, players[i], 44);

            errorOFF(smallWin, TRUE);
            errorOFF(inputWin, FALSE);
        }
    }
    if (*nbPlayers == 1)
    {
        players[1] = "Computer";
    }
}

int gridSizeChoice(WINDOW *smallWin, WINDOW *smallWinShadow, WINDOW *input)
{
    mvwprintw(smallWin, 0, 19, " Grid size ");
    mvwprintw(smallWin, 2, 3, "How many tokens should be aligned to win?");
    mvwprintw(smallWin, 3, 3, "Should be between 3 and 15");
    mvwprintw(input, 0, 0, "> ");
    wrefresh(smallWin);
    wrefresh(input);
    int toAlign = safeIntInput_GUI(input);

    while (toAlign < 3 || toAlign > 15)
    {

        errorON(smallWin, TRUE);
        errorON(input, FALSE);

        mvwprintw(smallWin, 2, 3, "How many tokens should be aligned to win?");

        strongStandoutON(smallWin);

        mvwprintw(smallWin, 3, 3, "Should be between 3 and 15");

        strongStandoutOFF(smallWin);

        mvwprintw(input, 0, 0, "> ");

        wrefresh(smallWin);
        wrefresh(input);

        toAlign = safeIntInput_GUI(input);

        errorOFF(smallWin, TRUE);
        errorOFF(input, FALSE);
    }
    return toAlign;
}

void showGrid_GUI(gridClass *grid, WINDOW *win)
{
    int x = getmaxx(win);

    for (int i = 0; i < grid->col + 1; i++)
    {
        wmove(win, 2, ((x - grid->col * 3) / 2) + 3 * i);

        wattron(win, COLOR_PAIR(1));
        wvline(win, ACS_VLINE, grid->lin);
        wattroff(win, COLOR_PAIR(1));
    }

    for (int i = 0; i < grid->lin; i++)
    {
        for (int j = 0; j < grid->col; j++)
        {
            if (grid->grille[i][j] == 'O')
            {

                wattron(win, COLOR_PAIR(5));
                mvwprintw(win, i + 2, (((x - grid->col * 3) / 2) + 3 * j) + 1, "  ");
                wattroff(win, COLOR_PAIR(5));
            }
            else if (grid->grille[i][j] == 'X')
            {
                wattron(win, COLOR_PAIR(6));
                mvwprintw(win, i + 2, (((x - grid->col * 3) / 2) + 3 * j) + 1, "  ");
                wattroff(win, COLOR_PAIR(6));
            }
            else
            {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, i + 2, (((x - grid->col * 3) / 2) + 3 * j) + 1, "  ");
                wattroff(win, COLOR_PAIR(2));
            }
        }
    }
    wrefresh(win);
}

void initializeGameWin(WINDOW *gameWinBkgdShadow, WINDOW *gameWinBkgd, WINDOW *gameBoradWin, WINDOW *playerWin, WINDOW *moveChoiceWin, WINDOW *columnChoiceWin, gridClass *grid, char **players, int player)
{
    wrefresh(gameWinBkgdShadow);
    box(gameWinBkgd, 0, 0);
    centerPrint(gameWinBkgd, 0, " Connect N ");
    wrefresh(gameWinBkgd);

    box(gameBoradWin, 0, 0);
    centerPrint(gameBoradWin, 0, " Gameboard ");
    wrefresh(gameBoradWin);

    initializePlayerWin(playerWin, players, player);

    initializeMoveChoiceWin(moveChoiceWin);

    int yBeg, xBeg, xMax;
    getbegyx(gameBoradWin, yBeg, xBeg);
    xMax = getmaxx(gameBoradWin);

    mvwin(columnChoiceWin, yBeg + 2 + grid->col, ((xMax - grid->col * 3) / 2) + xBeg);
    wresize(columnChoiceWin, 1, (grid->col * 3) + 1);
    wbkgd(columnChoiceWin, COLOR_PAIR(2));
    wrefresh(columnChoiceWin);
}

void initializeMoveChoiceWin(WINDOW *moveChoiceWin)
{
    werase(moveChoiceWin);
    box(moveChoiceWin, 0, 0);
    centerPrint(moveChoiceWin, 0, " Action Selection ");
    wrefresh(moveChoiceWin);
}

void initializePlayerWin(WINDOW *playerWin, char **players, int player)
{
    werase(playerWin);
    box(playerWin, 0, 0);
    centerPrint(playerWin, 0, " Player ");
    wattron(playerWin, A_UNDERLINE);
    centerPrint(playerWin, 2, "Current player");
    wattron(playerWin, COLOR_PAIR(5));
    centerPrint(playerWin, 5, "  Player YELLOW  ");
    wattroff(playerWin, COLOR_PAIR(5));
    wattron(playerWin, COLOR_PAIR(6));
    centerPrint(playerWin, 8, "  Player RED  ");
    wattroff(playerWin, COLOR_PAIR(6));
    wattroff(playerWin, A_UNDERLINE);

    int currPlayer = (player == 1) ? 0 : 1;

    centerPrint(playerWin, 3, players[currPlayer]);
    centerPrint(playerWin, 6, players[0]);
    centerPrint(playerWin, 9, players[1]);

    wrefresh(playerWin);
}

int moveChoice_GUI(WINDOW *moveChoiceWin, int tokenNumber)
{
    initializeMoveChoiceWin(moveChoiceWin);

    int choice = 0, curr = 0;
    keypad(moveChoiceWin, TRUE);

    if (tokenNumber > 0)
    {
        char items[3][15] = {{"  Add token   "}, {" Remove token "}, {"     Quit     "}};
        for (int i = 0; i < 3; i++)
        {

            centerPrint(moveChoiceWin, 2 * i + 2, items[i]);
        }
        wrefresh(moveChoiceWin);
        wattron(moveChoiceWin, COLOR_PAIR(3));
        centerPrint(moveChoiceWin, 2 * choice + 2, items[choice]);
        wattroff(moveChoiceWin, COLOR_PAIR(3));

        while ((curr = wgetch(moveChoiceWin)) != KEY_ENTER_FIXED)
        {

            centerPrint(moveChoiceWin, 2 * choice + 2, items[choice]);

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
            wattron(moveChoiceWin, COLOR_PAIR(3));
            centerPrint(moveChoiceWin, 2 * choice + 2, items[choice]);
            wattroff(moveChoiceWin, COLOR_PAIR(3));
        }
        werase(moveChoiceWin);
        wattron(moveChoiceWin, COLOR_PAIR(8));
        initializeMoveChoiceWin(moveChoiceWin);
        centerPrint(moveChoiceWin, 4, items[choice]);
        wattroff(moveChoiceWin, COLOR_PAIR(8));
        wrefresh(moveChoiceWin);

        keypad(moveChoiceWin, FALSE);
        choice++;
    }
    else
    {
        char items[2][15] = {{"  Add token   "}, {"     Quit     "}};
        for (int i = 0; i < 2; i++)
        {
            centerPrint(moveChoiceWin, 2 * i + 3, items[i]);
        }
        wrefresh(moveChoiceWin);
        wattron(moveChoiceWin, COLOR_PAIR(3));
        centerPrint(moveChoiceWin, 2 * choice + 3, items[choice]);
        wattroff(moveChoiceWin, COLOR_PAIR(3));

        while ((curr = wgetch(moveChoiceWin)) != KEY_ENTER_FIXED)
        {

            centerPrint(moveChoiceWin, 2 * choice + 3, items[choice]);

            switch (curr)
            {
            case KEY_UP:
                choice--;
                choice = (choice < 0) ? 1 : choice;
                break;

            case KEY_DOWN:
                choice++;
                choice = (choice > 1) ? 0 : choice;
                break;
            default:
                break;
            }
            wattron(moveChoiceWin, COLOR_PAIR(3));
            centerPrint(moveChoiceWin, 2 * choice + 3, items[choice]);
            wattroff(moveChoiceWin, COLOR_PAIR(3));
        }
        werase(moveChoiceWin);
        wattron(moveChoiceWin, COLOR_PAIR(8));
        initializeMoveChoiceWin(moveChoiceWin);
        centerPrint(moveChoiceWin, 4, items[choice]);
        wattroff(moveChoiceWin, COLOR_PAIR(8));
        wrefresh(moveChoiceWin);

        keypad(moveChoiceWin, FALSE);
        choice = (choice == 1) ? 3 : 1;
    }
    return choice;
}

int selectColumn_GUI(gridClass *grid, WINDOW *columnChoiceWin, int moveChoice, int removedColumn)
{
    keypad(columnChoiceWin, TRUE);
    int choice = 0, curr = 0;

    if (moveChoice == 1)
    {
        while (grid->grille[0][choice] != '_' || (choice + 1) == removedColumn)
        {
            choice++;
        }
    }
    else
    {
        while (grid->grille[grid->col - 1][choice] == '_')
        {
            choice++;
        }
    }

    wattron(columnChoiceWin, COLOR_PAIR(7));
    werase(columnChoiceWin);
    mvwprintw(columnChoiceWin, 0, (3 * choice) + 1, "/\\");
    wattroff(columnChoiceWin, COLOR_PAIR(7));
    wrefresh(columnChoiceWin);

    while ((curr = wgetch(columnChoiceWin)) != KEY_ENTER_FIXED)
    {
        switch (curr)
        {
        case KEY_RIGHT:
            if (moveChoice == 1)
            {
                do
                {
                    choice++;
                    choice = (choice > grid->col - 1) ? 0 : choice;
                } while (grid->grille[0][choice] != '_' || (choice + 1) == removedColumn);
            }
            else
            {
                do
                {
                    choice++;
                    choice = (choice > grid->col - 1) ? 0 : choice;
                } while (grid->grille[grid->col - 1][choice] == '_');
            }
            break;

        case KEY_LEFT:
            if (moveChoice == 1)
            {
                do
                {
                    choice--;
                    choice = (choice < 0) ? grid->col - 1 : choice;
                } while (grid->grille[0][choice] != '_' || (choice + 1) == removedColumn);
            }
            else
            {
                do
                {
                    choice--;
                    choice = (choice < 0) ? grid->col - 1 : choice;
                } while (grid->grille[grid->col - 1][choice] == '_');
            }
            break;

        default:
            break;
        }
        wattron(columnChoiceWin, COLOR_PAIR(7));
        werase(columnChoiceWin);
        mvwprintw(columnChoiceWin, 0, (3 * choice) + 1, "/\\");
        wattroff(columnChoiceWin, COLOR_PAIR(7));
        wrefresh(columnChoiceWin);
    }
    werase(columnChoiceWin);
    wrefresh(columnChoiceWin);
    keypad(columnChoiceWin, FALSE);
    return choice + 1;
}

void game_GUI(WINDOW *smallWin, WINDOW *smallWinShadow, WINDOW *gameWinBkgd, WINDOW *playerWin, WINDOW *moveChoiceWin, WINDOW *columnChoiceWin, WINDOW *gameBoardWin, gridClass *gameBoard, tokenClass *token, int *player, int *nbPlayers, int *toAlign, char **players)
{
    int column = 0;
    int hasPlayed = 0;
    int hasWon = -1;
    int quit = 0;
    int tie = 0;
    int removedColumn = 0;
    int moveChoice = 0;
    while (hasWon < 0 && quit < 1 && tie < 1)
    {
        token->type = ((*player == 1) ? 'O' : 'X');
        hasPlayed = 0;

        initializePlayerWin(playerWin, players, *player);
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
                    hasPlayed = addToken_GUI(gameBoard, column, token);
                    removedColumn = 0;
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
            switch (aiAddOrRemove(gameBoard))
            {
            case 1:
                do
                {
                    column = aiSelectColumn(gameBoard);
                    hasPlayed = addToken_GUI(gameBoard, column, token);
                } while (hasPlayed != 1);
                break;
            case 2:
                do
                {
                    column = aiSelectColumn(gameBoard);
                    hasPlayed = removeToken_GUI(gameBoard, token, column);
                } while (hasPlayed != 1);
                break;
            default:
                break;
            }
            delay(1500);
        }
        if (quit < 1)
        {
            showGrid_GUI(gameBoard, gameBoardWin);
            hasWon = checkWinner(gameBoard, toAlign, token);
            tie = checkTie(gameBoard);
            if (hasWon > -1)
            {
                if (*nbPlayers > 1 || *player == 1)
                {
                    clear();
                    refresh();
                    werase(smallWin);
                    box(smallWin, 0, 0);
                    centerPrint(smallWin, 0, "  Congratulations  ");

                    wattron(smallWin, COLOR_PAIR(9));
                    wattron(smallWin, A_BOLD);
                    int winner = (*player == 1) ? 0 : 1;
                    centerPrint(smallWin, 3, players[winner]);
                    centerPrint(smallWin, 4, "has won!");
                    wattroff(smallWin, COLOR_PAIR(9));
                    wattroff(smallWin, A_BOLD);

                    smallWinShadow = createShadow(smallWin);
                    wrefresh(smallWinShadow);
                    wrefresh(smallWin);
                }
                else
                {
                    clear();
                    refresh();
                    werase(smallWin);
                    box(smallWin, 0, 0);
                    centerPrint(smallWin, 0, "  Try again  ");

                    wattron(smallWin, COLOR_PAIR(9));
                    wattron(smallWin, A_BOLD);
                    centerPrint(smallWin, 3, "You lose, try again");
                    wattroff(smallWin, COLOR_PAIR(9));
                    wattroff(smallWin, A_BOLD);

                    smallWinShadow = createShadow(smallWin);
                    wrefresh(smallWinShadow);
                    wrefresh(smallWin);
                }
            }
            else if (tie > 0)
            {
                clear();
                refresh();
                werase(smallWin);
                box(smallWin, 0, 0);
                centerPrint(smallWin, 0, "  Tie  ");

                wattron(smallWin, COLOR_PAIR(9));
                wattron(smallWin, A_BOLD);
                centerPrint(smallWin, 3, "The game is tied. Try again.");
                wattroff(smallWin, COLOR_PAIR(9));
                wattroff(smallWin, A_BOLD);

                smallWinShadow = createShadow(smallWin);
                wrefresh(smallWinShadow);
                wrefresh(smallWin);
            }
            *player = (*player == 1) ? 0 : 1;
        }
        else
        {
            clear();
            refresh();
            werase(smallWin);
            box(smallWin, 0, 0);
            centerPrint(smallWin, 0, "  Game saved  ");

            wattron(smallWin, COLOR_PAIR(9));
            wattron(smallWin, A_BOLD);
            centerPrint(smallWin, 3, "The game has been saved. To continue it");
            centerPrint(smallWin, 4, "next time, select 'Continue last saved game'.");
            wattroff(smallWin, COLOR_PAIR(9));
            wattroff(smallWin, A_BOLD);

            smallWinShadow = createShadow(smallWin);
            wrefresh(smallWinShadow);
            wrefresh(smallWin);
        }
    }
}

int addToken_GUI(gridClass *grid, int col, tokenClass *token)
{
    int line = grid->lin;

    if (col > (grid->col) || col < 1)
    {
        return 0;
    }
    else if ((token->type) != 'X' && (token->type) != 'O')
    {
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

int removeToken_GUI(gridClass *grid, tokenClass *token, int col)
{
    int line = 0;

    if (col > grid->col || col < 1)
    {
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