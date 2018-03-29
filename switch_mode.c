#include "switch_mode.h"

int toggle_mode(int currentMode, WINDOW *stdscr, int xmax) {
	if (currentMode == 1) {//switch from cmd mode
		mvprintw(0, 60, "%s", "-- INSERT MODE --\n");
		return 0;

	} else if (currentMode == 0){
		mvprintw(0, 60, "%s", "-- CMD MODE --\n");
		return 1;
	}	
}


