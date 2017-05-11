#include "rt_hist.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void
hist_init (hist_head_t* list) {
    memset(list, 0, sizeof(hist_head_t));
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



