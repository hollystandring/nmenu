/*
    A 'plug and play' menu system for ncurses with automatic sizing and centering
    Joe Standring <git@joestandring.com>
    GNU GPLv3
*/

#include "nmenu.h"
#include <ncurses.h>

char *choices[4] = {"Yes", "No", "Maybe", "Sometimes"};

int main()
{
    // Start ncurses
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    int choice1 = menu("Ver 1", "Choices should be uncentered and presented vertically", choices, 4, true, false);
    int choice2 = menu("Ver 2", "Choices should be centered and presented vertically", choices, 4, true, true);
    int choice3 = menu("Hor 1", "Choices should be uncentered and presented horizontally", choices, 4, false, false);
    int choice4 = menu("Hor 2", "Choices should be centered and presented horizontally", choices, 4, false, true);

    // End ncurses
    endwin();

    printf("Choice 1: %d\nChoice 2: %d\nChoice 3: %d\nChoice 4: %d", choice1, choice2, choice3, choice4);

    return 0;
}
