#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <edit.h>

int main(int argc, char **argv) {
    FILE *file = fopen(argv[1], "r");
    
    int x = 0, y = 0, i = 0, j = 0, lncount = 0, maxy, maxx; //cursor's x, cursor's y, first counter,
    getmaxyx(stdscr, maxy, maxx);                          //second counter, line counter, max x, max y
    
    char arr[600000][maxx]; //storage of file
    char input; //user input
    char message[] = "To save, press s/S";
    char quitMessage[] = "To stop editing, press F1. Press any key to continue.";
    
    while((input = fgetc(file)) != EOF) { //traverse through file and put data in an array
       if(j == maxx || input == '\n') {
           i++;
           j = 0;
       }
       arr[i][j] = input;
       j++;
    }
    
    fclose(file);
    
    initscr(); //start ncurses
    raw();
    keypad(stdscr, TRUE);
    noecho();
    scrollok(stdscr,TRUE);
    mvprintw(maxy/2, (maxx-strlen(quitMessage))/2, "%s", quitMessage);
    getch();
    
    i = 0;
    j = 0;
    while((input = fgetc(arr[i][j])) != EOF) { //display file
        while(x != maxx || x != strlen(arr[i])) {
            mvprint(y, x, input);
            x++;
            j++;
        }
        x = 0;
        y++;
        i++;
        lncount++;
        refresh();
    }
    
    x = 0;
    y = 0;
    move(y, x); //move cursor to beginning of file
    
    while((input = getch()) != KEY_F(1)) { //loop until done editing
        switch(input) {
            case KEY_LEFT: //move left
                left();
                break;
            case KEY_RIGHT: //move right
                right();
                break;
            case KEY_UP: //move up
                up();
                break;
            case KEY_DOWN: //move down
                down();
                break;
            case KEY_BACKSPACE(): //delete character
                backspace();
                break;
            default: //insert character
                insert();
                break;
        }
    }
    
    clear();
    mvprintw(maxy/2, (maxx-strlen(message))/2, "%s", message); //change to write into temp file
    input = getch();
    if(input == 's' || input == 'S') {
        save();
    }
    endwin();
    return 0;
}

void left() { //move left
    if(x - 1 >= 0) { //if not at left screen border
        x--;
        move(y, x);
        refresh();
    }
}

void right() { //move right
    if(x + 1 < maxx && x != strlen(arr[y])) {
        x++;
        move(y, x);
        refresh();
    }
}

void up() { //move up
    if(y - 1 >= 0) {
        if(strlen(arr[y]) > strlen(arr[y - 1])) {
            x = strlen(arr[y - 1]);
        }
        y--;
    }
    move(y, x);
    refresh();
}

void down() { //move down
    if(y + 1 < lncount - 1) {
        if(strlen(arr[y]) > strlen(arr[y + 1])) {
            x = strlen(arr[y - 1]);
        }
        y++;
    }
    move(y, x);
    refresh();
}

void backspace() { //delete character
    memmove(&arr[y][x], &arr[y][x + 1], maxx - x);
}

void insert() { //insert character
    
}
