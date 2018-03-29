#include "copy_pasta.h"
#include <ncurses.h>
#include <stdio.h>
#include <ctype.h>
#include <ncurses.h>
#include <string.h>

int perform_copy(WINDOW *stdscr, char *copyQuery) {

	char c;
	int s, start_x, start_y, end_x, end_y, temp_x, temp_y;
	int cur_x, cur_y, ymax, xmax;
	getmaxyx(stdscr, ymax, xmax);

	while((c = getch()) != 27) {
		switch(c) {
			case 2://ctrl+b -> start copy index
				getyx(stdscr, temp_y, temp_x);
				getyx(stdscr, start_y, start_x);	
				mvprintw(0, 0, "%s", "Starting index chosen.");
				move(temp_y, temp_x);
				break;

			case 14://ctrl+n -> end copy index
				getyx(stdscr, end_y, end_x);
				getyx(stdscr, temp_y, temp_x);
				move(temp_y, temp_x);
				for (s = start_x; s < end_x; s++) {
					copyQuery[s] = mvinch(start_y, s);
				}
				mvprintw(0, 0, "%s", "String copied. ctrl+p to paste");
				return 1;
				break;

			case 37://left
				mvprintw(0, 0, "%s", "lefting");
				getyx(stdscr, cur_y, cur_x);
				move(cur_y, cur_x-1);
				break;

			case 39://right
				mvprintw(0, 0, "%s", "righting");
				getyx(stdscr, cur_y, cur_x);
				if (cur_x + 1 < xmax)
					move(cur_y, cur_x+1);
				break;

			case 38://up
				getyx(stdscr, cur_y, cur_x);
					if (cur_y - 2 > 0)
						move(cur_y-1, cur_x);
				else
					if (cur_y - 1 > 0)
						move(cur_y-1, cur_x);
				break;
			case 40://down
				getyx(stdscr, cur_y, cur_x);
				move(cur_y+1, cur_x);
				break;

			default:
				break;
		}
		wrefresh(stdscr);
	}
}

void perform_paste() {
	
}