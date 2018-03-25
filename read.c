#include <stdio.h>
#include<ncurses.h>
//using namespace std;

int main(int argc, char** argv){
    	FILE *f;
    	f= fopen("textfile.txt", "r");
    	char arr[50000];
    	int ind = 0;
    	char data[1000];
   	 while(fgets(data, 1000, f)){ 
		int ind2=0;
		do{
		    arr[ind] = data[ind2];
		    ind ++; ind2++;
		//printf(str);
		}while(data[ind2-1]!='\n');
    	}
    	fclose(f);
    //printf(arr);

	initscr();
	cbreak();
    	int xmax, ymax, y, x;
    	getmaxyx(stdscr, ymax, xmax);
   	getyx(stdscr, y ,x);
	int yup=0, ydown=ymax-3;
    	char arr2[1000][xmax];
    	int indy=0, ind2=0;
    	char tchar=arr[ind2];
    	while(arr[ind2]){
     		int nl=0;
        	for(int i=0; i<xmax; i++){
	    		if(arr[ind2]=='\n'){nl=1;ind2++;}
            		if(nl==0){
                		arr2[indy][i] = arr[ind2];
				ind2++;
	    		}else{
                		arr2[indy][i] = ' ';
	    		}
	    
		}
		indy++;
    	}

    	attron(A_BOLD);
 	attron(A_PROTECT);
    	move(0, xmax/2);
    	printw("Group 12 - %s", argv[0]);
    	attroff(A_PROTECT);
    	attroff(A_BOLD);
    	move(3,0);
	int dy=indy;
	if(indy>ydown){dy=ydown;} 
	for(int i=yup; i<ydown; i++){
		for(int j=0; j<xmax; j++){    
			printw("%c", arr2[i][j]);
//printw("%d", ydown);
		}
	}
    	int t=0;
/*    while(arr[t]!=NULL){
	addch(arr[t]);
	t++;
    }
*/
    	refresh();
	keypad(stdscr, true);
   	//f = fopen("outfile.txt", "w");
    	//fprintf(f,"%s", arr);
	//fclose(f);
    	int c, dInd=0;
    	char dat[10000];
    	while((c=getch())!=27){
		switch(c){
			case KEY_DOWN:
				//clear();
				
				getyx(stdscr, y ,x);
				if(indy>ydown){
					ydown++; yup++;
					move(3,0);  
					for(int i=yup; i<ydown; i++){
						for(int j=0; j<xmax; j++){    
							printw("%c", arr2[i][j]);
						}
					}
					refresh();
				}
				break;
			case KEY_UP:
				getyx(stdscr, y ,x);
				if(yup>0){
					yup--; ydown--;
					move(3,0);  
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
    //for(int i=0; i<indy; i++){printf("%s", arr2[i]);}  				
    //printf("%s", data);
    	return 0;
}
