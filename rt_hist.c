#include "rt_hist.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

hist_head_t     send;
hist_head_t     recv;

void
hist_init (void) {
    memset(&send, 0, sizeof(send));
    memset(&recv, 0, sizeof(recv));
}

/* Push to the front */
void
hist_push (hist_head_t* list, int c) {
    hist_t* hist;

    hist = malloc(sizeof(hist_t));
    assert(hist);
    hist->c = c;
    hist->prev = NULL;
    if (!list->tail) {
        list->tail = hist;
    }
    hist->next = list->head;
    list->head = hist;
    if (hist->next) {
        hist->next->prev = hist;
    }
    list->size += 1;
}

/* Pop from back */
void
hist_remv (hist_head_t* list) {
    hist_t* hist;

    if (!list->tail) {
        return;
    }
    hist = list->tail;
    list->tail = hist->prev;
    if (list->tail) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }
    free(hist);
    list->size -= 1;
}

void
hist_gc (hist_head_t* list, int sz) {
    while (list->size > sz) {
        hist_remv(list);
    }
}



