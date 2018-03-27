#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void deleteLine(int y, int x, int maxx, int lncount, char arr[][]) {
	move(y,0);
	int iter = maxx;
	for(; lncount > y; lncount--) {
		while(0 < iter) {	
		memmove(&arr[y][x], &arr[y][x + 1], maxx - x);
		iter--;
		}
	}	
}	
