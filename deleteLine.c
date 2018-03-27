#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void deleteLine(int y, int x, int maxx, int lncount, char arr[][]) {
	x = 0;
	move(y,x);
	int iter = maxx;
	
	for(; lncount > y; lncount--) {
		while(0 < iter) {	
		memmove(&arr[y][x], &arr[y+1][x], maxx - x);
		iter--;
		}
	}
}	
