#ifndef INSERT_H
#define INSERT_H
#include <ncurses.h>
#include "buffer.h"

void insert_line(WINDOW *stdscr, int remove_y, int ymax, int xmax, int *furthest_y);

#endif