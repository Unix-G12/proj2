#ifndef READ_H
#define READ_H
#include <ncurses.h>
#include "buffer.h"

void read_file(char* *argv, WINDOW *stdscr, int ymax, int xmax, int *furthest_y, buffer *buff);

#endif