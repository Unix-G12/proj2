#ifndef COPY_H
#define COPY_H
#include <ncurses.h>

int perform_copy(WINDOW *stdscr, char *copyQuery);
void perform_paste();

#endif