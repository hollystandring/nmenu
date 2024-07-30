/*
    A 'plug and play' menu system for ncurses with automatic sizing and centering
    GNU GPLv3
*/

#ifndef _NMENU_H_
#define _NMENU_H_

#include <stdbool.h>

int menu(char title[], char description[], char *choices[], int choicesSize, bool vertical, bool centered);

#endif
