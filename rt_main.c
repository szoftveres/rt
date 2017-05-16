#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <termios.h>
#include <unistd.h>
#include <pthread.h>

#include "rt_common.h"
#include "rt_queue.h"
#include "rt_disp_thrd.h"
#include "rt_rx_thrd.h"


pthread_t       disp_thrd_info;
pthread_t       rx_thrd_info;

queue_head_t    event_queue;


int main() {
    int run;

    queue_init(&event_queue);
    pthread_create(&disp_thrd_info, NULL, disp_thrd, NULL);
    pthread_create(&rx_thrd_info, NULL, rx_thrd, NULL);
    sleep(1);
    run = 1;

    while (run) {
        int key;
        rt_event_t *event;
        key = getch();
        if (key == ERR) {
            key = 0x18;
        }
        event = (rt_event_t*) malloc(sizeof(rt_event_t));
        assert(event);
        switch (key) {
          case KEY_RESIZE:
            event->e = EVENT_REDRAW;
            break;
          case 0x18:
            event->e = EVENT_EXIT;
            run = 0;
            break;
          default:
            event->e = EVENT_TX;
            event->c = key;
            break;
        }
        queue_push (&event_queue, (queue_item_t*)event);
    }

    pthread_join(disp_thrd_info, NULL);
    return 0;
}


