#include <stdio.h>
#include <ctype.h>
#include <ncurses.h>
#include <string.h>
#include "flext.h"

#define SIZE 10000

void printFurthest(int my, int mx);

int main(int argc, char** argv){

    int xmax, ymax, y, x;

	initscr();
	cbreak();
	noecho();
    getmaxyx(stdscr, ymax, xmax);
   	int furthest_x = 0, furthest_y = 0;

   	buffer b;
   	b.grid = malloc(ymax * sizeof(char));
   	for (int y_alloc = 0; y_alloc < ymax; y_alloc++) {
   		b.grid[y_alloc] = malloc(xmax * sizeof(char));
   	}
	read_file(argv, stdscr, ymax, xmax, &furthest_y, &b);
    attron(A_BOLD); attron(A_PROTECT);
    move(0, ((xmax / 2 ) - 10));
    printw("Group 12 - Editting %s", argv[1]);
    attroff(A_PROTECT); attroff(A_BOLD);
    move(3,0);

    int t = 0;
    refresh();
	keypad(stdscr, true);
	int c, dInd = 0;
	int cur_x = 0, cur_y = 0, temp_x = 0, temp_y = 0;
	int temp_x1 = 0, temp_x2 = 0;
	int cmdMode = 0, copyMode = 0, searchMode = 0, replaceMode = 0;
	int editMode = 1;
	char copyQuery[xmax-1];
	const int MAX_SEARCH_QUERY_SIZE = 32;
	char searchNReplaceQuery[MAX_SEARCH_QUERY_SIZE];//user search/replace query
	int queryLength = 0;
	char searchQuery[MAX_SEARCH_QUERY_SIZE / 2];
	char replaceQuery[MAX_SEARCH_QUERY_SIZE / 2];
	int s, p;//copy & paste for-loop vars
	int m, n;//saving ncurses window to array vars
	int a, bb;
	char *wb;

	int start_copy_x, start_copy_y, end_copy_x, end_copy_y;
	int c_y, c_x;
	int searchInd = 0;//iterate through searchNReplaceQuery 
	char inputChar;
	scrollok(stdscr, TRUE);
	int matchFound = 0;
	int fillReplace = 0;
	int searchQueryLength = 0;
	int replaceQueryLength = 0;
	int finishedSearching = 0;
	char substring[6];
	int currentMode = 0; // 0 - editting | 1 - command

	while((c = getch()) != 27) {
	switch(c){
		case 4://ctrl+d -> delete line
			getyx(stdscr, cur_y, cur_x);
			delete_line(stdscr, cur_y, xmax);
			break;

		case 11://ctrl+k (kopy time);
			copyQuery[0] = '\0';
			getyx(stdscr, temp_y, temp_x);
			mvprintw(0, 0, "%s", "Kopy time! ctrl+b to select first index.");
			move(temp_y, temp_x);
			int ret = perform_copy(stdscr, copyQuery);
			break;

		case 2:

			break;
/*		case 2://ctrl+b (start copy index)
			if (copyMode) {
			
			}
			break;
		case 13://return
			getyx(stdscr, cur_y, cur_x);
			move(cur_y+1, cur_x);
			break;
		case 14://ctrl+n (find end copy index and store string)
			if (copyMode) {
				getyx(stdscr, end_copy_y, end_copy_x);
				getyx(stdscr, temp_y, temp_x);
				move(temp_y, temp_x);
				for (s = start_copy_x; s < end_copy_x; s++) {
					copyQuery[s] = mvinch(start_copy_y, s);
				}
				mvprintw(0, 0, "%s", "String copied. ctrl+p to paste");
			copyMode = 0;
			}
			break;
*/
		case 15://ctrl+o (insert line)
			getyx(stdscr, cur_y, cur_x);
			insert_line(stdscr, cur_y, ymax, xmax, furthest_y);

		case 16://ctrl+p (paste)
			perform_paste(stdscr, copyQuery);

			getyx(stdscr, cur_y, cur_x);
			for (int p = 0; p < end_copy_x - start_copy_x; p++) {
				mvprintw(cur_y, p + cur_x, "%c", copyQuery[p]);
			}
			break;

		case 20://ctrl+t -> toggle between insert / command mode
			currentMode = toggle_mode(currentMode, stdscr, xmax);
			break;

		case 22://ctrl+v -> search
			searchMode = 1;
			mvprintw(1, 0, "%s", "Enter search & replace term separated by space then hit return: ");
			move(2, 0);
			while (searchInd < MAX_SEARCH_QUERY_SIZE) {//retrieve search and replace queries
				inputChar = getch();
				searchNReplaceQuery[searchInd] = inputChar;
				if (searchNReplaceQuery[searchInd] == '\n'){
					mvprintw(1, 0, "%s", "\n");
					searchMode = 0;
					break;
				}
				getyx(stdscr, cur_y, cur_x);
				mvprintw(cur_y, cur_x++, "%c", inputChar);
				queryLength++;
				searchInd++;
			}

			/*for (int m = 1; m < ymax; m++) {//
				for (int n = 0; n < xmax-1; n++) {
					windowBuffer[m][n] = mvinch(m, n);
				}
			}*/
			
			for (int spl = 0; spl < queryLength; spl++) {//split search and replace query into 2 char arrays
				if (searchNReplaceQuery[spl] == ' ') {
					searchQuery[spl] = '\0';
					searchQueryLength = spl + 2 ;
					fillReplace = 1;
					spl++;
				}
				if (!fillReplace)
					searchQuery[spl] = searchNReplaceQuery[spl];
				else {
					replaceQuery[spl - (searchQueryLength - 1)] = searchNReplaceQuery[spl];
					replaceQueryLength++;
				}
			}
			replaceQuery[queryLength - searchQueryLength + 1] = '\0';

			search_and_replace(searchQuery, replaceQuery, stdscr, searchQueryLength, replaceQueryLength);



			//mvprintw(0, 0, "%c - %c", searchQuery, replaceQuery);

			//findNReplace(searchNReplaceQuery, )
			break;
		case 23://ctrl+w -> save.. the screen to file and quit
			save_file(furthest_y, xmax, stdscr);
			endwin();

			return 0;
			break;

		case KEY_LEFT:
			getyx(stdscr, cur_y, cur_x);
			move(cur_y, cur_x-1);
			break;

		case KEY_RIGHT:
			getyx(stdscr, cur_y, cur_x);
			if (cur_x + 1 < xmax)
				move(cur_y, cur_x+1);
			break;

		case KEY_UP:
			getyx(stdscr, cur_y, cur_x);
			if (!searchMode)
				if (cur_y - 2 > 0)
					move(cur_y-1, cur_x);
			else
				if (cur_y - 1 > 0)
					move(cur_y-1, cur_x);

			break;
		case KEY_DOWN:
			getyx(stdscr, cur_y, cur_x);
			move(cur_y+1, cur_x);
			break;

		/*case 98: //scroll down (letter b) //deprecated scrolling feature
			getyx(stdscr, y ,x);
			if(indy>ydown){
				ydown++; yup++;
				move(3, 0);  
				for(int i = yup; i < ydown; i++){
					for(int j = 0; j < xmax; j++){    
						printw("%c", arr2[i][j]);
					}
				}
				refresh();
			}
			break;

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
			break;
*/
		default://store entered char onto screen
			if (currentMode == 0) {
				getyx(stdscr, temp_y, temp_x);
				mvprintw(0, 0, "%s", "                ");
				move(temp_y, temp_x);
				getyx(stdscr, y, x);
				edit_(stdscr, y, x, c);
				if (y >= furthest_y) {
					furthest_x = x;
					furthest_y = y;
				}
				break;
			}
			else {
				getyx(stdscr, temp_y, temp_x);
				mvprintw(0, 0, "%s", "Not in edit mode.");
				move(temp_y, temp_x);

			}
		}
	}
	
	refresh();
    endwin();
    return 0;
}

void printFurthest(int my, int mx) {
	int temp_y, temp_x;
	getyx(stdscr, temp_y, temp_x);
	mvprintw(0, 0, "(f_y:%d, f_x:%d)", my, mx);
	move(temp_y, temp_x);
}