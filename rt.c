#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

static int lastkey;

void
redraw (void) {
    int i;
    clear();
    mvprintw(0, 0, "COLS = %d, LINES = %d", COLS, LINES);
    mvprintw(1, 0, "Press 'ESC' to exit");
    for (i = 0; i < COLS; i++) {
        mvaddch(2, i, '-');
        mvaddch(LINES - 2, i, '-');
    }
    mvprintw(LINES - 1, 0, "lastkey:%d", lastkey);
    refresh();
}

int main() {
    int key;

    initscr();
    redraw();
    while ((key = getch()) != ERR) {
        switch (key) {
          case KEY_RESIZE:
            redraw();
            break;
          case 27:
            endwin();
            exit(0);
          default:
            lastkey = key;
            redraw();
            break;
        }
    }
    endwin();
    return 0;
}


