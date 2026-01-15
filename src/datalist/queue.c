#include "datalist/queue.h"
#include "datalist/list.h"
#include <stdlib.h>
#include <string.h>

ZListResult ZQueue_new(ZList *list, size_t count, size_t size) {
  if(list == NULL)
    return ZLIST_ENOBUFFER;
  *list = (ZList){ 0 };
  list->data = calloc(count, size);
  if(list->data == NULL)
    return ZLIST_ENONMEMORY;
  list->type = ZLIST_TYPE_QUEUE;
  list->count = 0;
  list->head = list->tail = 0;
  list->cap = size * count;
  list->elem_size = size;
  return ZLIST_OK;
}

ZListResult ZQueue_enqueue(ZList *list, const void *elem) {
  if(list == NULL || elem == NULL)
    return ZLIST_ENOBUFFER;
  if(list->count == list->cap)
    return ZLIST_FULL;

  memcpy(&list->data[list->tail], elem, list->elem_size);
  list->count += list->elem_size;
  list->tail = (list->tail + list->elem_size) % list->cap;

  return ZLIST_OK;
}

ZListResult ZQueue_dequeue(ZList *list, void *buffer) {
  if(list == NULL)
    return ZLIST_ENOBUFFER;
  if(list->count == 0)
    return ZLIST_EMPTY;

  if(buffer != NULL)
    memcpy(buffer, &list->data[list->head], list->elem_size);
  memset(&list->data[(list->head - list->elem_size)], 0, list->elem_size);
  list->count -= list->elem_size;
  list->head = (list->head + list->elem_size) % list->cap;

  return ZLIST_OK;
}

ZListResult ZQueue_peek(ZList *list, void *buffer) {
  if(list == NULL || buffer == NULL)
    return ZLIST_ENOBUFFER;
  if(list->count == 0)
    return ZLIST_EMPTY;

  memcpy(buffer, &list->data[list->head % list->cap], list->elem_size);

  return ZLIST_OK;
}

ZListResult ZQueue_free(ZList *list) {
  if(list == NULL)
    return ZLIST_EALREADY_FREED;

  free(list->data);
  list->data = NULL;
  list->elem_size = 0;
  list->cap = list->count = 0;
  list->type = ZLIST_TYPE_UNKNOWN;

  return ZLIST_OK;
}
