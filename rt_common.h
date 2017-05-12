#ifndef __RT_COMMON_H__
#define __RT_COMMON_H__

#include "rt_queue.h"

typedef enum event_e {
    EVENT_EXIT,
    EVENT_REDRAW,
    EVENT_RX,
    EVENT_TX
} event_t;

typedef struct rt_event_s {
    QUEUE_HEADER
    event_t     e;
    int         c;
} rt_event_t;


extern queue_head_t    event_queue;


#endif
