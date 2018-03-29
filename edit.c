#include "edit.h"

int edit_(WINDOW *stdscr, int y, int x, char c) {
	mvprintw(y, x, "%c", c);
}