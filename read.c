#include <stdio.h>
#include <ctype.h>
#include<ncurses.h>

#define SIZE 50000

struct bufferStruct {
	//char **buffer = (char **)malloc(sizeof(char) * SIZE);
	char **line;
	int lineAmt;

} buffer;

void printFurthest(int my, int mx);

int main(int argc, char** argv){

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Can't open file!\n");
    }
	char arr[50000];
	int ind = 0;
	char data[10000];

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
	noecho();
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
    printw("Group 12 - Editting %s", argv[1]);
    attroff(A_PROTECT); attroff(A_BOLD);
    move(3,0);
	int dy = indy;

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
	int cur_x = 0, cur_y = 0, temp_x = 0, temp_y = 0;
	int furthest_x = 0, furthest_y = 0;
	int cmdMode = 0, copyMode = 0, searchMode = 0, replaceMode = 0;
	int editMode = 1;
	char copyQuery[xmax-1];
	char searchQuery[32];
	int s, p;//copy & paste for-loop vars
	int m, n;//saving ncurses window to array vars
	char windowBuffer[ymax][xmax];
	int a, b;
	for (a = 0; a < ymax; a++) {
		for (b = 0; b < xmax; b++) {
			windowBuffer[a][b] = ' ';
		}
	}

	windowBuffer[ymax][xmax] = '\0';
	//saveBuffer[furthest_y][xmax];
	char *wb;
	//wb = &windowBuffer;

	int start_copy_x, start_copy_y, end_copy_x, end_copy_y;
	int c_y, c_x;

	scrollok(stdscr, TRUE);
	while((c = getch()) != 27) {
	switch(c){
		case 4://ctrl+d -> delete line
			getyx(stdscr, cur_y, cur_x);
			getyx(stdscr, temp_y, temp_x);
			for (c_x = 0; c_x < xmax; c_x++) {
				mvprintw(cur_y, c_x, "%c", ' ');
			}
			move(temp_y+1, temp_x);
			break;
		case 5://ctrl+e -> command mode
			editMode = 0;
			cmdMode = 1;
			getyx(stdscr, temp_y, temp_x);
			mvprintw(0, 60, "%s", "-- CMD MODE --\n");
			move(temp_y, temp_x);
			break;
		case 127://backspace
			getyx(stdscr, cur_y, cur_x);
			mvprintw(cur_y, cur_x-1, "%s", "");
			break;
		case 11://ctrl+k (kopy time);
			copyMode = 1;
			copyQuery[0] = '\0';
			getyx(stdscr, temp_y, temp_x);
			mvprintw(0, 0, "%s", "Kopy time! ctrl+b to select first index.");
			move(temp_y, temp_x);
			break;
		case 2://ctrl+b (start copy index)
			if (copyMode) {
				getyx(stdscr, temp_y, temp_x);
				mvprintw(0, 0, "%s", "Starting index chosen.");
				move(temp_y, temp_x);
				getyx(stdscr, start_copy_y, start_copy_x);				
			}
			break;
		case 14://ctrl+n (find end copy index and store string)
			if (copyMode) {
				getyx(stdscr, end_copy_y, end_copy_x);
				getyx(stdscr, temp_y, temp_x);
				mvprintw(0, 0, "%s", "End index chosen & string copied.");
				move(temp_y, temp_x);
				for (s = start_copy_x; s < end_copy_x; s++) {
					copyQuery[s] = mvinch(start_copy_y, s);
				}
			}
			copyMode = 0;
			break;

		case 16://ctrl+p (paste)
			getyx(stdscr, cur_y, cur_x);
			for (int p = 0; p < end_copy_x - start_copy_x; p++) {
				mvprintw(cur_y, p + cur_x, "%c", copyQuery[p]);
			}
			break;

		case 9://ctrl+i
			editMode = 1;
			cmdMode = 0;
			getyx(stdscr, temp_y, temp_x);
			mvprintw(0, 60, "%s", "-- INSERT MODE --\n");
			move(temp_y, temp_x);
			break;

		case 22://ctrl+v -> search
			//mvprintw(1, 0, "%s", "Enter search & replace term separated by space then press ctrl+g: ");


			break;
		case 23://ctrl+w -> save
			for (int m = 1; m < ymax; m++) {//
				for (int n = 0; n < xmax-1; n++) {
					windowBuffer[m][n] = mvinch(m, n);
				}
			}
			//saveFile(wb, furthest_y, xmax);
			
			//windowBuffer[furthest_y][furthest_x] = "\0";
			FILE *save_file = fopen("temp.txt", "w+");
			if(fwrite(windowBuffer, sizeof(char), sizeof(windowBuffer), save_file))
			{
				getyx(stdscr, temp_y, temp_x);
				mvprintw(0, 0, "%s", "File saved!");
				move(temp_y, temp_x);
			}
			fclose(save_file);
			//exit(1);
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
			if (cur_y - 2 > 0)
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

		default://store entered char into character array
			if (editMode) {
				getyx(stdscr, y, x);
				mvprintw(y, x, "%c", c);
				if (y >= furthest_y) {
					furthest_x = x;
					furthest_y = y;
				}
				printFurthest(furthest_y, furthest_x);
				break;
			}
			//getyx(stdscr, temp_y, temp_x);
			//mvprintw(0, 0, "%s", "Not in edit mode. (ctrl+e)");
			//move(temp_y, temp_x);
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

void addchar() {
	//check for bounds when adding char, wrapping when needed
}

void clearInfo() {
	printw(0, 0, "%s", "                      ");
}

void saveFile(char *screenBuff, int furthest_y, int xmax) {
	FILE *s;
	s = fopen("temp.txt", "w+");
	int m, n, temp_y, temp_x;
	for (m = 0; m < furthest_y; m++) {
		for (n = 0; n < xmax; n++) {
			//fprintf(s, "%d", *(*(screenBuff + m) + n));
		}
	}
	getyx(stdscr, temp_y, temp_x);
	mvprintw(0, 0, "%s", "File saved?");
	move(temp_y, temp_x);
	fclose(s);
}
