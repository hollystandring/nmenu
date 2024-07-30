/*
    A 'plug and play' menu system for ncurses with automatic sizing and centering
    GNU GPLv3
*/

#include "nmenu.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int menu(char title[], char description[], char *choices[], int choicesSize, bool vertical, bool centered) // choicesSize is required as sizeOf does not work for array parameters (as far as I'm aware)
{
    int menuXMax = 0;
    int highlight = 0;
    int menuHeight = 9;
    int menuWidth = 30;
    int choicesLength = 0;
    int selection = 0;
    int yMax, xMax;

    getmaxyx(stdscr, yMax, xMax);

    for(int i = 0; i < choicesSize; i++) // Gets the longest string in the array
    {
        if(strlen(choices[i]) > choicesLength)
        {
            choicesLength = strlen(choices[i]);
        }
    }

    if(vertical)
    {
        menuHeight = choicesSize+8;
        menuWidth = choicesLength+4;
    } else
    {
        menuWidth = choicesLength*choicesSize+choicesSize; // Menu is scaled to fit all strings in array
    }

    if(strlen(description) > menuWidth) // If the description is huge, use that to scale the window
    {
        menuWidth = strlen(description)+4;
    }

    WINDOW *menu = newwin(menuHeight, menuWidth, yMax/2-menuHeight/2, xMax/2-menuWidth/2);
    box(menu, 0, 0);
    refresh();
    wrefresh(menu);
    keypad(menu, true);

    wattron(menu, A_REVERSE);
    mvwprintw(menu, 0, 2, title);
    wattroff(menu, A_REVERSE);

    mvwprintw(menu, 2, menuWidth/2-strlen(description)/2, description);
    mvwprintw(menu, menuHeight-3, menuWidth/2-4, "[C]ancel");

    menuXMax = getmaxx(menu);

    while(true)
    {
        for(int i = 0; i < choicesSize; i++)
        {
            if(i == highlight) // Highlight currently selected choice
            {
                wattron(menu, A_REVERSE);
            }

            if(vertical)
            {
                if(centered) // Can look ugly if not careful with string sizes
                {
                    mvwprintw(menu, i+4, menuXMax/2-strlen(choices[i])/2, choices[i]);
                } else
                {
                    mvwprintw(menu, i+4, 2, choices[i]);
                }
            } else
            {
                if(centered)
                {
                    mvwprintw(menu, 4, (menuXMax/2-choicesLength*choicesSize/2)+choicesLength*i, choices[i]);
                } else
                {
                    mvwprintw(menu, 4, 2+choicesLength*i, choices[i]);
                }
            }

            wattroff(menu, A_REVERSE);
        }

        switch(wgetch(menu)) // Interaction
        {
            case KEY_LEFT:
            case KEY_UP:
                highlight--;

                if(highlight == -1)
                {
                    highlight = 0;
                }

                break;

            case KEY_RIGHT:
            case KEY_DOWN:
                highlight++;

                if(highlight == choicesSize)
                {
                    highlight = choicesSize - 1;
                }

                break;

            case ' ':
            case 10:
                mvwprintw(menu, 0, 0, "This is a test");
                selection = highlight+1;

                goto MenuBreak;

            case 27:
            case 'c':
                goto MenuBreak;

            default:
                break;
        }
    }

    MenuBreak: ;

    wclear(menu);
    refresh();
    wrefresh(menu);

    return selection;
}
