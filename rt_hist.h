#ifndef __RT_HIST_H__
#define __RT_HIST_H__

typedef struct hist_s {
    int             c;
    struct hist_s   *next;
    struct hist_s   *prev;
} hist_t;

typedef struct hist_head_s {
    hist_t*         head;
    hist_t*         tail;
    int             size;
} hist_head_t;

void
hist_init (hist_head_t* list);
void
hist_push (hist_head_t* list, int c);
void
hist_remv (hist_head_t* list);
void
hist_gc (hist_head_t* list, int sz);

#endif
