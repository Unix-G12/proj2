#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void deleteLine(int y, int x, int maxx, char arr[][]) {
	move(y,0);
	while(0 < maxx) {	
	memmove(&arr[y][x], &arr[y][x + 1], maxx - x);
	}
}	