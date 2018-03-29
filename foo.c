#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {

  if(argc != 2) {
    printf("Usage: ./foo <text-file>\n");
    exit(1);
  }

  FILE *file = fopen(argv[1], "r");
  if(file == NULL) {
    perror("Cannot open file\n");
    exit(1);
  }

  char buff[10000];
  int row, col;
  int y, x; 

  initscr();
  getmaxyx(stdscr, row, col);
  row = 0;
  while(fgets(buff, sizeof buff, file) != NULL) {
    getyx(stdscr, y, x);
    if(y == (row - 1)) {
      printw("Press any key");
      getch();
      clear();
      row = 0;
    }
    mvprintw(row, (col-strlen(buff))/2, "%s", buff);
    row = row + 1;
    refresh();
  }

  printw("Press any key to exit");
  getch();
  endwin();
  exit(0);
}
