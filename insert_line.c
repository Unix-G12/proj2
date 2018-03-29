#include "insert_line.h"
#include <ncurses.h>

void insert_line(WINDOW *stdscr, int remove_y, int ymax, int xmax, int *furthest_y) {
	char tempBuff[ymax-remove_y][xmax];
	for (int my = 0; my < (ymax-1) - remove_y; my++) {
		for (int mx = 0; mx < xmax; mx++) {
			tempBuff[my][mx] = mvinch(remove_y + my, mx);
		}
	}

	move(remove_y, 0);
	printw("%s", "\n");

	for (int ry = 1; ry < ymax - remove_y - 1; ry++) {
		for (int rx = 0; rx < xmax; rx++) {
			mvprintw(remove_y + ry, rx, "%c", tempBuff[ry-1][rx]);
			//mvprintw(remove_y + ry, rx, "%s", "fill");
		}
	}

}
/*
		case 97: //scroll up (letter a)
			getyx(stdscr, y ,x);
			if(yup > 0){
				yup--; ydown--;
				move(3, 0);  
				for(int i=yup; i<ydown; i++){
					for(int j=0; j<xmax; j++){    
						printw("%c", arr2[i][j]);
					}
				}
				refresh();
			}
*/