#include "save.h"
#include <ncurses.h>

void save_file(int furthest_y, int xmax, WINDOW *stdscr) {
	char windowBuffer[furthest_y+1][xmax];
	int a, b;
	for (a = 0; a <= furthest_y; a++) {
		for (b = 0; b < xmax; b++) {
			windowBuffer[a][b] = ' ';//initialize with blank spaces
		}
	}


	for (int m = 0; m < furthest_y; m++) {
		for (int n = 0; n < xmax; n++) {
			windowBuffer[m][n] = mvinch(m+1, n);
		}
	}
	windowBuffer[furthest_y+1][xmax] = '\0';//null terminate

	FILE *save_fp = fopen("o.txt", "w+");
	if(fwrite(windowBuffer, sizeof(char), sizeof(windowBuffer), save_fp))
	{
		//getyx(stdscr, temp_y, temp_x);
		//mvprintw(0, 0, "%s", "File saved!");
		//move(temp_y, temp_x);
	}
	fclose(save_fp);
}