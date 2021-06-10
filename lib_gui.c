#include <ConnectN.h>

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

    while ((curr = wgetch(menuWin)) != KEY_ENTER)
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

    while ((curr = wgetch(smallWin)) != KEY_ENTER)
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

void playerNames(WINDOW *smallWin, WINDOW *smallWinShadow, WINDOW *inputWin, int xMax, int *nbPlayers, char** players)
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

        mvwprintw(smallWin, 3, 3, "Should be between 2 and 15");

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

void showGame(){
    
}