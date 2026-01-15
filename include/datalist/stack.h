#ifndef Z_datalist_h
#define Z_datalist_h

#include <stdbool.h>

#include "list.h"

#define RAW(x) ((unsigned char *)&(x))

ZListResult ZStack_new(ZList *list, size_t elem_count, size_t elem_size);
ZListResult ZStack_resize(ZList *list, size_t new_size);
ZListResult ZStack_push(ZList *list, const void *data);
ZListResult ZStack_peek(const ZList *list, void *buffer);
ZListResult ZStack_pop_into(ZList *list, void *buffer);
ZListResult ZStack_pop(ZList *list);
ZListResult ZStack_free(ZList *list);

#endif
