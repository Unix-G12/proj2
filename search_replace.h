#ifndef SEARCH_H
#define SEARCH_H
#include <ncurses.h>

int search_and_replace(char *searchQuery, char *replaceQuery, WINDOW *stdscr, int searchQueryLength, int replaceQueryLength);

#endif