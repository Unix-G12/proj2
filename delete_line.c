#include <ncurses.h>
#include "delete_line.h"

void delete_line(WINDOW *win, int del_y, int xmax) {
	int c_x, temp_y, temp_x;
	getyx(stdscr, temp_y, temp_x);
	for (c_x = 0; c_x < xmax; c_x++) {
		mvprintw(del_y, c_x, "%c", ' ');
	}
	move(temp_y+1, temp_x);
}