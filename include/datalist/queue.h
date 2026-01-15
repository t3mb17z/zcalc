#ifndef Z_queue_h
#define Z_queue_h

#include "datalist/list.h"
#include <stdint.h>

ZListResult ZQueue_new(ZList *list, size_t count, size_t size);
ZListResult ZQueue_enqueue(ZList *list, const void *elem);
ZListResult ZQueue_dequeue(ZList *list, void *buffer);
ZListResult ZQueue_peek(ZList *list, void *buffer);
ZListResult ZQueue_free(ZList *list);

#endif
