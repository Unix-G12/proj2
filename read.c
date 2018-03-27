#include <stdio.h>
#include<ncurses.h>
//using namespace std;

int main(int argc, char** argv){

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Can't open file!\n");
    }
	char arr[50000];
	int ind = 0;
	char data[1000];

   	while(fgets(data, 1000, f)){ 
		int ind2=0;
		do{
		    arr[ind] = data[ind2];
		    ind ++; ind2++;
		} while(data[ind2-1]!='\n');
    }

    fclose(f);
	initscr();
	cbreak();

    int xmax, ymax, y, x;
    getmaxyx(stdscr, ymax, xmax);
   	getyx(stdscr, y ,x);
	int yup = 0, ydown = ymax - 3;
	char arr2[1000][xmax];
	int indy = 0, ind2 = 0;
	char tchar = arr[ind2];

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

    attron(A_BOLD); attron(A_PROTECT);
    move(0, ((xmax / 2 ) - 10));
    printw("Group 12 - %s", argv[1]);
    attroff(A_PROTECT); attroff(A_BOLD);
    move(3,0);
	int dy=indy;

	if( indy > ydown ){ dy = ydown; }

	for(int i=yup; i<ydown; i++){
		for(int j=0; j<xmax; j++){    
			printw("%c", arr2[i][j]);
		}
	}

    int t = 0;
    refresh();
	keypad(stdscr, true);
	int c, dInd = 0;
	int cur_x = 0; int cur_y = 0;
	int cmdMode = 0;
	int editMode = 1;

	while((c = getch()) != 27) {
	switch(c){
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
			if (cur_y - 1 > 0)
				move(cur_y-1, cur_x);
			break;

		case KEY_DOWN:
			getyx(stdscr, cur_y, cur_x);
			move(cur_y+1, cur_x);
			break;

		case 98: //scroll down (letter b)
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
		}
	}
	
	refresh();
    endwin();
    return 0;
}
