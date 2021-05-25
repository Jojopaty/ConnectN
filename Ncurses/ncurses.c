#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    start_color();
    initscr();
    cbreak();
    
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW *menu, *background, *shadow;
    init_pair(1, COLOR_WHITE, COLOR_BLUE);

    


    char list[5][7] = {"One", "Two", "Three", "Four", "Five"};
    char item[7];
    int ch, i = 0, width = 7;

    menu = newwin(10, 12, 1, 1); // create a new window
    box(menu, 0, 0);             // sets default borders for the window
    // now print all the menu items and highlight the first one
    attrset(COLOR_PAIR(1));
    for (i = 0; i < 5; i++)
    {
        if (i == 0)
            wattron(menu, COLOR_PAIR(1)); // highlights the first item.
        else
            wattroff(menu, COLOR_PAIR(1));
        sprintf(item, "%-7s", list[i]);
        mvwprintw(menu, i + 1, 2, "%s", item);
    }
    wrefresh(menu); // update the terminal screen
    i = 0;
    noecho();        // disable echoing of characters on the screen
    keypad(menu, TRUE); // enable keyboard input for the window.
    curs_set(0);     // hide the default screen cursor.
    // get the input
    while ((ch = wgetch(menu)) != 'q')
    {
        // right pad with spaces to make the items appear with even width.
        sprintf(item, "%-7s", list[i]);
        mvwprintw(menu, i + 1, 2, "%s", item);
        // use a variable to increment or decrement the value based on the input.
        switch (ch)
        {
        case KEY_UP:
            i--;
            i = (i < 0) ? 4 : i;
            break;
        case KEY_DOWN:
            i++;
            i = (i > 4) ? 0 : i;
            break;
        }
        // now highlight the next item in the list.
        wattron(menu, A_STANDOUT);
        sprintf(item, "%-7s", list[i]);
        mvwprintw(menu, i + 1, 2, "%s", item);
        wattroff(menu, A_STANDOUT);
    }
    delwin(menu);
    endwin();
    return EXIT_SUCCESS;
}