#include "search_replace.h"

int search_and_replace(char *searchQuery, char *replaceQuery, WINDOW *stdscr, int searchQueryLength, int replaceQueryLength) {
		int ymax, xmax;
		int temp_x1 = 0, temp_x2 = 0;

		getmaxyx(stdscr, ymax, xmax);
		/*for (int q = 0; q < replaceQueryLength; q++) {
			mvprintw(20, temp_x1++, "%c", replaceQuery[q]); 
		}

		for (int p = 0; p < searchQueryLength; p++) {
			mvprintw(21, temp_x2++, "%c", searchQuery[p]);
		}*/

		int sub_u = 0;
		char *substring[searchQueryLength];
		int finishedSearching = 0;
		temp_x1 = 0;
		temp_x2 = 0;
		int temp_y = 21;
		while (!finishedSearching){
			for (int t = 2; t < ymax; t++) {//search n replace
				for (int u = 0; u < xmax-searchQueryLength; u++) {
					sub_u = u;
					for (int v = 0; v < searchQueryLength; v++) {//create substring from ncurses screen to compare
						substring[v] = mvinch(t, sub_u++);
					}
					if (strcmp(searchQuery, substring) == 0)
					{
						finishedSearching = 1;
						mvprintw(0, 0, "%s", "DING");
					}
					if (t == ymax-1 && u == xmax-searchQueryLength)
						finishedSearching = 1;
				}
					for (int p = 0; p < searchQueryLength; p++) {
						mvprintw(t+20, temp_x2++, "%c", substring[p]);
					}
			}	

			finishedSearching = 1;			
		}
}