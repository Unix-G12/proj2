#include "read.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>

#define SIZE 10000

void read_file(char* *argv, WINDOW *stdscr, int ymax, int xmax, int *furthest_y, buffer *buff) {

	FILE *f = fopen(argv[1], "r+");
	if (f == NULL) {
	    printf("Can't open file! Usage: ./flext <textfile>\n");
	    endwin();
	    //return 1;
	}

	int ind = 0, ind2 = 0, indy = 0;
	int yup = 0, ydown = ymax - 3;
	char arr2[SIZE][xmax];
	char arr[SIZE];
	char data[SIZE];
	int init_x, init_y;

	for (init_y = 0; init_y < SIZE; init_y++) {
		for (init_x = 0; init_x < xmax; init_x++) {
			//buff->grid[init_y][init_x] = ' ';
		}
	}
	buff->grid[1][1] = 'm';

	for (int init = 0; init < SIZE; init++) {
		arr[init] = ' ';
		data[init] = ' ';
		for (int init2 = 0; init2 < xmax; init2++) {
			arr2[init][init2] = ' ';
			//buff->grid[init][init2] = ' ';
		}
	}

   	while(fgets(data, 1000, f)){ 
		do{
		    arr[ind++] = data[ind2++];
		    furthest_y++;
		} while(data[ind2-1]!='\n');
    }

    for (int p = 0; p < ind2; p++) {
    	mvprintw(1, p, "%c", arr[p]);
    }
	for (int r = 0; r < ind2; r++) {
		//int row_length = strlen(arr[r]) + 1;
		//buff->grid[r] = malloc(xmax);
		//memcpy(buff->grid[r], arr[r], xmax);
	}
	//memcpy(buff->grid, arr2, sizeof())

/*
	while(arr[ind2]){
 		int nl = 0;
    	for(int i = 0; i < xmax; i++){
    		if(arr[ind2]=='\n'){nl=1;ind2++;}
        		if(nl==0){
            		arr2[indy][i] = arr[ind2];
			ind2++;
    		} else {
            	arr2[indy][i] = ' ';
    		}
		}
		indy++;
    }

	int dy = indy;

	if(indy > ydown ){ dy = ydown; }

	for(int i = yup; i < ydown; i++){
		for(int j = 0; j < xmax; j++){    
			printw("%c", arr2[i][j]);
		}
	}
*/
	wrefresh(stdscr);
    fclose(f);
}