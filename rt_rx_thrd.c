#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#include <pthread.h>

#include "rt_rx_thrd.h"
#include "rt_common.h"
#include "rt_queue.h"


void*
rx_thrd (void* arg) {
    int run;

    run = 1;
    while (run) {
        int c;
        rt_event_t *event;

        event = (rt_event_t*) malloc(sizeof(rt_event_t));
        assert(event);

        sleep(1);
        event->e = EVENT_RX;
        event->c = c;
        queue_push(&event_queue, (queue_item_t*)event);
        if (++c > 255) {c = 0;}

    }

    return NULL;
}

