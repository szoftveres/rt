#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <termios.h>
#include <unistd.h>

#include "rt_hist.h"

#define HIST_SIZE       (512)

hist_head_t     rx_head;
hist_head_t     tx_head;


void
draw_hist (void) {
    int y;
    int x;
    hist_t* rx;
    hist_t* tx;

    rx = rx_head.head;
    tx = tx_head.head;
    y = LINES - 3;
    while (y) {
        x = COLS - 14;
        if (y == 3) {
            mvprintw(y, x, "| -Rx- | -Tx- ");
            break;
        }
        mvprintw(y, x, "| ");
        x += 2;
        if (rx) {
            mvprintw(y, x, "0x%02X", rx->c);
            rx = rx->next;
        } else {
            mvprintw(y, x, "    ");
        }
        x += 4;
        mvprintw(y, x, " | ");
        x += 3;
        if (tx) {
            mvprintw(y, x, "0x%02X", tx->c);
            tx = tx->next;
        } else {
            mvprintw(y, x, "    ");
        }
        x += 4;
        y -= 1;
    }
}

void
redraw (void) {
    int i;
    clear();
    mvprintw(0, 0, "COLS = %d, LINES = %d", COLS, LINES);
    mvprintw(1, 0, "Press 'Ctrl-X' to exit");
    for (i = 0; i < COLS; i++) {
        mvaddch(2, i, '-');
        mvaddch(LINES - 2, i, '-');
    }
    draw_hist();
    refresh();
}


int main() {
    int key;

    hist_init(&rx_head);
    hist_init(&tx_head);
    initscr();
    redraw();
    while ((key = getch()) != ERR) {
        switch (key) {
          case KEY_RESIZE:
            redraw();
            break;
          case 0x18:
            endwin();
            exit(0);
          default:
            hist_push(&tx_head, key);
            hist_gc(&tx_head, HIST_SIZE);
            redraw();
            break;
        }
    }
    endwin();

    return 0;
}


