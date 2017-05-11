#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "rt_hist.h"

void
draw_hist (void) {
    int y;
    int x;
    hist_t* hist;

    hist = send.head;
    y = LINES - 3;
    while (y > 2) {
        if (hist) {
            mvprintw(y, COLS - 7, "| 0x%02X ", hist->c);
            hist = hist->next;
        } else {
            mvprintw(y, COLS - 7, "|      ");
        }
        y -= 1;
    }
}

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
    draw_hist();
    refresh();
}


int main() {
    int key;

    hist_init();
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
            hist_push(&send, key);
            hist_gc(&send, HIST_SIZE);
            redraw();
            break;
        }
    }
    endwin();

    return 0;
}


